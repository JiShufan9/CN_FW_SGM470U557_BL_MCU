/******************************************************************************
;Author: Orlando Huang
;Date: 2021-09-28 18:41:28
;LastEditTime: 2021-10-07 16:12:56
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\inc\EicDriver.h
;Description: N/A
******************************************************************************/

#ifndef EICDRIVER_H    /* Guard against multiple inclusion */
#define EICDRIVER_H


#include "hal/plib_auo/inc/ll_eic.h"

uint8_t EicDriver_init(eic_init_t tdEicInit);
uint8_t EicDriver_Enable(uint8_t u8Nothing);

#if 0
uint8_t EicDriver_Disable(uint8_t u8Nothing);
uint8_t EicDriver_ClockSeletion(uint8_t u8Clock);
uint8_t EicDriver_SoftwareReset(uint8_t u8Nothing);
uint8_t EicDriver_SenseFilterSetting(eic_init_t tdEicInit);
uint8_t EicDriver_PinStateRead(uint32_t u32Pin);
#endif

uint8_t EicDriver_DebouncePrescalerSetting(eic_debounce_init_t tdDebouncer_init);

#if 0
uint8_t EicDriver_DebounceEnable(uint32_t u32Channel);
uint8_t EicDriver_DebounceDisable(uint32_t u32Channel);
#endif

uint8_t EicDriver_InterruptEnable (uint32_t u32Pin);

#if 0
uint8_t EicDriver_InterruptDisable (uint32_t u32Pin);
#endif

uint8_t EicDriver_CallbackRegister(uint32_t u32Pin, EIC_CALLBACK tdCallback, uintptr_t context);

/* *****************************************************************************
 End of File
 */

#endif

