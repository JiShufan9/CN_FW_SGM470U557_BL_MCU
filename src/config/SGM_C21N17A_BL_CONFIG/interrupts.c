/*******************************************************************************
 System Interrupts File

  Company:
    Microchip Technology Inc.

  File Name:
    interrupt.c

  Summary:
    Interrupt vectors mapping

  Description:
    This file maps all the interrupt vectors to their corresponding
    implementations. If a particular module interrupt is used, then its ISR
    definition can be found in corresponding PLIB source file. If a module
    interrupt is not used, then its ISR implementation is mapped to dummy
    handler.
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
#include "definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

extern uint32_t _stack;
static uint8_t u8UnusedInterrupt=0U;

/* Brief default interrupt handler for unused IRQs.*/
void Unused_Handler(void)
{
	u8UnusedInterrupt+=1U;
	if(u8UnusedInterrupt >= 255U)
	{
		u8UnusedInterrupt=255U;
	}
}

void LL_WDT_ISR(void)
{
	LL_WDT_Handler();
}

void LL_EIC_ISR(void)
{
	LL_EIC_Handler();
}

void SERCOM0_6_ISR(void)
{
	SERCOM0_6_Handler();
}

void SERCOM0_3_ISR(void)
{
	//SERCOM_I2CM_Handler(3U);
  SERCOM_I2CM_TCON_Handler();
}

void SERCOM0_5_ISR(void)
{
	SERCOM_I2CM_Handler(SERCOM_CH5);
}

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table=
{
    /* Configure Initial Stack Pointer, using linker-generated symbols */
    .pvStack = (void*) (&_stack),

    .pfnReset_Handler              =  Reset_Handler,
    .pfnNonMaskableInt_Handler     =  NonMaskableInt_Handler,
    .pfnHardFault_Handler          =  HardFault_Handler,
    .pfnSVCall_Handler             =  Unused_Handler,
    .pfnPendSV_Handler             =  Unused_Handler,
    .pfnSysTick_Handler            =  SysTick_Handler,
    .pfnSYSTEM_Handler             =  Unused_Handler,
    .pfnWDT_Handler                =  LL_WDT_ISR,
    .pfnRTC_Handler                =  Unused_Handler,
    .pfnEIC_Handler                =  LL_EIC_ISR,
    .pfnFREQM_Handler              =  Unused_Handler,
    .pfnTSENS_Handler              =  Unused_Handler,
    .pfnNVMCTRL_Handler            =  Unused_Handler,
    .pfnDMAC_Handler               =  Unused_Handler,
    .pfnEVSYS_Handler              =  Unused_Handler,
    .pfnSERCOM0_6_Handler          =  SERCOM0_6_ISR,
    .pfnSERCOM1_7_Handler          =  Unused_Handler,
    .pfnSERCOM2_Handler            =  Unused_Handler,
    .pfnSERCOM3_Handler            =  SERCOM0_3_ISR,
    .pfnSERCOM4_Handler            =  Unused_Handler,
    .pfnSERCOM5_Handler            =  SERCOM0_5_ISR,
    .pfnCAN0_Handler               =  Unused_Handler,
    .pfnCAN1_Handler               =  Unused_Handler,
    .pfnTCC0_Handler               =  Unused_Handler,
    .pfnTCC1_Handler               =  Unused_Handler,
    .pfnTCC2_Handler               =  Unused_Handler,
    .pfnTC0_5_Handler              =  Unused_Handler,
    .pfnTC1_6_Handler              =  Unused_Handler,
    .pfnTC2_7_Handler              =  Unused_Handler,
    .pfnTC3_Handler                =  Unused_Handler,
    .pfnTC4_Handler                =  Unused_Handler,
    .pfnADC0_Handler               =  Unused_Handler,
    .pfnADC1_Handler               =  Unused_Handler,
    .pfnAC_Handler                 =  Unused_Handler,
    .pfnDAC_Handler                =  Unused_Handler,
    .pfnSDADC_Handler              =  Unused_Handler,
    .pfnPTC_Handler                =  Unused_Handler,
};

/*******************************************************************************
 End of File
*/
