/******************************************************************************
;       Program		: FunApp.h
;       Function	: Declare Scenario Functions
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 07 / 20
;       Author		: Joel Wang
******************************************************************************/
#ifndef FunApp_H
#define FunApp_H
/*---------------------------- Inculde Library ------------------------------*/
#include "cmsis_gcc.h"
/*---------------------------- Define Constant ------------------------------*/
#define 	APP_START_ADDR		ADDR_APP_START
#define		ADDR_VECTOR_RST		(APP_START_ADDR + 4U) 
#define		FAIL_ADDR			0xFFFFFFFFU

#define		BOOT_KEY_0			((void*)0x20003C00)		/* Set SRAM Address for boot key 0 */
#define		BOOT_KEY_1			((void*)0x20003C02)		/* Set SRAM Address for boot key 1 */
#define		SESSION_KEY			((void*)0x20003C04)		/* Set SRAM Address for session key */

/* Boot Access Key */
#define		CHK_ACCESS_KEY_0			0x55AAU
#define		CHK_ACCESS_KEY_1			0x33CCU
#define		CHK_SESSION_KEY				0xFFFFU
#define		CHK_SESSION_KEY_2			0x0000U
#define		CLR_KEYS					0x0000U

#define		ASM_NOP()			__NOP()
#define		ASM_SYS_RESET()	        (__NVIC_SystemReset())
#define		ASM_SET_MSP(u32Msp)	(__set_MSP(u32Msp))
#define		ASM_VECTOR_RESET(u32ResetVector)	asm("bx %0"::"r" (u32ResetVector))

#define		SIZE_ACCESS_KEY		6U

#define		DELAY_CLK_48MHZ		9500U	/* Based on 1ms, system clock 48MHz */

enum DelayMode{
	MODE_LOOP = 0U,
	MODE_SYSTICK = 0U,
	MODE_ISR = 1U
};

enum CounterPara{
	CNT_DONE = 0U,
	CNT_REDUCE = 1U		
};
/*---------------------------- Support Function -----------------------------*/
#define		FunApp_PAC_Irq_Disable(u8Irq)	(NVIC_DisableIRQ(u8Irq))
/*---------------------------- Declare Function -----------------------------*/
extern bool FunApp_Down_Counter(uint32_t *u32CountValues);
extern bool FunApp_Delay_Millisecond(uint32_t u32DelayTime, uint8_t u8Mode);
extern uint8_t FunApp_Startup_Check(void);
extern uint8_t FunApp_Irq_Disable(void);
extern uint8_t FunApp_Nvic_Init(void);
extern bool FunApp_Crc32FailFlag_Get(void);
#endif

