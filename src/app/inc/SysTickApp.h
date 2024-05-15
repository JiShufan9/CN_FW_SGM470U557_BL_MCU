/******************************************************************************
;       Program		: SysTickApp.h
;       Function	: Declare System Tick Functions
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 07 / 12
;       Author		: Fenderson Lu & Joel Wang
******************************************************************************/
#ifndef SysTickApp_H
#define SysTickApp_H
#include "config/SGM_C21N17A_BL_CONFIG/peripheral/systick/plib_systick.h"
/*---------------------------- Define Constant ------------------------------*/
#define     INT_TIME0       1000U        /* Based on 1ms */
#define 	TIME0_1S		(1000000U / INT_TIME0)
#define 	TIME0_9S		(9000000U / INT_TIME0)
#define 	TIME0_17MS		(17000U / INT_TIME0)

#define		SET_DEFAULT			0U
#define		COUNTING_DONE		0U
/*---------------------------- Support Function -----------------------------*/
#define		SysTickApp_Irq_Disable(u8Irq)						(NVIC_DisableIRQ(u8Irq))
#define		SysTickApp_Irq_Enable(u8Irq)						(NVIC_EnableIRQ(u8Irq))
#define		SysTickApp_Initialize()                             (SYSTICK_TimerInitialize())
#define		SysTickApp_Callback_Register(callback, context)		(SYSTICK_TimerCallbackSet((callback), (context)))
#define		SysTickApp_Start()                                  (SYSTICK_TimerStart())
#define		SysTickApp_Restart()                                (SYSTICK_TimerRestart())
#define		SysTickApp_Stop()                                   (SYSTICK_TimerStop())
/*---------------------------- Declare Function -----------------------------*/
extern uint8_t SysTickApp_Init(void);
extern uint32_t SysTickApp_gu32SysTick_Get(void);
extern uint8_t SysTickApp_Virtual_OS(void);
extern void SysTickApp_Call_Back(uintptr_t context);
extern bool SysTickApp_Trigger1ms_Set(bool bFlag);
extern bool SysTickApp_Trigger1ms_Get(void);
extern bool SysTickApp_TriggerEnable_Set(bool bFlag);
extern bool SysTickApp_TriggerEnable_Get(void);
#endif



