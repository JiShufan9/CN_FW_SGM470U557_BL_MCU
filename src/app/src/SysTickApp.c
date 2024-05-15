/******************************************************************************
;       Program  : SysTickApp.c
;       Function : Implement System Tick Function
;       Chip     : Microchip ATSAMC21N17A
;       Clock    : Internal 48MHz
;       Date		: 2021 / 06 / 04
;       Author   : Fenderson Lu
;       Describe	: Code Gen system tick function.
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/SysTickApp.h"

/*---------------------------- Declare External Var --------------------------*/
uint32_t gu32SysTick = 0U;
uint32_t gu32VTimerCnt = 0U, gu32VTimer1msCnt = 0U;
bool gbTrigger1ms = false;
bool gbTriggerEnable = false;
/*---------------------------- Start Program ---------------------------------*/
/******************************************************************************
;	Function Name			:	static void SysTickApp_Call_Back(uintptr_t context)
;	Function Description	:	System tick callback function.
;	Parameters				:	[context] - Value identifying the context of the application that registered the event handling function.
;	Return Values			:	
;	Source ID				:   GM_BL_SYSTICK-001
******************************************************************************/
void SysTickApp_Call_Back(uintptr_t context)
{
	gu32SysTick++;
	if(gbTriggerEnable == true)
	{
    gbTrigger1ms = true;
	}    
	(void)(context);
}

/******************************************************************************
;	Function Name			:	uint8_t SysTickApp_Init(uint8_t u8Para)
;	Function Description	:	Initialize system tick function.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_SYSTICK-002
******************************************************************************/
uint8_t SysTickApp_Init(void)
{
	SysTickApp_Initialize();
	SysTickApp_Callback_Register(&SysTickApp_Call_Back, (uintptr_t)(NULL));
	SysTickApp_Start();

	return true;
}

/******************************************************************************
;	Function Name			:	uint32_t SysTickApp_SysTickCnt_Get(void)
;	Function Description	:	Get gu32SysTickCnt value.
;	Parameters				:	void
;	Return Values			:	Return vaule.
;	Source ID				:   GM_BL_SYSTICK-003
******************************************************************************/
uint32_t SysTickApp_gu32SysTick_Get(void)
{
	return gu32SysTick;
}

/******************************************************************************
;	Function Name			:	uint8_t SysTickApp_Virtual_OS(uint8_t u8Para)
;	Function Description	:	Virtual task OS.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_SYSTICK-004
******************************************************************************/
uint8_t SysTickApp_Virtual_OS(void)
{
	if(gu32VTimerCnt != SysTickApp_gu32SysTick_Get())
	{
		(gu32VTimerCnt)++;
		(gu32VTimer1msCnt)++;
		(void)MainApp_Task_1ms(NOTHING);
	

		if((gu32VTimer1msCnt % (uint32_t)(TIME0_1S)) == (uint32_t)(COUNTING_DONE))
		{
			(void)MainApp_Task_1s(NOTHING);
		}
		
		if((gu32VTimer1msCnt % (uint32_t)(TIME0_9S)) == (uint32_t)(COUNTING_DONE))
		{
			gu32VTimer1msCnt = (uint32_t)(SET_DEFAULT);
		}
	}

	return true;
}

/******************************************************************************
;	Function Name			:	bool SysTickApp_Trigger1ms_Set(bool bFlag)
;	Function Description	:	Set gbTrigger1ms value.
;	Parameters				:	[bFlag] - Set true or false.
;	Return Values			:	true
;	Source ID				:	
******************************************************************************/
bool SysTickApp_Trigger1ms_Set(bool bFlag)
{
	gbTrigger1ms = bFlag;
	return true;
}

/******************************************************************************
;	Function Name			:	bool SysTickApp_Trigger1ms_Get(void)
;	Function Description	:	Get gbTrigger1ms value.
;	Parameters				:	void
;	Return Values			:	Return gbTrigger1ms variable values.
;	Source ID				:	
******************************************************************************/
bool SysTickApp_Trigger1ms_Get(void)
{
	return gbTrigger1ms;
}

/******************************************************************************
;	Function Name			:	bool SysTickApp_TriggerEnable_Set(bool bFlag)
;	Function Description	:	Set gbTriggerEnable value.
;	Parameters				:	void
;	Return Values			:	true
;	Source ID				:	SGM_BL_SYSTICK-007
******************************************************************************/
bool SysTickApp_TriggerEnable_Set(bool bFlag)
{
	gbTriggerEnable = bFlag;
	return true;
}

/******************************************************************************
;	Function Name			:	bool SysTickApp_TriggerEnable_Get(void)
;	Function Description	:	Get gbTriggerEnable value.
;	Parameters				:	void
;	Return Values			:	Return gbTriggerEnable variable values.
;	Source ID				:	SGM_BL_SYSTICK-008
******************************************************************************/
bool SysTickApp_TriggerEnable_Get(void)
{
	return gbTriggerEnable;
}
/*----------------------------------------------------------------------------*/
