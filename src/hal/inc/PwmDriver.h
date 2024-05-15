/******************************************************************************
;       Program		: PwmDriver.h
;       Function	: Declare and Define TCCx PWM 
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 04 / 09
;       Author		: Fenderson Lu & Sunny Kuo
******************************************************************************/
#ifndef PWMDRIVER_H
#define PWMDRIVER_H
/*---------------------------- Include Library -------------------------------*/
#include "main.h"
#include "peripheral/tcc/plib_tcc2.h"
#include "peripheral/tcc/plib_tcc_common.h"
/*---------------------------- Define Constant -------------------------------*/
#define	REGS_PWM_0		((tcc_registers_t*)0x42002400)		/* brief TCC0_REGS Registers Address */
#define	REGS_PWM_1		((tcc_registers_t*)0x42002800)		/* brief TCC1_REGS Registers Address */
#define	REGS_PWM_2		((tcc_registers_t*)0x42002c00)		/* brief TCC2_REGS Registers Address */

#define	RESOLUTION_24_BITS		0xFFFFFFU	/* 24-bits */	
#define	RESOLUTION_16_BITS		0xFFFFU		/* 16-bits */
/*---------------------------- Delcare Enum -----------------------------------*/
enum Channel
{
 	CH_0,
 	CH_1,
 	CH_2,
 	CH_3,
 	CH_4,
 	CH_5,
 	CH_6,
 	CH_7 
};

enum TCCxPWM
{
	S_PWM0,
	S_PWM1,
	S_PWM2
};

enum PwmStatus
{
	PWM_PROCESS_FINISH,
	PWM_STATUS_BUSY,
	PWM_ABNORMAL,
	PWM_PRE_DIV_ERROR	
};

enum PwmClockPrescaler
{
	PWM_PRE_DIV_1,
	PWM_PRE_DIV_2,
	PWM_PRE_DIV_4,
	PWM_PRE_DIV_8,	
	PWM_PRE_DIV_16,
	PWM_PRE_DIV_64,
	PWM_PRE_DIV_256,
	PWM_PRE_DIV_1024
};

enum TCCxCCBUFxRegs
{
	TCC_CCBUF0 = 0x70U,
	TCC_CCBUF1 = 0x74U,
	TCC_CCBUF2 = 0x78U,
	TCC_CCBUF3 = 0x7CU
};
/*---------------------------- Support MACRO ----------------------------------*/
#define		Irq_Enable(IRQn)		NVIC_EnableIRQ(IRQn)	
#define		Irq_Disable(IRQn)		NVIC_DisableIRQ(IRQn)	
/*---------------------------- Declare Function -------------------------------*/
#endif

