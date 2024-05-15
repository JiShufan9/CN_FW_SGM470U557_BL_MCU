/******************************************************************************
;Author: Orlando Huang
;Date: 2021-11-02 16:40:04
;LastEditTime: 2021-11-15 13:46:12
;FilePath: \TM_FW_GMBootloader_MCU\src\hal\plib_auo\inc\Sercom2I2CMaster.h
;Description: N/A
******************************************************************************/
/*******************************************************************************
  Serial Communication Interface Inter-Integrated Circuit (SERCOM I2C) Library
  Instance Header File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_sercom2_i2c.h

  Summary:
    SERCOM I2C PLIB Header file

  Description:
    This file defines the interface to the SERCOM I2C peripheral library. This
    library provides access to and control of the associated peripheral
    instance.
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

#ifndef PLIB_SERCOM2_I2C_H
#define PLIB_SERCOM2_I2C_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "SercomI2CMasterCommon.h"
#include "I2CCommon.h"
#include "hal/inc/I2CMDriver.h"
#ifdef __cplusplus
    extern "C" {
#endif

#define SERCOM_I2C_Read_ENABLE false

void SERCOM_I2CM_Initialize(uint8_t u8Ch);
bool SERCOM_I2C_Read(uint16_t u16Address, uint8_t *pu8Data, uint32_t u32Length, uint8_t u8Ch);
bool SERCOM_I2C_Write(uint16_t u16Address, uint8_t *pu8Data, uint32_t u32Length, uint8_t u8Ch);
#if I2CMDRIVER_ENABLE_WRITEREAD
bool SERCOM_I2C_WriteRead(uint16_t u16Address, uint8_t *pu8Wdata, uint32_t u32Wlength, uint8_t *pu8Rdata, uint32_t u32Rlength, uint8_t u8Ch);
#endif
void SERCOM_I2CM_TCON_Handler(void);
bool SERCOM_I2CM_IsBusy(uint8_t u8Ch);
void SERCOM_I2CM_CallbackRegister(SERCOM_I2C_CALLBACK I2CMCallback, uintptr_t contextHandle, uint8_t u8Ch);
bool SERCOM_I2C_TransferSetup(uint32_t* pu32Setup, uint32_t u32SrcClkFreq, uint8_t u8Ch );
#ifdef __cplusplus 
}
#endif


#endif /* PLIB_SERCOM2_I2C_H */
