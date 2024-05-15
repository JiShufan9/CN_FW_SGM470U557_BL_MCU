/*******************************************************************************
  Analog-to-Digital Converter(ADC0) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_adc0.h

  Summary
    ADC0 PLIB Header File.

  Description
    This file defines the interface to the ADC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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
/* DOM-IGNORE-END */

#ifndef ADCON_H      /* Guards against multiple inclusion */
#define ADCON_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "main.h"
#include "hal/plib_auo/inc/AdcCommon.h"

/* DOM-IGNORE-BEGIN */
#ifdef __cplusplus /* Provide C Compatibility */

    extern "C" {

#endif
/* DOM-IGNORE-END */
// *****************************************************************************
// *****************************************************************************
// Section: Define
// *****************************************************************************
// *****************************************************************************

#define ADC_SYNC_NO_BUSY            0x0000U
/*---ADC Number---*/
#define ADC0                          0x00U
#define ADC1                          0x01U

/*---ADC Sample Time--- sample time formula:sample time = (sample time +1) x ADCClk */
#define SAMPLETIME_4ADC_CLK            0x3U
        
#define ADJDIV_POS                     4U
#define ADJDIV_2                       0x1U
#define ADJDIV_4                       0x2U
#define ADJDIV_6                       0x3U
#define ADJDIV_8                       0x4U
#define ADJDIV_10                      0x5U
#define ADJDIV_12                      0x6U
#define ADJDIV_14                      0x7U
#define ADJ_SAMPLENUM_POS              0U
#define ADJ_SAMPLENUM_1                0x0U            
#define ADJ_SAMPLENUM_2                0x1U   
#define ADJ_SAMPLENUM_4                0x2U 
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
    uint32_t u32ADCBaseAddress;
    uint8_t  u8NumADC;
    uint16_t u16ADCch;
    uint16_t u16ADCAvgSample;
    uint8_t  u16ADCAvgDiv;
    uint16_t u16PositiveIn;
    uint16_t u16NegativeIn;
    uint16_t u16LowThreshold;
    uint16_t u16HighThreshold;
    uint8_t  u8WindowMode;
    uint16_t u16IntPriority;
    uint8_t u8Prescaler;
    uint16_t u16Mode;
}ADC_InitTypedef;
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/

uint8_t ADCON_Initial(ADC_InitTypedef *ADCN);
uint8_t ADCON_Enable( ADC_InitTypedef *ADCN);
uint8_t ADCON_Disable( ADC_InitTypedef *ADCN);

uint8_t ADCON_ConversionStart(ADC_InitTypedef *ADCN);
uint16_t ADCON_ConversionResultGet(ADC_InitTypedef *ADCN);


uint8_t ADCON_ConversionStatusGet(ADC_InitTypedef *ADCN);

#if 0
uint8_t ADCON_SetAvgControl(ADC_InitTypedef *ADCN);
uint8_t ADCON_SetINTPriority(ADC_InitTypedef *ADCN);
#endif

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  /* Provide C++ Compatibility */

    }

#endif
/* DOM-IGNORE-END */

#endif /* ADCON_H */
