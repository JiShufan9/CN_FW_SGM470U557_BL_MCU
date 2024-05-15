/******************************************************************************
;Author: Orlando Huang
;Date: 2021-09-28 18:41:28
;LastEditTime: 2021-10-22 09:00:31
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\plib_auo\inc\ll_wdt.h
;Description: N/A
******************************************************************************/
#ifndef LL_WDT_H
#define LL_WDT_H

#include "hal/inc/hal_common.h"

typedef void (*pWdt_Callback)(uintptr_t context);

typedef struct
{
    pWdt_Callback      callback;

    uintptr_t         context;

} Wdt_Callback_Typedef_s;

void LL_WDT_ISR_Handler(uintptr_t context);
uint8_t LL_WDT_Mode_Set(uint8_t u8Mode,uint32_t u32Timeout);
uint8_t LL_WDT_AllPeriod_Set(uint8_t u8NormalPeriod,uint8_t u8WindowPeriod);
uint8_t LL_WDT_NormalPeriod_Set(uint8_t u8Period);
uint8_t LL_WDT_WindowPeriod_Set(uint8_t u8Period);
uint8_t LL_WDT_EarlyWarningOffset_Set(uint8_t u8OffsetPeriod);
uint8_t LL_WDT_AlwaryOn_Set(uint8_t u8Enable, uint32_t u32Timeout);
uint8_t LL_WDT_Interrupt_Set(uint8_t u8Enable, uint8_t u8Priority);
uint8_t LL_WDT_Active(uint8_t u8Enable, uint32_t u32Timeout);
uint8_t LL_WDT_Clear(uint32_t u32Timeout);
uint8_t LL_WDT_ClearWithoutSync(void);
uint8_t LL_WDT_Flag_Clear(void);
#if 0
uint8_t LL_WDT_Flag_Get(void);
#endif

uint8_t LL_WDT_Callback_Register( pWdt_Callback WdtCallback, uintptr_t context);
void LL_WDT_Handler(void);

#endif
