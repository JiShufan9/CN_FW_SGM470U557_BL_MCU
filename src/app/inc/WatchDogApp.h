/******************************************************************************
;       Program		: WatchDogApp.h
;       Function	: Declare and Define Watchdog Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 03 / 12
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef WATCHDOGAPP_H
#define WATCHDOGAPP_H
/*---------------------------- Define Constant -------------------------------*/
enum WDTMode{
	MODE_Clear = 0U,
	MODE_ClearWithoutSync = 1U
};
/*---------------------------- Support Code Gen Function ---------------------*/

/*---------------------------- Declare Function ------------------------------*/
extern uint8_t WatchDogApp_Initial(uint8_t u8Active);
extern uint8_t WatchDogApp_Clean(uint8_t u8mode);
#endif

