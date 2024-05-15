/****************************************************************************************
;       Program		: WakeCtrlApp.h
;       Function	: Control MCU power management
;       Date		: 2020 / 06 / 10
;       Author		: Jack.Wu
;       Describe	: Implement WakeUp/Sleep Pin Control (PORT_PIN_PA06)
;                     Power Sequence On/Off , External interrupt I/O trigger WakeUp
*****************************************************************************************/

#ifndef WAKECTRLAPP_H    /* Guard against multiple inclusion */
#define WAKECTRLAPP_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include "hal/inc/EicDriver.h"
#include "hal/inc/PMDriver.h"
#include "app/inc/I2cMasterApp.h"
    
#define VALUE_CLEAN              0U
#define DEBOUNCE_COUNT_DONE      0U
#define INTO_SLEEP_TIMES         10U
#define INTO_WAKEUP_TIMES        10U    
#define COUNT_1                  0x0001U
#define WAKEUP_EXIT_PIN_NUMBER   EIC_PIN_6

uint8_t WakeCtrlApp_Period_WakePin_Check(uint16_t u16DebounceNum);
uint8_t WakeCtrlApp_Period_WakePin_Just_Check(uint16_t u16DebounceNum);
void WakeCtrlApp_Sleep_ExternalPin_Set(void);
void WakeCtrlApp_Eic_Wakeup(uintptr_t context);
uint8_t WakeCtrlApp_PreSleep_Driver_DeInitial(uint8_t u8Para);
uint8_t WakeCtrlApp_Parameter_Initial(uint8_t u8Value);
uint8_t WakeCtrlApp_Sleep_Mode(uint8_t u8Para);
uint8_t WakeCtrlApp_Sleep_Wake_Check(uint16_t u16DebounceNum);
#if 0
bool WakeCtrlApp_Program_To_Sleep_Get(void);
#endif
bool WakeCtrlApp_Program_To_Sleep_Set(bool bFlag);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* WAKECTRLAPP_H */
