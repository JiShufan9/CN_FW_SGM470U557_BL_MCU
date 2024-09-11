/******************************************************************************
;       Program		: InitApp.c 
;       Function	: Initialize Interfaces and State Machine Setting.
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 10
;       Author		: Joel Wang
;       Describe 	: 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/ClockApp.h"
#include "app/inc/AdcApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/FlashRwApp.h"
#include "app/inc/SysTickApp.h"
#include "app/inc/WatchDogApp.h"
#include "hal/inc/I2CSDriver.h"
#include "app/inc/I2cMasterApp.h"
#include "app/inc/LEDDriverApp.h"
#include "app/inc/SourceIcSpiIf.h"
#include "app/sfud/inc/sfud.h"
#include "app/fal/inc/fal.h"
#include "app/inc/SourceIcM.h"
/*---------------------------- Declare Global Variable ----------------------*/
static uint8_t gu8StateMachineStep = (uint8_t)(BL_STARTUP);
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	uint8_t InitApp_Startup_Init(uint8_t u8Para)
;       Function Description	:	Initialize startup interface.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	SGM_BL_INITAPP-001
******************************************************************************/
uint8_t InitApp_Startup(void)
{	
	(void)ClockApp_Init(NOTHING);	

	#if DEBUG_UART
		(void)Uart1App_Init(NOTHING);		/* SERCOM1 DEBUG UART */  
	#endif

	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t InitApp_All(uint8_t u8Para)
;       Function Description	:	First initialize PinIO and check wake up pin.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	SGM_BL_INITAPP-002
******************************************************************************/
uint8_t InitApp_PreInitWakeupCheck(void)
{

    (void)PinIOApp_Init(NOTHING);
    (void)InitApp_StateMachine_Set(BL_INIT);
    /*
    if (PortDrvier_PinRead(IO_VCUWakeC) == (uint8_t)(PIN_LEVEL_HIGH))
    {
        (void)InitApp_StateMachine_Set(BL_INIT);
    }
    else
    {
        (void)WakeCtrlApp_Period_WakePin_Check(INTO_SLEEP_TIMES);
    }
 */
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t InitApp_All(uint8_t u8Para)
;       Function Description	:	Initialize all interface.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	SGM_BL_INITAPP-002
******************************************************************************/
uint8_t InitApp_All(void)
{
	#if NVIC_ENABLE
    (void)FunApp_Nvic_Init();
	#endif	

	#if SYS_TICK
	(void)SysTickApp_Init();
	#endif		

	#if (ADC_BATT ||HW_VERSION)
	(void)AdcApp_Init();
	(void)AdcApp_Turn_OnOff_Switch(ADC_ENABLE);

	#endif

    (void)AdcApp_Start();
        
	#if I2C0_SLAVE
	(void)I2c0SlaveApp_Init();	/* SERCOM0 I2C Slave */
	#endif
    
    (void)PinIOApp_System_Power(SYS_PWR_ON);    
    
	#if WDT_RST
	(void)WatchDogApp_Initial(ENABLE);
	#endif       

    #if HW_VERSION
    (void)AdcApp_HW_Version_Transfer();         
    #endif
	(void)PinIOApp_Hw_Ver_Check(NOTHING);
    (void)FlashRwApp_FIDM_Ver_Check(NOTHING);
    
    (void)AdcApp_Start();
    (void)I2c0SlaveApp_BL_Status1_Set(SET_BL_ACTIVE);       /* Firest time active BL mode */
    (void)InitApp_StateMachine_Set(BL_TASK);			/* Jump to TASK state */     
    (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_4); /* TCON I2C */
    (void)I2cMasterApp_Master_Initial(I2C_MASTER_SERCOM_5); /* LED DRV I2C */
		LEDDriverApp_Initial(NOTHING);
	
    SourceIcSpiIf_Init();

	
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t InitApp_StateMachine_Get(void)
;       Function Description	:	Get state machine status.
;       Parameters				:	void
;       Return Values			:	Return present state.
;		Source ID				:	SGM_BL_INITAPP-003
******************************************************************************/

uint8_t InitApp_StateMachine_Get(void)
{
	return gu8StateMachineStep;
}

/******************************************************************************
;       Function Name			:	uint8_t InitApp_StateMachine_Set(uint8_t u8State)
;       Function Description	:	Set state machine status.
;       Parameters				:	void
;       Return Values			:	Return present state.
;		Source ID				:	SGM_BL_INITAPP-004
******************************************************************************/
uint8_t InitApp_StateMachine_Set(uint8_t u8State)
{
	gu8StateMachineStep = u8State;
	return gu8StateMachineStep;
}
/*--------------------------------------END-------------------------------*/


