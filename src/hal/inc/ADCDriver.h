/******************************************************************************
;Author: Orlando Huang
;Date: 2021-09-28 18:41:28
;LastEditTime: 2021-10-07 15:39:07
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\inc\ADCDriver.h
;Description: N/A
******************************************************************************/
/* ************************************************************************** 
;        Program    :   SystemClockDriver.h
;        Function   :   The system clock program
;        chip       :   Microchip ATSAMC21J18A
;        clock      :   Internal 48MHz
;        Date       :   2020 / 05 / 22
;        Author     :   Adolf   Yeh
;        Description:   System clock initial use   
;    
 *****************************************************************************/ 

#ifndef ADCDRIVER_H
#define	ADCDRIVER_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
/* This section lists the other files that are included in this file.
*/
#include "hal/plib_auo/inc/adcon.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus /* Provide C Compatibility */

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part it.
*/
typedef struct 
    {
        uint8_t u8Enable48MInternalOsc;
        
        uint32_t u8EnableAHBClk;
        
    }ADC_InitTypeDef;



/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
uint8_t ADCDriver_Initial(ADC_InitTypedef *CurrentADCSet);
uint8_t ADCDriver_Enable(ADC_InitTypedef *CurrentADCSet);
uint8_t ADCDriver_Disable(ADC_InitTypedef *CurrentADCSet);

uint8_t ADCDriver_ConversionStart( ADC_InitTypedef *CurrentADCSet );
uint16_t ADCDriver_ConversionResultGet( ADC_InitTypedef *CurrentADCSet);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

