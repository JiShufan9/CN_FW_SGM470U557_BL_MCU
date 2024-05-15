/*******************************************************************************
  Serial Communication Interface Inter-Integrated Circuit (SERCOM I2C) Library
  Instance Header File

  Company
    Microchip Technology Inc.

  File Name
    plib_sercom_i2c_master.h

  Summary
    SERCOM I2C peripheral library interface.

  Description
    This file defines the interface to the SERCOM I2C peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:

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

#ifndef PLIB_SERCOM_I2C_MASTER_H
#define PLIB_SERCOM_I2C_MASTER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_TRANSFER_WRITE  0U
#define I2C_TRANSFER_READ   1U

typedef enum
{
    SERCOM_I2C_ERROR_NONE,              /* No error has occurred. */
    SERCOM_I2C_ERROR_NAK,               /* A bus transaction was NAK'ed */
    SERCOM_I2C_ERROR_BUS,               /* A bus error has occurred. */
    SERCOM_I2C_ERROR_CH,                /* Input channel is out off range */
} SERCOM_I2C_ERROR;

typedef enum
{
    SERCOM_I2C_STATE_ERROR = -1,        /* SERCOM PLib Task Error State */
    SERCOM_I2C_STATE_IDLE,              /* SERCOM PLib Task Idle State */
    SERCOM_I2C_STATE_ADDR_SEND,         /* SERCOM PLib Task Address Send State */
    SERCOM_I2C_REINITIATE_TRANSFER,
    SERCOM_I2C_STATE_TRANSFER_READ,     /* SERCOM PLib Task Read Transfer State */
    SERCOM_I2C_STATE_TRANSFER_WRITE,    /* SERCOM PLib Task Write Transfer State */
    SERCOM_I2C_STATE_TRANSFER_DONE,     /* SERCOM PLib Task Transfer Done State */
} SERCOM_I2C_STATE;

typedef void (*SERCOM_I2C_CALLBACK)
(
    /*Transfer context*/
    uintptr_t contextHandle
);

typedef struct
{
    uint16_t address;
    uint8_t *writeBuffer;
    uint8_t *readBuffer;
    size_t  writeSize;
    size_t  readSize;
    size_t  writeCount;
    size_t  readCount;
    SERCOM_I2C_STATE state;             /* State */
    SERCOM_I2C_ERROR error;             /* Transfer status */
    SERCOM_I2C_CALLBACK callback;       /* Transfer Event Callback */
    uintptr_t context;                  /* Transfer context */
} SERCOM_I2C_OBJ;


#ifdef __cplusplus
}
#endif    

#endif /* PLIB_SERCOM_I2C_MASTER_H */