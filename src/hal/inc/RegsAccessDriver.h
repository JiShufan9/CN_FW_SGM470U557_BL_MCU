/******************************************************************************
;       Program		: RegsAccessDriver.h
;       Function	: Declare and Define Registers Access Parameters
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 04 / 12
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef REGSACCESSDRIVER_H
#define REGSACCESSDRIVER_H
/*---------------------------- Include Library -------------------------------*/
#include "main.h"
/*---------------------------- MACRO API -------------------------------------*/
#define		RegsAccessDriver_Irq_Disable()		__disable_irq()
#define		RegsAccessDriver_Irq_Enable()		__enable_irq()
/*---------------------------- Define Constant -------------------------------*/
#define REGS_SYS_RST	((rstc_registers_t*)0x40000c00)               /* brief RSTC_REGS Registers Address */
/*---------------------------- Define Constant -------------------------------*/
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t RegsAccessDriver_System_Reset_RCAUSE_Get(void);
#endif
