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

#ifndef __TCON_UPDATE_H__
#define __TCON_UPDATE_H__

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "main.h"

#define TCON_UPDATE_CLASS_EN          ENABLE_ON
#if (TCON_UPDATE_CLASS_EN == ENABLE_ON)
/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define TCON_UPDATE_ERASE_WHEN_WRITE_EN     ENABLE_ON
#define TCON_UPDATE_READ_BACK_CHECK_EN      ENABLE_ON

#define TCON_FW_CRC_START_ADDR  0U
#define TCON_FW_START_ADDR  2U
#define SIZE_TCON_FW    (512U * 1024U)
#define TCON_EXT_FLS_BLOCK_SIZE 4096U
#define TCON_WRITE_BUF_LEN      64U
#define TCON_READ_BACK_BUF_LEN  64U
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
uint8_t TconUpdate_EarseFunc(void);
uint8_t TconUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf);
uint8_t TconUpdate_CheckFunc(uint32_t u32HostCrc);

#endif
#endif
