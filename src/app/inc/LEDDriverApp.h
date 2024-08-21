/******************************************************************************
;       Program		: LEDDriverApp.h
;       Date		: 2024 / 04 / 23
;       Author		: Fan.Ji
;       Describe	: LEDDriver define
******************************************************************************/

#ifndef LEDDRIVERAPP_H    /* Guard against multiple inclusion */
#define LEDDRIVERAPP_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include "app/inc/I2cMasterApp.h"
#include "app/inc/WakeCtrlApp.h"
#include "main.h"
#include "app/inc/EepromApp.h"

#define ILED_DUTY_IF_EN                                 ENABLE_ON
#define PDIM_DUTY_IF_EN                                 ENABLE_OFF
    
#define LEDDRIVER_DATA_LEN_1                            1U
#define LEDDRIVER_DATA_LEN_2                            2U
    
#define LEDDRIVER_MODE_CTRL_ADD                         0x00U
#define LEDDRIVER_FREQ_FTM_ADD                          0x01U
#define LEDDRIVER_CON1_ADD                              0x02U
#define LEDDRIVER_CON2_ADD                              0x03U
#define LEDDRIVER_FUN_SET_ADD                           0x04U
#define LEDDRIVER_PDIM_MSB_ADD                          0x05U
#define LEDDRIVER_PDIM_LSB_ADD                          0x06U
#define LEDDRIVER_ILED_MSB_ADD                          0x07U
#define LEDDRIVER_ILED_LSB_ADD                          0x08U
#define LEDDRIVER_ILED_TEMP_ADD                         0x09U
#define LEDDRIVER_IC_TEMP_ADD                           0x0AU
#define LEDDRIVER_FAULE_ADD                             0x0BU
#define LEDDRIVER_DEV_ID_ADD                            0x0CU
    
#define LDEDRIVER_ILED_MAX                              0x000001FFU
#define LEDDRIVER_ILED_MIN                              0x0000U
#define LEDDRIVER_PDIM_MAX                              0x00003FFFU
#define LDEDRIVER_PDIM_MIN                              0x0000U

#define LEDDRIVER_BACKLIGHT_MAX                         0xFFFFU
#define LEDDRIVER_BACKLIGHT_MIN                         0x0000U

#define I2cMasterApp_LEDDriver_Tx(u8I2cAddr,u8Data,u8Len)                   I2cMasterApp_Tx(I2C_MASTER_SERCOM_5, u8Data, u8Len)
    
void LEDDriverApp_Initial(uint8_t u8Nothing);

uint8_t LEDDriverApp_BackLight_Output(uint16_t u16Duty);

#endif