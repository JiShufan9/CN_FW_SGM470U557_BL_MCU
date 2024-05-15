#include "isr.h"
#include "app/inc/ClockApp.h"
#include "main.h"

#ifdef HAL_WDT_ENABLED
void WDT_ISR_Handler(uintptr_t context)
{
    (void) context;
}
#endif

#ifdef HAL_CFD_ENABLED
void CFD_ISR_Handler(uintptr_t context)
{
    (void) context;
}
#endif

