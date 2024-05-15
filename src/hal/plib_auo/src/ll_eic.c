/*******************************************************************************
  External Interrupt Controller (EIC)

  Company
    AUO

  File Name
    Eic.c
 
  Version
    1.00.02

  Summary
    Source for EIC peripheral library interface Implementation.

  Description
    This file defines the interface to the EIC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "hal/plib_auo/inc/ll_eic.h"
#include "hal_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
static uint8_t gu8EicInterruptHandler;
// *****************************************************************************
// *****************************************************************************

/* EIC Channel Callback object */
static EIC_CALLBACK_OBJ eicCallbackObject[EXTINT_COUNT];

/******************************************************************************
* Function Name         :EIC_Init
* Function Description  :EIC function Initilization.
* Parameter				:Eic initial parameter structure - tdEicInit
* Return Value 			:u8Ret, 0x01-Initial Pass, 0x00-Initial Fail
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = Eic_Init(ptdEicInit);
* if(u8InitialResult==true)
* {
*    </code>
* }
* else if(u8InitialResult==false)
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_Init(eic_init_t tdEicInit)
{   
    uint8_t u8Status;
    uint32_t u32Input;
    
    u8Status = LL_Eic_SoftwareReset(12000U);  /*12000 = 5ms*/ 
    if(u8Status == DRIVER_TRUE)
    {
        u8Status = LL_Eic_ClockSeletion(tdEicInit.u8ClockSelect);
        if(u8Status == DRIVER_TRUE)
        {
            u8Status = LL_Eic_SenseFilterSetting(tdEicInit);
            if(u8Status == DRIVER_TRUE)
            {
                u32Input = (uint32_t)(tdEicInit.tdDebounce.u16EnableChannel);
                u8Status = LL_Eic_DebounceEnable(u32Input);
                if(u8Status == DRIVER_TRUE)
                {
                    u8Status = LL_Eic_DebounceSetting(tdEicInit.tdDebounce);
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

/******************************************************************************
* Function Name         :Eic_Enable
* Function Description  :This function enables EIC.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)EIC_Enable(NOTHING);
* </code>
* Remarks               :N/A EIC_CTRLA_ENABLE_Msk
******************************************************************************/
uint8_t LL_Eic_Enable(uint32_t u32Timeout)
{
    uint8_t u8Temp;
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = u32Timeout;
    uint32_t u32SWITCondition = EIC_SYNCBUSY_ENABLE(1U);	//Flag for test
    
    u8Temp = EIC_REGS->EIC_CTRLA;
    u8Temp |= EIC_CTRLA_ENABLE_Msk;
    
    EIC_REGS->EIC_CTRLA = u8Temp;
            
 	while(((EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_ENABLE_Msk) == u32SWITCondition) && (u32TimeoutTemp > 0U))
 	{
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }

    if(u32TimeoutTemp != 0U )
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_TIMEOUT; 
    }

    return u8Status;
}

/******************************************************************************
* Function Name         :Eic_Disable
* Function Description  :This function disables EIC.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)Eic_Disable(NOTHING);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t LL_Eic_Disable(uint32_t u32Timeout)
{
    uint8_t u8Temp;
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = u32Timeout;
    
    u8Temp = EIC_REGS->EIC_CTRLA;
    u8Temp &= ~EIC_CTRLA_ENABLE_Msk;
    
    EIC_REGS->EIC_CTRLA = u8Temp;
    
    
    while(((EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_ENABLE_Msk) == EIC_SYNCBUSY_ENABLE(1U)) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }

    if(u32TimeoutTemp != 0U )
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_TIMEOUT; 
    }
    
    return u8Status;
}
#endif

/******************************************************************************
* Function Name         :Eic_ClockSeletion
* Function Description  :Selects EIC clock.
* Parameter				:Setting Clock type
* Return Value 			:u8ClockResult, 0x01-Select GCLK, 0x00-select ULP32K, 0xFF-Setting Error
* Source ID    			:N/A
* Example               :
* <code>
* u8SelectClock = Eic_ClockSeletion(u8Clock);
* if(SelectClock==EIC_CLK_GCLK)
* {
*    </code>
* }
* else if(SelectClock==EIC_CLK_ULP32K)
* {
*    </code>
* }
* else
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_ClockSeletion(uint8_t u8Clock)
{
    uint8_t u8Temp;
    uint8_t u8Status;
    
    u8Temp = EIC_REGS->EIC_CTRLA;
    
    if(u8Clock == EIC_CLK_GCLK)
    {
        u8Temp &= ~EIC_CTRLA_CKSEL_Msk;
        EIC_REGS->EIC_CTRLA = u8Temp;
        u8Status = DRIVER_TRUE;
    }
    else if(u8Clock == EIC_CLK_ULP32K)
    {
        u8Temp |= EIC_CTRLA_CKSEL_Msk;
        EIC_REGS->EIC_CTRLA = u8Temp;
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
      
    return u8Status;
}

/******************************************************************************
* Function Name         :Eic_SoftwareReset
* Function Description  :Reset all EIC registers.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)Eic_SoftwareReset(NOTHING);
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_SoftwareReset(uint32_t u32Timeout)
{
    uint8_t u8Temp;
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = u32Timeout;
    uint32_t u32SWITCondition = EIC_SYNCBUSY_SWRST(1U);		//Flag for test
    
    u8Temp = EIC_REGS->EIC_CTRLA;
    u8Temp |= EIC_CTRLA_SWRST_Msk; 
    EIC_REGS->EIC_CTRLA = u8Temp;
   
    while(((EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_SWRST_Msk) == u32SWITCondition) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }

    if(u32TimeoutTemp != 0U )
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_TIMEOUT; 
    }

    return u8Status;  
}

/******************************************************************************
* Function Name         :Eic_SenseFilterSetting
* Function Description  :Setting EIC sense and filter enable.
* Parameter				:Eic initial parameter structure - tdEicInit
* Return Value 			:u8Ret, 0x01-Setting pass which u16EventControl is consistent with u8FilterEnable and u8Sense meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8SettingResult = Eic_SenseFilterSetting(ptdEicInit);
* if(u8SettingResult==true)
* {
*    </code>
* }
* else if(u8SettingResult==false)
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_SenseFilterSetting(eic_init_t tdEicInit)
{
    uint8_t u8Channel;
    uint8_t u8Status;
    uint8_t u8Shift;
    
    /* Clear all setting */
    EIC_REGS->EIC_CONFIG[0U] = 0U;
    EIC_REGS->EIC_CONFIG[1U] = 0U;
    
    u8Status = DRIVER_TRUE;
    
    /* Config sense setting */
    for(u8Channel = 0U; u8Channel < 16U; u8Channel++)
    {
        (void)(u8Status);
        if((tdEicInit.u8Sense[u8Channel] <= EIC_CONFIG_SENSE_LOW) && (tdEicInit.u8FilterEnable[u8Channel] <= EIC_FILTER_ENABLE))
        {
            if(u8Channel < 8U)
            {
                u8Shift = 4U * u8Channel;
            }
            else
            {
                u8Shift = (4U * u8Channel) - 32U;
            }
            EIC_REGS->EIC_CONFIG[(u8Channel >> 3U)] |= (uint32_t)(tdEicInit.u8FilterEnable[u8Channel]) << (u8Shift + 3U);
            EIC_REGS->EIC_CONFIG[(u8Channel >> 3U)] |= (uint32_t)(tdEicInit.u8Sense[u8Channel]) << u8Shift;
        }
        else
        {
            u8Status = DRIVER_PARAMETER_ERROR;
            break;
        }
    }
    
    return u8Status;
}
/******************************************************************************
* Function Name         :Eic_PinStateRead
* Function Description  :These function return the valid pin state of the debounced external interrupt pin EXTINTx.
* Parameter				:u32Pin - EIC Pin number
* Return Value 			:u8Pin_level,
*                        0x01 - high level
*                        0x00 - low level
*                        0xFF - format error
* Source ID    			:N/A
* Example               :
* <code>
* u8Pinlevel = Eic_PinStateRead(EIC_EXTINTEO_PIN_0);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t LL_Eic_PinStateRead(uint32_t u32Pin)
{
    uint8_t u8PinLevel;
    uint16_t u16Temp;
    
    switch(u32Pin)
    {
        case EIC_EXTINTEO_PIN_0:
        case EIC_EXTINTEO_PIN_1:
        case EIC_EXTINTEO_PIN_2:
        case EIC_EXTINTEO_PIN_3:
        case EIC_EXTINTEO_PIN_4:
        case EIC_EXTINTEO_PIN_5:
        case EIC_EXTINTEO_PIN_6:       
        case EIC_EXTINTEO_PIN_7:
        case EIC_EXTINTEO_PIN_9:
        case EIC_EXTINTEO_PIN_10:
        case EIC_EXTINTEO_PIN_11:      
        case EIC_EXTINTEO_PIN_12:
        case EIC_EXTINTEO_PIN_13:
        case EIC_EXTINTEO_PIN_14:
        case EIC_EXTINTEO_PIN_15:
            u16Temp = (uint16_t)((EIC_REGS->EIC_PINSTATE & EIC_PINSTATE_Msk) & u32Pin);
            
            if(u16Temp == 0U)
            {
                u8PinLevel = 0U;
            }
            else
            {
                u8PinLevel = 1U;
            }    
            break;        
        default:
            u16Temp = 0U;
            u8PinLevel = 0xFFU;
            (void)(u16Temp);
            break;
    }
    return u8PinLevel;
}
#endif

uint8_t LL_Eic_DebounceStatus0(uint8_t u8Status0)
{
    uint32_t u32ConfigTemp;
    uint8_t u8Status;
    uint32_t u32SWITCondition = EIC_DPRESCALER_STATES0(u8Status0);
    
    u32ConfigTemp = EIC_REGS->EIC_DPRESCALER;
    u32ConfigTemp &= ~EIC_DPRESCALER_STATES0_Msk;
    
    u32ConfigTemp |= EIC_DPRESCALER_STATES0(u8Status0);
    EIC_REGS->EIC_DPRESCALER = u32ConfigTemp;
    
    if(u8Status0 <= EIC_DPRESCALER_STATES0_LFREQ7_Val)
    {
        if((EIC_REGS->EIC_DPRESCALER & EIC_DPRESCALER_STATES0_Msk) == u32SWITCondition)
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

uint8_t LL_Eic_DebounceStatus1(uint8_t u8Status1)
{
    uint32_t u32ConfigTemp;
    uint8_t u8Status;
    uint32_t u32SWITCondition = EIC_DPRESCALER_STATES1(u8Status1);
    
    u32ConfigTemp = EIC_REGS->EIC_DPRESCALER;
    u32ConfigTemp &= ~EIC_DPRESCALER_STATES1_Msk;
    
    u32ConfigTemp |= EIC_DPRESCALER_STATES1(u8Status1);
    EIC_REGS->EIC_DPRESCALER = u32ConfigTemp;
    
    if(u8Status1 <= EIC_DPRESCALER_STATES1_LFREQ7_Val)
    {
        if((EIC_REGS->EIC_DPRESCALER & EIC_DPRESCALER_STATES1_Msk) == u32SWITCondition)
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

uint8_t LL_Eic_DebounceTick(uint8_t u8Tickon)
{
    uint32_t u32ConfigTemp;
    uint8_t u8Status;
    uint32_t u32SWITCondition = EIC_DPRESCALER_TICKON((uint32_t)(u8Tickon));
    
    u32ConfigTemp = EIC_REGS->EIC_DPRESCALER;
    u32ConfigTemp &= ~EIC_DPRESCALER_TICKON_Msk;
    
    u32ConfigTemp |= EIC_DPRESCALER_TICKON((uint32_t)(u8Tickon));
    EIC_REGS->EIC_DPRESCALER = u32ConfigTemp;
    
    if(u8Tickon <= EIC_DPRESCALER_TICKON_CLK_LFREQ_Val)
    {
        if((EIC_REGS->EIC_DPRESCALER & EIC_DPRESCALER_TICKON_Msk) == u32SWITCondition)
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
/******************************************************************************
* Function Name         :Eic_DebounceSetting
* Function Description  :Setting EIC debouncer channel and prescaler 
* Parameter				:tdDebouncer_init
* Return Value 			:u8Ret, 
*                        0x01 - setting pass
*                        0x00 - setting fail
* Source ID    			:N/A
* Example               :
* <code>
* u8SettingResult = Eic_DebounceSetting(tdDebouncer_init);
* if(u8SettingResult==true)
* {
*    </code>
* }
* else if(u8SettingResult==false)
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_DebounceSetting(eic_debounce_init_t tdDebouncer_init)
{
    uint8_t u8Status;
    
    EIC_REGS->EIC_DPRESCALER = 0UL;
    
    u8Status = LL_Eic_DebouncePrescaler0Set(tdDebouncer_init);
    if(u8Status == DRIVER_TRUE)
    {
        u8Status = LL_Eic_DebouncePrescaler1Set(tdDebouncer_init);
        if(u8Status == DRIVER_TRUE)
        {
            u8Status = LL_Eic_DebounceStatus0(tdDebouncer_init.u8States0);
            if(u8Status == DRIVER_TRUE)
            {
                u8Status = LL_Eic_DebounceStatus1(tdDebouncer_init.u8States1);
                if(u8Status == DRIVER_TRUE)
                {
                    u8Status = LL_Eic_DebounceTick(tdDebouncer_init.u8Tickon);
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
uint8_t LL_Eic_DebouncePrescaler0Set(eic_debounce_init_t tdDebouncer_init)
{
    uint8_t u8Status;
    uint32_t u32Temp;
    
    u32Temp = EIC_REGS->EIC_DPRESCALER;
    u32Temp = u32Temp & (~EIC_DPRESCALER_PRESCALER0_Msk);
    
    switch(tdDebouncer_init.u8Prescaler0)
    {
        case EIC_DPRESCALER_PRESCALER0_DIV2_Val:
            u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV2;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV4_Val:
            u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV4;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV8_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV8;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV16_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV16;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV32_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV32;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV64_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV64;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV128_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV128;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER0_DIV256_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER0_DIV256;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;       
        default:
            u8Status = DRIVER_PARAMETER_ERROR;
            break;
    }
    
    return u8Status;
}
uint8_t LL_Eic_DebouncePrescaler1Set(eic_debounce_init_t tdDebouncer_init)
{
    uint8_t u8Status;
    uint32_t u32Temp;
    
    u32Temp = EIC_REGS->EIC_DPRESCALER;
    u32Temp = u32Temp & (~EIC_DPRESCALER_PRESCALER1_Msk);
    
    switch(tdDebouncer_init.u8Prescaler1)
    {
        case EIC_DPRESCALER_PRESCALER1_DIV2_Val:
            u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV2;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV4_Val:
            u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV4;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV8_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV8;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV16_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV16;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV32_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV32;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV64_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV64;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV128_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV128;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;
        case EIC_DPRESCALER_PRESCALER1_DIV256_Val:
           u32Temp = u32Temp | EIC_DPRESCALER_PRESCALER1_DIV256;
            EIC_REGS->EIC_DPRESCALER = u32Temp;
            u8Status = DRIVER_TRUE;
            break;       
        default:
            u8Status = DRIVER_PARAMETER_ERROR;
            break;
    }
    
    return u8Status;
}
/******************************************************************************
* Function Name         :Eic_DebounceEnable
* Function Description  :These function will enable the debounce mode.
* Parameter				:u32Channel - EIC Pin
* Return Value 			:u8Ret,
*                        0x01 - enable successfully
*                        0x00 - enable fail
* Source ID    			:N/A
* Example               :
* <code>
* u8Pass = Eic_DebounceEnable(EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1);
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_DebounceEnable(uint32_t u32Channel)
{
    uint8_t u8Status;
    
    if(u32Channel <= 0x0000FFFFUL)
    {
        EIC_REGS->EIC_DEBOUNCEN = EIC_REGS->EIC_DEBOUNCEN | u32Channel;
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    } 
    
    return u8Status;
}
/******************************************************************************
* Function Name         :Eic_DebounceDisable
* Function Description  :These function will disable the debounce mode.
* Parameter				:u32Channel - EIC Pin
* Return Value 			:u8Ret,
*                        0x01 - enable successfully
*                        0x00 - enable fail
* Source ID    			:N/A
* Example               :
* <code>
* u8Pass = Eic_DebounceDisable(EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t LL_Eic_DebounceDisable(uint32_t u32Channel)
{
    uint8_t u8Status;
    
    if(u32Channel <= 0x0000FFFFUL)
    {
        EIC_REGS->EIC_DEBOUNCEN = EIC_REGS->EIC_DEBOUNCEN & (~u32Channel);
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }   
    return u8Status;
}
#endif
/******************************************************************************
* Function Name         :Eic_InterruptEnable
* Function Description  :This function enables interrupts on an external interrupt pin.
*                        When enabled, the interrupt pin sense will be configured as per the
*                        configuration set in MHC.
* Parameter				:u32Pin - EIC Pin number
* Return Value 			:u8Ret, 0x01-Setting pass which pin meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = Eic_Init(ptdEicInit);
* if(u8InitialResult==true)
* {
*    if(u8SettingResult = EIC_InterruptEnable(EIC_PIN_3))
*    {
*       </code>
*    }
*    else
*    {
*       </code>
*    }
* }
* else
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
uint8_t LL_Eic_InterruptEnable (uint32_t u32Pin)
{
    uint8_t u8Status;
    
    if(u32Pin < EIC_PIN_MAX)
    {
        EIC_REGS->EIC_INTENSET = (1U << u32Pin);
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
 
    return u8Status;
}

/******************************************************************************
* Function Name         :Eic_InterruptEnable
* Function Description  :Disables interrupts on a pin.
* Parameter				:u32Pin - EIC Pin number
* Return Value 			:u8Ret, 0x01-Setting pass which pin meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = Eic_Init(ptdEicInit);
* if(u8InitialResult==true)
* {
*    if(u8SettingResult = EIC_InterruptDisable(EIC_PIN_3))
*    {
*       </code>
*    }
*    else
*    {
*       </code>
*    }
* }
* else
* {
*    </code>
* }
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t LL_Eic_InterruptDisable (uint32_t u32Pin)
{
    uint8_t u8Status;
    
    if(u32Pin < EIC_PIN_MAX)
    {
        EIC_REGS->EIC_INTENCLR = (1U << u32Pin);
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }

    return u8Status;
}
#endif

/******************************************************************************
* Function Name         :Eic_CallbackRegister
* Function Description  :N/A
* Parameter				:N/A
* Return Value 			:N/A
* Source ID    			:N/A
* Example               :N/A
* Remarks               :This comment is sort out by Yousheng.cehn. Please Coding member Frank supplement
******************************************************************************/
uint8_t LL_Eic_CallbackRegister(uint32_t u32Pin, EIC_CALLBACK tdCallback, uintptr_t tdContext)
{
    uint8_t u8Status;
    
    if((u32Pin < EIC_PIN_MAX) && (tdCallback != NULL))
    {
        eicCallbackObject[u32Pin].u32EicPinNo = u32Pin;    
        eicCallbackObject[u32Pin].EICcallback = tdCallback;
        eicCallbackObject[u32Pin].context  = tdContext;
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    (void)(eicCallbackObject[u32Pin].u32EicPinNo);
    (void)(eicCallbackObject[u32Pin].EICcallback);
    (void)(eicCallbackObject[u32Pin].context);
    return u8Status;
}

/******************************************************************************
* Function Name         :LL_EIC_Handler
* Function Description  :N/A
* Parameter				:N/A
* Return Value 			:N/A
* Source ID    			:N/A
* Example               :N/A
* Remarks               :This comment is sort out by Yousheng.cehn. Please Coding member Frank supplement
******************************************************************************/
void LL_EIC_Handler(void)
{
    uint8_t currentChannel;
    uint32_t eicIntFlagStatus = 0U;

    gu8EicInterruptHandler = 0U;
    
    /* Find any triggered channels, run associated callback handlers */
    for (currentChannel = 0U; currentChannel < EXTINT_COUNT; currentChannel++)
    {
        (void)(eicIntFlagStatus);
        
        /* Verify if the EXTINT x Interrupt Pin is enabled */
        if ((eicCallbackObject[currentChannel].u32EicPinNo == currentChannel))
        {
            /* Read the interrupt flag status */
            eicIntFlagStatus = EIC_REGS->EIC_INTFLAG & (1U << currentChannel);

            if (eicIntFlagStatus > 0U)
            {
                eicCallbackObject[currentChannel].EICcallback(eicCallbackObject[currentChannel].context);
                gu8EicInterruptHandler += 1U;

                /* Clear interrupt flag */
                EIC_REGS->EIC_INTFLAG = (1U << currentChannel);
            }
        }
    }
}

