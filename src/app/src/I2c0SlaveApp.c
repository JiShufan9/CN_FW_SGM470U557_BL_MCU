/******************************************************************************
;       Program     : I2c0SlaveApp.c
;       Function    : Declear SERCOM0 I2C Slave Application Function
;       Chip        : Microchip ATSAMC21N17A
;       Clock       : Internal 48MHz
;       Date        : 2021 / 07 / 15
;       Author      : Joel Wang
;       Describe    : Use SERCOM0 for I2C Slave
;                     I2C_SDA_PA08 = SERCOM0/PAD[0] 
;                     I2C_SCL_PA09 = SERCOM0/PAD[1]
;                     [Function Requirements]                     
;                     1. The ECU is disabled program flash in the SM_UPDATE state when battery voltage is under 9V for SGM.
;                     2. The ECU don't into SM_UPDATE state when battery voltage is under 9V for SGM.
;                     3. CRC32 calculate address range are 0x0000 ~ 0xFFDF. (APP=64KB, deduct CustomerID, MCU VER, CRC32)
;                     4. I2C slave frequency set 1MHz.
;             5. I2C protocol packets is LSB (Low Byte) first.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/CrcApp.h"
#include "app/inc/FlashRwApp.h"
#include "app/inc/SysTickApp.h"
#include "app/inc/AdcApp.h"
#include "app/inc/WatchDogApp.h"
#include "hal/inc/FmcDriver.h"
#include "app/NodesInterface/NodeUpdate.h"
/*---------------------------- Declare External Var -------------------------*/
static st_ring_buffer tsI2cSlaveRx;
static st_queue tsI2cSlaveTx;
static st_i2c_slave_config tsI2cSlaveDev;
static uint8_t st_u8GoSleepFlag = VALUE_CLEAN;
static uint8_t st_u8Done = VALUE_CLEAN;
uint8_t gPacketDir = (uint8_t)(I2C_READ); /* true = i2cs read, false = i2cs write */
uint8_t u8ExternalFlag = (uint8_t)(NOTHING);
uint8_t gu8DisplayBLCmd[CMD_DISPLAY_BL_MAX] = {0};
uint8_t gu8ResetCmd[CMD_FORCE_RST_MAX]  = {0};
uint8_t gu8MemUnlockCmd[CMD_MEM_UNLOCK_MAX] = {0};
uint8_t gu8MemEraseCmd[CMD_MEM_ERASE_MAX]   = {0};
uint8_t gu8FlashWriteCmd[CMD_FLASH_WRITE_MAX]   = {0};
uint8_t u8AppMemRawDataBuff[SIZE_APP_MEM_BLOCK] = {0};
uint8_t u8AppCrc32Buff[LEN_APP_CRC32] = {0};
#if AUTO_MATCH_ADDRESS
static uint16_t gu16PageCounter = 0U;
#endif
const uint8_t gu8AllowedDataAddress[CMD_SIZE] = 
{
    CMD_HW_VER_GET,
    CMD_FIDM_VER_GET,
    CMD_TP_ID_GET,
    CMD_DISPLAY_ID_GET,
    CMD_DISPLAY_BL_CONTROL,
   CMD_UPGRADE_FW_PARAMETER,
    CMD_FORCE_RST,
    CMD_FIDM_PROGRAM_UPDATE,
    CMD_BL_STATUS,
    CMD_APP_MEM_UNLOCK,
    CMD_APP_MEM_ERASE,
    CMD_FLASH_PAGE_WRITE,
};
uint8_t gu8BacklightVal[BM_VALUE_SIZE] = 
{
    0x1E,
    0x1E,
};

/*------------------- u8ExternalFlag -----------------------
Bit7 : Reserved
Bit6 : Reserved
Bit5 : Reserved
Bit4 : Reserved
Bit3 : Reserved
Bit2 : 1 = The I2C slave transfer finish.
Bit1 : 1 = The I2C slave TX is ready.
Bit0 : 1 = The I2C slave RX is ready.
------------------------------------------------------------*/

static uint8_t u8BootloaderStatus1Flag = (uint8_t)(DEFAULT_BL_STATUS_1);            /* default is BL mode */
/*------------------- u8BootloaderStatus1Flag ----------------
Bit7 : 0 = Voltage is normal, 1 = Voltage is abnormal.
Bit6 : 0 = CRC16 is correct, 1 = CRC16 is failure.
Bit5 : 0 = Erase key is correct, 1 = Erase key is failure.
Bit4 : 0 = Session key is correct, 1 = Session key is failure.
Bit3 : 0 = Flash writes failure, 1 = Flash writes successful.
Bit2 : 0 = Application memory hasn't erase, 1 = Application memory erased.
Bit1 : 0 = Application memory locked, 1 = Application memory unlocked.
Bit0 : 0 = Application mode active, 1 = Bootloader mode active.
------------------------------------------------------------*/

static uint8_t u8BootloaderStatus2Flag = (uint8_t)(DEFAULT_BL_STATUS_2);        
/*------------------- u8BootloaderStatus2Flag ----------------
Bit7 : Reserved
Bit6 : Reserved
Bit5 : Reserved
Bit4 : Reserved
Bit3 : Reserved
Bit2 : Reserved
Bit1 : 0 = No unknown error, 1 = Unknown error.
Bit0 : 0 = Programming pass, 1 = Programming error.
------------------------------------------------------------*/
static bool I2c0SlaveApp_Rx_Crc16_Check(uint16_t u16PacketLen);
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Irq_Control(uint8_t u8IrqSwitch)
;       Function Description    :   IRQ signal control.
;       Parameters              :   [u8IrqSwitch] - Signal level control
;                                   (1) SET_IRQ_ASSERT : The pin sets level low.
;                                   (2) SET_IRQ_RELEASE : The pin sets level high.  
;       Return Values           :   true
;       Source ID               :   GM_BL_I2C_SLA-001
******************************************************************************/
static bool I2c0SlaveApp_Irq_Control(uint8_t u8IrqSwitch)
{
    if((u8IrqSwitch == (uint8_t)(SET_IRQ_ASSERT)))
    {
        (void)PinIOApp_High(portMCU_INT, pinMCU_INT);   /* Assert IRQ Signal */
    }
    else if(u8IrqSwitch == (uint8_t)(SET_IRQ_RELEASE))
    {
        (void)PinIOApp_Low(portMCU_INT, pinMCU_INT);    /* Rlease IRQ Signal */
    }
    else
    {
        /* NOTHING */
    }

    (void)(u8IrqSwitch);
    return true;
}
/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_BL_Status1_Set(uint8_t u8Status)
;       Function Description    :   Set bootloader status 1 flags information and trigger IRQ signal.
;       Parameters              :   [u8Status] - Set bootloader flags. 
;       Return Values           :   Return bootloader status 1 information.
;       Source ID               :   GM_BL_I2C_SLA-002
******************************************************************************/
uint8_t I2c0SlaveApp_BL_Status1_Set(uint8_t u8Status)
{
    u8BootloaderStatus1Flag |= u8Status;
    (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
    return u8BootloaderStatus1Flag;
}

/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_BL_Status1_Clear(uint8_t u8Status)
;       Function Description    :   Clear bootloader status 1 flags information and trigger IRQ signal.
;       Parameters              :   [u8Status] - Set bootloader flags. 
;       Return Values           :   Return bootloader status 1 information.
;       Source ID               :   GM_BL_I2C_SLA-004
******************************************************************************/
uint8_t I2c0SlaveApp_BL_Status1_Clear(uint8_t u8Status)
{
    u8BootloaderStatus1Flag &= ~u8Status;
    (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
    return u8BootloaderStatus1Flag;
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_BL_Status2_Clear(uint8_t u8Status)
;       Function Description    :   Clear bootloader status 2 flags information and trigger IRQ signal.
;       Parameters              :   [u8Status] - Set bootloader flags. 
;       Return Values           :   Return bootloader status 2 information.
;       Source ID               :   GM_BL_I2C_SLA-005
******************************************************************************/
uint8_t I2c0SlaveApp_BL_Status2_Clear(uint8_t u8Status)
{
    u8BootloaderStatus2Flag &= ~u8Status;
    (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
    return u8BootloaderStatus2Flag;
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_SM_Status_Clear(uint8_t u8Para) 
;       Function Description    :   Clear all flags status to default.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-007
******************************************************************************/
static uint8_t I2c0SlaveApp_SM_Status_Clear(uint8_t u8Para)   
{
    (void)I2c0SlaveApp_BL_Status1_Clear(SET_FLASH_WRITE_SUCCESS| SET_APP_UNLOCK | SET_APP_ERASE | SET_ERASE_KEY_ERR | SET_CRC16_ERR);       /* Set APP memory is locked, and other flag to default */
    (void)I2c0SlaveApp_BL_Status2_Clear(SET_PROGRAMMING_ERROR | SET_UNKNOWN_ERROR);/* Set to default value */
    (void)InitApp_StateMachine_Set(BL_TASK);
    SysTickApp_Irq_Enable(SysTick_IRQn);

    #if DEBUG_UART
        Uart1App_String_Show("Resume to SM_TASK\r");
    #endif

    (void)(u8Para);
    return u8Para;
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_Slave_Tx_Send(uint8_t u8Para)
;       Function Description    :   Send packets to the host.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-008
******************************************************************************/
static uint8_t I2c0SlaveApp_Slave_Tx_Send(uint8_t u8Para)
{
    (void)slave_i2c_data_ready_wait(&tsI2cSlaveDev);                                        /* Check last data are transmitted finish */
    (void)slave_i2c_transmitte(&tsI2cSlaveDev, &tsI2cSlaveTx.buf[tsI2cSlaveTx.cnt]);        /* Send data to the host */
    tsI2cSlaveTx.cnt++;     
    (void)(u8Para);
    return u8Para;
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_Global_Cmd_Check(uint8_t u8Para)
;       Function Description    :   Determine global commands condition.
;       Parameters              :   [u8Para] - NOTHING 
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-010
******************************************************************************/
static void I2c0SlaveApp_Global_Cmd_Check(uint8_t u8Cmd)
{
    switch(u8Cmd)
    {
        case CMD_FORCE_RST:
            if((gu8ResetCmd[FR_DATA] & (uint8_t)RST_FIDM) == (uint8_t)RST_FIDM)
            {
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_RELEASE);
                u8BootloaderStatus1Flag = (uint8_t)(DEFAULT_CLEAR_VALUES);      /* Set to default value */
                u8BootloaderStatus2Flag = (uint8_t)(DEFAULT_CLEAR_VALUES);      /* Set to default value */
                (void)FunApp_Irq_Disable();
                (void)PinIOApp_System_Power(SYS_PWR_OFF);

                #if MICROCHIP_ARM_ENV
                    ASM_SYS_RESET();
                #endif
            }
            else if((gu8ResetCmd[FR_DATA] & (uint8_t)RST_TOUCH) == (uint8_t)RST_TOUCH)
            {
                (void)PinIOApp_Low(portXRES_TP_R, pinXRES_TP_R);
            }
            else
            {
                /*Nothing*/
                #if DEBUG_UART
                    Uart1App_String_Show("CMD_FORCE_RST FAIL\r");
                #endif
            }
        break;
    
        default:         
            /*Nothing*/
        break;
    }
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_TASK_Cmd_Check(uint8_t u8Para)
;       Function Description    :   Parse the host commands in the TASK state.
;       Parameters              :   [u8Para] - NOTHING 
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-011
******************************************************************************/
static void I2c0SlaveApp_TASK_Cmd_Check(uint8_t u8Cmd)
{
#if (CMD_STYLE == GM_STYLE)
    uint16_t u16Key0, u16Key1;
#elif (CMD_STYLE == BOSCH_STYLE)
    uint16_t u16Key0;
#endif
    uint8_t u8Crc, u8CounterUp, u8CounterDown;
    uint16_t u16BacklightVal;
    uint16_t u16Crc8Len = BL_CMD_CRC_SIZE;

    switch(u8Cmd)
    {
        case CMD_DISPLAY_BL_CONTROL:
            /* Panel Backlight Control */
            u8CounterUp = gu8DisplayBLCmd[BL_CMD_INDEX_CT] & DIAGNOSIS_COUNTER;
            u8CounterDown = gu8DisplayBLCmd[BL_CMD_INDEX_CT] & CMD_COUNTER_FILTER;
            if(MainApp_getDisplayID() == gu8DisplayBLCmd[BL_CMD_INDEX_DID])
            {
                if((u8CounterUp == DIAGNOSIS_COUNTER) && (u8CounterDown < CMD_COUNTER_FILTER))
                {
                    u8Crc = CrcApp_Crc8_Calculation((&gu8DisplayBLCmd[2]),u16Crc8Len);
                    if(u8Crc == gu8DisplayBLCmd[BL_CMD_INDEX_CRC])
                    {
                        gu8BacklightVal[0U] = gu8DisplayBLCmd[BL_CMD_INDEX_DATAH];
                        gu8BacklightVal[1U] = gu8DisplayBLCmd[BL_CMD_INDEX_DATAL];
                        u16BacklightVal = ((uint16_t)(gu8BacklightVal[0U]) << 8U) | (uint16_t)(gu8BacklightVal[1U]);
                        if(u16BacklightVal >= BACKLIGHT_FILTER_MAX)
                        {
                            gu8BacklightVal[0U] = 0xFFU;
                            gu8BacklightVal[1U] = 0xFFU;
                        }
                        else
                        {
                            /* NOTHING */
                        }
                    }
                    else
                    {
                        /* 100nis */
                    //    gu8BacklightVal[0U] = (uint8_t)(BACKLIGHT_100NITS >> 8U);
                    //    gu8BacklightVal[1U] = (uint8_t)(BACKLIGHT_100NITS & 0x00FFU);
                        /*Nothing*/
                    }
                }
                else
                {
                    /* NOTHING */
                }
            }
            else
            {
                /* NOTHING */
            }
        break;

        case CMD_APP_MEM_UNLOCK:

#if (CMD_STYLE == GM_STYLE)
            u16Key0 = ((uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY0_L]);
            u16Key1 = ((uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY1_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY1_L]);         
            if((u16Key0 == (uint16_t)(CHK_ACCESS_KEY_0)) && (u16Key1 == (uint16_t)(CHK_ACCESS_KEY_1)))
#elif (CMD_STYLE == BOSCH_STYLE)
            u16Key0 = ((uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemUnlockCmd[P_BOOT_KEY0_L]);    
            if(
                   (u16Key0 == (uint16_t)(CHK_SESSION_KEY)) ||
                   (u16Key0 == (uint16_t)(CHK_SESSION_KEY_2))
            )
#endif                
            {
                (void)InitApp_StateMachine_Set(BL_UPDATE);
                u8BootloaderStatus1Flag |= SET_APP_UNLOCK;      /* Set APP memory unlock */
                u8BootloaderStatus1Flag &= ~SET_SESSION_KEY_ERR;
                #if DEBUG_UART
                    //Uart1App_String_Show("Into BL_UPDATE\r");
                    Uart1App_String_Show("App mem UNLOCK\r");
                #endif
                SysTickApp_Irq_Disable(SysTick_IRQn);
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
            }
            else
            {
                u8BootloaderStatus1Flag &= ~SET_APP_UNLOCK;     /* Set APP memory lock */
                u8BootloaderStatus1Flag |= SET_SESSION_KEY_ERR;
                #if DEBUG_UART
                    //Uart1App_String_Show("Boot keys ERROR\r");
                    //Uart1App_String_Show("App mem NOT unlcok\r");
                #endif
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
            }   
        break;

        default:
            /*Nothing*/
        break;
    }

}

#if MCU_UPDATE_ONLY
/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Flash_Page_Write_Check(uint8_t u8Status)
;       Function Description    :   Check the flash write status in the UPDATE state.
;       Parameters              :   [u8Status] - Flash write status.
;       Return Values           :   true
;       Source ID               :   GM_BL_I2C_SLA-012
******************************************************************************/
static bool I2c0SlaveApp_Flash_Page_Write_Check(uint8_t u8Status)
{
    if(u8Status != (uint8_t)(STATUS_FINISH))
    {
        /* Flash write is failure */
        u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;    /* Flash is written error */
        u8BootloaderStatus2Flag |= SET_PROGRAMMING_ERROR;       /* Programming error */
        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
        #if DEBUG_UART
            //Uart1App_String_Show("Flash write ERROR\r");
        #endif
    }
    else
    {
        /* Flash write is success */
        u8BootloaderStatus1Flag |= SET_FLASH_WRITE_SUCCESS;     /* Flash write successful */
        u8BootloaderStatus2Flag &= ~SET_PROGRAMMING_ERROR;      /* Programming pass */
        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
    }

    (void)(u8Status);
    return true;
}
#endif

/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_Slave_Rx_Compare(uint32_t u32StartAddr, uint32_t u32CompareSize, uint8_t *u8SrcBuff)
;       Function Description    :   Check data is the same after the MCU is writed.
;       Parameters              :   [u32StartAddr] - Set start address.
;                                   [u32CompareSize] - Input compare size.
;                                   [u8SrcBuff] - Input compare's data.
;       Return Values           :   Return status.
;                                   (1) STATUS_FAIL
;                                   (2) STATUS_FINISH
;       Source ID               :   GM_BL_I2C_SLA-013
******************************************************************************/
uint8_t I2c0SlaveApp_Slave_Rx_Compare(uint32_t u32StartAddr, uint32_t u32CompareSize, uint8_t *pu8SrcBuff)
{
    uint8_t u8Status;
    uint8_t u8FlashCompareBuff[SIZE_A_PAGE] = {0};
    
    u8Status = FlashRwApp_Read(u32StartAddr, u32CompareSize, &u8FlashCompareBuff[0]);
    (void)(u8Status);
    if(u8Status == (uint8_t)(NVC_FINISH))
    {
        if(0 == memcmp(pu8SrcBuff, u8FlashCompareBuff, SIZE_A_PAGE))
        {
            u8Status = (uint8_t)(STATUS_FINISH);    /* Packets are match */
        } else {
            u8Status = (uint8_t)(STATUS_FAIL);  /* Data are not match */
        }
        (void)(u8Status);
    }
    else
    {
        /* NOTHING */
    }

    (void)(u32StartAddr);
    (void)(u32CompareSize);
    (void)(*pu8SrcBuff);
    return u8Status;
}

/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Flash_Cmd_Check(uint8_t u8Cmd, uint16_t u16Key0, uint16_t u16Key1)
;       Function Description    :   Check flash commands in the UPDATE state.
;       Parameters              :   [ucCmd] - Received the host command.
;                                   [u8FlashKey0] - Received the host flash key 0.
;                                   [u8FlashKey1] - Received the host flash key 1.
;       Return Values           :   true
;       Source ID               :   GM_BL_I2C_SLA-014
******************************************************************************/
static bool I2c0SlaveApp_Flash_Cmd_Check(uint8_t u8Cmd, uint16_t u16Key0, uint16_t u16Key1)
{
#if MCU_UPDATE_ONLY
    uint32_t u32Index;
#endif
    uint32_t u32FlashWriteAddr;
    
    switch(u8Cmd)
    {
        case CMD_FLASH_PAGE_WRITE:
        #if (CMD_STYLE == GM_STYLE)
            if((u16Key0 == (uint16_t)(CHK_ACCESS_KEY_0)) && (u16Key1 == (uint16_t)(CHK_ACCESS_KEY_1)))
        #elif (CMD_STYLE == BOSCH_STYLE)
            if(
                    (u16Key0 == (uint16_t)(CHK_SESSION_KEY)) ||
                    (u16Key0 == (uint16_t)(CHK_SESSION_KEY_2))
              )
        #endif
            {
                u8BootloaderStatus1Flag &= ~SET_SESSION_KEY_ERR;
                #if FLASH_WRITE
#if MCU_UPDATE_ONLY
                #if AUTO_MATCH_ADDRESS
                    u32FlashWriteAddr = (uint32_t)((uint32_t)ADDR_APP_START+(uint32_t)((uint32_t)gu16PageCounter*(uint32_t)SIZE_64B));
                    if(u32FlashWriteAddr < (uint32_t)(ADDR_APP_START + SIZE_APP_BASE))
                #else
                    u32FlashWriteAddr = ((uint32_t)(gu8FlashWriteCmd[PU_ADDR_2]) << (uint32_t)(SHIFT_BIT_16)) | ((uint32_t)(gu8FlashWriteCmd[PU_ADDR_1]) << (uint32_t)(SHIFT_BIT_8)) | (uint32_t)(gu8FlashWriteCmd[PU_ADDR_0]);
                    if((u32FlashWriteAddr >= (uint32_t)(ADDR_APP_START)) && (u32FlashWriteAddr < (uint32_t)(ADDR_APP_START + SIZE_APP_BASE)))
                #endif
#else
                #if AUTO_MATCH_ADDRESS
                    u32FlashWriteAddr = (uint32_t)((uint32_t)ADDR_START+(uint32_t)((uint32_t)gu16PageCounter*(uint32_t)SIZE_2048B));
                    if(u32FlashWriteAddr < (uint32_t)(ADDR_START + SIZE_TOTAL_BASE))
                #else
                    u32FlashWriteAddr = ((uint32_t)(gu8FlashWriteCmd[PU_ADDR_2]) << (uint32_t)(SHIFT_BIT_16)) | ((uint32_t)(gu8FlashWriteCmd[PU_ADDR_1]) << (uint32_t)(SHIFT_BIT_8)) | (uint32_t)(gu8FlashWriteCmd[PU_ADDR_0]);
                    if((u32FlashWriteAddr >= (uint32_t)(ADDR_START)) && (u32FlashWriteAddr < (uint32_t)(ADDR_START + SIZE_TOTAL_BASE)))
                #endif
#endif
                    {
                        #if DEBUG_UART
                            if(u32FlashWriteAddr == (uint32_t)(ADDR_APP_START))
                            {
                                Uart1App_String_Show("MCU is WRITING...\r");
                            }                           
                        #endif
#if MCU_UPDATE_ONLY
                        (void)I2c0SlaveApp_Flash_Page_Write_Check(FlashRwApp_64B_Page_Write(u32FlashWriteAddr, &gu8FlashWriteCmd[PU_DATA]));        
#else
                        if(NodeUpdate_UpdateFunc(u32FlashWriteAddr,SIZE_2048B,&gu8FlashWriteCmd[PU_DATA]) == UPDATE_STS_SUCCESS)
                        {
                            /* Flash write is success */
                            u8BootloaderStatus1Flag |= SET_FLASH_WRITE_SUCCESS;     /* Flash write successful */
                            u8BootloaderStatus2Flag &= ~SET_PROGRAMMING_ERROR;      /* Programming pass */
                            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                            #if DEBUG_UART
                                //Uart1App_String_Show("Flash write SUCCESS\r");
                            #endif
                            #if AUTO_MATCH_ADDRESS
                                gu16PageCounter += 1U;
                            #endif
                        }
                        else
                        {
                            /* Flash write is failure */
                            u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;    /* Flash is written error */
                            u8BootloaderStatus2Flag |= SET_PROGRAMMING_ERROR;       /* Programming error */
                            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                            #if DEBUG_UART
                                //Uart1App_String_Show("Flash write ERROR\r");
                            #endif
                        }

#endif
                    }
                    else
                    {
                        u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;            /* Flash is written error */
                        u8BootloaderStatus2Flag |= (uint8_t)(SET_PROGRAMMING_ERROR);            /* APP memory set address is range over */
                        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                        #if DEBUG_UART
                            Uart1App_String_Show("Programming addr is range OVER\r");
                        #endif                      
                    }
                #endif
            }
            else
            {
                u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;            /* Flash is written error */
                u8BootloaderStatus1Flag |= SET_SESSION_KEY_ERR;                
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);         
                #if DEBUG_UART
                    Uart1App_String_Show("CMD_FLASH_PAGE_WRITE ERROR\r");
                #endif
            }           
        break;
        case CMD_APP_MEM_ERASE:
            if((u8BootloaderStatus1Flag & SET_APP_UNLOCK) != (uint8_t)(SET_APP_UNLOCK))
            {
                // Recieve erase cmd before unlock
                u8BootloaderStatus2Flag|=SET_UNKNOWN_ERROR;
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
            } 
            else 
            {
                /* Calculate CRC16 from cmd byte */
                if(I2c0SlaveApp_Rx_Crc16_Check(CMD_MEM_ERASE_MAX)==TRUE)
                {
                    if((gu8MemEraseCmd[W_ERASE_KEY] != ERASE_KEY)){
                        u8BootloaderStatus1Flag &= (uint8_t)(~SET_APP_ERASE);           /* APP memory has not erase */
                        u8BootloaderStatus1Flag |= (uint8_t)(SET_ERASE_KEY_ERR);
                        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                        #if DEBUG_UART
                        Uart1App_String_Show("CMD_APP_MEM_ERASE ERROR\r");
                        #endif
                    }
                #if (CMD_STYLE == GM_STYLE)
                    else if(
                        (u16Key0 == (uint16_t)(CHK_ACCESS_KEY_0)) && 
                        (u16Key1 == (uint16_t)(CHK_ACCESS_KEY_1))
                    )
                #elif (CMD_STYLE == BOSCH_STYLE)
                    else if(
                        (u16Key0 == (uint16_t)(CHK_SESSION_KEY)) || 
                        (u16Key0 == (uint16_t)(CHK_SESSION_KEY_2))
                    ) 
                #endif
                    {
#if MCU_UPDATE_ONLY
                        for(u32Index=0U; u32Index<LEN_ERASE; u32Index++)
                        {
                            #if FLASH_ERASE
                                (void)FlashRwApp_256B_Erase((uint32_t)(ADDR_APP_START), u32Index);  /* Erase APP code size */
                            #endif
                        }
                        
                        (void)FunApp_Delay_Millisecond(50U, MODE_SYSTICK);                 /* Delaly 500ms, waiting for the MCU erase finish */
#else
                        if(NodeUpdate_EarseFunc() == UPDATE_STS_SUCCESS)
                        {
                            u8BootloaderStatus1Flag |= (uint8_t)(SET_APP_ERASE);            /* APP memory is erased finish */
                            u8BootloaderStatus1Flag &= (uint8_t)(~SET_CRC16_ERR);
                            u8BootloaderStatus1Flag &= ~SET_SESSION_KEY_ERR;
                            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                            #if DEBUG_UART
                                Uart1App_String_Show("Flash ERASED\r");
                            #endif
                        }
                        else
                        {
                            u8BootloaderStatus1Flag &= (uint8_t)(~SET_APP_ERASE);           /* APP memory has not erase */
                            u8BootloaderStatus1Flag |= SET_SESSION_KEY_ERR;
                            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                            #if DEBUG_UART
                            Uart1App_String_Show("CMD_APP_MEM_ERASE ERROR\r");
                            #endif
                        }
#endif

                        
                    } else {
                        u8BootloaderStatus1Flag &= (uint8_t)(~SET_APP_ERASE);           /* APP memory has not erase */
                        u8BootloaderStatus1Flag |= SET_SESSION_KEY_ERR;
                        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                        #if DEBUG_UART
                        Uart1App_String_Show("CMD_APP_MEM_ERASE ERROR\r");
                        #endif
                    }
                }
                else
                {
                    u8BootloaderStatus1Flag &= (uint8_t)(~SET_APP_ERASE);           /* APP memory has not erase */
                    u8BootloaderStatus1Flag |= (uint8_t)(SET_CRC16_ERR);
                    (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                    #if DEBUG_UART
                        Uart1App_String_Show("CMD_APP_MEM_ERASE ERROR\r");
                    #endif
                }   
            }       
        break;
        default:
            /*Nothing*/
        break;
    }

    (void)(u8Cmd);
    (void)(u16Key0);
    (void)(u16Key1);
    return true;
}

/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_Update_Cmd_Check(uint8_t u8Para)
;       Function Description    :   Check the host command's classification in the UPDATE state.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-015
******************************************************************************/
static void I2c0SlaveApp_Update_Cmd_Check(uint8_t u8Cmd)
{
    uint16_t u16Key0Temp = 0U, u16Key1Temp = 0U;
#if (CMD_STYLE == BOSCH_STYLE)
    if((u8Cmd == (uint8_t)(CMD_FLASH_PAGE_WRITE)))
    {
        u16Key0Temp = ((uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY0_L]);        
        (void)I2c0SlaveApp_Flash_Cmd_Check(u8Cmd, u16Key0Temp, u16Key1Temp);
    } else if(u8Cmd == (uint8_t)(CMD_APP_MEM_ERASE))
    {     
        u16Key0Temp = ((uint16_t)(gu8MemEraseCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemEraseCmd[P_BOOT_KEY0_L]);
        (void)I2c0SlaveApp_Flash_Cmd_Check(u8Cmd, u16Key0Temp, u16Key1Temp);
    } 
#elif (CMD_STYLE == GM_STYLE)
    if((u8Cmd == (uint8_t)(CMD_FLASH_PAGE_WRITE)))
    {     
        u16Key0Temp = ((uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY0_L]);
        u16Key1Temp = ((uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY1_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8FlashWriteCmd[P_BOOT_KEY1_L]);   
        (void)I2c0SlaveApp_Flash_Cmd_Check(u8Cmd, u16Key0Temp, u16Key1Temp);
    } else if(u8Cmd == (uint8_t)(CMD_APP_MEM_ERASE))
    {     
        u16Key0Temp = ((uint16_t)(gu8MemEraseCmd[P_BOOT_KEY0_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemEraseCmd[P_BOOT_KEY0_L]);
        u16Key1Temp = ((uint16_t)(gu8MemEraseCmd[P_BOOT_KEY1_H]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemEraseCmd[P_BOOT_KEY1_L]);   
        (void)I2c0SlaveApp_Flash_Cmd_Check(u8Cmd, u16Key0Temp, u16Key1Temp);
    }
#endif
    else
    {
        /*Nothing*/
    }   

    (void)(u16Key0Temp);
    (void)(u16Key1Temp);
}

/******************************************************************************
;       Function Name           :   bool I2c0SlaveApp_Crc32_Check(uint32_t u32Size)         
;       Function Description    :   Compute and check MCU flash CRC32 values.
;       Parameters              :   [u32Size] - Input App memory size.
;       Return Values           :   Return CRC32 check status.
;                                   (1) true - CRC32 check is correct.
;                                   (2) false - CRC32 check is failure.
;       Source ID               :   GM_BL_I2C_SLA-016
******************************************************************************/
#if CRC32_CHECK
bool I2c0SlaveApp_Crc32_Check(uint32_t u32Size)                         
{
    bool bCheck = false;
    volatile uint32_t u32Index,u32CRC=0;
    volatile uint32_t u32ComputeCrc32 = (uint32_t)(INIT_CRC32);
    
    (void)(bCheck);

    for(u32Index=0U; u32Index<u32Size; u32Index++)                      /* Calculate APP memory size CRC32,  APP_SIZE/A_PAGE = timers */
    {       
            #if FLASH_READ
                (void)FlashRwApp_Read((uint32_t)(ADDR_APP_START) + (u32Index*(uint32_t)(LEN_READ_MEM)), (uint32_t)(LEN_READ_MEM), &u8AppMemRawDataBuff[0]);
            #endif      
        if(u32Index == (u32Size-LEN_LAST))  
        {
            /* Reserved for CustomerId, MCU Version and MCU CRC32 */
            u32ComputeCrc32 = CrcApp_Crc32_Calculation(&u8AppMemRawDataBuff[0], (uint32_t)(LEN_READ_MEM - LEN_RESERVED), u32ComputeCrc32);  
            (void)(u32ComputeCrc32);
        }
        else
        {
            u32ComputeCrc32 = CrcApp_Crc32_Calculation(&u8AppMemRawDataBuff[0], (uint32_t)(LEN_READ_MEM), u32ComputeCrc32);
            (void)(u32ComputeCrc32);
        }       
    }
    u32ComputeCrc32 = (~u32ComputeCrc32);

    /* Get APP CRC32 Value */       
    #if FLASH_READ
        (void)FlashRwApp_Read(ADDR_APP_CRC32, LEN_APP_CRC32, u8AppCrc32Buff);
    #endif
    u32CRC |= u8AppCrc32Buff[0];
    u32CRC <<= 8;
    u32CRC |= u8AppCrc32Buff[1];
    u32CRC <<= 8;
    u32CRC |= u8AppCrc32Buff[2];
    u32CRC <<= 8;
    u32CRC |= u8AppCrc32Buff[3];
    
    if(
            u32CRC == u32ComputeCrc32
      )
    {
        bCheck = true;
    }else
    {
        bCheck = false;
    }
    
    #if DEBUG_UART
        Uart1App_Crc_Show(u32ComputeCrc32, u32CRC);
    #endif

    (void)(u32Size);
    return bCheck;
}
#endif

/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Rx_Crc16_Check(uint8_t u8PacketLen)                
;       Function Description    :   Compute and check the host packet CRC16 values.
;       Parameters              :   [u8PacketLen] - Input data length. 
;       Return Values           :   Return CRC16 check status.
;                                   (1) true - CRC16 check is correct.
;                                   (2) false - CRC16 check is failure.
;       Source ID               :   GM_BL_I2C_SLA-017
******************************************************************************/
#if CRC16_CHECK
static bool I2c0SlaveApp_Rx_Crc16_Check(uint16_t u16PacketLen)                    
{
    bool bCheck = false;
    uint16_t u16CalculateCrc16, u16HostCrc16;
    uint16_t u16NibbleH, u16NibbleL;

    (void)(bCheck);
    u16NibbleH = u16PacketLen - (uint16_t)(LEN_CRC16_H);
    u16NibbleL = u16PacketLen - (uint16_t)(LEN_CRC16_H) - (uint16_t)(LEN_CRC16_L);
    
    if(u16PacketLen == CMD_MEM_UNLOCK_MAX)
    {
        u16HostCrc16 = ((uint16_t)(gu8MemUnlockCmd[u16NibbleH]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemUnlockCmd[u16NibbleL]);
        u16CalculateCrc16 = CrcApp_Crc16_Calculation(gu8MemUnlockCmd+1, ((uint32_t)(u16PacketLen) - (uint32_t)(LEN_CRC16) -1));
    }else if(u16PacketLen == CMD_MEM_ERASE_MAX)
    {        
        u16HostCrc16 = ((uint16_t)(gu8MemEraseCmd[u16NibbleH]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8MemEraseCmd[u16NibbleL]);
        u16CalculateCrc16 = CrcApp_Crc16_Calculation(&gu8MemEraseCmd[CMD_DATA_START], CMD_DATA_LENGTH);
    }
    else    /* u16PacketLen == CMD_FLASH_WRITE_MAX */
    {
        u16HostCrc16 = ((uint16_t)(gu8FlashWriteCmd[u16NibbleH]) << (uint16_t)(SHIFT_BIT_8)) | (uint16_t)(gu8FlashWriteCmd[u16NibbleL]);
        u16CalculateCrc16 = CrcApp_Crc16_Calculation(gu8FlashWriteCmd+1, ((uint32_t)(u16PacketLen) - (uint32_t)(LEN_CRC16) -1));
    }

    if(u16HostCrc16 != u16CalculateCrc16)
    {
        bCheck = false; /* CRC16 fail */
    }       
    else
    {
        bCheck = true;  /* CRC16 pass */
    }       

    (void)(u16PacketLen);
    return bCheck;  
}
#endif

/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Crc16_Load(uint8_t *pu8Buff, uint32_t u32Len)
;       Function Description    :   Load CRC16 values to packets.
;       Parameters              :   [*pu8Buff] - Input data.
;                                   [u32Len] - Input packets length.
;       Return Values           :   true
;       Source ID               :   GM_BL_I2C_SLA-018
******************************************************************************/
#if CRC16_CHECK
static bool I2c0SlaveApp_Crc16_Load(uint8_t *pu8Buff, uint32_t u32Len)
{
    uint16_t u16Crc16;
    
    u16Crc16 = CrcApp_Crc16_Calculation(pu8Buff, u32Len);
    tsI2cSlaveTx.buf[u32Len + (uint32_t)(R_CRC16_L)] = (uint8_t)(u16Crc16);                                         /* Load CRC16_L */
    tsI2cSlaveTx.buf[u32Len + (uint32_t)(R_CRC16_H)] = (uint8_t)((uint16_t)(u16Crc16) >> (uint16_t)(SHIFT_BIT_8));  /* Load CRC16_H */

    return true;    
}
#endif

/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_Rx_TASK_Process(uint8_t u8Para)
;       Function Description    :   Receive the host commands Process in the TASK state.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-019
******************************************************************************/
uint8_t I2c0SlaveApp_Rx_TASK_Process(void)
{
    if((u8ExternalFlag & 0x01U) == (uint8_t)(I2CS_RX_READY))    
    {
        if(gu8MemUnlockCmd[PU_CMD] == (uint8_t)(CMD_APP_MEM_UNLOCK))
        {
            if(I2c0SlaveApp_Rx_Crc16_Check(CMD_MEM_UNLOCK_MAX) == true)
            {
                (void)MainApp_BLControl();
                (void)I2c0SlaveApp_TASK_Cmd_Check(CMD_APP_MEM_UNLOCK);      /* Check CMD_APP_MEM_UNLOCK command */
            }
            else
            {
                (void)I2c0SlaveApp_BL_Status1_Set((uint8_t)(SET_CRC16_ERR));        /* Set CRC16 failure */
                #if DEBUG_UART
                Uart1App_String_Show("CMD_APP_MEM_UNLOCK Crc16 FAIL\r");
                #endif
            }
            (void)memset(gu8MemUnlockCmd, (uint8_t)(NOTHING), CMD_MEM_UNLOCK_MAX );
        }
        u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */   
    }else{
        /*Nothing*/
    }

    return true;
}

/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_Rx_Program_Process(uint8_t u8Para)
;       Function Description    :   Receive the host commands Process in the UPDATE state.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-020
******************************************************************************/
uint8_t I2c0SlaveApp_Rx_Program_Process(void)
{
    /* Program flash */
    if((u8BootloaderStatus1Flag & SET_APP_UNLOCK) == 0)
    {
        (void)I2c0SlaveApp_SM_Status_Clear(NOTHING);        /* Stop ECU Update and return to TASK state */
        #if DEBUG_UART
        Uart1App_String_Show("APP memory no UNLOCK\r"); 
        #endif          
    } else {
        /*Nothing*/
    }

    #if ADC_BATT
    /* Cause state machine change to BL_UPDATE. There can not use 1s loop voltage protect function */
    if(AdcApp_Converstion_Ready() == DRIVER_TRUE)
    {
        if(AdcApp_AdcDebounceFlag_Get() == true)
        {
            (void)FunApp_Delay_Millisecond(1000U, MODE_SYSTICK);        /* debounce the ADC initialize operation */
            (void)AdcApp_AdcDebounceFlag_Set(false);
        }                       
        (void)AdcApp_Battery_Volt_Transfer();
        if(AdcApp_AdcToVolt_Get() < (uint8_t)(THRESHLOD_VOLT_PROTECT)) 
        {
            /* Battery voltage is abnormal */
            u8BootloaderStatus1Flag |= (uint8_t)(SET_VOLT_ERR); /* Set battery voltage error */ 
        }
    }
    #endif

    #if WDT_RST
    (void)WatchDogApp_Clean(MODE_ClearWithoutSync);
    #endif  

    if(FALSE == WakeCtrlApp_Period_WakePin_Just_Check(INTO_SLEEP_TIMES)){
        if(TRUE==st_u8Done){ 
            (void)FunApp_Delay_Millisecond(5U, MODE_SYSTICK); 
            st_u8GoSleepFlag=VALUE_CLEAN;
            (void)InitApp_StateMachine_Set(BL_SLEEP);           /* Jump to BL_SLEEP state if neeeded*/
        } else {
            st_u8GoSleepFlag= (uint8_t)TRUE;
            st_u8Done = VALUE_CLEAN;
            u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;          
            u8BootloaderStatus2Flag = (uint8_t)(SET_PROGRAMMING_ERROR); 
            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
        }
    }

    (void)PinIOApp_High(portXRES_TP_R, pinXRES_TP_R);
    return true;
}
/******************************************************************************
;       Function Name           :   static uint8_t I2c0SlaveApp_Customer_Cmd_Check(uint8_t u8Para)
;       Function Description    :   Check customer commands in the ISR callback function.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-022
******************************************************************************/
static void I2c0SlaveApp_Customer_Cmd_Check(uint8_t u8Cmd)
{
    switch(u8Cmd)
    {
        case CMD_BL_STATUS:
            if(TRUE==st_u8GoSleepFlag){
                st_u8Done = TRUE;
            }
            /* IRQ Status Response function is disabled */
            tsI2cSlaveTx.buf[R_BL_STATUS_1] = u8BootloaderStatus1Flag;  /* BL Status 1 */
            tsI2cSlaveTx.buf[R_BL_STATUS_2] = u8BootloaderStatus2Flag;  /* BL Status 2 */

            (void)I2c0SlaveApp_Crc16_Load(tsI2cSlaveTx.buf, LEN_BL_STATUS);
            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_RELEASE);            /* Set IRQ Release flag, and rlease IRQ signal after the host read */
        break;
        case CMD_FIDM_VER_GET:
            if(FunApp_Crc32FailFlag_Get() == true)
            {
                /* APP CRC32 is failure, so APP version is failure version */
                tsI2cSlaveTx.buf[R_FIDM_VER_L] = 0xFFU;     /* CRC32 Failure */
                tsI2cSlaveTx.buf[R_FIDM_VER_H] = 0xFFU;     /* CRC32 Failure */
            }
            else
            {
                /* APP CRC32 is correct */
                tsI2cSlaveTx.buf[R_FIDM_VER_L] = (uint8_t)(FlashRwApp_FIDM_Ver_Get() & (uint16_t)(0x00FFU));
                tsI2cSlaveTx.buf[R_FIDM_VER_H] = (uint8_t)((FlashRwApp_FIDM_Ver_Get() & (uint16_t)(0xFF00U)) >> (uint16_t)(SHIFT_BIT_8));
            }
        break;
        case CMD_TP_ID_GET:
            tsI2cSlaveTx.buf[R_TP_MCU_ID] = (uint8_t)(ID_TP);
        break;
        case CMD_DISPLAY_ID_GET:
            tsI2cSlaveTx.buf[R_DISPLAY_ID] = (uint8_t)(ID_DISPLAY);
        break;
        case CMD_HW_VER_GET:
            tsI2cSlaveTx.buf[R_HW_VER_L] = (uint8_t)(AdcApp_AdcToHWVersion_Get() & (uint16_t)(0x00FFU));
            tsI2cSlaveTx.buf[R_HW_VER_H] = (uint8_t)((AdcApp_AdcToHWVersion_Get() & (uint16_t)(0xFF00U)) >> (uint16_t)(SHIFT_BIT_8));
        break;
       case CMD_UPGRADE_FW_PARAMETER:
           tsI2cSlaveTx.buf[R_SINGLE_PACKET_DATA_LEN_LSB] = SINGLE_PACKET_DATA_LEN_LSB;
           tsI2cSlaveTx.buf[R_SINGLE_PACKET_DATA_LEN_MSB] = SINGLE_PACKET_DATA_LEN_MSB;
           tsI2cSlaveTx.buf[R_POLLING_INTERVAL_LSB] = POLLING_INTERVAL_LSB;
           tsI2cSlaveTx.buf[R_POLLING_INTERVAL_MSB] = POLLING_INTERVAL_MSB;
           tsI2cSlaveTx.buf[R_Reserved0] = RESERVED;
           tsI2cSlaveTx.buf[R_Reserved1] = RESERVED;
           tsI2cSlaveTx.buf[R_CRC8] = CrcApp_Crc8_Calculation(&tsI2cSlaveTx.buf[1],6);
       break;
        default:
            /*Nothing*/
        break;
    }
}

/******************************************************************************
;   Function Name           :   uint8_t HostCmdApp_Cmd_Parser(st_ring_buffer *ptdRingBuffer)
;   Function Description    :   Parser the receive data
;   Parameters              :   [u8Cmd] : Cmd
;   Return Values           :   None
******************************************************************************/
static uint8_t I2cSlaveApp_Write_Cmd_Parser(st_ring_buffer *ptdRingBuffer)
{
    uint8_t u8Return;
    switch(ptdRingBuffer->u8Buf[ptdRingBuffer->u16Head])
    {
        case CMD_DISPLAY_BL_CONTROL:
            (void)slave_i2c_ringbuffer_pull(ptdRingBuffer, gu8DisplayBLCmd, (uint16_t)CMD_DISPLAY_BL_MAX);

            I2c0SlaveApp_TASK_Cmd_Check(CMD_DISPLAY_BL_CONTROL);
            u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */   
            u8Return = TRUE;
        break;

        case CMD_FORCE_RST:
            (void)slave_i2c_ringbuffer_pull(ptdRingBuffer, gu8ResetCmd, (uint16_t)CMD_FORCE_RST_MAX);

            I2c0SlaveApp_Global_Cmd_Check(CMD_FORCE_RST);
            u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */   
            u8Return = TRUE;
        break;

        case CMD_APP_MEM_UNLOCK:
            (void)slave_i2c_ringbuffer_pull(ptdRingBuffer, gu8MemUnlockCmd, (uint16_t)CMD_MEM_UNLOCK_MAX);

            u8Return = TRUE;
        break;

        case CMD_APP_MEM_ERASE:
            (void)slave_i2c_ringbuffer_pull(ptdRingBuffer, gu8MemEraseCmd, (uint16_t)CMD_MEM_ERASE_MAX);
            if(
                ((uint8_t)(u8BootloaderStatus2Flag & SET_UNKNOWN_ERROR) != (uint8_t)(SET_UNKNOWN_ERROR)) && 
                (VALUE_CLEAN==st_u8GoSleepFlag)    
                )
            {
                if(
                    ((u8BootloaderStatus1Flag & SET_APP_UNLOCK) != (uint8_t)(SET_APP_UNLOCK))                   
                )
                {
                    // Recieve write cmd before unlock
                    u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;            /* Flash is written error */
                    u8BootloaderStatus2Flag |= (uint8_t)SET_UNKNOWN_ERROR;
                    (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                }
                else
                {
                    I2c0SlaveApp_Update_Cmd_Check(CMD_APP_MEM_ERASE);
                }
            } else {
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                u8BootloaderStatus2Flag |= (uint8_t)(SET_UNKNOWN_ERROR);
                /* Nothing To Do */
            }
            
            u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */   
            u8Return = TRUE;
        break;

        case CMD_FLASH_PAGE_WRITE:
            (void)slave_i2c_ringbuffer_pull(ptdRingBuffer, gu8FlashWriteCmd, (uint16_t)CMD_FLASH_WRITE_MAX); 
            if(
                ((u8BootloaderStatus1Flag & SET_APP_UNLOCK) == (uint8_t)(SET_APP_UNLOCK)) &&
                ((u8BootloaderStatus1Flag & SET_APP_ERASE) == (uint8_t)(SET_APP_ERASE))
            )
            {
                if(
                    ((uint8_t)(u8ExternalFlag & 0x01U) == (uint8_t)(I2CS_RX_READY)) &&
                    (VALUE_CLEAN==st_u8GoSleepFlag)    
                    )
                {
                    if(I2c0SlaveApp_Rx_Crc16_Check(CMD_FLASH_WRITE_MAX) == true)
                    {
                        /* If CRC16 error flag is enabled, then set CRC16 error is disabled. */
                        if((u8BootloaderStatus1Flag & 0x40U) == SET_CRC16_ERR)
                        {
                            u8BootloaderStatus1Flag &= (uint8_t)(~SET_CRC16_ERR);           /* Set CRC16 correct */
                            (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                        }

                        (void)I2c0SlaveApp_Update_Cmd_Check(CMD_FLASH_PAGE_WRITE);
                    }
                    else
                    {
                        u8BootloaderStatus1Flag |= (uint8_t)(SET_CRC16_ERR);            /* Set CRC16 error */
                        u8BootloaderStatus1Flag &= (uint8_t)(~SET_FLASH_WRITE_SUCCESS); /* Flash is written error */
                        u8BootloaderStatus2Flag |= (uint8_t)(SET_PROGRAMMING_ERROR);    /* Programming error */
                        (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
                        #if DEBUG_UART
                        Uart1App_String_Show("Packet Crc16 FAIL\r");
                        #endif
                    }
                }
            }else{
                u8BootloaderStatus1Flag &= ~SET_FLASH_WRITE_SUCCESS;            /* Flash is written error */
                u8BootloaderStatus2Flag |= (uint8_t)(SET_PROGRAMMING_ERROR);
                u8BootloaderStatus2Flag |= (uint8_t)(SET_UNKNOWN_ERROR);
                (void)I2c0SlaveApp_Irq_Control(SET_IRQ_ASSERT);
            }
            u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */
            u8Return = TRUE;
        break;

        default:
            slave_i2c_ringbuffer_init(ptdRingBuffer);
            u8ExternalFlag &= (~((uint8_t)(I2CS_RX_READY)));    /* Clear I2C Slave RX Flag */
            u8Return = FALSE;
        break;
    }
    return u8Return;
}

/******************************************************************************
;   Function Name           :   static void I2cSlaveApp_Handshake_Finish(st_ring_buffer *ptdRingBuffer)
;   Function Description    :   I2C slave done
;   Parameters              :   tsI2csRx
;   Return Values           :   tsI2csRx
******************************************************************************/
static void I2cSlaveApp_Handshake_Finish(st_ring_buffer *ptdRingBuffer)
{
    uint32_t u32TimeoutTemp = 1000U;
    
    if (gPacketDir == (uint8_t)(I2C_READ))
    {
        tsI2cSlaveTx.cnt = 0U;  /* Clear Index */
        u8ExternalFlag |= (uint8_t)(I2CS_TX_READY);
    }
    else        /* gbPacketDir == (bool)(I2CS_WRITE) */
    {
        u8ExternalFlag |= (uint8_t)(I2CS_RX_READY);
        while((ptdRingBuffer->u16Length != 0U) && (u32TimeoutTemp > 0U))
        {
            (void)I2cSlaveApp_Write_Cmd_Parser(ptdRingBuffer);
            u32TimeoutTemp = u32TimeoutTemp - 1;
        }
    }
}

/******************************************************************************
;   Function Name           :   static void I2cSlaveApp_Error_Event(void)
;   Function Description    :   I2C Error
;   Parameters              :   N/A
;   Return Values           :   N/A
******************************************************************************/
static uint8_t I2cSlaveApp_Error_Event(void)
{
    uint8_t u8ErrorFlag;
    sercom_registers_t *reg = i2c_channel_reg(SERCOM_CH0);
    
    if (reg != NULL)
    {
        if ((reg->I2CS.SERCOM_INTFLAG & SERCOM_I2CS_INTFLAG_ERROR_Msk) > 0U)
        {
            u8ErrorFlag = SERCOM_I2CS_INTFLAG_ERROR_Msk;
        }
        else
        {
            u8ErrorFlag = VALUE_CLEAN;
        }
    }
    else
    {
        u8ErrorFlag = VALUE_CLEAN;
    }
    
    (void)clear_slave_i2c_flag(SERCOM_CH0, u8ErrorFlag);
    return u8ErrorFlag;
}

/******************************************************************************
;   Function Name           :   uint8_t I2cSlaveApp_Slave_DeInitial(void)
;   Function Description    :   I2C slave deinitial
;   Parameters              :   None.
;   Return Values           :   bState
******************************************************************************/
uint8_t I2cSlaveApp_Slave_DeInitial(void)
{
    uint8_t u8Return;
    if (true == slave_i2c_stop(SERCOM_CH0))
    {
        u8Return = TRUE;
    }
    else
    {
        u8Return = FALSE;
    }

    (void)I2cSlaveApp_Error_Event();
    return u8Return;
}

/******************************************************************************
;       Function Name           :   static bool I2c0SlaveApp_Callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle)
;       Function Description    :   SERCOM0 I2C slave callback API.
;       Parameters              :   [event] - I2C slave transfer event.
;                                   [contextHandle] - Context Handler.
;       Return Values           :   Return status.
;                                   (1) true - ISR is normal or abmormal.
;                                   (2) false - Unknown condition.
;       Source ID               :   GM_BL_I2C_SLA-023
******************************************************************************/
bool I2c0SlaveApp_Callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle)
{
    bool bReturn = false;
    uint8_t u8CmdTemp = 0;
    uint8_t u8RecDataTemp = 0;
    uint8_t u8CmdCechkIndex = 0;
    bool bIsDataAddrMateched = false;
    sercom_registers_t *ptdReg = i2c_channel_reg(tsI2cSlaveDev.channel);

    if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_ADDR_MATCH))
    {
        if((get_slave_i2c_status(tsI2cSlaveDev.channel) & SERCOM_I2CS_STATUS_DIR_Msk) == SERCOM_I2CS_STATUS_DIR_Msk)
        {
            gPacketDir = (uint8_t)(I2C_READ);
            (void)slave_i2c_ringbuffer_pull(&tsI2cSlaveRx, &u8CmdTemp, (uint16_t)CMD_OTHER_MAX);
            (void)I2c0SlaveApp_Customer_Cmd_Check(u8CmdTemp);
        }
        else
        {
            gPacketDir = (uint8_t)I2C_WRITE;
        }

        /* Triggling to check data address is vaild or invaild */
        tsI2cSlaveDev.FirstByteCheckFinished = false;
        bReturn = true;
    }
    else if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_RX_READY))
    {
        if(tsI2cSlaveDev.FirstByteCheckFinished == false)
        {
            tsI2cSlaveDev.FirstByteCheckFinished = true;
            u8RecDataTemp = ptdReg->I2CS.SERCOM_DATA;
            while(u8CmdCechkIndex < CMD_SIZE)
            {
                if(u8RecDataTemp == gu8AllowedDataAddress[u8CmdCechkIndex])
                {
                    bIsDataAddrMateched = true;
                    break;
                }
                else
                {
                    u8CmdCechkIndex++;
                }
            }

            if(bIsDataAddrMateched == false)
            {
                bReturn = false;
            }
            else
            {
                (void)slave_i2c_ringbuffer_push(&tsI2cSlaveRx, u8RecDataTemp);
                bReturn = true;
            }
        }
        else
        {
            /* Master write -> slave read */
            (void)slave_i2c_read(&tsI2cSlaveDev, &tsI2cSlaveRx);    /* Get Data */
            bReturn = true;
        }
    }
    else if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_TX_READY))
    {
        (void)I2c0SlaveApp_Slave_Tx_Send(NOTHING);
        bReturn = true;
    }
    else if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_STOP_RECEIVED))
    {
        I2cSlaveApp_Handshake_Finish(&tsI2cSlaveRx);
        bReturn = true;
    }
    else if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_ERROR_EVENT))
    {
        (void)I2cSlaveApp_Error_Event();
        bReturn = true;
    }
    else if((uint8_t)(event) == (uint8_t)(SERCOM_I2C_SLAVE_NONE))
    {
        /* NOTHING */
        bReturn = true;
    }
    else
    {
        bReturn = false;
    }

    (void)u8RecDataTemp;
    (void)ptdReg;
    (void)u8CmdTemp;
    (void)(contextHandle);
    return bReturn;
}

/******************************************************************************
;       Function Name           :   uint8_t I2c0SlaveApp_Init(uint8_t u8Para)
;       Function Description    :   Initialize I2C slave function.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   GM_BL_I2C_SLA-024
******************************************************************************/
uint8_t I2c0SlaveApp_Init(void)
{ 
    tsI2cSlaveDev.channel = SERCOM_CH0;
    tsI2cSlaveDev.addr = ADDR_SLAVE;
    tsI2cSlaveDev.speed = I2CS_1MHz;
    tsI2cSlaveDev.callback = I2c0SlaveApp_Callback;
    tsI2cSlaveDev.inte.addr_matched = true;
    tsI2cSlaveDev.inte.data_ready = true;
    tsI2cSlaveDev.inte.error_int = true;
    tsI2cSlaveDev.inte.stop_receive = true;
    tsI2cSlaveDev.FirstByteCheckFinished = false;

    slave_i2c_ringbuffer_init(&tsI2cSlaveRx);
    (void)memset(&tsI2cSlaveTx, 0U, sizeof(tsI2cSlaveTx));
    
    (void)slave_i2c_init(&tsI2cSlaveDev);

    u8BootloaderStatus1Flag = (uint8_t)SET_BL_ACTIVE;
    u8BootloaderStatus2Flag = (uint8_t)(DEFAULT_BL_STATUS_2);
#if AUTO_MATCH_ADDRESS
    gu16PageCounter = 0U;
#endif
    return true;
}

/******************************************************************************
;Author: Orlando Huang
;Description: Return BL Value From Host
;Return Parameter: {*}
******************************************************************************/
uint16_t I2cSlaveApp_GetHostBL(void)
{
    return ((uint16_t)(gu8BacklightVal[0U]) << 8U) | (uint16_t)(gu8BacklightVal[1U]);
}
/*--------------------------------------END-------------------------------*/
