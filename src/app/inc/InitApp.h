/******************************************************************************
;       Program		: InitApp.h
;       Function	: Declare Init and SM Function & Variable
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 04 / 08
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef INITAPP_H
#define INITAPP_H
/*---------------------------- Include File ---------------------------------*/
/*---------------------------- Define Constant ------------------------------*/
/*---------------------------- Support Function -----------------------------*/
/*---------------------------- Declare Enum ---------------------------------*/
/*---------------------------- Declare Function -----------------------------*/ 
extern uint8_t InitApp_Startup(void);
extern uint8_t InitApp_PreInitWakeupCheck(void);
extern uint8_t InitApp_All(void);
extern uint8_t InitApp_StateMachine_Get(void);
extern uint8_t InitApp_StateMachine_Set(uint8_t u8State);
#endif

