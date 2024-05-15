/******************************************************************************
;       Program		: main.c 
;       Function	: The Main Program and State Machine
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 04
;       Author		: Fenderson Lu
;       Describe 	: 
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/SysTickApp.h"
#include "app/inc/I2c0SlaveApp.h"
/*---------------------------- Declare Global Variable ----------------------*/
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	int main(void)
;       Function Description	:	Main function.
;       Parameters				:	void
;       Return Values			:	NA
;		Source ID				:	SGM_BL_MAIN-001
******************************************************************************/
int main(void)
{
    uint8_t u8LocalLoop = ENABLE_ON;

	while(ENABLE_ON == u8LocalLoop)
	{
		switch(InitApp_StateMachine_Get())
		{
            case BL_PREINIT:
				(void)InitApp_PreInitWakeupCheck();
				u8LocalLoop = ENABLE_ON;
			break;
            
			case BL_INIT:
				(void)InitApp_All();
				u8LocalLoop = ENABLE_ON;
			break;
            
			case BL_STARTUP:
				(void)InitApp_Startup();
				(void)FunApp_Startup_Check();
				u8LocalLoop = ENABLE_ON;
			break;
            
			case BL_TASK:
				#if VTOS
					(void)SysTickApp_Virtual_OS();
				#endif
				u8LocalLoop = ENABLE_ON;
			break;
            
			case BL_UPDATE:
				#if I2C0_SLAVE
                (void)I2c0SlaveApp_Rx_Program_Process();
				#endif
                (void)WakeCtrlApp_Program_To_Sleep_Set(true);
				u8LocalLoop = ENABLE_ON;
			break;
            
            case BL_SLEEP:
                (void)WakeCtrlApp_Sleep_Mode(NOTHING);
				u8LocalLoop = ENABLE_ON;
			break;
            
            case BL_WAKEUP_CHECK:
                (void)WakeCtrlApp_Sleep_Wake_Check(INTO_WAKEUP_TIMES);
				u8LocalLoop = ENABLE_ON;
			break;

			case BL_IRQ_ERR:
				/* Lock to stop */
			break;
            
			default:
				u8LocalLoop = ENABLE_OFF;
			break;
		}
	}

	return (int)(0U);
}
/*---------------------------------------------------------------------------*/ 

