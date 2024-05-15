/* ************************************************************************** 
;        Program    :   ADCDriver.c
;        Function   :   The system clock program
;        chip       :   Microchip ATSAMC21J18A
;        clock      :   Internal 48MHz
;        Date       :   2020 / 05 / 22
;        Author     :   Adolf   Yeh
;        Description:   System clock initial use   
;    
 *****************************************************************************/ 


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include "hal/inc/ADCDriver.h"
#include "math.h"
/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
//#define ADC0_LINEARITY_POS  (0)
//#define ADC0_LINEARITY_Msk   (0x7 << ADC0_LINEARITY_POS)
//
//#define ADC0_BIASCAL_POS  (3)
//#define ADC0_BIASCAL_Msk   (0x7 << ADC0_BIASCAL_POS)
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
//static uint16_t ADC_OSCCtrl_Initialize(ADC_InitTypeDef *CurrentADCSetting);


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
/*******************************************************************************
   Function Name                :   ADC_Initialize
   Parameters                   :   u32ADCBaseAddress
                                    CurrentADCSet 
   Return Values                :   Nothing
   Function Descripttion        :   Initialize parameters
   
  
 *******************************************************************************/
uint8_t ADCDriver_Initial(ADC_InitTypedef *CurrentADCSet)
{   
    return ADCON_Initial(CurrentADCSet);
}
uint8_t ADCDriver_Enable( ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_Enable(CurrentADCSet);
}
uint8_t ADCDriver_Disable( ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_Disable(CurrentADCSet);
}
uint8_t ADCDriver_ConversionStart( ADC_InitTypedef *CurrentADCSet )
{
    return ADCON_ConversionStart( CurrentADCSet );
}
uint16_t ADCDriver_ConversionResultGet( ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_ConversionResultGet(CurrentADCSet);
}

#if 0
uint8_t ADCDriver_ComparisonWindowSet(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_ComparisonWindowSet(CurrentADCSet);
}
uint8_t ADCDriver_WindowModeSet(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_WindowModeSet(CurrentADCSet);
}
uint8_t ADCDriver_ConversionSequenceIsFinished(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_ConversionSequenceIsFinished(CurrentADCSet);
}

uint8_t ADCDriver_ConversionStatusGet(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_ConversionStatusGet(CurrentADCSet);
}

uint8_t ADCDriver_SetAvgControl(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_SetAvgControl(CurrentADCSet);
}
uint8_t ADCDriver_SetINTPriority(ADC_InitTypedef *CurrentADCSet)
{
    return ADCON_SetINTPriority(CurrentADCSet);
}
#endif
/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

