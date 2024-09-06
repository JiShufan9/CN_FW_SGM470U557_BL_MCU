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

#define SOURCE_IC_TOTAL_NUMBER          2U

#define CMD1_P0     0x10U /* Voltage, I/F, Resolution, TP_SYNC */
#define CMD1_P1     0x11U /* LUT_R (Target) */
#define CMD1_P2     0x12U /* LUT_R (Target) */
#define CMD1_P3     0x13U /* LUT_G (Target) */
#define CMD1_P4     0x14U /* LUT_G (Target) */
#define CMD1_P5     0x15U /* LUT_B (Target) */
#define CMD1_P6     0x16U /* LUT_B (Target) */
#define CMD1_P7     0x17U /* Digital Gamma Positive (Target) */
#define CMD1_P8     0x18U /* Digital Gamma Positive (Target) */
#define CMD1_P9     0x19U /* Digital Gamma Negative (Target) */
#define CMD1_PA     0x1AU /* Digital Gamma Negative (Target) */
#define CMD1_PZ     0x7FU /* User ID */
#define CMD1_PB     0x1BU /* LUT_R (Current) */
#define CMD1_PC     0x1CU /* LUT_R (Current) */
#define CMD1_PD     0x1DU /* LUT_G (Current) */
#define CMD1_PE     0x1EU /* LUT_G (Current) */
#define CMD1_PF     0x1FU /* LUT_B (Current) */
#define CMD1_PG     0x30U /* LUT_B (Current) */
#define CMD1_PH     0x31U /* Digital Gamma Positive (Current) */
#define CMD1_PI     0x32U /* Digital Gamma Positive (Current) */
#define CMD1_PJ     0x33U /* Digital Gamma Negative (Current) */
#define CMD1_PK     0x34U /* Digital Gamma Negative (Current) */
#define CMD2_P0     0x20U /* GRB, STBYB, BIST, Temperature Compensation */
#define CMD2_P1     0x21U /* Source, I/F Control */
#define CMD2_P2     0x22U /* ASIL */
#define CMD2_P3     0x23U /* ASIL, Power Sequence */
#define CMD2_P4     0x24U /* CGOUT DRIVING */
#define CMD2_PB     0x2BU /* Others, Auto Check CRC */
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
uint8_t SourceIcM_ReadVersionInfo(uint8_t *result);
uint8_t SourceIcM_ReadFlashCrcInd(uint8_t *result);
uint8_t SourceIcM_EnterExtFlsBypassMode(void);
uint8_t SourceIcM_ExitExtFlsBypassMode(void);

#endif
#endif
