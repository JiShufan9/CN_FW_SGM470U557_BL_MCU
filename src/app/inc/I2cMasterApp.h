/******************************************************************************
;Author: Orlando Huang
;Date: 2021-11-05 13:13:09
;LastEditTime: 2021-11-12 13:51:15
;FilePath: \TM_FW_GMBootloader_MCU\src\app\inc\I2cMasterApp.h
;Description: N/A
******************************************************************************/
#ifndef I2CMASTERAPP_H    /* Guard against multiple inclusion */
#define I2CMASTERAPP_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
/* Include *.h */
#include "hal/inc/I2CMDriver.h"
/* Marco Define */
#define I2CMASTERAPP_TIMEOUT_COUNTER	11154U/*3ms*/
#define I2CMASTERAPP_ENABLE_TX  true
#define I2CMASTERAPP_ENABLE_RX  false
#define ADDR_TCON 0x52U
#define LED_DRIVER_ADDRESS              0x38U

typedef enum I2CMasterSercomType
{
    I2C_MASTER_SERCOM_3 = 0U,
    I2C_MASTER_SERCOM_2,
    I2C_MASTER_SERCOM_5
}I2CMasterSercom;

/* Releasing Function */
bool I2cMasterApp_Master_Initial(uint8_t u8Master);
bool I2cMasterApp_DeInitial(uint8_t u8Master);
#if I2CMASTERAPP_ENABLE_TX
bool I2cMasterApp_Tx(uint8_t u8Master, uint8_t *u8Data, uint8_t u8Len);
#endif
#if I2CMASTERAPP_ENABLE_RX
bool I2cMasterApp_Rx(uint8_t u8Master, uint8_t *u8TxData, uint8_t u8TxLen, uint8_t *u8RxData, uint8_t u8RxLen);
#endif
/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif
#endif
