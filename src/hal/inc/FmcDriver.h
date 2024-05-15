/******************************************************************************
;       Program		: FmcDriver.h
;       Function	: Declare and Define Internal EEPROM and Flash API.
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2020 / 07 / 01
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef FmcDriver_H
#define FmcDriver_H
/*---------------------------- Include Library -------------------------------*/
#include "hal/plib_auo/inc/NvmCtrl.h"
/*---------------------------- Define Constant -------------------------------*/
/*---------------------------- Declare Enum Structure ------------------------*/
/*---------------------------- Declare Data Structure ------------------------*/
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t FmcDriver_Init(NvmCtrl_Config_ts *tsInitConfig);
#if 0
extern uint8_t FmcDriver_Busy_Status_Get(void);
#endif
#if 0
extern uint8_t FmcDriver_Region_Lock(Eeprom_Region_Lock_ts *tsLockRegion);
#endif
extern uint8_t FmcDriver_Region_Unlock(Eeprom_Region_Unlock_ts *tsUnlockRegion);
#if 0
extern uint16_t FmcDriver_Error_Status_Get(void);
#endif
#if 0
extern uint8_t FmcDriver_Eeprom_Read(Eeprom_Read_ts *tsEepromRead);
#endif
#if 0
extern uint8_t FmcDriver_Eeprom_Page_Write(Eeprom_Page_Write_ts *tsEepromWrite);
#endif
#if 0
extern uint8_t FmcDriver_Eeprom_Row_Erase(Eeprom_Row_Erase_ts *tsEepromErase);
#endif
extern uint8_t FmcDriver_Flash_Read(Flash_Read_ts *tsFlashRead);
extern uint8_t FmcDriver_Flash_Page_Write(Flash_Page_Write_ts *tsFlashWrite);
extern uint8_t FmcDriver_Flash_Row_Erase(Flash_Row_Erase_ts *tsFlashErase);
#endif


