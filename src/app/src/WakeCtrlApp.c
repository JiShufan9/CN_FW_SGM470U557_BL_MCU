/******************************************************************************
;       Program		: WakeCtrlApp.c 
;       Function	: Control MCU power management
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 09 / 01
;       Author		: Joel Wang
;       Describe 	: Implement WakeUp/Sleep Pin Control (PORT_PIN_PA06)
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
/*---------------------------- Declare Global Variable ----------------------*/
static uint16_t gu16SleepTimes = INTO_SLEEP_TIMES;
static uint16_t gu16WakeupTimes = INTO_WAKEUP_TIMES;
static uint8_t gu8WakeFromEIC = FALSE;
static eic_init_t tdEic;
static bool gbProgrammingToSleepFlag = false;
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	static uint8_t WakeCtrlApp_Wake_Sleep_Debounce(uint16_t u16ResetCount)
;       Function Description	:	Check wakeup pin state and debounce.
;       Parameters				:	[u16ResetCount] - Reciprocal count
;       Return Values			:	TRUE / FALSE
;		Source ID				:	GM_BL_WAKE-001
******************************************************************************/
static uint8_t WakeCtrlApp_Wake_Sleep_Debounce(uint16_t u16ResetCount)
{
    uint8_t u8Return;
    
    if (PortDrvier_PinRead(IO_VCUWakeC) == (uint8_t)(PIN_LEVEL_HIGH))
    {
        gu16SleepTimes = u16ResetCount;
        u8Return = TRUE;
    }
    else if (gu16SleepTimes > VALUE_CLEAN)
    {
        gu16SleepTimes -= COUNT_1;
        u8Return = FALSE;
    }
    else
    {
        u8Return = FALSE;
    }
    
    return u8Return;
}

/******************************************************************************
;       Function Name			:	static uint8_t WakeCtrlApp_Wake_Sleep_Debounce(uint16_t u16ResetCount)
;       Function Description	:	Check wakeup pin state and debounce.
;       Parameters				:	[u16ResetCount] - Reciprocal count
;       Return Values			:	TRUE / FALSE
;		Source ID				:	GM_BL_WAKE-001
******************************************************************************/
static uint8_t WakeCtrlApp_Sleep_Wake_Debounce(uint16_t u16ResetCount)
{
    uint8_t u8Return;
    
    if (PortDrvier_PinRead(IO_VCUWakeC) == (uint8_t)(PIN_LEVEL_LOW))
    {
        gu16WakeupTimes = u16ResetCount;
        u8Return = TRUE;
    }
    else if (gu16WakeupTimes > VALUE_CLEAN)
    {
        gu16WakeupTimes -= COUNT_1;
        u8Return = FALSE;
    }
    else
    {
        u8Return = FALSE;
    }
    
    return u8Return;
}

/******************************************************************************
;       Function Name			:	uint8_t WakeCtrlApp_Period_WakePin_Check(uint16_t u16DebounceNum)
;       Function Description	:	Period check wakeup pin state.
;       Parameters				:	[u16DebounceNum] - Debounce number
;       Return Values			:	TRUE
;		Source ID				:	GM_BL_WAKE-002
******************************************************************************/
uint8_t WakeCtrlApp_Period_WakePin_Check(uint16_t u16DebounceNum)
{

	(void)WakeCtrlApp_Wake_Sleep_Debounce(u16DebounceNum);

	if (gu16SleepTimes == DEBOUNCE_COUNT_DONE)
	{
		(void)InitApp_StateMachine_Set(BL_SLEEP);			// Jump to BL_SLEEP state 
	}
	
    return TRUE;
}


/******************************************************************************
;       Function Name           :   uint8_t WakeCtrlApp_Period_WakePin_Check(uint16_t u16DebounceNum)
;       Function Description    :   Period check wakeup pin state.
;       Parameters              :   [u16DebounceNum] - Debounce number
;       Return Values           :   TRUE
;       Source ID               :   GM_BL_WAKE-002
******************************************************************************/
uint8_t WakeCtrlApp_Period_WakePin_Just_Check(uint16_t u16DebounceNum)
{

    uint8_t u8CheckRes = FALSE;
    (void)WakeCtrlApp_Wake_Sleep_Debounce(u16DebounceNum);

    if (gu16SleepTimes == DEBOUNCE_COUNT_DONE)
    {       
        u8CheckRes = FALSE;
    } else {
        u8CheckRes = TRUE;
    }
    
    return u8CheckRes;
}

/******************************************************************************
;       Function Name			:	bool WakeCtrlApp_Eic_Wakeup(uintptr_t context)
;       Function Description	:	External interrupt trigger(VCUWakeC pin callback function is called)
;       Parameters				:	u8Nothing
;       Return Values			:	u8Nothing
;		Source ID				:	GM_BL_WAKE-003
******************************************************************************/
void WakeCtrlApp_Eic_Wakeup(uintptr_t context)
{
	gu8WakeFromEIC=TRUE;
	(void)context;
}
/******************************************************************************
;       Function Name			:	void WakeCtrlApp_Sleep_ExternalPin_Set(void)
;       Function Description	:	Setup external I/O interrupt for wakeup sleep mode
;       Parameters				:	void
;       Return Values			:	void
;       Source ID               :   GM_BL_WAKE-004
******************************************************************************/
void WakeCtrlApp_Sleep_ExternalPin_Set(void)
{
	tdEic.u8ClockSelect = EIC_CLK_ULP32K;

	tdEic.u8FilterEnable[WAKEUP_EXIT_PIN_NUMBER] = EIC_FILTER_ENABLE;
	tdEic.u8Sense[WAKEUP_EXIT_PIN_NUMBER] = EIC_CONFIG_SENSE_RISE;

	tdEic.u16EventControl = (((uint16_t)1U) << WAKEUP_EXIT_PIN_NUMBER);
	(void)EicDriver_init(tdEic);

	tdEic.tdDebounce.u8Prescaler0 = EIC_DPRESCALER_PRESCALER0_DIV16_Val;
	tdEic.tdDebounce.u8Tickon = EIC_DPRESCALER_TICKON_CLK_LFREQ_Val;
	tdEic.tdDebounce.u8States0 = EIC_DPRESCALER_STATES1_LFREQ3_Val;
	(void)EicDriver_DebouncePrescalerSetting(tdEic.tdDebounce);

	(void)EicDriver_CallbackRegister(WAKEUP_EXIT_PIN_NUMBER, WakeCtrlApp_Eic_Wakeup, VALUE_CLEAN);
	(void)EicDriver_InterruptEnable(WAKEUP_EXIT_PIN_NUMBER);

	NVIC_SetPriority(EIC_IRQn, PRIORITY_1); 
	NVIC_EnableIRQ(EIC_IRQn);

	(void)EicDriver_Enable(NOTHING);
}

/******************************************************************************
;       Function Name			:	uint8_t WakeCtrlApp_PreSleep_Driver_DeInitial(uint8_t u8Para)
;       Function Description	:	DeInitial Driver in MCU
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;       Source ID               :   GM_BL_WAKE-005
******************************************************************************/
uint8_t WakeCtrlApp_PreSleep_Driver_DeInitial(uint8_t u8Para)
{
	(void)WatchDogApp_Clean(MODE_ClearWithoutSync);

    (void)I2cMasterApp_DeInitial(I2C_MASTER_SERCOM_2);
    (void)I2cMasterApp_DeInitial(I2C_MASTER_SERCOM_5);
	(void)I2cSlaveApp_Slave_DeInitial();
	(void)AdcApp_Turn_OnOff_Switch(ADC_DISABLE);
    (void)WatchDogApp_Initial(DISABLE);
    
	(void)(u8Para);
	return  (u8Para);
}

/******************************************************************************
;       Function Name			:	uint8_t WakeCtrlApp_Parameter_Initial(uint8_t u8Value)
;       Function Description	:	Initial Value
;       Parameters				:	[u8Value] - initial 0
;       Return Values			:	TRUE
;       Source ID               :   GM_BL_WAKE-006
******************************************************************************/
uint8_t WakeCtrlApp_Parameter_Initial(uint8_t u8Value)
{
    uint32_t u32Size = sizeof(tdEic);
    (void) memset(&tdEic, 0U, u32Size);
    (void) u8Value;
    return TRUE;
}

/******************************************************************************
;       Function Name			:	uint8_t WakeCtrlApp_Sleep_Mode(uint8_t u8Para)
;       Function Description	:	Into sleep mode setting.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;       Source ID               :   GM_BL_WAKE-007
******************************************************************************/
uint8_t WakeCtrlApp_Sleep_Mode(uint8_t u8Para)
{
    #if DEBUG_UART
    Uart1App_String_Show("Into sleep mode\r");
	#endif
    (void)I2c0SlaveApp_BL_Status1_Clear(SET_APP_UNLOCK | SET_APP_ERASE | SET_ERASE_KEY_ERR | SET_CRC16_ERR);		/* Set APP memory is locked, and other flag to default */
	(void)I2c0SlaveApp_BL_Status2_Clear(SET_PROGRAMMING_ERROR | SET_UNKNOWN_ERROR);/* Set to default value */
#if 0    
    if(WakeCtrlApp_Program_To_Sleep_Get() == true)
    {
        (void)I2c0SlaveApp_BL_Programming_Error_Set(SET_PROGRAMMING_ERROR);		/* Set battery voltage error */
    }
#endif
    (void)WakeCtrlApp_PreSleep_Driver_DeInitial(NOTHING);
    (void)WakeCtrlApp_Parameter_Initial(VALUE_CLEAN);
    (void)PinIOApp_System_Power(SYS_PWR_OFF);
    WakeCtrlApp_Sleep_ExternalPin_Set();
    (void)PMDriver_EnterStandBy();
    (void)InitApp_StateMachine_Set(BL_WAKEUP_CHECK);			/* Jump to TASK state */

    (void)(u8Para);
	return  (u8Para);
}

/******************************************************************************
;       Function Name			:	uint8_t WakeCtrlApp_Sleep_Wake_Check(uint16_t u16DebounceNum)
;       Function Description	:	WakeUP check
;       Parameters				:	[u16DebounceNum] - Debounce number
;       Return Values			:	TRUE
;       Source ID               :   GM_BL_WAKE-008
******************************************************************************/
uint8_t WakeCtrlApp_Sleep_Wake_Check(uint16_t u16DebounceNum)
{
    (void)WakeCtrlApp_Sleep_Wake_Debounce(u16DebounceNum);
    
	if (gu16WakeupTimes == DEBOUNCE_COUNT_DONE)
	{
		(void)InitApp_StateMachine_Set(BL_INIT);			/* Jump to BL_INIT state */
	}

	return TRUE;
}

/******************************************************************************
;       Function Name			:	bool WakeCtrlApp_Program_To_Sleep_Get(void)
;       Function Description	:	Get gbProgrammingToSleepFlag.
;       Parameters				:	void
;       Return Values			:	Return gbProgrammingToSleepFlag.
;		Source ID				:	GM_BL_WAKE-009
******************************************************************************/
#if 0
bool WakeCtrlApp_Program_To_Sleep_Get(void)
{
	return gbProgrammingToSleepFlag;
}
#endif
/******************************************************************************
;	Function Name			:	bool WakeCtrlApp_Program_To_Sleep_Set(bool bFlag)
;	Function Description	:	Set gbProgrammingToSleepFlag value.
;	Parameters				:	void
;	Return Values			:	true
;	Source ID				:	GM_BL_WAKE-010
******************************************************************************/
bool WakeCtrlApp_Program_To_Sleep_Set(bool bFlag)
{
	gbProgrammingToSleepFlag = bFlag;
	return true;
}
/*---------------------------------------------------------------------------*/ 
