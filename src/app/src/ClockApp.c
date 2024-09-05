/******************************************************************************
;       Program		: ClockApp.c 
;       Function	: The Main Program
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 04 / 19
;       Author		: Fenderson Lu & Joel Wang
;       Describe 	: Trim code set CAL48M_3V3_POS for MCU Vref.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/ClockApp.h"
/*---------------------------- Declare Global Variable ----------------------*/
static NvmCtrl_Config_ts NvmCtrlInit;
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t ClockApp_Init(uint8_t u8Para)
;       Function Description	:	Initialize system clock.
;       Parameters				:	NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_CLK-001
******************************************************************************/
uint8_t ClockApp_Init(uint8_t u8Para)
{
    SystemClock_InitTypeDef CurrentSystemClockSet;
    SystemClock_GCLKTypeDef CurrentGCLK;

	NvmCtrlInit.u32ReadWaitStates = 2U;
   (void)FmcDriver_Init(&NvmCtrlInit);

    (void)ClockDriver_Initialize(&CurrentSystemClockSet,&CurrentGCLK);
    (void)ClockDriver_EnableHSIOsc(&CurrentSystemClockSet);
    (void)ClockDriver_Enable32KHiAccuOsc(&CurrentSystemClockSet);
    /* SystemClock_EnableLSExternalCrystalOsc(&CurrentSystemClockSet); */
    (void)ClockDriver_EnableGCLKN(&CurrentGCLK,GCLKENABLE0,OSC48M,DIV1);

	/* Configure GCLK Clocks */
    (void)ClockDriver_GCLKToPeri(GCLK_SERCOM0_CORE,GCLKGEN0);           /* I2C Slave */
    (void)ClockDriver_GCLKToPeri(GCLK_SERCOM1_CORE,GCLKGEN0);           /* Debug UART */
	(void)ClockDriver_GCLKToPeri(GCLK_SERCOM2_CORE,GCLKGEN0);           /* Source IC I2C */
    (void)ClockDriver_GCLKToPeri(GCLK_SERCOM5_CORE,GCLKGEN0);       /* Led Driver , I2C , Master */

    (void)ClockDriver_GCLKToPeri(GCLK_ADC0,GCLKGEN0);                   /* Battery Voltage Detection and HW version*/
 
    (void)ClockDriver_EnableAHBClock(&CurrentSystemClockSet);
    MCLK_REGS->MCLK_APBCMASK = ((MCLK_APBCMASK_SERCOM0_Msk) | (MCLK_APBCMASK_SERCOM1_Msk) | (MCLK_APBCMASK_SERCOM2_Msk) | (MCLK_APBCMASK_ADC0_Msk) | (MCLK_APBCMASK_TCC0_Msk) | (MCLK_APBCMASK_SERCOM5_Msk));

    (void)(u8Para);
	return u8Para;
}
/*---------------------------------------------------------------------------*/ 
