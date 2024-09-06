/* ************************************************************************** 
;        Program    :   .h
;        Function   :   
;        chip       :   
;        clock      :   
;        Date       :   2024 / 05 / 29
;        Author     :   chenaoli
;        Description:      
;    
 *****************************************************************************/

#ifndef __SOURCE_IC_EXT_FLASH_UPDATE_H__
#define __SOURCE_IC_EXT_FLASH_UPDATE_H__

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "main.h"

#define SOURCE_IC_EXT_FLASH_UPDATE_CLASS_EN          ENABLE_ON
#if (SOURCE_IC_EXT_FLASH_UPDATE_CLASS_EN == ENABLE_ON)
/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define NOT_CHANGE_WPC_DATA_EN      TRUE
#define SRC_IC_UPDATE_READ_BACK_CHECK_FUNC  ENABLE_ON

#define SIZE_SOURCE_IC_FW    (1U * 1024U)
#define SOURCE_IC_EXT_FLS_BLOCK_SIZE  4096U
#define SRC_EXT_FLS_READ_BACK_BUF_LEN      64U

#define WPC_DATA_START_ADDR      0x14DU
#define WPC_DATA_LEN       (0x1CAU - WPC_DATA_START_ADDR + 1U)
#define WPC_CRC_START_ADDR  0x3F7U
#define WPC_CRC_LEN       1U


/* ************************************************************************** */
/* Section: Enum                                                              */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Struct Typedef                                                    */
/* ************************************************************************** */



/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */



/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
uint8_t SourceIcExtFlashUpdate_EarseFunc(void);
uint8_t SourceIcExtFlashUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf);
uint8_t SourceIcExtFlashUpdate_CheckFunc(uint32_t u32HostCrc);

#endif
#endif
