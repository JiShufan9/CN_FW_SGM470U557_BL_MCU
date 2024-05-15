/******************************************************************************
;       Program		: WatchDogApp.c
;       Function	: Monitor MCU System
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 04
;       Author		: Fenderson Lu
;       Describe 	: Watchdog reset period is WDT_16384_CLK, WDT_1KHz * 16384 = 16 second.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/WatchDogApp.h"
#include "hal/inc/hal_wdt.h"

/*---------------------------- Declare Global Variable ----------------------*/
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t WatchDogApp_Initial(uint8_t u8Active)
;       Function Description	:	WDG initial
;       Parameters				:	void
;       Return Values			:	reutrn enable/disable success or not
;		Source ID				:	SGM_BL_WDT-001
******************************************************************************/
uint8_t WatchDogApp_Initial(uint8_t u8Active)
{
    uint8_t u8Return;
    
    if (u8Active == (uint8_t)ENABLE)
    {
        u8Return = HAL_WDT_Init();
    }
    else
    {
        u8Return = HAL_WDT_DeInit();
    }
    return u8Return;
}

/******************************************************************************
;       Function Name			:	uint8_t WatchDogApp_Clean(uint8_t u8Nothing)
;       Function Description	:	Clear WDG counter
;       Parameters				:	u8Nothing
;       Return Values			:	reutrn clean success or not
;		Source ID				:	SGM_BL_WDT-002
******************************************************************************/
uint8_t WatchDogApp_Clean(uint8_t u8mode)
{
    switch(u8mode)
    {
        case MODE_Clear:        
            (void)HAL_WDT_Clear();
        break;
        case MODE_ClearWithoutSync:        
            (void)HAL_WDT_ClearWithoutSync();
        break;
        default:
				/* NOTHING */
		break;
    }
    return u8mode;
}
/*---------------------------------------------------------------------------*/
