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

#ifndef I2CM_DRIVER_H    /* Guard against multiple inclusion */
#define I2CM_DRIVER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "hal/plib_auo/inc/SercomI2CMasterCommon.h"
#include "hal/plib_auo/inc/Sercom2I2CMaster.h"
#include "hal/plib_auo/inc/I2CCommon.h"

/* This section lists the other files that are included in this file.
 */

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
banner.
*/
/* **************************************************************************** */
/* **************************************************************************** */
/* Section: Data Types                                                          */
/* **************************************************************************** */
/* **************************************************************************** */

/*  A brief description of a section can be given directly below the section
banner.
*/
typedef struct{
	uint8_t master_on_bus:1;
	uint8_t slave_on_bus:1;
	uint8_t error_int:1;
}st_i2cm_intset;

#define	STANDARD_MODE  0U  	/* 100KHz ~ 400KHz */
#define	FAST_MODE_PLUS 1U 	/* up to 1MHz */
#define	HIGH_SPEED_MODE 2U 	/* up to 3U_(2).4MHz */

#define I2CMDRIVER_ENABLE_WRITEREAD 	TRUE
#define I2CMDRIVER_ENABLE_READ	FALSE

typedef struct{
	/* Device address */
	uint32_t addr;
	/* Device speed mode */
	uint32_t speed;
	/* Real SCL baudrate, KHz base.*/
	uint32_t baudrate;
	/* SERCOM "N" */
	en_i2c_channel channel;
	/* Interrupt enable */
	st_i2cm_intset inte;
	/* Operating funtions */
	SERCOM_I2C_CALLBACK callback;
}st_i2c_master_config;

/* **************************************************************************** */
/* **************************************************************************** */
/* Section: Interface Functions                                                 */
/* **************************************************************************** */
/* **************************************************************************** */

/*  A brief description of a section can be given directly below the section
banner.
*/

bool master_i2c_init(st_i2c_master_config *ptdConfig);
bool master_i2c_start(en_i2c_channel eCh);
bool master_i2c_stop(en_i2c_channel eCh);
#if I2CMDRIVER_ENABLE_WRITEREAD
bool master_i2c_writeread(st_i2c_master_config *ptdDev, uint8_t *pu8WBuf, uint32_t u32Wlen, uint8_t *pu8RBuf, uint32_t u32Rlen);
#endif
bool master_i2c_transmitte(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Wlen);
bool master_i2c_interrupt(st_i2c_master_config *ptdDev);
#if I2CMDRIVER_ENABLE_READ
bool master_i2c_read(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Rlen);
#endif
#if 0
uint16_t get_master_i2c_status(en_i2c_channel eCh);
#endif
    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_SLAVE_I2C_H_ */

/* *****************************************************************************
 End of File
 */

