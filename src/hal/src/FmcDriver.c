/******************************************************************************
;       Program		: FmcDriver.c
;       Function	: Siumlate EEPROM Function and Flash by NVMCTRL.
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2020 / 07 / 07 
;       Author		: Fenderson Lu
;       Describe	: 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "hal/inc/FmcDriver.h"
/*---------------------------- Declare Variable -----------------------------*/
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Init(NvmCtrl_Config_ts *tsInitConfig)
;	Function Description	:	Initializes Eeprom Function.
;	Parameters				:	[tsInitConfig] - Reference NvmCtrl_Config_ts data structure definition.
;												(1) u8ReadWaitStates : Default is 3, these bits control the number of wait states for a read operation.
;												(2) u8Status : Check status is finish.
;	Return Values			:	Return config setting status
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Init(NvmCtrl_Config_ts *tsInitConfig)
{
	return NvmCtrl_Initialize(tsInitConfig);
}

/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Busy_Status_Get(void)
;	Function Description	:	Check EEPROM busy status.
;	Parameters				:	None.
;	Return Values			:	Return busy status.
;	Source ID				:
******************************************************************************/
#if 0
uint8_t FmcDriver_Busy_Status_Get(void)
{
	return NvmCtrl_IsBusy_Get();
}
#endif
#if 0
/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Region_Lock(Eeprom_Region_Lock_ts *tsLockRegion)
;	Function Description	:	Locks the region containing the address location.
;	Parameters				:	[tsLockRegion] - Reference Eeprom_Region_Lock_ts data structure definition.
;												(1) u32Addr : Set lock start address.
;												(2) u8Status : Check status is finish.
;	Return Values			:	Return lock status.
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Region_Lock(Eeprom_Region_Lock_ts *tsLockRegion)
{
	return NvmCtrl_RegionLock(tsLockRegion);
}
#endif
/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Region_Unlock(Eeprom_Region_Unlock_ts *tsUnlockRegion)
;	Function Description	:	Unlocks the region containing the address location.
;	Parameters				:	[tsUnlockRegion] - Reference Eeprom_Region_Unlock_ts data structure definition.
;												 (1) u32Addr : Set unlock start address.
;												 (2) u8Status : Check status is finish.
;	Return Values			:	Return unlock status.
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Region_Unlock(Eeprom_Region_Unlock_ts *tsUnlockRegion)
{
	return NvmCtrl_RegionUnlock(tsUnlockRegion);
}

/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Flash_Read(Flash_Read_ts *tsFlashRead)
;	Function Description	:	Read N byte data in the flash.
;	Parameters				:	[tsFlashRead] - Reference Flash_Read_ts data structure definition.
;												(1) u32Addr : Set start address.
;												(2) u32Length : Read data length.
;												(3) u32Data : The buffer of receive data. 
;												(4) u8Status : Check process is busy or finish.
;	Return Values			:	Return read status.
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Flash_Read(Flash_Read_ts *tsFlashRead)
{
	return NvmCtrl_Read(tsFlashRead);
}

/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Flash_Page_Write(Flash_Page_Write_ts *tsFlashWrite)
;	Function Description	:	Writes the contents of the page buffer to the page addressed in the flash.
;	Parameters				:	[tsFlashWrite] - Reference Flash_Page_Write_ts data structure definition.
;												(1) u32Addr : Set start address.
;												(2) u32Data : The buffer of transmit data. 
;												(3) u8Status : Check process is busy or finish.
;	Return Values			:	Return write status.
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Flash_Page_Write(Flash_Page_Write_ts *tsFlashWrite)
{
	return NvmCtrl_PageWrite(tsFlashWrite);
}

/******************************************************************************
;	Function Name			:	uint8_t FmcDriver_Flash_Row_Erase(Flash_Row_Erase_ts *tsFlashErase)
;	Function Description	:	Erased the row addressed in the flash, the row size are 256 Bytes.
;	Parameters				:	[tsFlashErase] - Reference Flash_Row_Erase_ts data structure definition.
;												(1) u32Addr : Set start address. 
;												(2) u8Status : Check process if busy or finish.
;	Return Values			:	Return erase status.
;	Source ID				:
******************************************************************************/
uint8_t FmcDriver_Flash_Row_Erase(Flash_Row_Erase_ts *tsFlashErase)
{
	return NvmCtrl_RowErase(tsFlashErase);
}
/*---------------------------------------------------------------------------*/

