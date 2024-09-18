/******************************************************************************
;       Program		: AdcApp.c
;       Function	: Battery Voltage Monitor by ADC0 Channel 1
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 10
;       Author		: Joel Wang
;       Describe	: Use AIN[1] = ADC0_CH1_PA03 for battery detection.
;					  ADC Values = Resolution/Vref * Vi
;					  Fixed parameters:
;					  (1) Resolution = 16bits (ADC_CTRLC_RESSEL_16BIT, 65536)
;					  (2) Averaging Div = 16 (ADC_AVGCTRL_SAMPLENUM_16)
;					  (3) ADC Sample = 16 pcs (ADC_AVGCTRL_SAMPLENUM_16)
;
;					  Customer Requirement:
;					  1. [SWRA-02-009] Stop the ECU update function when battery voltage is under 9V.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/AdcApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "hal/inc/ADCDriver.h"
#include "hal_common.h"

#define AdcApp_Conversion_Get() 	ADCDriver_ConversionResultGet(&tsAdc0)
/*---------------------------- Declare External Var -------------------------*/
ADC_InitTypedef tsAdc0 = {0U};

uint8_t gu8VoltCnt = 0U;
uint8_t gu8BatteryState = 0U;
bool gbVoltProtectTriggerFlag = false;
uint32_t gu32AdcCaptureEnableCnt = DEBOUNCE_ADC_BYPASS;
uint8_t gu8AdcToVolt = 0U;
uint8_t gu8VoltDebounceCnt = 0U;
uint8_t gu8AdcToHWVersion = 0U;
static uint16_t gu16AdcToHWVersion = 0U;
bool gbAdcDebounceFlag = true;

#if DEBUG_UART
static bool gbBatStateShowFlag = true;
#endif

static const uint16_t gu16BatteryVoltAdcTable[SIZE_BATT_VOLT] = {
65520U, 64805U, 63320U, 61312U, 59456U, 57536U, 55488U, 53344U, 51136U, 48832U,	/* 30V ~ 21V */
46480U, 44096U, 41728U, 39312U, 36896U, 34528U, 32112U, 29696U, 27280U, 24848U,	/* 20V ~ 11V */
22480U, 19856U, 17632U, 15232U, 12832U, 10400U,1248U                            /* 10V ~ 04V */
};

/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Init(uint8_t u8Para)
;       Function Description	:	Initialize ADC0 function.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_ADC-001
******************************************************************************/
uint8_t AdcApp_Init(void)
{ 
    /* HW version and Battery voltage*/        
    tsAdc0.u32ADCBaseAddress    = (uint32_t)ADC0_BASE_ADDRESS;
	tsAdc0.u8NumADC             = (uint8_t)0x00U;
	tsAdc0.u16ADCch             = ADC0_CH1_BATT;
	tsAdc0.u16ADCAvgSample      = (ADC_AVGCTRL_SAMPLENUM_16);
	tsAdc0.u16ADCAvgDiv         = (ADC_AVGCTRL_SAMPLENUM_16);                    
	tsAdc0.u16PositiveIn        = ADC0_CH1_BATT;
	tsAdc0.u16NegativeIn        = ADC_INPUTCTRL_MUXNEG_GND;
	tsAdc0.u16LowThreshold      = (uint16_t)0U;
	tsAdc0.u16HighThreshold     = (uint16_t)0U;
	tsAdc0.u8WindowMode         = (uint8_t)ADC_CTRLC_WINMODE_DISABLE_Val;
	tsAdc0.u16IntPriority       = (uint16_t)(PRIORITY_LOWEST);
	//tsAdc0.u16Mode              = ADC_CTRLC_FREERUN(0U);
	//tsAdc0.u8Prescaler          = ADC_CTRLB_PRESCALER_DIV4;
    
    (void)ADCDriver_Initial(&tsAdc0);

	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Start(uint8_t u8Number)
;       Function Description	:	Start ADC conversion operation.
;       Parameters				:	Adc0 or Adc1
;       Return Values			:	Return conversion status.
;									(1) Ready is TRUE
;									(2) Busy is FALSE
;		Source ID				:	GM_BL_ADC-002
******************************************************************************/
uint8_t AdcApp_Start(void)
{
	uint8_t u8Return;
    u8Return = ADCDriver_ConversionStart(&tsAdc0); 
    
    return u8Return;
}


/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Converstion_Ready(uint8_t u8Number)
;       Function Description	:	Check ADC conversion status.
;       Parameters				:	None.
;       Return Values			:	Return busy status.
;									(1) Ready is TRUE
;									(2) Busy is FALSE
;		Source ID				:	GM_BL_ADC-004
******************************************************************************/
uint8_t AdcApp_Converstion_Ready(void)
{
    uint8_t u8Return;
    u8Return = ADCON_ConversionStatusGet(&tsAdc0);
    
    return u8Return;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Turn_OnOff_Switch(uint8_t u8Switch)
;       Function Description	:	Enable or disable ADC function.
;       Parameters				:	[u8Switch] - Choose turn-on/off.
;									(1) ADC_ENABLE
;									(2) ADC_DISABLE
;       Return Values			:	Return turn status.
;									(1) Finish is TRUE
;									(2) Failure is FALSE
;		Source ID				:	GM_BL_ADC-005
******************************************************************************/
uint8_t AdcApp_Turn_OnOff_Switch(uint8_t u8Switch)
{
    uint8_t u8Status;
    
    if(u8Switch == (uint8_t)(ADC_ENABLE))
    {
        u8Status = ADCDriver_Enable(&tsAdc0);
    }
    else
    {
        u8Status = ADCDriver_Disable(&tsAdc0);
    }

	(void)(u8Switch);
    return u8Status;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Battery_Volt_Transfer(uint8_t u8Para)
;       Function Description	:	The battery ADC to voltage values. 
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_ADC-006
******************************************************************************/
uint8_t AdcApp_Battery_Volt_Transfer(void)
{
	uint8_t u8Cnt;
    
	/* Index Battery Voltage ADC Vaule */
	for(u8Cnt=0U; u8Cnt < (uint8_t)(STEPS_BATT_VOLT); u8Cnt++)
	{
		if(AdcApp_Conversion_Get() >= gu16BatteryVoltAdcTable[u8Cnt])
		{
			gu8AdcToVolt = (uint8_t)(INDEX_VOLT) - u8Cnt;	/* ADC to Voltage */
			break;
		}		
		else
		{
			gu8AdcToVolt = 0U;
			(void)(gu8AdcToVolt);
		}
	}			
	#if (DEBUG_BAT_ADC && DEBUG_UART)
		Uart1App_String_Value_Show("BattADC = ", AdcApp_Conversion_Get(NOTHING), (uint8_t)(SHOW_DEC));
	#endif
	#if (DEBUG_BAT_VOL && DEBUG_UART)
		Uart1App_String_Value_Show("BattVolt = ", gu8AdcToVolt, (uint8_t)(SHOW_DEC));
	#endif	
	(void)AdcApp_Start();

	
	return true;
}

/******************************************************************************
;       Function Name			:	static bool AdcApp_Battery_State_Show(uint8_t u8ShowState)
;       Function Description	:	Show battery state.
;       Parameters				:	[u8ShowState] - Battery State.
;												   (1) STATE_BAT_INIT
;												   (2) STATE_BAT_BOOT
;												   (3) STATE_BAT_NORMAL
;												   (4) STATE_BAT_PROTECT
;       Return Values			:	true
;		Source ID				:	
******************************************************************************/
#if DEBUG_UART
static bool AdcApp_Battery_State_Show(uint8_t u8ShowState)
{
	if(gbBatStateShowFlag == true)
	{
		switch(u8ShowState)
		{
			case STATE_BAT_INIT:
				#if DEBUG_UART
					Uart1App_String_Show("BATT State = INIT\r");
				#endif
				gbBatStateShowFlag = false;
			break;
			case STATE_BAT_BOOT:
				#if DEBUG_UART
					Uart1App_String_Show("BATT State = BOOT\r");
				#endif
				gbBatStateShowFlag = false;
			break;
			case STATE_BAT_NORMAL:
				#if DEBUG_UART
					Uart1App_String_Show("BATT State = NORMAL\r");
				#endif
				gbBatStateShowFlag = false;
			break;
			case STATE_BAT_PROTECT:
				#if DEBUG_UART
					Uart1App_String_Show("BATT State = PROTECT\r");
				#endif
				gbBatStateShowFlag = false;
			break;
			default:
				/* NOTHING */
			break;
		}
	}
	else
	{
        /* Nothing */
    }

	(void)(u8ShowState);
	(void)(gbBatStateShowFlag);
	return true;
}
#endif

/******************************************************************************
;       Function Name			:	static bool AdcApp_Volt_Threshold_Check(uint8_t u8State, uint8_t u8VoltThreshold)
;       Function Description	:	When the battery voltage is abnormal, change the battery state when is counting to threshold vaules.
;       Parameters				:	[u8ShowState] - Battery State.
;												   (1) STATE_BAT_INIT
;												   (2) STATE_BAT_BOOT
;												   (3) STATE_BAT_NORMAL
;       Return Values			:	true
;		Source ID				:	GM_BL_ADC-007
******************************************************************************/
static bool AdcApp_Volt_Threshold_Check(uint8_t u8State, uint8_t u8VoltThreshold)
{
	if(gu8VoltCnt >= u8VoltThreshold)
	{
		switch(u8State)
		{
			case STATE_BAT_INIT:
				gu8BatteryState = (uint8_t)(STATE_BAT_BOOT);
				gu8VoltCnt = 0u;
				#if DEBUG_UART	
					gbBatStateShowFlag = true;
				#endif
			break;
			case STATE_BAT_BOOT:
				gu8BatteryState = (uint8_t)(STATE_BAT_PROTECT);
				gbVoltProtectTriggerFlag = true;
				gu8VoltCnt = 0u;
                #if I2C0_SLAVE
                    (void)I2c0SlaveApp_BL_Status1_Set(SET_VOLT_ERR);		/* Set battery voltage error */
                #endif
				#if DEBUG_UART	
					gbBatStateShowFlag = true;
				#endif
			break;
			case STATE_BAT_NORMAL:
				gu8BatteryState = (uint8_t)(STATE_BAT_PROTECT);
				gbVoltProtectTriggerFlag = true;
				gu8VoltCnt = 0u;
                #if I2C0_SLAVE
                    (void)I2c0SlaveApp_BL_Status1_Set(SET_VOLT_ERR);		/* Set battery voltage error */
                #endif
				#if DEBUG_UART	
					gbBatStateShowFlag = true;
				#endif
			break;
			default:
				/* NOTHING */
			break;
		}
	}

	(void)(u8State);
	(void)(u8VoltThreshold);
	return true;
}

/******************************************************************************
;       Function Name			:	static bool AdcApp_Volt_Protect_Check(uint8_t u8Volt)
;       Function Description	:	Check the battery voltage whether is enabled the battery protection.
;       Parameters				:	[u8Volt] - Input the battery voltage value.
;       Return Values			:	true
;		Source ID				:	GM_BL_ADC-008
******************************************************************************/
static bool AdcApp_Volt_Protect_Check(uint8_t u8Volt)
{
	if((u8Volt >= (uint8_t)(THRESHLOD_VOLT_PROTECT)))		
	{
		if(gu8VoltDebounceCnt == (uint8_t)(DEBOUNCE_VOLT))
		{
			gu8BatteryState = (uint8_t)(STATE_BAT_NORMAL);		
			gbVoltProtectTriggerFlag = true;						/* Set to default */ 
			gu8VoltDebounceCnt = 0U;
	#if I2C0_SLAVE
            (void)I2c0SlaveApp_BL_Status1_Clear(SET_VOLT_ERR); /* Set battery voltage is normal */
	#endif
	#if DEBUG_UART
			gbBatStateShowFlag = true;
	#endif
	}
	else
	{
			gu8VoltDebounceCnt++;	
		}
	}
	else
	{
		if((gbVoltProtectTriggerFlag == true))
		{
		#if I2C0_SLAVE
				(void)I2c0SlaveApp_BL_Status1_Set(SET_VOLT_ERR);	/* Set battery voltage error */			
		#endif

			gbVoltProtectTriggerFlag = false;						/* Clear flag */
			gu8BatteryState = (uint8_t)(STATE_BAT_PROTECT);
		#if DEBUG_UART
				(void)AdcApp_Battery_State_Show(STATE_BAT_PROTECT);
		#endif			
		}
		else
		{
			gu8VoltDebounceCnt = 0U;
			(void)(gu8VoltDebounceCnt);
		}
	}

	(void)(u8Volt);
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_Battery_Volt_Protect_Process(uint8_t u8Para)
;       Function Description	:	The battery protection process.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_ADC-009
******************************************************************************/
uint8_t AdcApp_Battery_Volt_Protect_Process(void)
{
	switch(gu8BatteryState)
	{
		case STATE_BAT_INIT:
			#if DEBUG_UART
				(void)AdcApp_Battery_State_Show(STATE_BAT_INIT);
			#endif
			if((gu8AdcToVolt >= (uint8_t)(THRESHLOD_VOLT_PROTECT)))
			{
					gu8BatteryState = (uint8_t)(STATE_BAT_NORMAL);
					gu8VoltCnt = 0U;
					#if DEBUG_UART
							gbBatStateShowFlag = true;
					#endif
			}
			else
			{
					gu8VoltCnt++;				
					(void)AdcApp_Volt_Threshold_Check(STATE_BAT_INIT, DEBOUNCE_VOLT);
			}
		break;
		case STATE_BAT_BOOT:
				#if DEBUG_UART
						(void)AdcApp_Battery_State_Show(STATE_BAT_BOOT);
				#endif			
				if((gu8AdcToVolt >= (uint8_t)(THRESHLOD_VOLT_PROTECT)))
				{
						gu8BatteryState = (uint8_t)(STATE_BAT_NORMAL);
						gu8VoltCnt = 0U;
						#if DEBUG_UART
								gbBatStateShowFlag = true;
						#endif
				}
				else
				{
						gu8VoltCnt++;
						(void)AdcApp_Volt_Threshold_Check(STATE_BAT_BOOT, DEBOUNCE_BOOT_VOLT);
				}
		break;
		case STATE_BAT_NORMAL:
				#if DEBUG_UART
						(void)AdcApp_Battery_State_Show(STATE_BAT_NORMAL);
				#endif
				if((gu8AdcToVolt >= (uint8_t)(THRESHLOD_VOLT_PROTECT)))
				{
						gu8VoltCnt = 0U;
				}				
				else
				{
						gu8VoltCnt++;
						(void)AdcApp_Volt_Threshold_Check(STATE_BAT_NORMAL, DEBOUNCE_VOLT);
				}
		break;
		case STATE_BAT_PROTECT:
				(void)AdcApp_Volt_Protect_Check(gu8AdcToVolt); 		
		break;
		default:
				/* NOTHING */
		break;
	}

	return true;
}

/******************************************************************************
;       Function Name			:	uint32_t AdcApp_AdcCaptureEnableCnt_Get(void)
;       Function Description	:	Get ADC capture debounce time value.
;       Parameters				:	void
;       Return Values			:	Return debounce time vaule.
;		Source ID				:	GM_BL_ADC-010
******************************************************************************/
uint32_t AdcApp_AdcCaptureEnableCnt_Get(void)
{
	return gu32AdcCaptureEnableCnt;
}

/******************************************************************************
;       Function Name			:	uint32_t AdcApp_AdcCaptureEnableCnt_Set(uint32_t ulValue)
;       Function Description	:	Set ADC capture debounce time.
;       Parameters				:	[ulValue] - ADC capture debounce time.
;       Return Values			:	Return debounce time vaule.
;		Source ID				:	GM_BL_ADC-011
******************************************************************************/
uint32_t AdcApp_AdcCaptureEnableCnt_Set(uint32_t ulValue)
{	
	gu32AdcCaptureEnableCnt = ulValue;
	
	(void)(ulValue);
	return gu32AdcCaptureEnableCnt;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_AdcToVolt_Get(void)
;       Function Description	:	Get battery voltage.
;       Parameters				:	void
;       Return Values			:	Return battery voltage.
;		Source ID				:	GM_BL_ADC-012
******************************************************************************/
uint8_t AdcApp_AdcToVolt_Get(void)
{
	return gu8AdcToVolt;
}

/******************************************************************************
;       Function Name			:	bool AdcApp_AdcDebounceFlag_Get(void)
;       Function Description	:	Get gbAdcDebounceFlag status.
;       Parameters				:	void
;       Return Values			:	Return gbAdcDebounceFlag value.
;		Source ID				:	GM_BL_ADC-013
******************************************************************************/
bool AdcApp_AdcDebounceFlag_Get(void)
{
	return gbAdcDebounceFlag;
}

/******************************************************************************
;       Function Name			:	bool AdcApp_AdcDebounceFlag_Set(bool bSwitch)
;       Function Description	:	Set gbAdcDebounceFlag status.
;       Parameters				:	[bSwitch] - Enable or disable gbAdcDebounceFlag status.
;       Return Values			:	true
;		Source ID				:	GM_BL_ADC-014
******************************************************************************/
bool AdcApp_AdcDebounceFlag_Set(bool bSwitch)
{
	gbAdcDebounceFlag = bSwitch;
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t AdcApp_HW_Version_Transfer(uint8_t u8Para)
;       Function Description	:	The ADC to HW version values. 
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_ADC-015
******************************************************************************/
uint8_t AdcApp_HW_Version_Transfer(void)
{
	gu16AdcToHWVersion = ((PortDrvier_PinRead(IO_PCBA_A3) << 3U) | (PortDrvier_PinRead(IO_PCBA_A2) << 2U) | (PortDrvier_PinRead(IO_PCBA_A1) << 1U) | PortDrvier_PinRead(IO_PCBA_A0));
	#if (DEBUG_UART)
		Uart1App_String_Value_Show("HW version = V", gu8AdcToHWVersion, (uint8_t)(SHOW_DEC));
	#endif	
    
	return true;
}

/******************************************************************************
;       Function Name			:	uint16_t AdcApp_AdcToHWVersion_Get(void)
;       Function Description	:	Get HW version.
;       Parameters				:	void
;       Return Values			:	Return HW version.
;		Source ID				:	GM_BL_ADC-016
******************************************************************************/
uint16_t AdcApp_AdcToHWVersion_Get(void)
{
	return gu16AdcToHWVersion;
}



/*--------------------------------------------------------------------------*/
