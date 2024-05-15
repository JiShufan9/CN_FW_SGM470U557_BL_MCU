/******************************************************************************* 
  External Interrupt Controller (EIC)

  Company
    AUO

  File Name
    Eic.h

  Version
    1.00.02
	
  Summary
    EIC Header File.

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

/* Guards against multiple inclusion */
#ifndef LL_EIC_H
#define LL_EIC_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "main.h"
#include "hal/inc/hal_common.h"

// DOM-IGNORE-BEGIN
// Provide C++ Compatibility
#ifdef __cplusplus

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part of it.
*/

/* EIC Pin Count */
#define EXTINT_COUNT                        (16U)

// *****************************************************************************
/* EIC Pins

  Summary:
    Identifies the available EIC pins.

  Description:
    This enumeration identifies all the available EIC pins. Not all pins will be
    implemented in a device. The pins described here are for documentation
    purposes only. The MHC will generate this enumeration with the enabled EIC
    pins only. The application should not use the constant value that are
    assigned to enumeration constants as this may vary between devices.

  Remarks:
    None.
*/
#define EIC_PIN_0       0U 
#define EIC_PIN_1       1U
#define EIC_PIN_2       2U
#define EIC_PIN_3       3U 
#define EIC_PIN_4       4U
#define EIC_PIN_5       5U
#define EIC_PIN_6       6U 
#define EIC_PIN_7       7U
#define EIC_PIN_8       8U
#define EIC_PIN_9       9U 
#define EIC_PIN_10      10U
#define EIC_PIN_11      11U
#define EIC_PIN_12      12U 
#define EIC_PIN_13      13U
#define EIC_PIN_14      14U
#define EIC_PIN_15      15U  
#define EIC_PIN_MAX     16U       
        
#define EIC_EXTINTEO_PIN_0  (1U << EIC_PIN_0)
#define EIC_EXTINTEO_PIN_1  (1U << EIC_PIN_1)
#define EIC_EXTINTEO_PIN_2  (1U << EIC_PIN_2)
#define EIC_EXTINTEO_PIN_3  (1U << EIC_PIN_3)
#define EIC_EXTINTEO_PIN_4  (1U << EIC_PIN_4)
#define EIC_EXTINTEO_PIN_5  (1U << EIC_PIN_5)
#define EIC_EXTINTEO_PIN_6  (1U << EIC_PIN_6)
#define EIC_EXTINTEO_PIN_7  (1U << EIC_PIN_7)
#define EIC_EXTINTEO_PIN_8  (1U << EIC_PIN_8)
#define EIC_EXTINTEO_PIN_9  (1U << EIC_PIN_9)
#define EIC_EXTINTEO_PIN_10 (1U << EIC_PIN_10)
#define EIC_EXTINTEO_PIN_11 (1U << EIC_PIN_11)
#define EIC_EXTINTEO_PIN_12 (1U << EIC_PIN_12)
#define EIC_EXTINTEO_PIN_13 (1U << EIC_PIN_13)
#define EIC_EXTINTEO_PIN_14 (1U << EIC_PIN_14)
#define EIC_EXTINTEO_PIN_15 (1U << EIC_PIN_15)
     
#define EIC_CTRLA_ENABLE_OFFSET                 0x01U       
        
#define EIC_CLK_GCLK                            0x00U
#define EIC_CLK_ULP32K                          0x01U 
#define EIC_CLK_ERROR                           0xFFU

#define EIC_FILTER_DISABLE                      0U
#define EIC_FILTER_ENABLE                       1U

#define EIC_CONFIG_SENSE_NONE                   0x0U                                          
#define EIC_CONFIG_SENSE_RISE                   0x1U                                             
#define EIC_CONFIG_SENSE_FALL                   0x2U                                             
#define EIC_CONFIG_SENSE_BOTH                   0x3U                                            
#define EIC_CONFIG_SENSE_HIGH                   0x4U                                             
#define EIC_CONFIG_SENSE_LOW                    0x5U   

typedef struct
{
    uint8_t u8InterruptSense;
    uint8_t u8FilterEnable;
    uint8_t u8AsynchronousMode;
}eic_nmi_init_t;

typedef struct
{
    uint16_t u16EnableChannel;
    uint8_t u8Prescaler0;
    uint8_t u8Prescaler1;
    uint8_t u8States0;
    uint8_t u8States1;
    uint8_t u8Tickon;
}eic_debounce_init_t;

typedef struct
{
    uint8_t u8ClockSelect;
    uint16_t u16EventControl;
    uint8_t u8Sense[EXTINT_COUNT];
    uint8_t u8FilterEnable[EXTINT_COUNT];
    eic_debounce_init_t tdDebounce;
}eic_init_t;
// *****************************************************************************
/* EIC Interrupt Pin Callback Function Pointer Type

  Summary:
    Defines the data type and function signature of the EIC peripheral callback
    function.

  Description:
    This data type defines the function signature for the EIC peripheral
    callback function. The EIC peripheral will call back the client's function
    with this signature when an interrupt condition has been sensed on the pin.
    The EIC library allows the application to register a callback function for
    each enabled external interrupt.

  Function:
    void (*EIC_CALLBACK)(uintptr_t context )

  Precondition:
    EIC_Initialize must have been called for the given EIC
    peripheral instance and EIC_CallbackRegister must have been
    called to set the function to be called.

  Parameters:
    context - Allows the caller to provide a context value (usually a pointer
    to the callers context for multi-instance clients).

  Returns:
    None.

  Example:
    <code>

    void EIC_Pin0Callback (uintptr_t context)
    {
        This means an interrupt condition has been sensed on EIC Pin 0.
    }

    (void)EIC_CallbackRegister(EIC_PIN_0, EIC_Pin0Callback, 0);
    </code>

  Remarks:
    None.
*/

typedef void (*EIC_CALLBACK) (uintptr_t context);

typedef struct
{
    /* External Interrupt Pin Callback Handler */
    EIC_CALLBACK    EICcallback;

    /* External Interrupt Pin Client context */
    uintptr_t       context;

    /* External Interrupt Pin number */
    uint32_t         u32EicPinNo;

} EIC_CALLBACK_OBJ;

// *****************************************************************************
/* EIC NMI Interrupt Pin Callback Function Pointer Type

  Summary:
    Defines the data type and function signature of the EIC peripheral NMI
    callback function.

  Description:
    This data type defines the function signature of the EIC peripheral NMI
    callback function. The EIC peripheral will call back the client's function
    with this signature when an interrupt condition has been sensed on the NMI
    pin.

  Function:
    void (*EIC_NMI_CALLBACK)(uintptr_t context )

  Precondition:
    EIC_Initialize must have been called for the given EIC
    peripheral instance and EIC_NMICallbackRegister must have been
    called to set the function to be called.

  Parameters:
    context - Allows the caller to provide a context value (usually a pointer
    to the callers context for multi-instance clients).

  Returns:
    None.

  Example:
    <code>

    void EIC_NMICallback (uintptr_t context)
    {
        This means an interrupt condition has been sensed on the NMI Pin.
    }

    (void)EIC_NMICallbackRegister(EIC_NMICallback, 0);
    </code>

  Remarks:
    None.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/

uint8_t LL_Eic_Init(eic_init_t tdEicInit);
uint8_t LL_Eic_Enable(uint32_t u32Timeout);

#if 0
uint8_t LL_Eic_Disable(uint32_t u32Timeout);
#endif

uint8_t LL_Eic_ClockSeletion(uint8_t u8Clock);
uint8_t LL_Eic_SoftwareReset(uint32_t u32Timeout);
uint8_t LL_Eic_SenseFilterSetting(eic_init_t tdEicInit);

#if 0
uint8_t LL_Eic_PinStateRead(uint32_t u32Pin);
#endif

uint8_t LL_Eic_DebouncePrescaler0Set(eic_debounce_init_t tdDebouncer_init);
uint8_t LL_Eic_DebouncePrescaler1Set(eic_debounce_init_t tdDebouncer_init);
uint8_t LL_Eic_DebounceStatus0(uint8_t u8Status0);
uint8_t LL_Eic_DebounceStatus1(uint8_t u8Status1);
uint8_t LL_Eic_DebounceTick(uint8_t u8Tickon);
uint8_t LL_Eic_DebounceSetting(eic_debounce_init_t tdDebouncer_init);
uint8_t LL_Eic_DebounceEnable(uint32_t u32Channel);
#if 0
uint8_t LL_Eic_DebounceDisable(uint32_t u32Channel);
#endif

uint8_t LL_Eic_InterruptEnable (uint32_t u32Pin);

#if 0
uint8_t LL_Eic_InterruptDisable (uint32_t u32Pin);
#endif

uint8_t LL_Eic_CallbackRegister(uint32_t u32Pin, EIC_CALLBACK tdCallback, uintptr_t tdContext);
void LL_EIC_Handler(void);

#endif /* PLIB_EIC_H */
