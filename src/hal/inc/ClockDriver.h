/* ************************************************************************** 
;        Program    :   ClockDriver.h
;        Function   :   The system clock program
;        chip       :   Microchip ATSAMC21J18A
;        clock      :   Internal 48MHz
;        Date       :   2020 / 05 / 22
;        Author     :   Adolf   Yeh
;        Description:   System clock initial use   
;    
 *****************************************************************************/ 

#ifndef CLOCKDRIVER_H    /* Guard against multiple inclusion */
#define CLOCKDRIVER_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "hal/plib_auo/inc/Clock.h"

/* Provide C++ Compatibility */
#ifdef cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */
    

    
    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    
    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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

#if 0
uint8_t ClockDriver_EnableHSCOsc(SystemClock_InitTypeDef *CurrentSystemClockSet);
uint8_t ClockDriver_EnableFDPLL(SystemClock_InitTypeDef *CurrentSystemClockSet,uint16_t u16GCLKSrc,uint8_t u8RefClock);
uint8_t ClockDriver_EnableLSIOsc(SystemClock_InitTypeDef *CurrentSystemClockSet);
uint8_t ClockDriver_EnableLSCOsc(SystemClock_InitTypeDef *CurrentSystemClockSet);
uint8_t ClockDriver_SetFDPLLRatio(SystemClock_InitTypeDef *CurrentSystemClockSet,uint16_t u16LDRatio,uint8_t u8LDRatioFracPart,uint8_t u8DPLLPrescaler);
uint8_t ClockDriver_DisableHSCOsc(void);
#endif
uint8_t ClockDriver_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSet,SystemClock_GCLKTypeDef *CurrentGCLK);
uint8_t ClockDriver_EnableHSIOsc(SystemClock_InitTypeDef *CurrentSystemClockSet);
uint8_t ClockDriver_Enable32KHiAccuOsc(SystemClock_InitTypeDef *CurrentSystemClockSet);
uint8_t ClockDriver_EnableGCLKN(SystemClock_GCLKTypeDef *CurrentGCLK,uint16_t u16GCLKNumber,uint16_t u16GCLKSrcSelect,uint16_t u16GCLKDiv);
uint8_t ClockDriver_GCLKToPeri(uint16_t u16PeripheralNum,uint16_t u16GCLKGENValue);
uint8_t ClockDriver_EnableAHBClock(SystemClock_InitTypeDef *CurrentSystemClockSet);

    /* Provide C++ Compatibility */
#ifdef cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
