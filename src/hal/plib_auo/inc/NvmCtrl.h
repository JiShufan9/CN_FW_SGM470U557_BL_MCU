/******************************************************************************
;       Program		: NvmCtrl.h
;       Function	: Interface Internal EEPROM definition of NVMCTRL (Non-Volatile Memory Controller) and Flash Access Library.
;       Chip		: Microchip SAMC21J17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 03 / 29
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef NvmCtrl_H
#define NvmCtrl_H
/*---------------------------- Include Library -------------------------------*/
#include "main.h"
/*---------------------------- Define Constant -------------------------------*/
#define NVC_FLASH_START_ADDRESS			0x00000000U
#define NVC_FLASH_SIZE					0x20000U	/*0x40000U = 256KB, 0x20000U = 128KB */
#define NVC_FLASH_PAGESIZE				64U
#define NVC_FLASH_ROWSIZE				256U

#define NVC_RWWEEPROM_START_ADDRESS    0x00400000U
#define NVC_RWWEEPROM_SIZE             0x2000U
#define NVC_RWWEEPROM_PAGESIZE         64U
#define NVC_RWWEEPROM_ROWSIZE          256U

#define	NVC_READ_UNIT					4U
#define NVC_ARRAY_SIZE                  16U
/*---------------------------- Declare Enum Structure -------------------------*/
enum NvcFunStatus
{
	NVC_FINISH = 0U,
	NVC_FAIL = 1U,
	NVC_WAIT = 2U, 
	NVC_BUSY = 3U,
};
/*---------------------------- Declare Data Structure -------------------------*/
typedef struct
{
	uint32_t u32ReadWaitStates;	/* 0 ~ 15 */
	uint8_t u8Status;
}NvmCtrl_Config_ts;

typedef struct
{
	uint32_t *u32Addr;
	uint32_t u32Length;
	uint32_t u32Data[NVC_RWWEEPROM_ROWSIZE];
	uint8_t u8Status;
}Eeprom_Read_ts;

typedef struct
{
	uint32_t *u32Addr;
	uint32_t *u32Data;		/* A page is 64B */
	uint8_t u8Status;	
}Eeprom_Page_Write_ts;

typedef struct
{
	uint32_t u32Addr;
	uint8_t u8Status;
}Eeprom_Row_Erase_ts;

typedef struct
{
	uint32_t u32Addr;
	uint8_t u8Status;
}Eeprom_Region_Lock_ts;

typedef struct
{
	uint32_t u32Addr;
	uint8_t u8Status;	
}Eeprom_Region_Unlock_ts;

typedef struct
{
	uint32_t *u32Addr;
	uint32_t u32Length;
	uint32_t u32Data[NVC_FLASH_ROWSIZE];
	uint8_t u8Status;
}Flash_Read_ts;

typedef struct
{
	uint32_t *u32Addr;
	uint32_t *u32Data;		/* A page is 64B */
	uint8_t u8Status;	
}Flash_Page_Write_ts;

typedef struct
{
	uint32_t u32Addr;
	uint8_t u8Status;
}Flash_Row_Erase_ts;
/*---------------------------- Declare Function -------------------------------*/
extern uint8_t NvmCtrl_Initialize(NvmCtrl_Config_ts *tsInitConfig);

uint8_t NvmCtrl_RWWEEPROM_Read(Eeprom_Read_ts *tsEepromRead);
uint8_t NvmCtrl_RWWEEPROM_PageWrite(Eeprom_Page_Write_ts *tsEepromWrite);
uint8_t NvmCtrl_RWWEEPROM_RowErase(Eeprom_Row_Erase_ts *tsEepromErase);
#if 0
extern uint8_t NvmCtrl_CacheInvalidate(uint8_t u8Para);
#endif
extern uint8_t NvmCtrl_IsBusy_Get(void);
extern uint8_t NvmCtrl_RegionLock(Eeprom_Region_Lock_ts *tsLockRegion);
extern uint8_t NvmCtrl_RegionUnlock(Eeprom_Region_Unlock_ts *tsUnlockRegion);
extern uint8_t NvmCtrl_Read(Flash_Read_ts *tsFlashRead);
extern uint8_t NvmCtrl_PageWrite(Flash_Page_Write_ts *tsFlashWrite);
extern uint8_t NvmCtrl_RowErase(Flash_Row_Erase_ts *tsFlashErase);
#endif
