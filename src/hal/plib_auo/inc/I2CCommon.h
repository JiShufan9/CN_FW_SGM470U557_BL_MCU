/******************************************************************************
;Author: Orlando Huang
;Date: 2021-09-28 18:41:28
;LastEditTime: 2021-10-07 16:24:29
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\plib_auo\inc\I2CCommon.h
;Description: N/A
******************************************************************************/
/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef I2CCOMMON_H    /* Guard against multiple inclusion */
#define I2CCOMMON_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_DEFAULT     0U
#define FREQ_REF        48000000UL
#define QUEUE_MAX       150U

typedef enum
{
    I2CS_RX_READY = 1U,
    I2CS_TX_READY = 2U,
    I2CM_TRANSFER_READY = 4U,
}en_externel_int_event;

typedef enum
{
    SERCOM_CH0,
    SERCOM_CH1,
    SERCOM_CH2,
    SERCOM_CH3,
    SERCOM_CH4,
    SERCOM_CH5
}en_i2c_channel;

typedef struct
{
    uint8_t buf[QUEUE_MAX];
    uint8_t cnt;
    uint8_t length;
}st_queue;

typedef struct
{
    uint8_t u8Buf[QUEUE_MAX];
    uint8_t u16Head;
    uint8_t u16Tail;
    uint16_t u16Length;
    uint16_t u16LengthMax;
}st_ring_buffer;

sercom_registers_t * i2c_channel_reg(en_i2c_channel eCh);
bool i2c_io_setup(en_i2c_channel eCh);
#if 0
bool i2c_nvic_enable(en_i2c_channel eCh);
#endif
#if 0
bool wait_sync(sercom_registers_t *ptdReg);
#endif
bool wait_slave_sync(sercom_registers_t *ptdReg);

#ifdef __cplusplus
}
#endif

#endif /* I2CCOMMON_H */
