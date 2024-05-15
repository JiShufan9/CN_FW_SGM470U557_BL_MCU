#ifndef ISR_H
#define ISR_H

#include "hal/inc/hal_wdt_def.h"
#include "hal/hal_config/hal_config.h"

#ifdef HAL_WDT_ENABLED
void WDT_ISR_Handler(uintptr_t context);
#endif

#ifdef HAL_CFD_ENABLED
void CFD_ISR_Handler(uintptr_t context);
#endif

#endif
