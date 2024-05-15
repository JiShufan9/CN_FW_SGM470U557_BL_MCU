/* ************************************************************************** 
;        Program    :   ClockDriver.c
;        Function   :   The system clock program
;        chip       :   Microchip ATSAMC21J18A
;        clock      :   Internal 48MHz
;        Date       :   2020 / 05 / 22
;        Author     :   Adolf   Yeh
;        Description:   System clock initial use   
;    
 *****************************************************************************/ 
/*****************************************************************************
     Using Example while we use default Internal 48MHz Osillator 
     Useage: User can append following function(SystemClock_CurrentInitial) to your code ,
             then replace CLOCK_Initialize() in SYS_Initialize() by following function(SystemClock_CurrentInitial).
             And Do not forget to include SystemCLockDriver.h
 *****************************************************************************/
/*
uint16_t SystemClock_CurrentInitial(uint16_t u16Nothing)
{
    (void)u16Nothing;                                               <= coding style rule
    SystemClock_InitTypeDef CurrentSystemClockSet;                  <=This line must have
    SystemClock_GCLKTypeDef CurrentGCLK;                            <=This line must have
    
    SystemClock_Initialize(&CurrentSystemClockSet,&CurrentGCLK);    <=This line must have , do clock initial
    
    SystemClock_EnableHSInternalOsc(&CurrentSystemClockSet);        <=This line must have, 
    
    SystemClock_EnableLSExternalCrystalOsc(&CurrentSystemClockSet); <=This line must have
                                                                    <=If user need more clock source,
                                                                      you should appeend by using following API.
 
    SystemClock_EnableGCLKN(&CurrentGCLK,GCLKENABLE0,OSC48M,DIV1);  <=This line (enable GCLK0) must have.
                                                                    <= If user need more GCLK(eg. 1~8) to assign,
                                                                       you can appeend by using following API.
    
    SystemClock_GCLKToPeripheral(GCLK_EIC,GCLKGEN0);                <=Desired peripherial clock source provide
    SystemClock_GCLKToPeripheral(GCLK_TC0_TC1,GCLKGEN0);            <=Desired peripherial clock source provide
                                                                    <= Don't forgot connect GCLK to peripheral.
 
    SystemClock_AHBClock_Enable(&CurrentSystemClockSet);            <=This line must have,
    return NOTHING;
}
*/
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "hal/inc/ClockDriver.h"
/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
/*
static int ExampleLocalFunction(int param1, int param2) {
    return 0;
}
*/

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */


/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/*******************************************************************************
   Function Name                :   ClockDriver_Initialize
   Parameters                   :   CurrentSystemClockSet:
                                    CurrentGCLK 
   Return Values                :   Nothing
   Function Descripttion        :   Initialize parameters
   
  
 *******************************************************************************/

uint8_t ClockDriver_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSet,SystemClock_GCLKTypeDef *CurrentGCLK) {
   
    /*Default Disable each Oscillator*/
    uint8_t u8Status = DEFAULT;
    CurrentSystemClockSet->u8Enable48MInternalOsc = NO;
    CurrentSystemClockSet->u8EnableHSCrystalOsc = NO;
    CurrentSystemClockSet->u8EnableFDPLL = NO;
    CurrentSystemClockSet->u8Enable32KHighAccuacyInternalOsc = NO;
    CurrentSystemClockSet->u8EnableLSCrystalOsc = NO;
    CurrentSystemClockSet->u8EnableOSCClkFault = NO;
    
    /*Default setting GCLK section*/
    
    CurrentGCLK->u16EnableNumGCLK = GCLKENABLE0;
    CurrentGCLK->u16GCLKDIV = DIV1;
    CurrentGCLK->u16GCLKSrcSelect = OSC48M;
    
    if(CurrentGCLK->u16EnableNumGCLK == GCLKENABLE0)
    {
        u8Status |= CLOCK_INIT_OK;
    }
    else
    {
        u8Status &= ~CLOCK_INIT_FAIL;
    }
    
    return u8Status;
}
/*
uint16_t ClockDriver_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSet,SystemClock_GCLKTypeDef *CurrentGCLK) {
   
    Setting each Oscillator
    
    CurrentSystemClockSet.u8Enable48MInternalOsc = NO;
    CurrentSystemClockSet.u8EnableHSCrystalOsc = NO;
    CurrentSystemClockSet.u8EnableFDPLL = NO;
    CurrentSystemClockSet.u8Enable32KHighAccuacyInternalOsc = NO;
    CurrentSystemClockSet.u8EnableLSCrystalOsc = NO;
    CurrentSystemClockSet.u8EnableAHBClk = YES;
    
    Setting HS Osc section
    
    SystemClock_OSCCtrl_Initialize(&CurrentSystemClockSet);
    
    Setting 32K Osc section
    
    SystemClock_OSC32KCtrl_Initialize(&CurrentSystemClockSet);
    
    Setting GCLK section
    
    CurrentGCLK.u16EnableNumGCLK = GCLKENABLE0;
    CurrentGCLK.u16GCLKDIV = DIV1;
    CurrentGCLK.u16GCLKSrcSelect = OSC48M;
    
    SystemClock_GCLKN_Initialize(&CurrentGCLK);
    
    SystemClock_GCLKN_Initialize();
    
    Setting FDPLL section
    SystemClock_FDPLL_Initialize(&CurrentSystemClockSet);
    
    Set GCLK output clock to peripherals
 
    SystemClock_GCLKToPeripheral(GCLK_EIC,GCLKGEN0);
    SystemClock_GCLKToPeripheral(GCLK_TC0_TC1,GCLKGEN0);
    
    SystemClock_AHBClock_Enable(&CurrentSystemClockSet);
    
    
    
    return NOTHING;
}
*/
/*******************************************************************************
   Function Name                :   ClockDriver_EnableHSInternalOsc
   Parameters                   :   CurrentSystemClockSet:
                                     
   Return Values                :   Nothing
   Function Descripttion        :   Enable 48M High Speed Internal Oscillator 
                                    Default Setting
  
 *******************************************************************************/
uint8_t ClockDriver_EnableHSIOsc(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    CurrentSystemClockSet->u8Enable48MInternalOsc = YES;
    return Clock_OSCCtrl_Initialize(CurrentSystemClockSet);
}
#if 0
/*******************************************************************************
   Function Name                :   ClockDriver_EnableHSCrystalOsc
   Parameters                   :   CurrentSystemClockSet:
                                     
   Return Values                :   Nothing
   Function Descripttion        :   Enable High Speed External Crystal Oscillator 
                                    
  
 *******************************************************************************/
uint8_t ClockDriver_EnableHSCOsc(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    CurrentSystemClockSet->u8EnableHSCrystalOsc = YES;
    return Clock_OSCCtrl_Initialize(CurrentSystemClockSet);
}
/*******************************************************************************
   Function Name                :   ClockDriver_EnableFDPLL
   Parameters                   :   CurrentSystemClockSet:
                                    u16GCLKSrc 
                                    u8RefClock
   Return Values                :   Nothing
   Function Descripttion        :   Enable FDPLL, set FDPLL source from which GLCK source
                                    and Reference clock source 
                                    
  
 *******************************************************************************/
uint8_t ClockDriver_EnableFDPLL(SystemClock_InitTypeDef *CurrentSystemClockSet,uint16_t u16GCLKSrc,uint8_t u8RefClock)
{
    CurrentSystemClockSet->u8EnableFDPLL = YES;
    (*CurrentSystemClockSet).u16FDPLLSrc = u16GCLKSrc;
    (*CurrentSystemClockSet).u8FDPLL_RefClk = u8RefClock ;
    /*Setting FDPLL section*/
    return Clock_FDPLL_Initialize(CurrentSystemClockSet);
} 
/*******************************************************************************
   Function Name                :   ClockDriver_EnableLSInternalOsc
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Enable Low Speed Low power Internal Oscillator 
                                    
  
 *******************************************************************************/
uint8_t ClockDriver_EnableLSIOsc(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    CurrentSystemClockSet->u8EnableLSCrystalOsc = NO;
    CurrentSystemClockSet->u8Enable32KHighAccuacyInternalOsc = NO;
    return Clock_OSC32KCtrl_Initialize(CurrentSystemClockSet);
}
/*******************************************************************************
   Function Name                :   ClockDriver_EnableLSExternalCrystalOsc
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Enable High Speed External Crystal Oscillator 
                                    
 *******************************************************************************/
uint8_t ClockDriver_EnableLSCOsc(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    CurrentSystemClockSet->u8EnableLSCrystalOsc = YES;
    return Clock_OSC32KCtrl_Initialize(CurrentSystemClockSet);
}
/*******************************************************************************
   Function Name                :   ClockDriver_SetFDPLLRatio
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Set FDPLL frequency Multiply ratio, it must be called before 
                                    Enable FDPLL
 *******************************************************************************/
uint8_t ClockDriver_SetFDPLLRatio(SystemClock_InitTypeDef *CurrentSystemClockSet,uint16_t u16LDRatio,uint8_t u8LDRatioFracPart,uint8_t u8DPLLPrescaler)
{
    uint8_t u8Status = DEFAULT;
    if(u16LDRatio < LDR_OVERFLOW)
    {
        (*CurrentSystemClockSet).u16FDPLL_LDR = u16LDRatio & LDR_MASK;
        (*CurrentSystemClockSet).u8FDPLL_LDRFrac = u8LDRatioFracPart & LDR_FRAC_MASK;
        (*CurrentSystemClockSet).u8FDPLL_LDRPresc = u8DPLLPrescaler & FDPLL_PRESCALER_MASK;
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    return u8Status;
}
uint8_t ClockDriver_DisableHSCOsc(void)
{
    return Clock_DisableHSCOsc();
}
#endif
/*******************************************************************************
   Function Name                :   ClockDriver_Enable32KHiAccuInOsc
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Enable Low Speed High Accuracy Internal Oscillator 
                                    
 *******************************************************************************/
uint8_t ClockDriver_Enable32KHiAccuOsc(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    CurrentSystemClockSet->u8Enable32KHighAccuacyInternalOsc = YES;
    return Clock_OSC32KCtrl_Initialize(CurrentSystemClockSet);
}       

/*******************************************************************************
   Function Name                :   ClockDriver_EnableGCLKN
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Enable GCLK source,then set GCLK divider and GCLK source
                                    we must call this at least one time to create
                                    GCLK0
 *******************************************************************************/
uint8_t ClockDriver_EnableGCLKN(SystemClock_GCLKTypeDef *CurrentGCLK,uint16_t u16GCLKNumber,uint16_t u16GCLKSrcSelect,uint16_t u16GCLKDiv)
{
    (*CurrentGCLK).u16EnableNumGCLK = u16GCLKNumber;
    (*CurrentGCLK).u16GCLKDIV = u16GCLKDiv;
    (*CurrentGCLK).u16GCLKSrcSelect = u16GCLKSrcSelect;
    return Clock_GCLKN_Initialize(CurrentGCLK);
}
/*******************************************************************************
   Function Name                :   ClockDriver_GCLKToPeri
   Parameters                   :   u16PeripheralNum 
                                    u16GCLKGENValue
   Return Values                :   Nothing
   Function Descripttion        :   Connect GCLK to each peripheral
 *******************************************************************************/
uint8_t ClockDriver_GCLKToPeri(uint16_t u16PeripheralNum,uint16_t u16GCLKGENValue)
{
    return Clock_GCLKToPeri(u16PeripheralNum,u16GCLKGENValue);   
}
/*******************************************************************************
   Function Name                :   ClockDriver_EnableAHBClock
   Parameters                   :   CurrentSystemClockSet
   Return Values                :   Nothing
   Function Descripttion        :   Turn on AHB bus clock to peripherals
 *******************************************************************************/
uint8_t ClockDriver_EnableAHBClock(SystemClock_InitTypeDef *CurrentSystemClockSet)
{
    return Clock_AHBClock_Enable(CurrentSystemClockSet);
}

/* *****************************************************************************
 End of File
 */
