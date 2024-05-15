/* ***************************************************************************** 
;        Program    :   
;        chip       :   Microchip ATSAMC21N17A
;        Version    :   1.00.00
;        Author     :   Frank
;        Description:    
;    
 ******************************************************************************/ 
#ifndef HAL_WDT_H
#define HAL_WDT_H

#include "../inc/hal_common.h"

/*------------------------------------------------------------------------------
Watchdog Timer Mode Define
*/
#define MODE_NORMAL                 0x00U
#define MODE_WINDOW                 0x01U
/*------------------------------------------------------------------------------
Watchdog Timer Window/Normal Modes and Early Warning Period Define
*/
#define WDT_8_CLK                   0x00U
#define WDT_16_CLK                  0x01U
#define WDT_32_CLK                  0x02U
#define WDT_64_CLK                  0x03U
#define WDT_128_CLK                 0x04U
#define WDT_256_CLK                 0x05U
#define WDT_512_CLK                 0x06U
#define WDT_1024_CLK                0x07U
#define WDT_2048_CLK                0x08U
#define WDT_4096_CLK                0x09U
#define WDT_8192_CLK                0x0AU
#define WDT_16384_CLK               0x0BU

typedef struct
{
    wdt_registers_t *tpInstance;
    uint8_t u8AlwaysOnEnable;
    uint8_t u8Mode;
    uint8_t u8FunctionEnable;
    uint8_t u8WindowModePeriod;
    uint8_t u8NormalModePeriod;
    uint8_t u8InterruptEnable;
    uint8_t u8NvicPriority;
    uint8_t u8EarlyWarningOffset;
    uint32_t u32Timeout;
}Wdt_Config_Typedef_s;

uint8_t HAL_WDT_Init(void);
uint8_t HAL_WDT_DeInit(void);
uint8_t HAL_WDT_Active(uint8_t u8Enable, uint32_t u32Timeout);
uint8_t HAL_WDT_Clear(void);
uint8_t HAL_WDT_ClearWithoutSync(void);
uint8_t HAL_WDT_Interrupt_Set(uint8_t u8Enable, uint8_t u8Priority);

#if 0
uint8_t HAL_WDT_Flag_Clear(void);
uint8_t HAL_WDT_Flag_Get(void);
#endif

#endif
