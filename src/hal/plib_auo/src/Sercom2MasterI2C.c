/*******************************************************************************
  Serial Communication Interface Inter-Integrated Circuit (SERCOM I2C) Library
  Source File

  Company:
    Microchip Technology Inc.

  File Name:
    plib_sercom2_i2c.c

  Summary:
    SERCOM I2C PLIB Implementation file

  Description:
    This file defines the interface to the SERCOM I2C peripheral library.
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
#include "hal/plib_auo/inc/Sercom2I2CMaster.h"
#include "hal/plib_auo/inc/I2CCommon.h"
#include "packs/ATSAMC21N17A_DFP/atsamc21n17a.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************


/* SERCOM2 I2C baud value */
#define SERCOM2_I2CM_BAUD_VALUE (0xE8U)

#define RIGHT_ALIGNED           (0x0008U)

#define TEN_BIT_ADDR_MASK       (0x0078U)

static SERCOM_I2C_OBJ gtObj[6U]; 

// *****************************************************************************
// *****************************************************************************
// Section: SERCOM2 I2C Implementation
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SERCOM2_I2C_Initialize(void)

  Summary:
    Initializes the instance of the SERCOM peripheral operating in I2C mode.

  Description:
    This function initializes the given instance of the SERCOM I2C peripheral as
    configured by the user from the MHC.

  Remarks:
    Refer plib_sercom2_i2c.h for more information.
*/

void SERCOM_I2CM_Initialize(uint8_t u8Ch)
{
    /* Initialize the SERCOM2 PLib Object */
    gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;
    gtObj[u8Ch].state = SERCOM_I2C_STATE_IDLE;
}

bool SERCOM_I2C_TransferSetup(uint32_t* pu32Setup, uint32_t u32SrcClkFreq, uint8_t u8Ch )
{
    sercom_registers_t *ptReg = i2c_channel_reg((en_i2c_channel)u8Ch);
    uint32_t u32TimeoutTemp;
    uint32_t u32Temp;
    bool bReturn;

    uint32_t u32BaudValue;
    uint32_t u32ClkSpeed;

    if (pu32Setup == NULL)
    {
        bReturn = false;
    }
    else
    {
        u32ClkSpeed = *pu32Setup;

        if( u32SrcClkFreq == 0U)
        {
            u32SrcClkFreq = 48000000UL;
        }
        else
        {
            ;
        }
        
        /* Reference clock frequency must be atleast two times the baud rate */
        if (u32SrcClkFreq < (2U * u32ClkSpeed))
        {
            bReturn = false;
        }
        else
        {
            u32Temp = (u32SrcClkFreq / 10000000U) + 10U;     
            u32BaudValue = (u32SrcClkFreq / u32ClkSpeed) - u32Temp;

            if (u32ClkSpeed <= 400000UL)
            {
                /* For I2C clock speed upto 400 KHz, the value of BAUD<7:0> determines both SCL_L and SCL_H with SCL_L = SCL_H */
                if (u32BaudValue > (0xFFU * 2U))
                {
                    /* Set baud rate to the minimum possible value */
                    u32BaudValue = 0xFFU;
                }
                else if (u32BaudValue <= 1U)
                {
                    /* Baud value cannot be 0. Set baud rate to maximum possible value */
                    u32BaudValue = 1U;
                }
                else
                {
                    u32BaudValue /= 2U;
                }
            }
            else
            {
                /* To maintain the ratio of SCL_L:SCL_H to 2:1, the max value of BAUD_LOW<15:8>:BAUD<7:0> can be 0xFF:0x7F. Hence BAUD_LOW + BAUD can not exceed 255+127 = 382 */
                if (u32BaudValue >= 382U)
                {
                    /* Set baud rate to the minimum possible value while maintaining SCL_L:SCL_H to 2:1 */
                    u32BaudValue = (0xFFU << 8U) | (0x7FU);
                }
                else if (u32BaudValue <= 3U)
                {
                    /* Baud value cannot be 0. Set baud rate to maximum possible value while maintaining SCL_L:SCL_H to 2:1 */
                    u32BaudValue = (2U << 8U) | 1U;
                }
                else
                {
                    /* For Fm+ mode, I2C SCL_L:SCL_H to 2:1 */
                    u32BaudValue  = ((((u32BaudValue * 2U)/3U) << 8U) | (u32BaudValue/3U));
                }
            }
            /* Disable the I2C before changing the I2C clock speed */
            ptReg->I2CM.SERCOM_CTRLA &= ~SERCOM_I2CM_CTRLA_ENABLE_Msk;

            u32TimeoutTemp = 12000U;
            /* Wait for synchronization */
            while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            /* Baud rate - Master Baud Rate*/
            ptReg->I2CM.SERCOM_BAUD = (SERCOM_I2CM_BAUD_BAUDLOW(u32BaudValue >> 8U) | SERCOM_I2CM_BAUD_BAUD(u32BaudValue));
            
            bReturn = true;
        }
    }
    
    (void)ptReg->I2CM.SERCOM_CTRLA;
    (void)ptReg->I2CM.SERCOM_BAUD;
    return bReturn;
}

// *****************************************************************************
/* Function:
    void SERCOM2_I2C_InitiateRead(uint16_t address)

  Summary:
    Intiates I2C Read

  Description:

  Remarks:
    Refer plib_sercom2_i2c.h for more information.
*/

static void SERCOM_I2C_InitiateRead(uint16_t u16Address, uint8_t u8Ch)
{
    sercom_registers_t *ptReg = i2c_channel_reg((en_i2c_channel)u8Ch);
    uint32_t u32TimeoutTemp = 12000U;
    uint16_t u16ConfigTemp = 0;
    
    if(u16Address > 0x007FU)
    {
       /*
        * Write ADDR.ADDR[10:1] with the 10-bit address.
        * Set direction bit (ADDR.ADDR[0]) equal to 0.
        * Set ADDR.TENBITEN equals to 1.
        */
        gtObj[u8Ch].state = SERCOM_I2C_STATE_ADDR_SEND;
        u16ConfigTemp = (u16Address << 1U) | I2C_TRANSFER_WRITE | SERCOM_I2CM_ADDR_TENBITEN_Msk;
        ptReg->I2CM.SERCOM_ADDR = u16ConfigTemp;
    }
    else
    {
        gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_READ;  
        u16ConfigTemp |= (u16Address << 1U) | I2C_TRANSFER_READ;
        ptReg->I2CM.SERCOM_ADDR = u16ConfigTemp;
    }

    /* Wait for synchronization */
    while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }

    (void)ptReg->I2CM.SERCOM_ADDR;    
}

void SERCOM_I2CM_CallbackRegister(SERCOM_I2C_CALLBACK I2CMCallback, uintptr_t contextHandle, uint8_t u8Ch)
{
    gtObj[u8Ch].callback = I2CMCallback;
    gtObj[u8Ch].context  = contextHandle;
}

static void SERCOM_I2C_InitiateTransfer(uint16_t u16Address, bool bType, uint8_t u8Ch)
{
    sercom_registers_t *ptReg = i2c_channel_reg((en_i2c_channel)u8Ch);

    uint32_t u32TimeoutTemp;
    uint16_t u16ConfigTemp = 0U;
    
    gtObj[u8Ch].writeCount = 0U;
    gtObj[u8Ch].readCount = 0U;

    /* Clear all flags */
    ptReg->I2CM.SERCOM_INTFLAG = SERCOM_I2CM_INTFLAG_Msk;

    /* Smart mode enabled - ACK is set to send while receiving the data */
    ptReg->I2CM.SERCOM_CTRLB &= ~SERCOM_I2CM_CTRLB_ACKACT_Msk;
    
    u32TimeoutTemp = 12000U;
    /* Wait for synchronization */
    while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }
    
    /* Reset Error Information */
    gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;

    /* Check for 10-bit address */
    if(u16Address > 0x007FU)
    {
        if(bType)
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_ADDR_SEND;
        }
        else
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_WRITE;
        }

        /*
         * Write ADDR.ADDR[10:1] with the 10-bit address.
         * Set direction bit (ADDR.ADDR[0]) equal to 0.
         * Set ADDR.TENBITEN equals to 1.
         */
        u16ConfigTemp = (u16Address << 1U) | I2C_TRANSFER_WRITE | SERCOM_I2CM_ADDR_TENBITEN_Msk;
        ptReg->I2CM.SERCOM_ADDR = u16ConfigTemp;
    }
    else
    {
        if(bType)
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_READ;

            /* Write 7bit address with direction (ADDR.ADDR[0]) equal to 1*/
            u16ConfigTemp = (u16Address << 1U) | I2C_TRANSFER_READ;
            ptReg->I2CM.SERCOM_ADDR = u16ConfigTemp;
        }
        else
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_WRITE;

            /* Write 7bit address with direction (ADDR.ADDR[0]) equal to 0*/
            u16ConfigTemp = (u16Address << 1U) | I2C_TRANSFER_WRITE; 
            ptReg->I2CM.SERCOM_ADDR = u16ConfigTemp;
        }
    }
    
    u32TimeoutTemp = 12000U;
    /* Wait for synchronization */
    while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }
    
    (void)ptReg->I2CM.SERCOM_ADDR;
    (void)ptReg->I2CM.SERCOM_INTFLAG;
    (void)ptReg->I2CM.SERCOM_CTRLB;
}

#if SERCOM_I2C_Read_ENABLE
bool SERCOM_I2C_Read(uint16_t u16Address, uint8_t *pu8Data, uint32_t u32Length, uint8_t u8Ch)
{
    bool bReturn;
    
    /* Check for ongoing transfer */
    if(gtObj[u8Ch].state != SERCOM_I2C_STATE_IDLE)
    {
        bReturn = false;
    }
    else
    {    
        gtObj[u8Ch].address = u16Address;
        gtObj[u8Ch].readBuffer = pu8Data;
        gtObj[u8Ch].readSize = u32Length;
        gtObj[u8Ch].writeBuffer = NULL;
        gtObj[u8Ch].writeSize = 0U;
        gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;
        
        SERCOM_I2C_InitiateTransfer(u16Address, true, u8Ch);
        bReturn = true;
    }
        
    return bReturn;
}
#endif

bool SERCOM_I2C_Write(uint16_t u16Address, uint8_t *pu8Data, uint32_t u32Length, uint8_t u8Ch)
{
    bool bReturn;
    
    /* Check for ongoing transfer */
    if(gtObj[u8Ch].state != SERCOM_I2C_STATE_IDLE)
    {
        bReturn = false;
    }
    else
    {   
        gtObj[u8Ch].address = u16Address;
        gtObj[u8Ch].readBuffer = NULL;
        gtObj[u8Ch].readSize = 0U;
        gtObj[u8Ch].writeBuffer = pu8Data;
        gtObj[u8Ch].writeSize = u32Length;
        gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;
        
        SERCOM_I2C_InitiateTransfer(u16Address, false, u8Ch);
        bReturn = true;
    }
    
    return bReturn;
}
#if I2CMDRIVER_ENABLE_WRITEREAD
bool SERCOM_I2C_WriteRead(uint16_t u16Address, uint8_t *pu8Wdata, uint32_t u32Wlength, uint8_t *pu8Rdata, uint32_t u32Rlength, uint8_t u8Ch)
{
    bool bReturn;
    
    /* Check for ongoing transfer */
    if(gtObj[u8Ch].state != SERCOM_I2C_STATE_IDLE)
    {
        bReturn = false;
    }
    else
    {
        gtObj[u8Ch].address = u16Address;
        gtObj[u8Ch].readBuffer = pu8Rdata;
        gtObj[u8Ch].readSize = u32Rlength;
        gtObj[u8Ch].writeBuffer = pu8Wdata;
        gtObj[u8Ch].writeSize = u32Wlength;
        gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;
        SERCOM_I2C_InitiateTransfer(u16Address, false, u8Ch);
        bReturn = true;
    }
    
    return bReturn;
}
#endif
bool SERCOM_I2CM_IsBusy(uint8_t u8Ch)
{
    sercom_registers_t *ptReg = i2c_channel_reg((en_i2c_channel)u8Ch);
    uint16_t u16Reg_Temp = ptReg->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_BUSSTATE_Msk;
    bool bReturn;
    
    if((gtObj[u8Ch].state == SERCOM_I2C_STATE_IDLE) && (u16Reg_Temp != 0U))
    {
        bReturn = false;
    }
    else
    {
        bReturn = true;
    }
    
    return bReturn;
}

#if 0
static void SERCOM_I2CM_TCON_StatusCheck(void)
{
    en_i2c_channel u8Ch = 3U;
    uint32_t u32TimeoutTemp;
    uint32_t u32ConfigTemp;
    uint16_t u16Address = gtObj[u8Ch].address;
    switch(gtObj[u8Ch].state)
    {
        case SERCOM_I2C_REINITIATE_TRANSFER:
        {
            if (gtObj[u8Ch].writeSize != 0U)
            {
                /* Initiate Write transfer */
                SERCOM_I2C_InitiateTransfer(u16Address, false, u8Ch);
            }
            else
            {
                /* Initiate Read transfer */
                SERCOM_I2C_InitiateTransfer(u16Address, true, u8Ch);
            }
            break;
        }

        case SERCOM_I2C_STATE_ADDR_SEND:
        {
            /*
             * Write ADDR[7:0] register to "11110 address[9:8] 1"
             * ADDR.TENBITEN must be cleared
             */
            u32ConfigTemp = gtObj[u8Ch].address >> RIGHT_ALIGNED;
            u32ConfigTemp |=TEN_BIT_ADDR_MASK;
            u32ConfigTemp = u32ConfigTemp << 1U;
            u32ConfigTemp |= I2C_TRANSFER_READ;
            SERCOM3_REGS->I2CM.SERCOM_ADDR = u32ConfigTemp;

            u32TimeoutTemp = 12000U;
            /* Wait for synchronization */
            while((SERCOM3_REGS->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_READ;
            break;
        }
        
        case SERCOM_I2C_STATE_TRANSFER_WRITE:
        {
            if (gtObj[u8Ch].writeCount == (gtObj[u8Ch].writeSize))
            {
                if(gtObj[u8Ch].readSize != 0U)
                {
                    SERCOM_I2C_InitiateRead(u16Address,u8Ch);
                }
                else
                {
                    u32ConfigTemp = SERCOM3_REGS->I2CM.SERCOM_CTRLB;
                    u32ConfigTemp &= ~SERCOM_I2CM_CTRLB_CMD_Msk; 
                    u32ConfigTemp |= SERCOM_I2CM_CTRLB_CMD(3U);
                    SERCOM3_REGS->I2CM.SERCOM_CTRLB = u32ConfigTemp;

                    u32TimeoutTemp = 12000U;
                    /* Wait for synchronization */
                    while((SERCOM3_REGS->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
                    {
                        u32TimeoutTemp = u32TimeoutTemp - 1U;
                    }
                    gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_DONE;
                }
            }
            /* Write next byte */
            else
            {
                SERCOM3_REGS->I2CM.SERCOM_DATA = gtObj[u8Ch].writeBuffer[gtObj[u8Ch].writeCount];
                gtObj[u8Ch].writeCount += 1U;
            }
            break;
        }
        
        case SERCOM_I2C_STATE_TRANSFER_READ:
        {
            if(gtObj[u8Ch].readCount == (gtObj[u8Ch].readSize - 1U))
            {
                /* Set NACK and send stop condition to the slave from master */
                u32ConfigTemp = SERCOM3_REGS->I2CM.SERCOM_CTRLB;
                u32ConfigTemp &= ~(SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD_Msk);
                u32ConfigTemp |= SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD(3U);
                SERCOM3_REGS->I2CM.SERCOM_CTRLB = u32ConfigTemp;

                u32TimeoutTemp = 12000U;
                /* Wait for synchronization */
                while((SERCOM3_REGS->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
                {
                    u32TimeoutTemp = u32TimeoutTemp - 1U;
                }
                gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_DONE;
            }
            else
            {
                /* Set ACK receive data from the slave */
                u32ConfigTemp = SERCOM3_REGS->I2CM.SERCOM_CTRLB;
                u32ConfigTemp &= ~(SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD_Msk);
                u32ConfigTemp |= SERCOM_I2CM_CTRLB_ACKACT(0U) | SERCOM_I2CM_CTRLB_CMD(2U);
                SERCOM3_REGS->I2CM.SERCOM_CTRLB = u32ConfigTemp;
            }

            /* Read the received data */
            gtObj[u8Ch].readBuffer[gtObj[u8Ch].readCount] = SERCOM3_REGS->I2CM.SERCOM_DATA;
            gtObj[u8Ch].readCount += 1U;
            break;
        }
        default:
        {
            break;
        }
    } 
}

void SERCOM_I2CM_TCON_Handler(void)
{
    en_i2c_channel u8Ch = 3U;
    uint32_t u32TimeoutTemp;
    
    if(SERCOM3_REGS->I2CM.SERCOM_INTENSET != 0)
    {
        /* Checks if the arbitration lost in multi-master scenario */
        if((SERCOM3_REGS->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_ARBLOST_Msk) == SERCOM_I2CM_STATUS_ARBLOST_Msk)
        {
            /*
             * Re-initiate the transfer if arbitration is lost
             * in between of the transfer
             */
            gtObj[u8Ch].state = SERCOM_I2C_REINITIATE_TRANSFER;

        }
        else if((SERCOM3_REGS->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_BUSERR_Msk) == SERCOM_I2CM_STATUS_BUSERR_Msk)
        {
            /* Set Error status */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_ERROR;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_BUS;
        }
        else if((SERCOM3_REGS->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_RXNACK_Msk) == SERCOM_I2CM_STATUS_RXNACK_Msk)
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_ERROR;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_NAK;
        }
        else
        {
            SERCOM_I2CM_TCON_StatusCheck();
        }
                    
        if(gtObj[u8Ch].state == SERCOM_I2C_STATE_ERROR)
        {
            /* Reset the PLib objects and Interrupts */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_IDLE;

            /* Generate STOP condition */
            SERCOM3_REGS->I2CM.SERCOM_CTRLB |= SERCOM_I2CM_CTRLB_CMD(3U);

            u32TimeoutTemp = 12000U;
            /* Wait for synchronization */
            while((SERCOM3_REGS->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            SERCOM3_REGS->I2CM.SERCOM_INTFLAG = SERCOM_I2CM_INTFLAG_Msk;

            if (gtObj[u8Ch].callback != NULL)
            {
                gtObj[u8Ch].callback(gtObj[u8Ch].context);
            }
        }
        else if(gtObj[u8Ch].state == SERCOM_I2C_STATE_TRANSFER_DONE)
        {
            /* Reset the PLib objects and interrupts */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_IDLE;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;

            SERCOM3_REGS->I2CM.SERCOM_INTFLAG = SERCOM_I2CM_INTFLAG_Msk;

            u32TimeoutTemp = 12000U;
            /* Wait for the NAK and STOP bit to be transmitted out and I2C state machine to rest in IDLE state */
            while(((SERCOM3_REGS->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_BUSSTATE_Msk) != SERCOM_I2CM_STATUS_BUSSTATE(0x01U)) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp -1U;
            }

            if(gtObj[u8Ch].callback != NULL)
            {
                gtObj[u8Ch].callback(gtObj[u8Ch].context);
            }         
        }
        else
        {/* Nothing */}
    }
}
#endif

static void SERCOM_I2CM_StatusCheck(sercom_registers_t *ptReg, uint8_t u8Ch)
{
    uint32_t u32TimeoutTemp;
    uint32_t u32ConfigTemp;
    uint16_t u16Address = gtObj[u8Ch].address;
    switch(gtObj[u8Ch].state)
    {
        case SERCOM_I2C_REINITIATE_TRANSFER:
        {
            if (gtObj[u8Ch].writeSize != 0U)
            {
                /* Initiate Write transfer */
                SERCOM_I2C_InitiateTransfer(u16Address, false, u8Ch);
            }
            else
            {
                /* Initiate Read transfer */
                SERCOM_I2C_InitiateTransfer(u16Address, true, u8Ch);
            }
            break;
        }

        case SERCOM_I2C_STATE_ADDR_SEND:
        {
            /*
             * Write ADDR[7:0] register to "11110 address[9:8] 1"
             * ADDR.TENBITEN must be cleared
             */
            u32ConfigTemp = (((uint32_t)gtObj[u8Ch].address) >> RIGHT_ALIGNED);
            u32ConfigTemp |=TEN_BIT_ADDR_MASK;
            u32ConfigTemp = u32ConfigTemp << 1U;
            u32ConfigTemp |= I2C_TRANSFER_READ;
            ptReg->I2CM.SERCOM_ADDR = u32ConfigTemp;

            u32TimeoutTemp = 12000U;
            /* Wait for synchronization */
            while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_READ;
            break;
        }
        
        case SERCOM_I2C_STATE_TRANSFER_WRITE:
        {
            if (gtObj[u8Ch].writeCount == (gtObj[u8Ch].writeSize))
            {
                if(gtObj[u8Ch].readSize != 0U)
                {
                    SERCOM_I2C_InitiateRead(u16Address,u8Ch);
                }
                else
                {
                    u32ConfigTemp = ptReg->I2CM.SERCOM_CTRLB;
                    u32ConfigTemp &= ~SERCOM_I2CM_CTRLB_CMD_Msk; 
                    u32ConfigTemp |= SERCOM_I2CM_CTRLB_CMD(3U);
                    ptReg->I2CM.SERCOM_CTRLB = u32ConfigTemp;

                    u32TimeoutTemp = 12000U;
                    /* Wait for synchronization */
                    while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
                    {
                        u32TimeoutTemp = u32TimeoutTemp - 1U;
                    }
                    gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_DONE;
                }
            }
            /* Write next byte */
            else
            {
                ptReg->I2CM.SERCOM_DATA = gtObj[u8Ch].writeBuffer[gtObj[u8Ch].writeCount];
                gtObj[u8Ch].writeCount += 1U;
            }
            break;
        }
        
        case SERCOM_I2C_STATE_TRANSFER_READ:
        {
            if(gtObj[u8Ch].readCount == (gtObj[u8Ch].readSize - 1U))
            {
                /* Set NACK and send stop condition to the slave from master */
                u32ConfigTemp = ptReg->I2CM.SERCOM_CTRLB;
                u32ConfigTemp &= ~(SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD_Msk);
                u32ConfigTemp |= SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD(3U);
                ptReg->I2CM.SERCOM_CTRLB = u32ConfigTemp;

                u32TimeoutTemp = 12000U;
                /* Wait for synchronization */
                while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
                {
                    u32TimeoutTemp = u32TimeoutTemp - 1U;
                }
                gtObj[u8Ch].state = SERCOM_I2C_STATE_TRANSFER_DONE;
            }
            else
            {
                /* Set ACK receive data from the slave */
                u32ConfigTemp = ptReg->I2CM.SERCOM_CTRLB;
                u32ConfigTemp &= ~(SERCOM_I2CM_CTRLB_ACKACT_Msk | SERCOM_I2CM_CTRLB_CMD_Msk);
                u32ConfigTemp |= SERCOM_I2CM_CTRLB_ACKACT(0U) | SERCOM_I2CM_CTRLB_CMD(2U);
                ptReg->I2CM.SERCOM_CTRLB = u32ConfigTemp;
            }

            /* Read the received data */
            gtObj[u8Ch].readBuffer[gtObj[u8Ch].readCount] = ptReg->I2CM.SERCOM_DATA;
            gtObj[u8Ch].readCount += 1U;
            break;
        }
        default:
        {
            break;
        }
    } 
    
    (void)ptReg->I2CM.SERCOM_DATA;
    (void)ptReg->I2CM.SERCOM_ADDR;
    (void)ptReg->I2CM.SERCOM_CTRLB;
}




// LDRA_EXCLUDE_START 76 D
void SERCOM_I2CM_Handler(uint8_t u8Ch)
{
    sercom_registers_t *ptReg = i2c_channel_reg(u8Ch);
    uint32_t u32TimeoutTemp;
    
    if(ptReg != NULL)
    {
    if(ptReg->I2CM.SERCOM_INTENSET != 0U)
    {
        /* Checks if the arbitration lost in multi-master scenario */
        if((ptReg->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_ARBLOST_Msk) == SERCOM_I2CM_STATUS_ARBLOST_Msk)
        {
            /*
             * Re-initiate the transfer if arbitration is lost
             * in between of the transfer
             */
            gtObj[u8Ch].state = SERCOM_I2C_REINITIATE_TRANSFER;

        }
        else if((ptReg->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_BUSERR_Msk) == SERCOM_I2CM_STATUS_BUSERR_Msk)
        {
            /* Set Error status */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_ERROR;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_BUS;
        }
        else if((ptReg->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_RXNACK_Msk) == SERCOM_I2CM_STATUS_RXNACK_Msk)
        {
            gtObj[u8Ch].state = SERCOM_I2C_STATE_ERROR;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_NAK;
        }
        else
        {
            SERCOM_I2CM_StatusCheck(ptReg,u8Ch);
        }
                    
        if(gtObj[u8Ch].state == SERCOM_I2C_STATE_ERROR)
        {
            /* Reset the PLib objects and Interrupts */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_IDLE;

            /* Generate STOP condition */
            ptReg->I2CM.SERCOM_CTRLB |= SERCOM_I2CM_CTRLB_CMD(3U);

            u32TimeoutTemp = 12000U;
            /* Wait for synchronization */
            while((ptReg->I2CM.SERCOM_SYNCBUSY != 0x0U) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            ptReg->I2CM.SERCOM_INTFLAG = SERCOM_I2CM_INTFLAG_Msk;

            if (gtObj[u8Ch].callback != NULL)
            {
                gtObj[u8Ch].callback(gtObj[u8Ch].context);
            }
        }
        else if(gtObj[u8Ch].state == SERCOM_I2C_STATE_TRANSFER_DONE)
        {
            /* Reset the PLib objects and interrupts */
            gtObj[u8Ch].state = SERCOM_I2C_STATE_IDLE;
            gtObj[u8Ch].error = SERCOM_I2C_ERROR_NONE;

            ptReg->I2CM.SERCOM_INTFLAG = SERCOM_I2CM_INTFLAG_Msk;

            u32TimeoutTemp = 12000U;
            /* Wait for the NAK and STOP bit to be transmitted out and I2C state machine to rest in IDLE state */
            while(((ptReg->I2CM.SERCOM_STATUS & SERCOM_I2CM_STATUS_BUSSTATE_Msk) != SERCOM_I2CM_STATUS_BUSSTATE(0x01U)) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp -1U;
            }

            if(gtObj[u8Ch].callback != NULL)
            {
                gtObj[u8Ch].callback(gtObj[u8Ch].context);
            }         
        }
        else
        {/* Nothing */}
    }
    (void) ptReg->I2CM.SERCOM_INTFLAG;
    (void) ptReg->I2CM.SERCOM_SYNCBUSY;
    (void) ptReg->I2CM.SERCOM_STATUS;
    (void) ptReg->I2CM.SERCOM_CTRLB;
    }
    else
    {

    }
}
// LDRA_EXCLUDE_END 76 D

