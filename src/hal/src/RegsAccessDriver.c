/******************************************************************************
;       Program		: RegsAccessDriver.c
;       Function	: Declear and Define Registers Access API Function
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2020 / 11 / 03
;       Author		: Fenderson Lu
;       Describe	: 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "hal/inc/RegsAccessDriver.h"
#include "cmsis_gcc.h"
/*---------------------------- Declare Variable -----------------------------*/
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t RegsAccessDriver_System_Reset_RCAUSE_Get(void)
;       Function Description	:	Get system reset registers status.
;       Parameters				:	None.
;       Return Values			:	Return system reset status.
;		Source ID				:
******************************************************************************/
uint8_t RegsAccessDriver_System_Reset_RCAUSE_Get(void)
{
	return 	(uint8_t)(REGS_SYS_RST->RSTC_RCAUSE) & (uint8_t)(RSTC_RCAUSE_Msk);
}
/*---------------------------------------------------------------------------*/
