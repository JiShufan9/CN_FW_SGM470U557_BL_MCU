/******************************************************************************
;       Program		: FlashRwApp.c
;       Function	: Declear Flash R/W Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 05 / 04
;       Author		: Fenderson Lu & Joel Wang
;       Describe	: Use Microchip NVMCTRL (Non-Volatile Memory Controller) 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/FlashRwApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "hal/inc/FmcDriver.h"
#include "hal/inc/RegsAccessDriver.h"
/*---------------------------- Declare External Var -------------------------*/
static Flash_Page_Write_ts tsFlashPageW;
static Flash_Read_ts tsFlashR;
static Flash_Row_Erase_ts tsFlashE;
#if FLASH_RW_APP_LOCK_TEST
static Eeprom_Region_Lock_ts	tsNvmLock;		/* JOEL: for Test */
#endif
static Eeprom_Region_Unlock_ts	tsNvmUnlock;	/* JOEL: for Test */
static uint32_t gu32TransferBuff[NVC_RWWEEPROM_PAGESIZE/NVC_READ_UNIT] = {0U};
static uint32_t gu32Cnt; 
static uint8_t gu8FidmVerTable[SIZE_FIDM_VER] = {0U};	
#if WRITE_COUNT_TEST
static uint16_t u16WriteTimes = 0U; 
#endif
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	static bool FlashRwApp_32Bits_Buff_Transfer(uint8_t *pu8Buff)
;       Function Description	:	Transfer data from 8 bits to 32 bits.
;       Parameters				:	[*pu8Buff] - Input data.
;       Return Values			:	true
;		Source ID				:	GM_BL_FLASHRW-001
******************************************************************************/
static bool FlashRwApp_32Bits_Buff_Transfer(uint8_t *pu8Buff)
{
	uint8_t u8Index; 
	uint32_t u32Temp = 0U;

	for(u8Index=0U;u8Index<NVC_FLASH_PAGESIZE;u8Index++)
	{
		/* 0xH_M1_M0_L */
		if((u8Index % NVC_READ_UNIT) == (uint8_t)(BYTE_L))
		{
			u32Temp |= (uint32_t)(*(pu8Buff + u8Index));
		}
		else if((u8Index % NVC_READ_UNIT)  == (uint8_t)(BYTE_M0))
		{
			u32Temp |= (uint32_t)(*(pu8Buff + u8Index))<< (uint32_t)(SHIFT_BIT_8);
		}
		else if((u8Index % NVC_READ_UNIT)  == (uint8_t)(BYTE_M1))
		{
			u32Temp |= (uint32_t)(*(pu8Buff + u8Index))<< (uint32_t)(SHIFT_BIT_16);		
		}
		else 
		{
			/* (u8Index % NVC_READ_UNIT)  == (uint8_t)(BYTE_H) */
			gu32TransferBuff[u8Index/NVC_READ_UNIT] = u32Temp | ((uint32_t)(*(pu8Buff + u8Index)) << (uint32_t)(SHIFT_BIT_24));
            u32Temp = 0U;
		}
	}
	
	(void)(*pu8Buff);
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t FlashRwApp_64B_Page_Write(uint32_t u32StartAddr, uint8_t *pu8DataBuff)
;       Function Description	:	Write a page of 64 bytes to flash memory.
;       Parameters				:	[u32StartAddr] - Set start address. 
;									[*pu8DataBuff] - Input data.
;       Return Values			:	Return status.
;									(1) NVC_FINISH
;									(2) NVC_BUSY
;									(3) NVC_FAIL
;		Source ID				:	GM_BL_FLASHRW-002
******************************************************************************/
uint8_t FlashRwApp_64B_Page_Write(uint32_t u32StartAddr, uint8_t *pu8DataBuff)
{
    #if WRITE_COUNT_TEST
    u16WriteTimes ++;
    Uart1App_String_Value_Show("Write number of pages = ", u16WriteTimes, (uint8_t)(SHOW_DEC));
    #endif

	uint8_t u8Status;
	uint32_t u32Timeout = 0U;
	
	tsFlashPageW.u32Addr = (uint32_t *)(u32StartAddr);	
	(void)FlashRwApp_32Bits_Buff_Transfer(pu8DataBuff);
	tsFlashPageW.u32Data = &gu32TransferBuff[0];
	#if MICROCHIP_ARM_ENV
		RegsAccessDriver_Irq_Disable();
	#endif

	tsNvmUnlock.u32Addr = u32StartAddr;
	(void)FmcDriver_Region_Unlock(&tsNvmUnlock);

	tsFlashPageW.u8Status = FmcDriver_Flash_Page_Write(&tsFlashPageW);
	if(tsFlashPageW.u8Status == (uint8_t)(NVC_FINISH))	/* Check flash write is finish */
	{
		tsFlashPageW.u8Status = (uint8_t)(NVC_BUSY);
		while((tsFlashPageW.u8Status == (uint8_t)(NVC_BUSY)) && (u32Timeout <= (uint32_t)(LOOP_MAX)))
		{
			u32Timeout++;
			if(NvmCtrl_IsBusy_Get() == (uint8_t)(NVMCTRL_INTFLAG_READY_Msk))
			{							
				tsFlashPageW.u8Status = (uint8_t)(NVC_FINISH);	/* Ready */
			}
			else
			{				
				tsFlashPageW.u8Status = (uint8_t)(NVC_BUSY);		/* Busy */
			}
		}
	}
	else
	{
		tsFlashPageW.u8Status = (uint8_t)(NVC_FAIL);
	}	

	u8Status = I2c0SlaveApp_Slave_Rx_Compare(u32StartAddr, SIZE_A_PAGE, pu8DataBuff);
	#if FLASH_RW_APP_LOCK_TEST
	tsNvmLock.u32Addr = u32StartAddr;
	(void)FmcDriver_Region_Lock(&tsNvmLock);
	#endif
	#if MICROCHIP_ARM_ENV
		RegsAccessDriver_Irq_Enable();
	#endif

	(void)(u32StartAddr);
	(void)(*pu8DataBuff);
	return u8Status;
}

/******************************************************************************
;       Function Name			:	uint8_t FlashRwApp_Read(uint32_t u32DestAddr, uint32_t u32ReadByteLen, uint8_t *pu8DataBuff)
;       Function Description	:	Read flash memory, , the maximum range are 256 bytes.
;       Parameters				:	[u32DestAddr] - Set destination address.
;									[u32ReadByteLen] - Set read's length.
;									[*pu8DataBuff] - Input data.
;       Return Values			:	Return status.
;									(1) NVC_FINISH
;									(2) NVC_FAIL
;		Source ID				:	GM_BL_FLASHRW-003
******************************************************************************/
uint8_t FlashRwApp_Read(uint32_t u32DestAddr, uint32_t u32ReadByteLen, uint8_t *pu8DataBuff)
{
    uint8_t u8Status;
    
	tsFlashR.u32Addr = (uint32_t *)(u32DestAddr);
	tsFlashR.u32Length = u32ReadByteLen;
	if(tsFlashR.u32Length < (uint32_t)(SIZE_READ_THRESHOLD))
	{
		#if MICROCHIP_ARM_ENV
			RegsAccessDriver_Irq_Disable();
		#endif
		u8Status = FmcDriver_Flash_Read(&tsFlashR);	
		if(u8Status == (uint8_t)(NVC_FINISH))
		{
			for(gu32Cnt=0U;gu32Cnt<u32ReadByteLen;gu32Cnt++)
			{
				*(pu8DataBuff + gu32Cnt) = tsFlashR.u32Data[gu32Cnt];
			}
		}
		else
		{
			u8Status = (uint8_t)(NVC_FAIL);			
		}
		#if MICROCHIP_ARM_ENV
			RegsAccessDriver_Irq_Enable();
		#endif
	}
	else
	{
		u8Status = (uint8_t)(NVC_FAIL);	
		#if MICROCHIP_ARM_ENV
			RegsAccessDriver_Irq_Enable();
		#endif
	}	

	(void)(u32DestAddr);
	(void)(u32ReadByteLen);
	(void)(*pu8DataBuff);
	return u8Status;
}

/******************************************************************************
;       Function Name			:	uint8_t FlashRwApp_256B_Erase(uint32_t u32StartAddr, uint32_t u32PageShift)
;       Function Description	:	Erase 256 bytes flash memory.
;       Parameters				:	[u32StartAddr] - Set start address.
;									[u32PageShift] - Set erase page.
;       Return Values			:	Return status.
;									(1) NVC_FINISH
;									(2) NVC_FAIL
;		Source ID				:	GM_BL_FLASHRW-004
******************************************************************************/
uint8_t FlashRwApp_256B_Erase(uint32_t u32StartAddr, uint32_t u32PageShift)
{
    uint8_t u8Status;
    
	tsNvmUnlock.u32Addr = u32StartAddr;
	(void)FmcDriver_Region_Unlock(&tsNvmUnlock);

	tsFlashE.u32Addr = u32StartAddr + ((uint32_t)(SIZE_ERASE_256B) * u32PageShift);
	#if MICROCHIP_ARM_ENV
		RegsAccessDriver_Irq_Disable();
	#endif
	u8Status = FmcDriver_Flash_Row_Erase(&tsFlashE);
	if(u8Status == (uint8_t)(NVC_FINISH))
	{
		u8Status = (uint8_t)(NVC_FINISH);	
	}
	else
	{
		u8Status = (uint8_t)(NVC_FAIL);		
	}	

#if FLASH_RW_APP_LOCK_TEST
	tsNvmLock.u32Addr = u32StartAddr;
	(void)FmcDriver_Region_Lock(&tsNvmLock);	
#endif
	#if MICROCHIP_ARM_ENV
		RegsAccessDriver_Irq_Enable();
	#endif

	(void)(u32StartAddr);
    (void)(u32PageShift);
	return u8Status;
}

/******************************************************************************
;       Function Name			:	uint8_t FlashRwApp_FIDM_Ver_Check(uint8_t u8Para)
;       Function Description	:	Screen FIDM version of internal flash.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	SGM_BL_FLASHRW-005
******************************************************************************/
uint8_t FlashRwApp_FIDM_Ver_Check(uint8_t u8Para)
{	
	(void)FlashRwApp_Read((uint32_t)(ADDR_FIDM_VER), (uint32_t)(SIZE_FIDM_VER), &gu8FidmVerTable[0]);
	(void)(u8Para);
	return u8Para;
}

/******************************************************************************
;       Function Name			:	uint16_t FlashRwApp_FIDM_Ver_Get(void)
;       Function Description	:	Get FIDM version of internal flash.
;       Parameters				:	void
;       Return Values			:	Return local or non-local dimming FIDM version.
;		Source ID				:	SGM_BL_FLASHRW-006
******************************************************************************/
uint16_t FlashRwApp_FIDM_Ver_Get(void)
{
	uint16_t u16FidmVer = 0U;
	(void)FlashRwApp_FIDM_Ver_Check(NOTHING);
	u16FidmVer = ((uint16_t)(gu8FidmVerTable[NONLOCAL_FIDM_VER_H]) << (uint16_t)(SHIFT_BIT_8))  | (uint16_t)(gu8FidmVerTable[NONLOCAL_FIDM_VER_L]);		

	return u16FidmVer;
}
/*---------------------------------------------------------------------------*/
