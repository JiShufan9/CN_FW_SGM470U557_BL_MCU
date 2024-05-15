/*******************************************************************************
  Serial Communication Interface Inter-Integrated Circuit (SERCOM I2C) Library
  Source File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_sercom2_i2c_slave.c

  Summary:
    SERCOM I2C PLIB Slave Implementation file

  Description:
    This file defines the interface to the SERCOM I2C Slave peripheral library.
    This library provides access to and control of the associated peripheral
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "hal/plib_auo/inc/I2CSlave.h"

static SERCOM_I2C_SLAVE_OBJ sercom0I2CSObj;

SERCOM_I2C_SLAVE_TRANSFER_DIR SERCOM0_I2C_TransferDirGet(void)
{
    SERCOM_I2C_SLAVE_TRANSFER_DIR eDirectionTemp;
    
    if((SERCOM0_REGS->I2CS.SERCOM_STATUS & SERCOM_I2CS_STATUS_DIR_Msk) == SERCOM_I2CS_STATUS_DIR(1U))
    {
        eDirectionTemp = SERCOM_I2C_SLAVE_TRANSFER_DIR_READ;
    }
    else
    {
        eDirectionTemp = SERCOM_I2C_SLAVE_TRANSFER_DIR_WRITE;
    }
    
    return eDirectionTemp;
}
#if 0
SERCOM_I2C_SLAVE_ACK_STATUS SERCOM0_I2C_LastByteAckStatusGet(void)
{
    SERCOM_I2C_SLAVE_ACK_STATUS eStatusTemp;
    
    if((SERCOM0_REGS->I2CS.SERCOM_STATUS & SERCOM_I2CS_STATUS_RXNACK_Msk) == SERCOM_I2CS_STATUS_RXNACK(1U))
    {
        eStatusTemp = SERCOM_I2C_SLAVE_ACK_STATUS_RECEIVED_NAK;
    }
    else
    {
        eStatusTemp = SERCOM_I2C_SLAVE_ACK_STATUS_RECEIVED_ACK;
    }
    
    return eStatusTemp;
}
#endif
#if SERCOM0_I2C_COMM_SET
bool SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND eCommand)
{
    bool bReturn;
    if (eCommand == SERCOM_I2C_SLAVE_COMMAND_SEND_ACK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03U)) & (~SERCOM_I2CS_CTRLB_ACKACT_Msk);
        bReturn = true;
    }
    else if (eCommand == SERCOM_I2C_SLAVE_COMMAND_SEND_NAK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB |= (SERCOM_I2CS_CTRLB_CMD(0x03U) | (SERCOM_I2CS_CTRLB_ACKACT_Msk));
        bReturn = true;
    }
    
    else if (eCommand == SERCOM_I2C_SLAVE_COMMAND_RECEIVE_ACK_NAK)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03U));
        bReturn = true;
    }
    else if (eCommand == SERCOM_I2C_SLAVE_COMMAND_WAIT_FOR_START)
    {
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB & ~SERCOM_I2CS_CTRLB_CMD_Msk) | SERCOM_I2CS_CTRLB_CMD(0x02U);
        bReturn = true;
    }
    else
    {
        bReturn = false;
        ;/* Do nothing */
    }
    
    return bReturn;
}
#endif
void SERCOM0_I2CS_CallbackRegister(SERCOM_I2C_SLAVE_CALLBACK I2CScallback, uintptr_t contextHandle)
{
    sercom0I2CSObj.callback = I2CScallback;
    sercom0I2CSObj.context  = contextHandle;
}

static void I2CSlave_Receive_Action(void)
{
    if (sercom0I2CSObj.callback(SERCOM_I2C_SLAVE_RX_READY, sercom0I2CSObj.context) == true)
    {
        #if SERCOM0_I2C_COMM_SET
        (void)SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND_SEND_ACK);
        #else
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03U)) & (~SERCOM_I2CS_CTRLB_ACKACT_Msk);
        #endif
    }
    else
    {
        #if SERCOM0_I2C_COMM_SET
        (void)SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND_SEND_NAK);
        #else
        SERCOM0_REGS->I2CS.SERCOM_CTRLB |= (SERCOM_I2CS_CTRLB_CMD(0x03U) | (SERCOM_I2CS_CTRLB_ACKACT_Msk));
        #endif
    }    
}

void SERCOM0_6_Handler(void)
{     
    if ((SERCOM0_REGS->I2CS.SERCOM_INTFLAG & SERCOM_I2CS_INTFLAG_AMATCH_Msk) == SERCOM_I2CS_INTFLAG_AMATCH(1U))
    {     
        (void)sercom0I2CSObj.callback(SERCOM_I2C_SLAVE_ADDR_MATCH, sercom0I2CSObj.context);
        #if SERCOM0_I2C_COMM_SET
        (void)SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND_SEND_ACK);
        #else
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB | SERCOM_I2CS_CTRLB_CMD(0x03U)) & (~SERCOM_I2CS_CTRLB_ACKACT_Msk);
        #endif
        if (SERCOM0_I2C_TransferDirGet() == SERCOM_I2C_SLAVE_TRANSFER_DIR_WRITE)
        {
            ;
        }
        else
        {
            (void)sercom0I2CSObj.callback(SERCOM_I2C_SLAVE_TX_READY, sercom0I2CSObj.context);
            SERCOM0_REGS->I2CS.SERCOM_INTFLAG = SERCOM_I2CS_INTFLAG_DRDY_Msk;
        }
    }
    else
    {
        ;
    }
    
    if ((SERCOM0_REGS->I2CS.SERCOM_INTFLAG & SERCOM_I2CS_INTFLAG_DRDY_Msk) == SERCOM_I2CS_INTFLAG_DRDY(1U)) 
    {              
        if (SERCOM0_I2C_TransferDirGet() == SERCOM_I2C_SLAVE_TRANSFER_DIR_WRITE)
        {
            (void)I2CSlave_Receive_Action();
        }
        else
        {
            (void)sercom0I2CSObj.callback(SERCOM_I2C_SLAVE_TX_READY, sercom0I2CSObj.context);
            SERCOM0_REGS->I2CS.SERCOM_INTFLAG = SERCOM_I2CS_INTFLAG_DRDY_Msk;
        }
    }
    else
    {
        ;
    }
    
    if ((SERCOM0_REGS->I2CS.SERCOM_INTFLAG & SERCOM_I2CS_INTFLAG_PREC_Msk) == SERCOM_I2CS_INTFLAG_PREC(1U))
    {              
        (void)sercom0I2CSObj.callback(SERCOM_I2C_SLAVE_STOP_RECEIVED, sercom0I2CSObj.context);
        SERCOM0_REGS->I2CS.SERCOM_INTFLAG = SERCOM_I2CS_INTFLAG_PREC_Msk;
    }
    else
    {
        ;/* Do nothing */
    }
    
    if ((SERCOM0_REGS->I2CS.SERCOM_INTFLAG & SERCOM_I2CS_INTFLAG_ERROR_Msk) == SERCOM_I2CS_INTFLAG_ERROR(1U))
    {   
        #if SERCOM0_I2C_COMM_SET
        (void)SERCOM0_I2C_CommandSet(SERCOM_I2C_SLAVE_COMMAND_WAIT_FOR_START);
        #else
        SERCOM0_REGS->I2CS.SERCOM_CTRLB = (SERCOM0_REGS->I2CS.SERCOM_CTRLB & ~SERCOM_I2CS_CTRLB_CMD_Msk) | SERCOM_I2CS_CTRLB_CMD(0x02U);
        #endif
        SERCOM0_REGS->I2CS.SERCOM_INTFLAG = SERCOM_I2CS_INTFLAG_ERROR_Msk;
    }
    else
    {
        ;/* Do nothing */
    }
}

