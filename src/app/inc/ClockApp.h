/******************************************************************************
;       Program		: ClockApp.h
;       Function	: Declare & Variable System Clock Function 
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2020 / 08 / 25
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef CLOCKAPP_H
#define CLOCKAPP_H
#include "hal/inc/ClockDriver.h"
#include "hal/inc/FmcDriver.h"
#include "app/inc/MainApp.h"
#include "app/inc/PinIOApp.h"
/*---------------------------- Switch Support Function ----------------------*/
/*---------------------------- Define Constant ------------------------------*/

/*---------------------------- Declare Enum ---------------------------------*/
/*---------------------------- Declare Function -----------------------------*/
extern uint8_t ClockApp_Init(uint8_t u8Para);
#endif

