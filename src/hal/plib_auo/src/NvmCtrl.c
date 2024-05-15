/******************************************************************************
;       Program		: NvmCtrl.c
;       Function	: Internal EEPROM definition of NVMCTRL (Non-Volatile Memory Controller) and Flash Access Library.
;       Chip		: Microchip SAMC21J18A
;       Clock		: Internal 48MHz
;       Date		: 2020 / 11 / 03
;       Author		: Fenderson Lu
;       Describe	: This file defines the interface for the NVMCTRL library.
;					  It allows user to Program, Erase and lock the on-chip Non Volatile Flash Memory.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "../../hal/plib_auo/inc/NvmCtrl.h"
/*---------------------------- Declare Variable -----------------------------*/
static uint32_t gu32Index;
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_Initialize(NvmCtrl_Config_ts *tsInitConfig)
;	Function Description	:	Initializes NVMCTRL Function.
;	Parameters				:	[tsInitConfig] - Reference NvmCtrl_Config_ts data structure definition.
;												(1) u8ReadWaitStates : Default is 3, these bits control the number of wait states for a read operation.
;												(2) u8Status : Check status is finish.
;	Return Values			:	Return config status
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_Initialize(NvmCtrl_Config_ts *tsInitConfig)
{
	uint32_t u32NvmctrlCtrlbRws;
	nvmctrl_registers_t *tsNvmctrlRegs;
		
	tsNvmctrlRegs = NVMCTRL_REGS;
	u32NvmctrlCtrlbRws = (NVMCTRL_CTRLB_RWS_Msk) & (((*tsInitConfig).u32ReadWaitStates) << (NVMCTRL_CTRLB_RWS_Pos));
	(*tsNvmctrlRegs).NVMCTRL_CTRLB = NVMCTRL_CTRLB_READNOMISSPENALTY | NVMCTRL_CTRLB_SLEEPPRM_WONA | u32NvmctrlCtrlbRws | (NVMCTRL_CTRLB_MANW_Msk);
	(*tsInitConfig).u8Status = (uint8_t)(NVC_FINISH);
	
	(void)(tsInitConfig);
	return (*tsInitConfig).u8Status;	
}

/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_IsBusy_Get(void)
;	Function Description	:	Check EEPROM busy status.
;	Parameters				:	None.
;	Return Values			:	Return busy status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_IsBusy_Get(void)
{
	return ((NVMCTRL_REGS->NVMCTRL_INTFLAG) & (NVMCTRL_INTFLAG_READY_Msk));
}

/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_CacheInvalidate(uint8_t u8Para)
;	Function Description	:	Invalidates all cache lines.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	Return NOTHING
;	Source ID				:
******************************************************************************/
#if 0
uint8_t NvmCtrl_CacheInvalidate(uint8_t u8Para)
{	
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
	(*tsNvmctrlRegs).NVMCTRL_CTRLA = (NVMCTRL_CTRLA_CMD_INVALL) | (NVMCTRL_CTRLA_CMDEX_KEY);
	
	(void)(u8Para);
	return u8Para; 
}
#endif
#if 0
/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_RegionLock(Eeprom_Region_Lock_ts *tsLockRegion)
;	Function Description	:	Locks the region containing the address location.
;	Parameters				:	[tsLockRegion] - Reference Eeprom_Region_Lock_ts data structure definition.
;												(1) u32Addr : Set lock start address.
;												(2) u8Status : Check status is finish.
;	Return Values			:	Return lock status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_RegionLock(Eeprom_Region_Lock_ts *tsLockRegion)
{
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
    (*tsLockRegion).u8Status = (uint8_t)(NVC_FINISH);
    (*tsNvmctrlRegs).NVMCTRL_ADDR = (uint32_t)((*tsLockRegion).u32Addr) >> 1U;		/* Set address and command */
    (*tsNvmctrlRegs).NVMCTRL_CTRLA = (NVMCTRL_CTRLA_CMD_LR_Val) | (NVMCTRL_CTRLA_CMDEX_KEY);
	
	(void)(tsLockRegion);
	return (*tsLockRegion).u8Status;
}
#endif
/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_RegionUnlock(Eeprom_Region_Unlock_ts *tsUnlockRegion)
;	Function Description	:	Unlocks the region containing the address location.
;	Parameters				:	[tsUnlockRegion] - Reference Eeprom_Region_Unlock_ts data structure definition.
;												 (1) u32Addr : Set unlock start address.
;												 (2) u8Status : Check status is finish.
;	Return Values			:	Return unlock status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_RegionUnlock(Eeprom_Region_Unlock_ts *tsUnlockRegion)
{
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
	(*tsUnlockRegion).u8Status = (uint8_t)(NVC_FINISH);    
    (*tsNvmctrlRegs).NVMCTRL_ADDR = (uint32_t)((*tsUnlockRegion).u32Addr) >> 1U;	/* Set address and command */
    (*tsNvmctrlRegs).NVMCTRL_CTRLA = (NVMCTRL_CTRLA_CMD_UR_Val) | (NVMCTRL_CTRLA_CMDEX_KEY);
	
	(void)(tsUnlockRegion);
	return (*tsUnlockRegion).u8Status;
}

/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_Read(Flash_Read_ts *tsFlashRead)
;	Function Description	:	Read N byte data in the flash, read unit are 4 bytes.
;	Parameters				:	[tsFlashRead] - Reference Flash_Read_ts data structure definition.
;												(1) u32Addr : Set start address.
;												(2) u32Length : Read data length.
;												(3) u32Data : The buffer of receive data. 
;												(4) u8Status : Check process is busy or finish.
;	Return Values			:	Return read status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_Read(Flash_Read_ts *tsFlashRead)
{
	uint8_t *paddress = (uint8_t *)((*tsFlashRead).u32Addr);
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
	(*tsFlashRead).u8Status = (uint8_t)(NVC_BUSY);	
	while(((*tsFlashRead).u8Status) == (uint8_t)(NVC_BUSY))
	{
		if(((uint8_t)((*tsNvmctrlRegs).NVMCTRL_INTFLAG) & (uint8_t)(NVMCTRL_INTFLAG_READY_Msk)) == (uint8_t)(NVMCTRL_INTFLAG_READY_Msk))
		{	
			/* Flash is ready */
			for(gu32Index=0U; gu32Index<(*tsFlashRead).u32Length; gu32Index++)		/* Writing 32-bit words in the given address */
			{
				(*tsFlashRead).u32Data[gu32Index] = (*paddress);
				(void)(*paddress++);
			}
			 
			(*tsFlashRead).u8Status = (uint8_t)(NVC_FINISH);	
		}
		else
		{
			/* Flash is busy */
			(*tsFlashRead).u8Status = (uint8_t)(NVC_BUSY);
		}
	}

	(*tsNvmctrlRegs).NVMCTRL_ADDR = (uint32_t)((*tsFlashRead).u32Addr) >> 1U;	/* Set address and command */	
	
	(void)(tsFlashRead);
	return (*tsFlashRead).u8Status;
}

/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_PageWrite(Flash_Page_Write_ts *tsFlashWrite)
;	Function Description	:	Writes the contents of the page buffer to the page addressed in the flash.
;	Parameters				:	[tsFlashWrite] - Reference Flash_Page_Write_ts data structure definition.
;												(1) u32Addr : Set start address.
;												(2) u32Data : The buffer of transmit data. 
;												(3) u8Status : Check process is busy or finish.
;	Return Values			:	Return write status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_PageWrite(Flash_Page_Write_ts *tsFlashWrite)
{
    uint32_t *paddress = (*tsFlashWrite).u32Addr;
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
	(*tsFlashWrite).u8Status = (uint8_t)(NVC_BUSY);
	while(((*tsFlashWrite).u8Status) == (uint8_t)(NVC_BUSY))
	{
		if(((uint8_t)((*tsNvmctrlRegs).NVMCTRL_INTFLAG) & (uint8_t)(NVMCTRL_INTFLAG_READY_Msk)) == (uint8_t)(NVMCTRL_INTFLAG_READY_Msk))
		{	
			/* Flash is ready */
			for(gu32Index=0U; gu32Index<(NVC_FLASH_PAGESIZE/NVC_READ_UNIT); gu32Index++)		/* Writing 32-bit words in the given address */
			{
				*paddress = (*tsFlashWrite).u32Data[gu32Index];
				(void)(*paddress++);
			}
			 
			(*tsFlashWrite).u8Status = (uint8_t)(NVC_FINISH);	
		}
		else
		{
			/* Flash is busy */
			(*tsFlashWrite).u8Status = (uint8_t)(NVC_BUSY);
		}
	}

	(*tsNvmctrlRegs).NVMCTRL_ADDR = (uint32_t)((*tsFlashWrite).u32Addr) >> 1U;		// Set address and command 
	(*tsNvmctrlRegs).NVMCTRL_CTRLA = (NVMCTRL_CTRLA_CMD_WP_Val) | (NVMCTRL_CTRLA_CMDEX_KEY);	

	(void)(tsFlashWrite);
	return (*tsFlashWrite).u8Status;
}

/******************************************************************************
;	Function Name			:	uint8_t NvmCtrl_RowErase(Flash_Row_Erase_ts *tsFlashErase)
;	Function Description	:	Erased the row addressed in the flash, the row size are 256 Bytes.
;	Parameters				:	[tsFlashErase] - Reference Flash_Row_Erase_ts data structure definition.
;												(1) u32Addr : Set start address. 
;												(2) u8Status : Check process if busy or finish.
;	Return Values			:	Return erase status.
;	Source ID				:
******************************************************************************/
uint8_t NvmCtrl_RowErase(Flash_Row_Erase_ts *tsFlashErase)
{    	
	nvmctrl_registers_t *tsNvmctrlRegs;

	tsNvmctrlRegs = NVMCTRL_REGS;
	(*tsFlashErase).u8Status = (uint8_t)(NVC_BUSY);
	while(((*tsFlashErase).u8Status) == (uint8_t)(NVC_BUSY))
	{
		if(((uint8_t)((*tsNvmctrlRegs).NVMCTRL_INTFLAG) & (uint8_t)(NVMCTRL_INTFLAG_READY_Msk)) == (uint8_t)(NVMCTRL_INTFLAG_READY_Msk))
		{	
			/* Flash is ready */
			(*tsFlashErase).u8Status = (uint8_t)(NVC_FINISH);		
		}
		else
		{
			/* Flash is busy */
			(*tsFlashErase).u8Status = (uint8_t)(NVC_BUSY);			
		}
	}

	(*tsNvmctrlRegs).NVMCTRL_ADDR = (uint32_t)((*tsFlashErase).u32Addr) >> 1U;	 // Set address and command 
	(*tsNvmctrlRegs).NVMCTRL_CTRLA = (NVMCTRL_CTRLA_CMD_ER_Val) | (NVMCTRL_CTRLA_CMDEX_KEY);

	(void)(tsFlashErase);
    return (*tsFlashErase).u8Status;
}
/*---------------------------------------------------------------------------*/
