/******************************************************************************
;Author: Orlando Huang
;Date: 2021-09-28 18:41:28
;LastEditTime: 2021-10-27 19:41:15
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\inc\I2CSDriver.h
;Description: N/A
******************************************************************************/
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
#ifndef I2CSDRIVER_H    /* Guard against multiple inclusion */
#define I2CSDRIVER_H
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "hal/plib_auo/inc/I2CSlave.h"
#include "hal/plib_auo/inc/I2CCommon.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define I2CS_READ       TRUE
#define I2CS_WRITE      FALSE
#define I2CS_400KHz     0x00000000UL
#define I2CS_1MHz       0x01000000UL
#define I2CS_3_4MHz     0x02000000UL
    
typedef struct
{
        uint8_t stop_receive:1;
        uint8_t addr_matched:1;
        uint8_t data_ready:1;
        uint8_t error_int:1;
    }st_i2cs_intset;
    
typedef struct i2c_slave_config
{
	uint32_t addr;              /* Device address */
	uint32_t speed;             /* Device speed */
	en_i2c_channel channel;     /* SERCOM "N" */
	st_i2cs_intset inte;        /* Interrupt enable */
  bool FirstByteCheckFinished;
	bool (*callback)(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle);       /* Operating funtions */
}st_i2c_slave_config;
    
bool clear_slave_i2c_flag(en_i2c_channel eCh, uint8_t u8ClrFlag);
bool slave_i2c_init(st_i2c_slave_config *ptdConfig) ;
bool slave_i2c_start(en_i2c_channel eCh);
bool slave_i2c_stop(en_i2c_channel eCh);
uint16_t get_slave_i2c_status(en_i2c_channel eCh);
#if 0
uint8_t get_slave_i2c_flag(en_i2c_channel eCh);
#endif
bool slave_i2c_interrupt(st_i2c_slave_config *ptdConfig);
bool slave_i2c_read(st_i2c_slave_config *ptdConfig, st_ring_buffer *ptdRingBuffer);
bool slave_i2c_transmitte(st_i2c_slave_config *ptdConfig, uint8_t *pu8Buffer) ;
bool slave_i2c_data_ready_wait(st_i2c_slave_config *ptdConfig);
void slave_i2c_ringbuffer_init(st_ring_buffer *ptdRingBuffer);
bool slave_i2c_ringbuffer_pull(st_ring_buffer *ptdRingBuffer, uint8_t *pu8Temp, uint16_t u16Size);
bool slave_i2c_ringbuffer_push(st_ring_buffer *ptdRingBuffer, uint8_t u8Data);

#ifdef __cplusplus
}
#endif

#endif /* I2CSDRIVER_H */

/* *****************************************************************************
 End of File
 */
