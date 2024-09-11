/******************************************************************************
;       Program		: MainApp.c 
;       Function	: Task and Schedule Management
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 10
;       Author		: Joel Wang
;       Describe	:	Bootloader firmware version is BL_VER
;						Optimization-Level set 1.
******************************************************************************/

/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/AdcApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/FlashRwApp.h"
#include "app/inc/WatchDogApp.h"
#include "app/inc/LEDDriverApp.h"
/*---------------------------- Declare Global Variable ----------------------*/
//static uint32_t gu32BLActiveCnt = TIME_BL_ACTIVE;
#if ADC_BATT
static uint32_t gu32AdcDetectCnt;
#endif
DisplayID gDisplayID = C304_DISPLAY_ID;
BacklightType gBlacklightType = BACKLIGHT_EDGE_BACKLIGHT;
st_TCON_TypeDef tsTconProtocal = {0U};
/*---------------------------- Start Program --------------------------------*/

/******************************************************************************
;Author: Orlando Huang
;Description: Retrun Display ID
;Return Parameter: uint8_t
******************************************************************************/
uint8_t MainApp_getDisplayID(void)
{
	return (uint8_t)(gDisplayID);
}

#if 0
void mainApp_SetBacklightDimmingType(void)
{
	uint8_t u8DimmingSetting = 0U;
	uint8_t u8Idx = 0U;

	if( (uint8_t)(LOCAL_DIMMING) == PinIOApp_HwStatusFlag_Get() ){
		u8DimmingSetting = (uint8_t)0U;
	} else {
		u8DimmingSetting = (uint8_t)1U;
	}

	/* Control TCON-E02 */
	*(tsTconProtocal.u8TconTxBuf) = TCONDimmCmdAddr;
	*(tsTconProtocal.u8TconTxBuf + 1U) = u8DimmingSetting;
	/* Calculate Data Sum */
	*(tsTconProtocal.u8TconTxBuf + 2U) = (uint8_t)(0x00U);
	while(u8Idx < 2U)
	{
		*(tsTconProtocal.u8TconTxBuf + 2U) += *(tsTconProtocal.u8TconTxBuf + u8Idx);
		u8Idx++;
	}
	tsTconProtocal.u8TxLen = 3U;
	/* Send I2C CMD to TCON */
	(void)I2cMasterApp_Tx(I2C_MASTER_SERCOM_4, &tsTconProtocal.u8TconTxBuf[0U], tsTconProtocal.u8TxLen);

	(void)u8Idx;
	(void)u8DimmingSetting;
}
#endif
/******************************************************************************
;Author: Orlando Huang
;Description: Controlinf backlight from different project type
;Return Parameter: {*}
******************************************************************************/
bool MainApp_BLControl(void)
{
	uint32_t u32Value = 0U;
	uint16_t u16BLValue = 0U;
	uint8_t u8Idx = 0U;
	bool bReturn = false;

	u16BLValue = I2cSlaveApp_GetHostBL();

	LEDDriverApp_BackLight_Output(u16BLValue);

	(void)u32Value;
	(void)u16BLValue;
	(void)u8Idx;
	return bReturn;
}
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t MainApp_Task_1ms(uint8_t u8Para)
;       Function Description	:	Task process is based on 1ms.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_MAINAPP-001
******************************************************************************/

uint8_t MainApp_Task_1ms(uint8_t u8Para)
{
	#if I2C0_SLAVE
	(void)I2c0SlaveApp_Rx_TASK_Process();
	#endif
	
    (void)WakeCtrlApp_Period_WakePin_Check(INTO_SLEEP_TIMES);

	(void)(u8Para);
	return (u8Para);
}

/******************************************************************************
;       Function Name			:	uint8_t MainApp_Task_1s(uint8_t u8Para)
;       Function Description	:	Task process is based on 1s.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_MAINAPP-002
******************************************************************************/
uint8_t MainApp_Task_1s(uint8_t u8Para)
{
	#if WDT_RST
        (void)WatchDogApp_Clean(MODE_ClearWithoutSync);
	#endif
	
	#if ADC_BATT
		if(AdcApp_Converstion_Ready() == DRIVER_TRUE)
		{
			gu32AdcDetectCnt = AdcApp_AdcCaptureEnableCnt_Get();
			if(FunApp_Down_Counter(&gu32AdcDetectCnt) == true)					/* 1 second get ADC values */
			{
				(void)AdcApp_Battery_Volt_Transfer();
				(void)AdcApp_Battery_Volt_Protect_Process();
				(void)AdcApp_AdcDebounceFlag_Set(false);				/* Disable ADC debounce counter in programming process */
			}
			else
			{
				(void)AdcApp_AdcCaptureEnableCnt_Set(gu32AdcDetectCnt);
			}
		}
	#endif
	/* Controling backlight */
	(void)MainApp_BLControl();
	
	#if DEBUG_UART
		Uart1App_String_Show("BL_TASK\r");
		Uart1App_String_Value_Show("CRC Fail Flag = ", (uint32_t)FunApp_Crc32FailFlag_Get(), (uint8_t)(SHOW_HEX));
		Uart1App_String_Show("\r");
	#endif
	(void)(u8Para);
	return (u8Para);	
}
/*---------------------------------------------------------------------------*/ 
