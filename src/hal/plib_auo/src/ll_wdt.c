#include "hal/plib_auo/inc/ll_wdt.h"
#include "hal/inc/hal_wdt.h"
#include "app/inc/FunApp.h"

static Wdt_Callback_Typedef_s tsWdtCallbackObj;

uint8_t LL_WDT_Mode_Set(uint8_t u8Mode,uint32_t u32Timeout)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = u32Timeout;
    uint32_t u32SWITCondition1 = WDT_SYNCBUSY_WEN(1U);
	uint32_t u32SWITCondition2 = WDT_CTRLA_WEN(u8Mode);
	    
    if((u8Mode == MODE_NORMAL) || (u8Mode == MODE_WINDOW))
    {
        uint8_t u8ConfigTemp  = WDT_REGS->WDT_CTRLA; 
        u8ConfigTemp &= ~WDT_CTRLA_WEN_Msk;
        u8ConfigTemp |= WDT_CTRLA_WEN(u8Mode);
        WDT_REGS->WDT_CTRLA = u8ConfigTemp;

        while(((WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_WEN_Msk) == u32SWITCondition1) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }

        if(u32TimeoutTemp != 0U )
        {
            if((WDT_REGS->WDT_CTRLA & WDT_CTRLA_WEN_Msk) == u32SWITCondition2)
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_WRITE_ERROR;
            }
        }
        else
        {
            u8Status = DRIVER_TIMEOUT; 
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
   
    return u8Status;
}
uint8_t LL_WDT_AllPeriod_Set(uint8_t u8NormalPeriod,uint8_t u8WindowPeriod) 
{
    uint8_t u8Status;
    u8Status = LL_WDT_NormalPeriod_Set(u8NormalPeriod);
    if(u8Status == DRIVER_TRUE)
    {
        u8Status = LL_WDT_WindowPeriod_Set(u8WindowPeriod);
    }
    else
    {
        ;
    }
    return u8Status;
}

uint8_t LL_WDT_NormalPeriod_Set(uint8_t u8Period)
{
    uint8_t u8Status; 
    uint8_t u8ConfigTemp;
    uint32_t u32SWITCondition = WDT_CONFIG_PER(u8Period);
    
    if(u8Period <=  WDT_16384_CLK)
    {
        u8ConfigTemp = WDT_REGS->WDT_CONFIG;
        u8ConfigTemp &= ~WDT_CONFIG_PER_Msk;
        u8ConfigTemp |= WDT_CONFIG_PER(u8Period);
        WDT_REGS->WDT_CONFIG  = u8ConfigTemp;

        if((WDT_REGS->WDT_CONFIG & WDT_CONFIG_PER_Msk) == u32SWITCondition)
        {
            u8Status = DRIVER_TRUE;
        }
        else
        {
            u8Status = DRIVER_WRITE_ERROR;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;    
}

uint8_t LL_WDT_WindowPeriod_Set(uint8_t u8Period)
{
    uint8_t u8Status;
    uint32_t u32SWITCondition = WDT_CONFIG_WINDOW(u8Period);
    
    if(u8Period <= WDT_16384_CLK)
    {
        uint8_t u8ConfigTemp  = WDT_REGS->WDT_CONFIG;
        u8ConfigTemp &= ~WDT_CONFIG_WINDOW_Msk;
        u8ConfigTemp |= WDT_CONFIG_WINDOW(u8Period);
        WDT_REGS->WDT_CONFIG  = u8ConfigTemp;

        if((WDT_REGS->WDT_CONFIG & WDT_CONFIG_WINDOW_Msk) == u32SWITCondition)
        {
            u8Status = DRIVER_TRUE;
        }
        else
        {
            u8Status = DRIVER_WRITE_ERROR;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;    
}

uint8_t LL_WDT_EarlyWarningOffset_Set(uint8_t u8OffsetPeriod)
{
    uint8_t u8Status;
    uint8_t u8ConfigTemp;
    uint32_t u32SWITCondition = WDT_EWCTRL_EWOFFSET(u8OffsetPeriod);
    
    if(u8OffsetPeriod <= WDT_16384_CLK)
    {
        u8ConfigTemp = WDT_REGS->WDT_CONFIG;
        u8ConfigTemp &= ~WDT_EWCTRL_EWOFFSET_Msk;
        u8ConfigTemp |= WDT_EWCTRL_EWOFFSET(u8OffsetPeriod);
        WDT_REGS->WDT_EWCTRL  = u8ConfigTemp;

        if((WDT_REGS->WDT_EWCTRL & WDT_EWCTRL_EWOFFSET_Msk) == u32SWITCondition)
        {
            u8Status = DRIVER_TRUE;
        }
        else
        {
            u8Status = DRIVER_WRITE_ERROR;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;    
}

uint8_t LL_WDT_AlwaryOn_Set(uint8_t u8Enable, uint32_t u32Timeout)
{
     uint8_t u8Status;
     uint32_t u32TimeoutTemp = u32Timeout;
     uint32_t u32SWITCondition1 = WDT_SYNCBUSY_ALWAYSON(1U);
	 uint32_t u32SWITCondition2 = WDT_CTRLA_ALWAYSON(u8Enable);
	      
    if(u8Enable == FUNC_ENABLE)
    {
        WDT_REGS->WDT_CTRLA |= WDT_CTRLA_ALWAYSON(u8Enable);
        
        while(((WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ALWAYSON_Msk) == u32SWITCondition1) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }
        
        if(u32TimeoutTemp > 0U)
        {
            if((WDT_REGS->WDT_CTRLA & WDT_CTRLA_ALWAYSON_Msk) == u32SWITCondition2)
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_WRITE_ERROR;
            }
        }
        else
        {
            u8Status = DRIVER_TIMEOUT;
        }
    }
    else if(u8Enable == FUNC_DISABLE)
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
     
    return u8Status;
}

void LL_WDT_ISR_Handler(uintptr_t context)
{
    /* Default disable WDT ISR */
    (void)FunApp_Delay_Millisecond(1U, MODE_ISR);   /* For MISRA-C issue : void function has no side effects. */
    (void) context;
}

uint8_t LL_WDT_Interrupt_Set(uint8_t u8Enable, uint8_t u8Priority)
{
    uint8_t u8Status;  
    uint32_t u32SWITCondition1 = WDT_INTENSET_EW(1U);
	uint32_t u32SWITCondition2 = WDT_INTENSET_EW(0U);
    pWdt_Callback tCallBack = LL_WDT_ISR_Handler;

    if(u8Priority < MAX_NVIC_PRIORITY)
    {
        /* Enable WDT Interrupt*/
        if(u8Enable == FUNC_ENABLE)
        {
            WDT_REGS->WDT_INTENSET |= WDT_INTENSET_EW(1U);
            if((WDT_REGS->WDT_INTENSET & WDT_INTENSET_EW_Msk) == u32SWITCondition1)
            {
                u8Status = LL_WDT_Callback_Register(tCallBack,(uintptr_t)NULL);
                NVIC_SetPriority(WDT_IRQn, u8Priority);
                NVIC_EnableIRQ(WDT_IRQn);
            }
            else
            {
                u8Status = DRIVER_WRITE_ERROR;
            }
        }
        /* Disable WDT Interrupt*/
        else if(u8Enable == FUNC_DISABLE)
        {
            WDT_REGS->WDT_INTENCLR |= WDT_INTENCLR_EW(1U);

            if((WDT_REGS->WDT_INTENSET & WDT_INTENSET_EW_Msk) == u32SWITCondition2)
            {
                NVIC_DisableIRQ(WDT_IRQn);
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_WRITE_ERROR;
            }        
        }
        else
        {
            u8Status = DRIVER_PARAMETER_ERROR;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    return u8Status;
}

uint8_t LL_WDT_Active(uint8_t u8Enable, uint32_t u32Timeout)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = u32Timeout;
    uint8_t u8ConfigTemp;
    uint32_t u32SWITCondition1 = WDT_CTRLA_ENABLE(u8Enable);
	uint32_t u32SWITCondition2 = WDT_SYNCBUSY_ENABLE(1U);
    
    if((u8Enable == FUNC_ENABLE) || (u8Enable == FUNC_DISABLE))
    {
        u8ConfigTemp = WDT_REGS->WDT_CTRLA;
        u8ConfigTemp &= ~WDT_CTRLA_ENABLE_Msk;
        u8ConfigTemp |= WDT_CTRLA_ENABLE(u8Enable);
        WDT_REGS->WDT_CTRLA  = u8ConfigTemp;    

        while(((WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_ENABLE_Msk) == u32SWITCondition2) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }

        if(u32TimeoutTemp > 0U)
        {
            if((WDT_REGS->WDT_CTRLA & WDT_EWCTRL_EWOFFSET_Msk) == u32SWITCondition1)
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_WRITE_ERROR;
            }
        }
        else
        {
            u8Status = DRIVER_TIMEOUT;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;   
}

uint8_t LL_WDT_Clear(uint32_t u32Timeout)
{
    uint8_t u8Status; 
    uint32_t u32TimeoutTemp = u32Timeout;
    uint32_t u32SWITCondition = WDT_SYNCBUSY_CLEAR(1U);
    
    WDT_REGS->WDT_CLEAR |= WDT_CLEAR_CLEAR(WDT_CLEAR_CLEAR_KEY_Val);
    
    while(((WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_CLEAR_Msk) == u32SWITCondition) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }
    
    if(u32TimeoutTemp > 0U)
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_TIMEOUT;
    }
    return u8Status;
}

uint8_t LL_WDT_ClearWithoutSync(void)
{  
    uint8_t u8Status;
    
    if((WDT_REGS->WDT_SYNCBUSY & WDT_SYNCBUSY_CLEAR_Msk) != WDT_SYNCBUSY_CLEAR_Msk)
    {
        WDT_REGS->WDT_CLEAR |= WDT_CLEAR_CLEAR(WDT_CLEAR_CLEAR_KEY_Val);
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_WRITE_ERROR;
    }
    return u8Status;  
}

uint8_t LL_WDT_Flag_Clear(void)
{
    uint8_t u8Status;
    uint32_t u32INTFLAG_EW = WDT_INTFLAG_EW(0U);
    
    WDT_REGS->WDT_INTFLAG |= WDT_INTFLAG_EW(1U);
    
    if((WDT_REGS->WDT_INTFLAG & WDT_INTFLAG_EW_Msk) == u32INTFLAG_EW)
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_WRITE_ERROR;
    }
    return u8Status;    
}

#if 0
uint8_t LL_WDT_Flag_Get(void)
{
    uint8_t  u8Temp;
    if((WDT_REGS->WDT_INTFLAG & WDT_INTFLAG_EW_Msk) == WDT_INTFLAG_EW(1U))
    {
        u8Temp = 1U;
    }
    else
    {
        u8Temp = 0U;
    }
    return u8Temp;
}
#endif

uint8_t LL_WDT_Callback_Register( pWdt_Callback WdtCallback, uintptr_t context)
{
    uint8_t u8Status;
    
    if(WdtCallback == NULL)
    {
        u8Status = DRIVER_REGISTER_ERROR;
    }
    else
    {
        tsWdtCallbackObj.callback = WdtCallback;
        tsWdtCallbackObj.context = context;
        u8Status = DRIVER_TRUE;
    }
    
    return u8Status;
}

void LL_WDT_Handler(void)
{
    /* Clear Early Watchdog Interrupt */
    WDT_REGS->WDT_INTFLAG = WDT_INTFLAG_EW_Msk;

	tsWdtCallbackObj.callback(tsWdtCallbackObj.context);
}

