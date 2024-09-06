/******************************************************************************
;Program:I2CMASTERAPP.C
;FUNCTION:DECLEAR SERCOM3 I2C MASTER APPLICATION FUNCTION FOR TCON
;DATE:2021/11/16
;AUTHOR:ORLANDO HUANG
;DESCRIBE:
;           1.CONTROL TCON TO PRODUCE BACKLIGHT CONTROL SIGNAL 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include"app/inc/I2cMasterApp.h"
/*---------------------------- Declare Global Variable ----------------------*/
static st_i2c_master_config gAPPI2cSourceIc;
static st_i2c_master_config gAPPI2cLEDRriver;
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;Author: Orlando Huang
;Description: N/A
;Return Parameter: {*}
;param {uint8_t} u8Master
******************************************************************************/
bool I2cMasterApp_Master_Initial(uint8_t u8Master)
{
    bool bReturn = false;

    switch(u8Master)
    {
        case I2C_MASTER_SERCOM_2:
            gAPPI2cSourceIc.addr = ADDR_SOURCE_IC;
            gAPPI2cSourceIc.channel = SERCOM_CH2;
            gAPPI2cSourceIc.speed = STANDARD_MODE;
            gAPPI2cSourceIc.baudrate = 400U;
            gAPPI2cSourceIc.callback = NULL;
            gAPPI2cSourceIc.inte.error_int = false;
            gAPPI2cSourceIc.inte.master_on_bus = true;
            gAPPI2cSourceIc.inte.slave_on_bus = true;

            bReturn = master_i2c_init(&gAPPI2cSourceIc);
            (void)master_i2c_interrupt(&gAPPI2cSourceIc);
        break;
        case I2C_MASTER_SERCOM_5:
            gAPPI2cLEDRriver.addr = LED_DRIVER_ADDRESS;
            gAPPI2cLEDRriver.channel = SERCOM_CH5;
            gAPPI2cLEDRriver.speed = STANDARD_MODE;
            gAPPI2cLEDRriver.baudrate = 400U;
            gAPPI2cLEDRriver.callback = NULL;
            gAPPI2cLEDRriver.inte.error_int = (uint8_t)false;
            gAPPI2cLEDRriver.inte.master_on_bus = (uint8_t)true;
            gAPPI2cLEDRriver.inte.slave_on_bus = (uint8_t)true;

            bReturn = master_i2c_init(&gAPPI2cLEDRriver);
            (void)master_i2c_interrupt(&gAPPI2cLEDRriver);
        break;

        default:
            bReturn = false;
        break;
    }

    return bReturn;
}
/******************************************************************************
;Author: Orlando Huang
;Description: N/A
;Return Parameter: {*}
;param {uint8_t} u8Master
******************************************************************************/
bool I2cMasterApp_DeInitial(uint8_t u8Master)
{
    bool bReturn = false;

    switch(u8Master)
    {
        case I2C_MASTER_SERCOM_2:
            (void)master_i2c_stop(SERCOM_CH2);
            __NVIC_DisableIRQ(SERCOM2_IRQn);

            bReturn = true;
        break;
        case I2C_MASTER_SERCOM_5:
            (void)master_i2c_stop(SERCOM_CH5);
            __NVIC_DisableIRQ(SERCOM5_IRQn);
            bReturn = true;
        break;

        default:

            bReturn = false;
        break;
    }

    return bReturn;
}


/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
void I2cMasterApp_SetDesI2cAddr(uint8_t u8Master,uint8_t addr)
{
    gAPPI2cSourceIc.addr = addr;
}


#if I2CMASTERAPP_ENABLE_TX
/******************************************************************************
;Author: Orlando Huang
;Description: N/A
;Return Parameter: {*}
;param {uint8_t} u8Address
;param {uint8_t} *u8Data
;param {uint8_t} u8Len
******************************************************************************/
bool I2cMasterApp_Tx(uint8_t u8Master, uint8_t *u8Data, uint8_t u8Len)
{
    bool ret = true;
    uint32_t u32Len = (uint32_t)u8Len;
	uint32_t u32Jump = 0UL;
#if COM2_INSERT_FRAME_GAP
    uint16_t u16delayCnt;
#endif

    switch(u8Master)
    {
        case I2C_MASTER_SERCOM_2:
            if (true == master_i2c_transmitte(&gAPPI2cSourceIc, u8Data, u32Len))
            {
                while((true == SERCOM_I2CM_IsBusy(gAPPI2cSourceIc.channel)) && (u32Jump < I2CMASTERAPP_TIMEOUT_COUNTER))
                {
                    u32Jump += 1UL;
                }

#if COM2_INSERT_FRAME_GAP
                u16delayCnt = 2000U;
                while(u16delayCnt > 0)
                {
                    u16delayCnt --;
                }
#endif
            }
            else
            {
                ret = false;
                (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_2);
            }
        break;
        case I2C_MASTER_SERCOM_5:
            if (true == master_i2c_transmitte(&gAPPI2cLEDRriver, u8Data, u32Len))
            {
                while((true == SERCOM_I2CM_IsBusy(gAPPI2cLEDRriver.channel)) && (u32Jump < I2CMASTERAPP_TIMEOUT_COUNTER))
                {
                    u32Jump += 1UL;
                }
            }
            else
            {
                ret = false;
                (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_5);
            }
        break;

        default:
            ret = false;
        break;
    }

    return ret;
}
#endif
/******************************************************************************
;FUNCTION NAME:I2cMasterApp_Rx
;DATE:2021/11/16
;AUTHOR:Orlando Huang
;DESCRIBE:
;INPUT VARIABLE:uint8_t u8Master, uint8_t *u8TxData, uint8_t u8TxLen, uint8_t *u8RxData, uint8_t u8RxLen
;OUTPUT VARIABLE:bool
******************************************************************************/
#if I2CMASTERAPP_ENABLE_RX
bool I2cMasterApp_Rx(uint8_t u8Master,uint8_t *u8TxData, uint8_t u8TxLen, uint8_t *u8RxData, uint8_t u8RxLen)
{
    bool ret = true;
	uint32_t u32Jump = 0UL;
	uint32_t u32TxLen = (uint32_t)u8TxLen;
	uint32_t u32RxLen = (uint32_t)u8RxLen;
#if COM2_INSERT_FRAME_GAP
    uint16_t u16delayCnt;
#endif

    switch(u8Master)
    {
        case I2C_MASTER_SERCOM_2:
            if(true == master_i2c_writeread(&gAPPI2cSourceIc, u8TxData, u32TxLen, u8RxData, u32RxLen))
            {
                while((true == SERCOM_I2CM_IsBusy(gAPPI2cSourceIc.channel)) && (u32Jump < I2CMASTERAPP_TIMEOUT_COUNTER))
                {
                    u32Jump += 1UL;
                }
#if COM2_INSERT_FRAME_GAP
                u16delayCnt = 2000u;
                while(u16delayCnt > 0)
                {
                    u16delayCnt --;
                }
#endif
            }
            else
            {
                ret = false;
                (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_2);
            }
        break;
        case I2C_MASTER_SERCOM_5:
            if(true == master_i2c_writeread(&gAPPI2cLEDRriver, u8TxData, u32TxLen, u8RxData, u32RxLen))
            {
                while((true == SERCOM_I2CM_IsBusy(gAPPI2cLEDRriver.channel)) && (u32Jump < I2CMASTERAPP_TIMEOUT_COUNTER))
                {
                    u32Jump += 1UL;
                }
            }
            else
            {
                ret = false;
                (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_5);
            }
        break;
        default:
            ret = false;
        break;
    }

    return ret;
}
#endif
/*--------------------------------------END-------------------------------*/
