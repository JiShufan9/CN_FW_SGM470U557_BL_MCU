/******************************************************************************
;       Program  : FunApp.c
;       Function : Implement Project Scenario Functions 
;       Chip     : Microchip ATSAMC21N17A
;       Clock    : Internal 48MHz
;       Date     : 2021 / 06 / 16
;       Author   : Joel Wang
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/FunApp.h"
#include "app/inc/SysTickApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/WatchDogApp.h"
#include "hal/inc/RegsAccessDriver.h"
#include "peripheral/systick/plib_systick.h"

/*---------------------------- Declare External Var --------------------------*/


static bool gbCrc32FailFlag = false;
static volatile uint16_t *u16AccessKey0RAM = BOOT_KEY_0;
static volatile uint16_t *u16AccessKey1RAM = BOOT_KEY_1; 
static volatile uint16_t *u16SessionKeyRAM = SESSION_KEY;
/*---------------------------- Start Program ---------------------------------*/
/******************************************************************************
;	Function Name			:	bool FunApp_Down_Counter(uint32_t *u32CountValues)
;	Function Description	:	Count down function.
;	Parameters				:	[u32CountValues] - Set count down values.
;	Return Values			:	Return status.
;								(1) true - Countdown is finish.
;								(2) false - Countdown.
;	Source ID				:   GM_BL_FUN-001
******************************************************************************/
bool FunApp_Down_Counter(uint32_t *u32CountValues)
{
	bool bFlag;

	if(*u32CountValues > 0U)
	{
		*u32CountValues -= (uint32_t)(CNT_REDUCE);
		if(*u32CountValues != (uint32_t)(CNT_DONE))
		{
			bFlag = false;
		}
		else
		{
			bFlag = true;
		}			
	}
	else
	{
		bFlag = false;
	}

	(void)(u32CountValues);
	return bFlag;
}

/******************************************************************************
;	Function Name			:	bool FunApp_Delay_Millisecond(uint32_t u32DelayTime, uint8_t u8Mode)		
;	Function Description	:	Process delay function, the counter is based on 1ms.
;	Parameters				:	[u32Time] - Set count delay values.
;	Return Values			:	Return count delay values.
;	Source ID				:   GM_BL_FUN-002
******************************************************************************/
bool FunApp_Delay_Millisecond(uint32_t u32DelayTime, uint8_t u8Mode)					
{
    bool bDelayFinishFlag = false;	
	uint32_t u32SysTickCnt = 0U, u32DelayTimeout = 0U;
    
	switch(u8Mode)
	{
		
        case MODE_SYSTICK:	
            while((u32SysTickCnt != u32DelayTime) && (u32DelayTimeout <= (uint32_t)(LOOP_MAX)))
            {
                u32DelayTimeout++;
                if(SYSTICK_TimerPeriodHasExpired() == true)
                {
                    u32SysTickCnt++;
                }
            }
			bDelayFinishFlag = true;
		break;
		case MODE_ISR:
			(void)SysTickApp_TriggerEnable_Set(true);		
			while((SysTickApp_TriggerEnable_Get() == true) && (u32DelayTimeout <= (uint32_t)(LOOP_MAX)))
            {
                u32DelayTimeout++;
                if(SysTickApp_Trigger1ms_Get() == true)
                {
					if(u32SysTickCnt == u32DelayTime)
					{
						(void)SysTickApp_TriggerEnable_Set(false);
						bDelayFinishFlag = true;
					}
					else
					{
                        u32SysTickCnt++;
                        (void)SysTickApp_Trigger1ms_Set(false);
                    }
                }
            }
        break;
        default:
				/* NOTHING */
		break;
    }

	(void)(bDelayFinishFlag);
	return (bDelayFinishFlag);
}

/******************************************************************************
;	Function Name			:	uint8_t FunApp_Irq_Disable(uint8_t u8Para)	
;	Function Description	:	Disable interface interrupt function.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-003
******************************************************************************/
uint8_t FunApp_Irq_Disable(void)
{
    #if SYS_TICK
		SysTickApp_Irq_Disable(SysTick_IRQn);
    #endif
    #if I2C0_SLAVE
        I2c0SlaveApp_Irq_Disable(SERCOM0_IRQn);
    #endif

    return true;
}

/******************************************************************************
;	Function Name			:	static uint8_t FunApp_Jump_to_App(uint8_t u8Para)
;	Function Description	:	Jump to application mode from bootloader mode.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-004
******************************************************************************/
static uint8_t FunApp_Jump_to_App(uint8_t u8Para)
{
    uint32_t u32Msp, u32ResetVector;

	u32Msp = *(uint32_t *)(APP_START_ADDR);
	u32ResetVector = *(uint32_t *)(ADDR_VECTOR_RST);
	(void)(u32Msp);
	(void)(u32ResetVector);
    if(u32Msp != (uint32_t)(FAIL_ADDR))
    {
    	#if MICROCHIP_ARM_ENV
			ASM_SET_MSP(u32Msp);
			ASM_VECTOR_RESET(u32ResetVector);
		#endif
    }

    (void)(u8Para);
    return u8Para;
}

/******************************************************************************
;	Function Name			:	static uint8_t FunApp_Jump_to_App_Check(uint8_t u8Para)
;	Function Description	:	Jump to the application mode check.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-005
******************************************************************************/
static uint8_t FunApp_Jump_to_App_Check(uint8_t u8Para)
{
	(void)WatchDogApp_Initial(DISABLE);
	(void)FunApp_Irq_Disable();
	(void)FunApp_Jump_to_App(NOTHING);
    (void)(u8Para);
    return u8Para;
}

/******************************************************************************
;	Function Name			:	static uint8_t FunApp_App_Crc_Check(uint8_t u8Para)
;	Function Description	:	App memory CRC32 check.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-006
******************************************************************************/
static uint8_t FunApp_App_Crc_Check(void)
{
	if(I2c0SlaveApp_Crc32_Check(TIMES_APP_MEM) == true)		/* Check APP CRC */
	{	
        #if DEBUG_UART
			Uart1App_String_Show("App Crc32 PASS\r");
			Uart1App_String_Show("Jump to APP mode\r");
        #endif
        (void)FunApp_Jump_to_App_Check(NOTHING);/* Jump to APP */
					
		gbCrc32FailFlag = false;	/* CRC32 is correct */
	}
	else
	{
        #if DEBUG_UART
			Uart1App_String_Show("App Crc32 ERROR\r");
        #endif
		if(RegsAccessDriver_System_Reset_RCAUSE_Get() == (uint8_t)(RSTC_RCAUSE_POR_Msk))		/* Check POR Reset */
		{
			*u16SessionKeyRAM = (uint16_t)(CLR_KEYS);	
			(void)InitApp_StateMachine_Set(BL_PREINIT);
            #if DEBUG_UART
				Uart1App_String_Show("Into BL_TASK\r");
            #endif
		}
		else
		{
			(void)InitApp_StateMachine_Set(BL_PREINIT);
			#if DEBUG_UART
				Uart1App_String_Show("Into BL_TASK\r");
            #endif
		}
		gbCrc32FailFlag = true;	/* CRC32 is failure */
	}

	return true;
}

/******************************************************************************
;	Function Name			:	uint8_t FunApp_Startup_Check(uint8_t u8Para)
;	Function Description	:	Check jump to App mode or bootloader mode.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-007
******************************************************************************/
uint8_t FunApp_Startup_Check(void)
{

	if(RegsAccessDriver_System_Reset_RCAUSE_Get() == (uint8_t)(RSTC_RCAUSE_SYST_Msk))	/* Check software reset */
	{
		#if DEBUG_UART
			Uart1App_Boot_Keys_Show(*u16AccessKey0RAM, *u16AccessKey1RAM, *u16SessionKeyRAM);
        #endif
		if((*u16AccessKey0RAM == (uint16_t)(CHK_ACCESS_KEY_0)) && (*u16AccessKey1RAM == (uint16_t)(CHK_ACCESS_KEY_1)) && (*u16SessionKeyRAM == (uint16_t)(CHK_SESSION_KEY)))
		{
			*u16AccessKey0RAM = (uint16_t)(CLR_KEYS);					/* Clear access key 0 */
			*u16AccessKey1RAM = (uint16_t)(CLR_KEYS);					/* Clear access key 1 */
			*u16SessionKeyRAM = (uint16_t)(CLR_KEYS);					/* Clear session key */
			(void)InitApp_StateMachine_Set(BL_PREINIT);
			#if DEBUG_UART
				Uart1App_String_Show("Into BL_TASK\r");
			#endif
		}
		else
		{
			(void)I2c0SlaveApp_BL_Status1_Set(SET_SESSION_KEY_ERR);         /* Session key is failure, set session key error flag */
			(void)FunApp_App_Crc_Check();							/* Check App memory */
		}
		gbCrc32FailFlag = false;
	}
	else
	{
		(void)FunApp_App_Crc_Check();
	}
    
	return true;
}

/******************************************************************************
;	Function Name			:	uint8_t FunApp_Nvic_Init(uint8_t u8Para)
;	Function Description	:	Initialize NVIC function. 
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:   GM_BL_FUN-008
******************************************************************************/
uint8_t FunApp_Nvic_Init(void)
{
	#if MICROCHIP_ARM_ENV
		/* Enable NVIC Controller */
		__DMB();
		__enable_irq();
	#endif

    return true;
}

/******************************************************************************
;	Function Name			:	bool FunApp_Crc32FailFlag_Get(void)
;	Function Description	:	Get APP CRC32 vaules.
;	Parameters				:	void
;	Return Values			:	Return CRC32 failure status.
;	Source ID				:	GM_BL_FUN-009
******************************************************************************/
bool FunApp_Crc32FailFlag_Get(void)
{
	return gbCrc32FailFlag;
}
/*----------------------------------------------------------------------------*/
