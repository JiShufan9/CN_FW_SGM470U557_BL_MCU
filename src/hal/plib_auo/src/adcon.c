/*******************************************************************************
  Analog-to-Digital Converter(ADC0) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_adc0.c

  Summary
    ADC0 PLIB Implementation File.

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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "hal/plib_auo/inc/adcon.h"
#include "hal_common.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

#define ADC0_LINEARITY_POS  (0U)
#define ADC0_LINEARITY_Msk  (0x7U << ADC0_LINEARITY_POS)

#define ADC0_BIASCAL_POS    (3U)
#define ADC0_BIASCAL_Msk    (0x7U << ADC0_BIASCAL_POS)

#define ADC1_LINEARITY_POS  (6U)
#define ADC1_LINEARITY_Msk  (0x7U << ADC1_LINEARITY_POS)

#define ADC1_BIASCAL_POS    (9U)
#define ADC1_BIASCAL_Msk    (0x7U << ADC1_BIASCAL_POS)

// *****************************************************************************
// *****************************************************************************
// Section: ADC0 Implementation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Initialize ADC module */
uint8_t ADCON_Initial(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    uint16_t u16LinearityForADC1;
    uint16_t u16BiasCalForADC1;
    uint16_t u16LinearityForADC0;
    uint16_t u16BiasCalForADC0;
    uint32_t u32TimeoutTemp = 12000U;
    adc_registers_t *ADCREGS;
    uint32_t u32SWITCondition1 = ADC_SYNCBUSY_SWRST_Msk;  //Flag for test
	int32_t i32SWITCondition2 = ADC_SYNC_NO_BUSY;  //Flag for test
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        
        /* Reset ADC */
        (*ADCREGS).ADC_CTRLA = ADC_CTRLA_SWRST_Msk;

        while((((*ADCREGS).ADC_SYNCBUSY & ADC_SYNCBUSY_SWRST_Msk) == u32SWITCondition1) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }
        
        if(u32TimeoutTemp > 0U)
        {
            /* Write linearity calibration in BIASREFBUF and bias calibration in BIASCOMP */
            if((*ADCN).u32ADCBaseAddress == ADC0_BASE_ADDRESS)
            {
                u16LinearityForADC0 = (uint16_t)(*(uint64_t*)OTP5_ADDR) & ADC0_LINEARITY_Msk;
                u16BiasCalForADC0 = (((*(uint64_t*)OTP5_ADDR) & ADC0_BIASCAL_Msk) >> ADC0_BIASCAL_POS);
                (*ADCREGS).ADC_CALIB = ADC_CALIB_BIASREFBUF(u16LinearityForADC0) | ADC_CALIB_BIASCOMP(u16BiasCalForADC0);
            }
            else
            {
                u16LinearityForADC1 = (uint16_t)(*(uint64_t*)OTP5_ADDR) & ADC1_LINEARITY_Msk;
                u16BiasCalForADC1 = (((*(uint64_t*)OTP5_ADDR) & ADC1_BIASCAL_Msk) >> ADC1_BIASCAL_POS);
                (*ADCREGS).ADC_CALIB = ADC_CALIB_BIASREFBUF(u16LinearityForADC1) | ADC_CALIB_BIASCOMP(u16BiasCalForADC1);
            }
            /* Prescaler */
            (*ADCREGS).ADC_CTRLB = (uint8_t)(*ADCN).u8Prescaler;
            
            /* Sampling length */
            (*ADCREGS).ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(3U);                    /* 58U */

            /* Reference */
            (*ADCREGS).ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC2;

            /* Input pin */
            (*ADCREGS).ADC_INPUTCTRL = (uint16_t)(*ADCN).u16ADCch;

            /* Resolution & Operation Mode */
            (*ADCREGS).ADC_CTRLC = ADC_CTRLC_RESSEL_16BIT | ADC_CTRLC_WINMODE(ADC_CTRLC_WINMODE_DISABLE) | (*ADCN).u16Mode;

            /* Result averaging */
            (*ADCREGS).ADC_AVGCTRL = ADC_AVGCTRL_SAMPLENUM_16 | ADC_AVGCTRL_ADJRES(0U);

            /* Clear all interrupt flags */
            (*ADCREGS).ADC_INTFLAG = ADC_INTFLAG_Msk;
            
            u32TimeoutTemp = 12000U;
            while(((*ADCREGS).ADC_SYNCBUSY > i32SWITCondition2) && (u32TimeoutTemp > 0U))
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

/* Enable ADC module */
uint8_t ADCON_Enable(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    adc_registers_t *ADCREGS;
    uint32_t u32TimeoutTemp = 12000U;
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        (*ADCREGS).ADC_CTRLA |= ADC_CTRLA_ENABLE_Msk;
        
        while(((*ADCREGS).ADC_SYNCBUSY > ADC_SYNC_NO_BUSY) && (u32TimeoutTemp > 0U))
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
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}

/* Disable ADC module */
uint8_t ADCON_Disable(ADC_InitTypedef *ADCN)
{
    uint32_t u32TimeoutTemp = 12000U;
    uint8_t u8Status;
    adc_registers_t *ADCREGS;
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        (*ADCREGS).ADC_CTRLA &= ~ADC_CTRLA_ENABLE_Msk;

        while(((*ADCREGS).ADC_SYNCBUSY > ADC_SYNC_NO_BUSY) && (u32TimeoutTemp > 0U))
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
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}

/* Start the ADC conversion by SW */
uint8_t ADCON_ConversionStart(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = 12000U;
    adc_registers_t *ADCREGS;
    uint32_t u32SWITCondition = ADC_SYNCBUSY_SWTRIG_Msk;  //Flag for test
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        
        /* Start conversion */
        (*ADCREGS).ADC_SWTRIG |= ADC_SWTRIG_START_Msk;
        
        while((((*ADCREGS).ADC_SYNCBUSY & ADC_SYNCBUSY_SWTRIG_Msk) == u32SWITCondition) && (u32TimeoutTemp > 0U))
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
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}

#if 0
/* Check whether auto sequence conversion is done */
uint8_t ADCON_ConversionSequenceIsFinished(ADC_InitTypedef *ADCN)
{
    adc_registers_t *ADCREGS;
    ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
    uint8_t u8Status;
    
    if (((*ADCREGS).ADC_SEQSTATUS & ADC_SEQSTATUS_SEQBUSY_Msk) != ADC_SEQSTATUS_SEQBUSY_Msk)
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_FALSE;
    }
    
    return u8Status;
    
}
#endif

#if 0
/* Configure window comparison threshold values */
uint8_t ADCON_ComparisonWindowSet(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = 12000U;
    adc_registers_t *ADCREGS;
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        (*ADCREGS).ADC_WINLT = ADCN->u16LowThreshold;
        (*ADCREGS).ADC_WINUT = ADCN->u16HighThreshold;
        
        while(((*ADCREGS).ADC_SYNCBUSY > ADC_SYNC_NO_BUSY) && (u32TimeoutTemp > 0U))
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
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
#endif

#if 0
uint8_t ADCON_WindowModeSet(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp = 12000U;
    adc_registers_t *ADCREGS;
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        (*ADCREGS).ADC_CTRLC &= ~ADC_CTRLC_WINMODE_Msk;
        (*ADCREGS).ADC_CTRLC |= ((ADCN->u8WindowMode & 0x7U) << ADC_CTRLC_WINMODE_Pos);
        
        while(((*ADCREGS).ADC_SYNCBUSY > ADC_SYNC_NO_BUSY) && (u32TimeoutTemp > 0U))
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
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
#endif

/* Read the conversion result */
uint16_t ADCON_ConversionResultGet(ADC_InitTypedef *ADCN )
{
    adc_registers_t *ADCREGS;
    
    ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
    
    return (uint16_t)(*ADCREGS).ADC_RESULT;
}

/* Check whether result is ready */
uint8_t ADCON_ConversionStatusGet(ADC_InitTypedef *ADCN)
{
    adc_registers_t *ADCREGS;
    ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
    uint8_t u8Status;

    if(((*ADCREGS).ADC_INTFLAG & ADC_INTFLAG_RESRDY_Msk)==ADC_INTFLAG_RESRDY_Msk)
    {
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_FALSE;
    }
    return u8Status;
}
#if 0
uint8_t ADCON_SetAvgControl(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status;
    adc_registers_t *ADCREGS;
    
    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        ADCREGS = (adc_registers_t *)(*ADCN).u32ADCBaseAddress;
        (*ADCREGS).ADC_AVGCTRL = ((*ADCN).u16ADCAvgDiv<<ADJDIV_POS)|(*ADCN).u16ADCAvgSample;
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
#endif
#if 0
uint8_t ADCON_SetINTPriority(ADC_InitTypedef *ADCN)
{
    uint8_t u8Status; 

    if((*ADCN).u32ADCBaseAddress > 0U)
    {
        switch((*ADCN).u32ADCBaseAddress)
        {
            case ADC0_BASE_ADDRESS:
                __NVIC_SetPriority(ADC0_IRQn,(*ADCN).u16IntPriority);
                u8Status = DRIVER_TRUE;
            break;
            case ADC1_BASE_ADDRESS:
                __NVIC_SetPriority(ADC1_IRQn,(*ADCN).u16IntPriority);
                u8Status = DRIVER_TRUE;
            break;
            default:
                u8Status = DRIVER_PARAMETER_ERROR;
            break;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    return u8Status;
}
#endif
