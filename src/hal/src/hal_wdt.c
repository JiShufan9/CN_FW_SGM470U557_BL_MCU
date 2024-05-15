/* ***************************************************************************** 
;        Program    :   
;        chip       :   Microchip ATSAMC21N17A
;        Version    :   1.00.00
;        Author     :   Frank
;        Description:    
;    
 ******************************************************************************/ 
#include "hal/inc/hal_wdt.h"
#include "hal/plib_auo/inc/ll_wdt.h"

static Wdt_Config_Typedef_s tsWdt_Config=
{
	.u8AlwaysOnEnable = FUNC_DISABLE,
	.u8Mode = MODE_NORMAL,
	.u8FunctionEnable = FUNC_ENABLE,
	.u8InterruptEnable = NVIC_PRIORITY_LOWEST,
	.u8WindowModePeriod = WDT_8_CLK,
	.u8NormalModePeriod = WDT_8192_CLK,
	.u8EarlyWarningOffset = WDT_8_CLK,
	.u32Timeout = 12000U	/*12000 = 5ms*/
};

uint8_t HAL_WDT_Init(void)
{
    uint8_t u8Status;

	tsWdt_Config.u8AlwaysOnEnable = FUNC_DISABLE;
	tsWdt_Config.u8Mode = MODE_NORMAL;
	tsWdt_Config.u8FunctionEnable = FUNC_ENABLE;
	tsWdt_Config.u8InterruptEnable = NVIC_PRIORITY_LOWEST;
	tsWdt_Config.u8WindowModePeriod = WDT_8_CLK;
	tsWdt_Config.u8NormalModePeriod = WDT_8192_CLK;
	tsWdt_Config.u8EarlyWarningOffset = WDT_8_CLK;
	tsWdt_Config.u32Timeout = 12000U;	/*12000 = 5ms*/
    
    u8Status = LL_WDT_Mode_Set(tsWdt_Config.u8Mode, tsWdt_Config.u32Timeout);
    if(u8Status == DRIVER_TRUE)
    {
        u8Status = LL_WDT_AllPeriod_Set(tsWdt_Config.u8NormalModePeriod,tsWdt_Config.u8WindowModePeriod);
        if(u8Status == DRIVER_TRUE)
        {
            u8Status = LL_WDT_EarlyWarningOffset_Set(tsWdt_Config.u8EarlyWarningOffset);
            if(u8Status == DRIVER_TRUE)
            {
                u8Status = HAL_WDT_Interrupt_Set(tsWdt_Config.u8InterruptEnable, tsWdt_Config.u8NvicPriority);                         
                if(u8Status == DRIVER_TRUE)
                {
                    if(tsWdt_Config.u8AlwaysOnEnable == FUNC_ENABLE)
                    {
                        u8Status = LL_WDT_AlwaryOn_Set(tsWdt_Config.u8AlwaysOnEnable, tsWdt_Config.u32Timeout);
                    }
                    else
                    {
                        u8Status = HAL_WDT_Active(tsWdt_Config.u8FunctionEnable,tsWdt_Config.u32Timeout);
                    }
                }
                else
                {
                    ;
                }  
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
    
    return u8Status;
}

uint8_t HAL_WDT_DeInit(void)
{
    uint8_t u8Status;    
    
    if(tsWdt_Config.u8AlwaysOnEnable == FUNC_DISABLE)
    {
        tsWdt_Config.u8AlwaysOnEnable = FUNC_DISABLE;
        tsWdt_Config.u8EarlyWarningOffset = WDT_8_CLK;
        tsWdt_Config.u8NormalModePeriod = WDT_8_CLK;
        tsWdt_Config.u8WindowModePeriod = WDT_8_CLK;
        tsWdt_Config.u8Mode = MODE_NORMAL;
        tsWdt_Config.u8FunctionEnable = FUNC_DISABLE;
        tsWdt_Config.u8InterruptEnable = FUNC_DISABLE;
        
        (void)HAL_WDT_Clear();
        u8Status = HAL_WDT_Active(tsWdt_Config.u8FunctionEnable,tsWdt_Config.u32Timeout);
        if(u8Status == DRIVER_TRUE)
        {
            u8Status = HAL_WDT_Interrupt_Set(tsWdt_Config.u8InterruptEnable, tsWdt_Config.u8NvicPriority);     
            if(u8Status == DRIVER_TRUE)
            {
                 u8Status = LL_WDT_AllPeriod_Set(tsWdt_Config.u8NormalModePeriod,tsWdt_Config.u8WindowModePeriod);
                if(u8Status == DRIVER_TRUE)
                {
                     u8Status = LL_WDT_EarlyWarningOffset_Set(tsWdt_Config.u8EarlyWarningOffset);
                    if(u8Status == DRIVER_TRUE)
                    {
                        u8Status = LL_WDT_Mode_Set(tsWdt_Config.u8Mode, tsWdt_Config.u32Timeout);
                    }
                    else
                    {
                        ;
                    }
                }
                else
                {
                    ;
                }
            }
            else
            {
                ;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        u8Status = DRIVER_FALSE;
    }

    return u8Status;
}

uint8_t HAL_WDT_Active(uint8_t u8Enable, uint32_t u32Timeout)
{
    uint8_t u8Status;
    
    u8Status = LL_WDT_Active(u8Enable, u32Timeout);
    
    return u8Status;   
}

uint8_t HAL_WDT_Clear(void)
{
    uint8_t u8Status; 
    
    u8Status = LL_WDT_Clear(tsWdt_Config.u32Timeout);

    return u8Status;
}

uint8_t HAL_WDT_ClearWithoutSync(void)
{
    uint8_t u8Status; 
    
    u8Status = LL_WDT_ClearWithoutSync();

    return u8Status;
}

uint8_t HAL_WDT_Interrupt_Set(uint8_t u8Enable, uint8_t u8Priority)
{
    uint8_t u8Status;
    
    u8Status = LL_WDT_Flag_Clear();
    if(u8Status == DRIVER_TRUE)
    {
        u8Status =  LL_WDT_Interrupt_Set(u8Enable, u8Priority);
    }
    else
    {
        ;
    }  
    return u8Status;
}
#if 0
uint8_t HAL_WDT_Flag_Clear(void)
{
    uint8_t u8Status;

    u8Status = LL_WDT_Flag_Clear();
    
    return u8Status;    
}
uint8_t HAL_WDT_Flag_Get(void)
{
    return LL_WDT_Flag_Get();
}
#endif

