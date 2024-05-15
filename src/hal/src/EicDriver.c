/* ************************************************************************** */
/** Descriptive File Name

  @Company
    AUO

  @File Name
    EicDriver.c

  @Version
    1.00.02
	
  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "hal/inc/EicDriver.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/******************************************************************************
* Function Name         :EicDriver_Demo_Initialize
* Function Description  :N/A
* Parameter				:N/A
* Return Value 			:N/A
* Source ID    			:N/A
* Example               :N/A
* Remarks               :This comment is sort out by Yousheng.cehn. Please Coding member Frank supplement
******************************************************************************/
#if 0
uint8_t EicDriver_Demo_Initialize(uint8_t u8Nothing)
{
    eic_init_t tdEicInit;
    
    //EIC_CLK_GCLK, EIC_CLK_ULP32K
    tdEicInit.u8ClockSelect = EIC_CLK_ULP32K;
    
    // EIC Pin0
    tdEicInit.u8FilterEnable[EIC_PIN_0] = EIC_FILTER_ENABLE;
    tdEicInit.u8Sense[EIC_PIN_0] = EIC_CONFIG_SENSE_RISE;
    
    // EIC Pin1
    tdEicInit.u8FilterEnable[EIC_PIN_1] = EIC_FILTER_ENABLE;
    tdEicInit.u8Sense[EIC_PIN_1] = EIC_CONFIG_SENSE_FALL;
    
    // EIC Pin15
    tdEicInit.u8FilterEnable[EIC_PIN_15] = EIC_FILTER_ENABLE;
    tdEicInit.u8Sense[EIC_PIN_15] = EIC_CONFIG_SENSE_BOTH;   
    
    tdEicInit.u16EventControl = EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1 |EIC_EXTINTEO_PIN_15;
    
    // debouncer prescaler 
    tdEicInit.tdDebounce.u8Tickon = EIC_DPRESCALER_TICKON_CLK_LFREQ_Val;
    tdEicInit.tdDebounce.u16EnableChannel = EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1 |EIC_EXTINTEO_PIN_15;
    
    tdEicInit.tdDebounce.u8States0 = EIC_DPRESCALER_STATES0_LFREQ3_Val;
    tdEicInit.tdDebounce.u8Prescaler0 = EIC_DPRESCALER_PRESCALER0_DIV16_Val;
    
    tdEicInit.tdDebounce.u8States1 = EIC_DPRESCALER_STATES0_LFREQ7_Val;
    tdEicInit.tdDebounce.u8Prescaler1 = EIC_DPRESCALER_PRESCALER1_DIV64_Val;
    (void)EicDriver_init(tdEicInit);
   
//Example Register ISR   
//    (void)Eic_CallbackRegister (EIC_PIN_1, (EIC_CALLBACK) test,(uintptr_t)NULL);
//    (void)EicDriver_InterruptEnable(EIC_PIN_1);

    (void)EicDriver_Enable(NOTHING);
    
    NVIC_SetPriority(EIC_IRQn, 2);
    NVIC_EnableIRQ(EIC_IRQn);
    
    (void)u8Nothing;
    return u8Nothing;
}
#endif

/******************************************************************************
* Function Name         :EicDriver_init
* Function Description  :EIC function Initilization.
* Parameter				:Eic initial parameter structure - tdEicInit
* Return Value 			:u8Ret, 0x01-Initial Pass, 0x00-Initial Fail
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = EicDriver_init(ptdEicInit);
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
uint8_t EicDriver_init(eic_init_t tdEicInit)
{
    return LL_Eic_Init(tdEicInit);
}

/******************************************************************************
* Function Name         :EicDriver_Enable
* Function Description  :This function enables EIC.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)EicDriver_Enable(NOTHING);
* </code>
* Remarks               :N/A EIC_CTRLA_ENABLE_Msk
******************************************************************************/
uint8_t EicDriver_Enable(uint8_t u8Nothing)
{
    (void)u8Nothing;
    return LL_Eic_Enable(1000U);
}

/******************************************************************************
* Function Name         :EicDriver_Disable
* Function Description  :This function disables EIC.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)EicDriver_Disable(NOTHING);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t EicDriver_Disable(uint8_t u8Nothing)
{
    (void)u8Nothing;
    return LL_Eic_Disable(1000U);
}
#endif

/******************************************************************************
* Function Name         :EicDriver_ClockSeletion
* Function Description  :Selects EIC clock.
* Parameter				:Setting Clock type
* Return Value 			:u8ClockResult, 0x01-Select GCLK, 0x00-select ULP32K, 0xFF-Setting Error
* Source ID    			:N/A
* Example               :
* <code>
* u8SelectClock = EicDriver_ClockSeletion(u8Clock);
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
#if 0
uint8_t EicDriver_ClockSeletion(uint8_t u8Clock)
{
    return  LL_Eic_ClockSeletion(u8Clock);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_SoftwareReset
* Function Description  :Reset all EIC registers.
* Parameter				:u8Nothing
* Return Value 			:u8Nothing
* Source ID    			:N/A
* Example               :
* <code>
* (void)EicDriver_SoftwareReset(NOTHING);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t EicDriver_SoftwareReset(uint8_t u8Nothing)
{
    (void)u8Nothing;
    return LL_Eic_SoftwareReset(12000U);    /*12000 = 5ms*/
}
#endif
/******************************************************************************
* Function Name         :EicDriver_SenseFilterSetting
* Function Description  :Setting EIC sense and filter enable.
* Parameter				:Eic initial parameter structure - tdEicInit
* Return Value 			:u8Ret, 0x01-Setting pass which u16EventControl is consistent with u8FilterEnable and u8Sense meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8SettingResult = EicDriver_SenseFilterSetting(ptdEicInit);
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
#if 0
uint8_t EicDriver_SenseFilterSetting(eic_init_t tdEicInit)
{
    return LL_Eic_SenseFilterSetting(tdEicInit);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_PinStateRead
* Function Description  :These function return the valid pin state of the debounced external interrupt pin EXTINTx.
* Parameter				:u32Pin - EIC Pin number
* Return Value 			:u8Pin_level,
*                        0x01 - high level
*                        0x00 - low level
*                        0xFF - format error
* Source ID    			:N/A
* Example               :
* <code>
* u8Pinlevel = EicDriver_PinStateRead(EIC_EXTINTEO_PIN_0);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t EicDriver_PinStateRead(uint32_t u32Pin)
{
    return LL_Eic_PinStateRead(u32Pin);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_DebouncePrescalerSetting
* Function Description  :Setting EIC debouncer channel and prescaler 
* Parameter				:tdDebouncer_init
* Return Value 			:u8Ret, 
*                        0x01 - setting pass
*                        0x00 - setting fail
* Source ID    			:N/A
* Example               :
* <code>
* u8SettingResult = EicDriver_DebouncePrescalerSetting(tdDebouncer_init);
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
uint8_t EicDriver_DebouncePrescalerSetting(eic_debounce_init_t tdDebouncer_init)
{
    return LL_Eic_DebounceSetting(tdDebouncer_init);
}
/******************************************************************************
* Function Name         :EicDriver_DebounceEnable
* Function Description  :These function will enable the debounce mode.
* Parameter				:u32Channel - EIC Pin
* Return Value 			:u8Ret,
*                        0x01 - enable successfully
*                        0x00 - enable fail
* Source ID    			:N/A
* Example               :
* <code>
* u8Pass = EicDriver_DebounceEnable(EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t EicDriver_DebounceEnable(uint32_t u32Channel)
{
    return LL_Eic_DebounceEnable(u32Channel);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_DebounceDisable
* Function Description  :These function will disable the debounce mode.
* Parameter				:u32Channel - EIC Pin
* Return Value 			:u8Ret,
*                        0x01 - disable successfully
*                        0x00 - disable fail
* Source ID    			:N/A
* Example               :
* <code>
* u8Pass = EicDriver_DebounceDisable(EIC_EXTINTEO_PIN_0 | EIC_EXTINTEO_PIN_1);
* </code>
* Remarks               :N/A
******************************************************************************/
#if 0
uint8_t EicDriver_DebounceDisable(uint32_t u32Channel)
{
    return LL_Eic_DebounceDisable(u32Channel);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_InterruptEnable
* Function Description  :This function enables interrupts on an external interrupt pin.
*                        When enabled, the interrupt pin sense will be configured as per the
*                        configuration set in MHC.
* Parameter				:pin - EIC Pin number
* Return Value 			:u8Ret, 0x01-Setting pass which pin meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = EicDriver_init(ptdEicInit);
* if(u8InitialResult==true)
* {
*    if(u8SettingResult = EicDriver_InterruptEnable(EIC_PIN_3))
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
uint8_t EicDriver_InterruptEnable (uint32_t u32Pin)
{
    return LL_Eic_InterruptEnable (u32Pin);
}

/******************************************************************************
* Function Name         :EicDriver_InterruptDisable
* Function Description  :Disables interrupts on a pin.
* Parameter				:pin - EIC Pin number
* Return Value 			:u8Ret, 0x01-Setting pass which pin meets the setting range, 0x00-Setting false
* Source ID    			:N/A
* Example               :
* <code>
* u8InitialResult = EicDriver_init(ptdEicInit);
* if(u8InitialResult==true)
* {
*    if(u8SettingResult = EicDriver_InterruptDisable(EIC_PIN_3))
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
uint8_t EicDriver_InterruptDisable (uint32_t u32Pin)
{
    return LL_Eic_InterruptDisable (u32Pin);
}
#endif
/******************************************************************************
* Function Name         :EicDriver_CallbackRegister
* Function Description  :N/A
* Parameter				:N/A
* Return Value 			:N/A
* Source ID    			:N/A
* Example               :N/A
* Remarks               :This comment is sort out by Yousheng.cehn. Please Coding member Frank supplement
******************************************************************************/
uint8_t EicDriver_CallbackRegister(uint32_t u32Pin, EIC_CALLBACK tdCallback, uintptr_t context)
{
    return LL_Eic_CallbackRegister(u32Pin,tdCallback,context);
}
/* *****************************************************************************
 End of File
 */
