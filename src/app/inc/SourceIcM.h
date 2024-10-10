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

#ifndef __SOURCE_IC_M_H__
#define __SOURCE_IC_M_H__

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "main.h"

#define SOURCE_IC_M_CLASS_EN          ENABLE
#if (SOURCE_IC_M_CLASS_EN == ENABLE)
/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define SOURCE_IC_IDX_MASTER        0U
#define SOURCE_IC_IDX_SLAVE         1U
#define SOURCE_IC_IDX_ALL         3U

#define SOURCE_IC_TOTAL_NUMBER          2U

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
// void SourceIcM_MainFunction(void);
// uint8_t SourceIcM_ReadDtc(uint8_t idx, uint8_t *result);
uint8_t SourceIcM_WriteReg(uint8_t idx,uint8_t page,uint8_t addr,uint8_t value);
uint8_t SourceIcM_ReadReg(uint8_t idx,uint8_t page,uint8_t addr,uint8_t *result,uint8_t len);
uint8_t SourceIcM_EnterExtFlsBypassMode(uint8_t idx);
uint8_t SourceIcM_ExitExtFlsBypassMode(uint8_t idx);

#endif
#endif
