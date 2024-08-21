
#include "app/inc/LEDDriverApp.h"
#include "app/inc/FunApp.h"

uint16_t LDEDRIVER_MAX;
uint8_t Initial_Flag = 0x00U;

void LEDDriverApp_Initial(uint8_t u8Nothing)
{
    uint32_t u32BLMAXINI = 0u, u32Temp;

#if(PDIM_DUTY_IF_EN == ENABLE_ON)
    {
        u32BLMAXINI = LEDDRIVER_PDIM_MAX;
    }
#elif(ILED_DUTY_IF_EN == ENABLE_ON)
    {
        u32BLMAXINI = LDEDRIVER_ILED_MAX;
    }
#else

#endif

    if(Initial_Flag == 0x00U){
        if(0xFFFFFFFFU == EepromApp_Read(EEPROM_REGION_5_BL_MAX, EEPROM_DATA_LENGTH_1))
        {
            EepromApp_Erase(EEPROM_REGION_5_BL_MAX);
            EepromApp_Write((uint32_t)EEPROM_REGION_5_BL_MAX, u32BLMAXINI);
        }
        Initial_Flag = 0x01U;
    }

    u32Temp = EepromApp_Read(EEPROM_REGION_5_BL_MAX, EEPROM_DATA_LENGTH_1);
    LDEDRIVER_MAX = (uint16_t)(u32Temp & 0xFFFFU);

    (void)FunApp_Delay_Millisecond(10, MODE_SYSTICK);                 /* Delay 10ms */ 
    uint8_t u8TxData_LEDDriver[LEDDRIVER_DATA_LEN_2];
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_MODE_CTRL_ADD;
    u8TxData_LEDDriver[DATA_1] = 0x4FU;
    (void)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_FREQ_FTM_ADD;
    u8TxData_LEDDriver[DATA_1] = 0x15U;
    (void)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);

//    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_CON1_ADD;
//    u8TxData_LEDDriver[DATA_1] = 0x15U;
//    (void)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_FUN_SET_ADD;
    u8TxData_LEDDriver[DATA_1] = 0xB8U;
    (void)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
  
    (void)u8Nothing;
    
    (void)LEDDriverApp_BackLight_Output(0x00U);
}

#if (ILED_DUTY_IF_EN == ENABLE_ON)
static uint8_t LEDDriverApp_ILED_Duty_Set(uint16_t u16Duty){
    uint8_t bResult;
    uint8_t u8TxData_LEDDriver[LEDDRIVER_DATA_LEN_2];
    uint16_t u16Temp;

    u16Duty = (uint32_t)u16Duty * LDEDRIVER_MAX / LEDDRIVER_BACKLIGHT_MAX;
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_ILED_MSB_ADD;
    u16Temp = (u16Duty >> 8) & 0xFFU;
    u8TxData_LEDDriver[DATA_1] = (uint8_t)u16Temp;
    bResult = (uint8_t)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_ILED_LSB_ADD;
    u16Temp = u16Duty & 0xFFU;
    u8TxData_LEDDriver[DATA_1] = (uint8_t)u16Temp;
    bResult &= (uint8_t)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    return bResult;
}
#endif

#if (PDIM_DUTY_IF_EN == ENABLE_ON)
static uint8_t LEDDriverApp_PDIM_Duty_Set(uint16_t u16Duty){
    uint8_t bResult;
    uint8_t u8TxData_LEDDriver[LEDDRIVER_DATA_LEN_2];
    uint16_t u16Temp = 0U;

    u16Duty = u16Duty * LDEDRIVER_MAX / LEDDRIVER_BACKLIGHT_MAX;
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_PDIM_MSB_ADD;
    u16Temp = (u16Duty >> 8) & 0xFFU;
    u8TxData_LEDDriver[DATA_1] = (uint8_t)u16Temp;
    bResult = (uint8_t)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    u8TxData_LEDDriver[DATA_0] = LEDDRIVER_PDIM_LSB_ADD;
    u16Temp = u16Duty & 0xFFU;
    u8TxData_LEDDriver[DATA_1] = (uint8_t)u16Temp;
    bResult &= (uint8_t)I2cMasterApp_LEDDriver_Tx(LED_DRIVER_ADDRESS, u8TxData_LEDDriver, LEDDRIVER_DATA_LEN_2);
    
    return bResult;
}
#endif

uint8_t LEDDriverApp_BackLight_Output(uint16_t u16Duty){
    uint8_t bResult;
    #if (ILED_DUTY_IF_EN == ENABLE_ON)
    bResult = LEDDriverApp_ILED_Duty_Set(u16Duty);
    #endif
    #if (PDIM_DUTY_IF_EN == ENABLE_ON)
    bResult = LEDDriverApp_PDIM_Duty_Set(u16Duty);
    #endif
    return bResult;
}

