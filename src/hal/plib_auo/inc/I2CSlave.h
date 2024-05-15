/*******************************************************************************
  Serial Communication Interface Inter-Integrated Circuit (SERCOM I2C) Library
  Instance Header File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_sercom0_i2c_slave.h

  Summary:
    SERCOM I2C Slave PLIB Header file

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

#ifndef I2CSLAVE_H
#define I2CSLAVE_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "hal/plib_auo/inc/SercomI2CSlaveCommon.h"

#ifdef __cplusplus 
extern "C" {
#endif

#define SERCOM0_I2C_COMM_SET true

void SERCOM0_I2C_Initialize(void);
void SERCOM0_I2CS_CallbackRegister(SERCOM_I2C_SLAVE_CALLBACK I2CScallback, uintptr_t contextHandle);
bool SERCOM0_I2C_IsBusy(void);
uint8_t SERCOM0_I2C_ReadByte(void);
SERCOM_I2C_SLAVE_TRANSFER_DIR SERCOM0_I2C_TransferDirGet(void);
#if 0
SERCOM_I2C_SLAVE_ACK_STATUS SERCOM0_I2C_LastByteAckStatusGet(void);
#endif
#if SERCOM0_I2C_COMM_SET
bool SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND eCommand);
#endif
void SERCOM0_6_Handler(void);

#ifdef __cplusplus
}
#endif


#endif /* I2CSLAVE_H */
