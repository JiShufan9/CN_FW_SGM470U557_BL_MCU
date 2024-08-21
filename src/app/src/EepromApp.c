/****************************************************************************************
;       Program		: EepromApp.c
;       Function	: Read Write EEprom
;       Date		: 2020 / 07 / 09
;       Author		: Jack.Wu
;       Describe	: Saved Data (Wakeup count / Reset / WDG) into eeprom
*****************************************************************************************/


#include "app/inc/EepromApp.h"
#include "hal/inc/RegsAccessDriver.h"
#include "main.h"

static NvmCtrl_Config_ts tsNvmCtrl;
static Eeprom_Page_Write_ts tsAppEepromWrite;
static Eeprom_Row_Erase_ts tsAppEepromErase;        



static uint32_t gu32EepromWriteBuff[NVC_ARRAY_SIZE] = {
0x10111213U, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 
0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU,
0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 0xffffffffU, 
0xffffffffU
};




/******************************************************************************
;	Function Name			:	void EepromApp_Initial(void)
;	Function Description	:	Eeprom Initial
;	Parameters				:	tsNvmCtrl
;	Return Values			:	tsNvmCtrl
******************************************************************************/
void EepromApp_Initial(void)
{
    tsNvmCtrl.u32ReadWaitStates = EEPROM_READ_WAIT_CLOCK_TIME;
    (void) FmcDriver_Init(&tsNvmCtrl);
}


/******************************************************************************
;	Function Name			:	uint32_t EepromApp_Read(uint32_t u32AddrOffset, uint32_t u32Len)
;	Function Description	:	Read Eeprom data
;	Parameters				:	tsAppEepromRead
;	Return Values			:	tsAppEepromRead
******************************************************************************/
uint32_t EepromApp_Read(uint32_t u32AddrOffset, uint32_t u32Len)
{
    Eeprom_Read_ts tsAppEepromRead;
    uint32_t u32Return;
    RegsAccessDriver_Irq_Disable();    
    tsAppEepromRead.u32Addr = (uint32_t*)(NVC_RWWEEPROM_START_ADDRESS + u32AddrOffset);
    tsAppEepromRead.u32Length = u32Len;
    (void) FmcDriver_Eeprom_Read(&tsAppEepromRead);
    RegsAccessDriver_Irq_Enable();

    u32Return = tsAppEepromRead.u32Data[DATA_0];
    return u32Return;
}


/******************************************************************************
;	Function Name			:	void EepromApp_Write(uint32_t u32AddrOffset, uint32_t u32Data)
;	Function Description	:	Write EEprom
;	Parameters				:	tsAppEepromWrite
;	Return Values			:	tsAppEepromWrite
******************************************************************************/
void EepromApp_Write(uint32_t u32AddrOffset, uint32_t u32Data)
{
    RegsAccessDriver_Irq_Disable();
    gu32EepromWriteBuff[DATA_0] = u32Data;
    tsAppEepromWrite.u32Addr = (uint32_t *)(NVC_RWWEEPROM_START_ADDRESS + u32AddrOffset);
    tsAppEepromWrite.u32Data = &gu32EepromWriteBuff[DATA_0];
    (void) FmcDriver_Eeprom_Page_Write(&tsAppEepromWrite);
    RegsAccessDriver_Irq_Enable();
}



/******************************************************************************
;	Function Name			:	void EepromApp_Erase(uint32_t u32AddrOffset)
;	Function Description	:	Erase EEprom
;	Parameters				:	u32AddrOffset
;	Return Values			:	tsAppEepromErase
******************************************************************************/
void EepromApp_Erase(uint32_t u32AddrOffset)
{
    RegsAccessDriver_Irq_Disable();
    tsAppEepromErase.u32Addr = (uint32_t)(NVC_RWWEEPROM_START_ADDRESS + u32AddrOffset);
    (void) FmcDriver_Eeprom_Row_Erase(&tsAppEepromErase);
    RegsAccessDriver_Irq_Enable();
}

