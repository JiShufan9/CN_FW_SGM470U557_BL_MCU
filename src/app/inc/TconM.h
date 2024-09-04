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

#ifndef __TCON_M_H__
#define __TCON_M_H__


#include "main.h"
#define TCON_M_EN   ENABLE_ON
#if (TCON_M_EN == ENABLE_ON)
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define    BURST_MODE_EN   ENABLE_ON
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
uint8_t TconM_WriteByte(uint8_t page, uint8_t address, uint8_t data);
uint8_t TconM_ReadByte(uint8_t page, uint8_t address, uint8_t* readValue);
uint8_t TconM_SetIcAccessKey(void);
uint8_t TconM_SetMagic(void);
uint8_t TconM_ReleasePowerDown(void);
uint8_t TconM_PowerDown(void);
uint8_t TconM_ChipErase(void);
uint8_t TconM_SectorErase(uint32_t u32SectorAddr);
uint8_t TconM_WriteEnable(void);
uint8_t TconM_CheckStatus(uint8_t checkBit, uint8_t expectedValue);
uint8_t TconM_ReadStatus(uint8_t* returnByte);
uint8_t TconM_WriteStatus(uint8_t data);
uint8_t TconM_Program(uint8_t* binBuffer, uint32_t addr, uint32_t size);
uint8_t TconM_ProgramData(uint8_t* binBuffer, uint32_t addr, uint32_t size);
uint8_t TconM_Read(uint32_t addr, uint32_t size, uint8_t* buffer);


#endif
#endif

