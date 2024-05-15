/* ************************************************************************** */
/** Descriptive File Name

  @Company
    AUO

  @File Name
    I2CSDriver.c
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "hal/inc/I2CSDriver.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
/** ===========================================================================
 * FUNCTION: slave_i2c_init
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O         DESCRIPTION
 * --------     ----                    ---         ---------------
 * config       st_i2c_slave_config     Input       The instance of i2c module
 * 
 * RETURNS: boolean
 *          true  --> initial succeed
 *          false --> initial fail
============================================================================**/
bool slave_i2c_init(st_i2c_slave_config *ptdConfig) 
{    
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdConfig->channel);
            
    if((NULL != ptdConfig) && (NULL != ptdReg))
    {   
        uint32_t u32ConfigTemp;
        
        (void)i2c_io_setup(ptdConfig->channel);

        /* Reset the module */
        ptdReg->I2CS.SERCOM_CTRLA |= SERCOM_I2CS_CTRLA_SWRST_Msk;;
        (void)wait_slave_sync(ptdReg);

        u32ConfigTemp = ptdReg->I2CS.SERCOM_CTRLA;

        /* Set Operation Mode to I2C Slave */
        u32ConfigTemp |= (SERCOM_I2CS_CTRLA_MODE_I2C_SLAVE | SERCOM_I2CS_CTRLA_SDAHOLD_75NS);            

        /* Set device speed */
        u32ConfigTemp |= ptdConfig->speed; 

        ptdReg->I2CS.SERCOM_CTRLA = u32ConfigTemp;

        /* Set the slave address */               
        ptdReg->I2CS.SERCOM_ADDR  |= SERCOM_I2CS_ADDR_ADDR(ptdConfig->addr);        

        SERCOM0_I2CS_CallbackRegister(ptdConfig->callback, (uintptr_t)NULL);
        (void)slave_i2c_interrupt(ptdConfig);

        /* Start the i2c module */
        bReturn = slave_i2c_start(ptdConfig->channel);
    }
    else
    {
        bReturn = false; /* Assign wrong sercom channel */
    } 
    
    (void)ptdReg->I2CS.SERCOM_CTRLA;
    (void)ptdReg->I2CS.SERCOM_ADDR;
    return bReturn;
}
/** ===========================================================================
 * FUNCTION: slave_i2c_start
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE              I/O         DESCRIPTION
 * --------     ----              ---         ---------------
 * channel      en_i2c_channel    Input       The target channel 0 ~ 5 for J18A
 * 
 * RETURNS: boolean
 *          true  --> start succeed
 *          false --> start fail
============================================================================**/
bool slave_i2c_start(en_i2c_channel eCh) 
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
    if(NULL != ptdReg)
    {
        /* Enable peripheral */
       ptdReg->I2CS.SERCOM_CTRLA |= SERCOM_I2CS_CTRLA_ENABLE_Msk;

       /* Wait for synchronization */
       (void)wait_slave_sync(ptdReg);
       bReturn = true;
    }
    else
    {
        (void)ptdReg;
        bReturn = false;
    }
    (void)ptdReg->I2CS.SERCOM_CTRLA;
    return bReturn;
}

/** ===========================================================================
 * FUNCTION: slave_i2c_stop
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE              I/O         DESCRIPTION
 * --------     ----              ---         ---------------
 * channel      en_i2c_channel    Input       The target channel 0 ~ 5 for J18A
 * 
 * RETURNS: boolean
 *          true  --> stop succeed
 *          false --> stop fail
============================================================================**/
bool slave_i2c_stop(en_i2c_channel eCh) 
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
    if(NULL != ptdReg)
    {
        /* Disable peripheral */
        ptdReg->I2CS.SERCOM_CTRLA &= ~SERCOM_I2CS_CTRLA_ENABLE_Msk ;

        /* Wait for synchronization */
        (void)wait_slave_sync(ptdReg);
        bReturn = true;
    }
    else
    {
        bReturn = false;
    }
    
    (void)ptdReg->I2CS.SERCOM_CTRLA;
    return bReturn;
}
/** ===========================================================================
 * FUNCTION: slave_i2c_interrupt
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * dev          st_i2c_slave_config     Input   the instance of i2c module
 * 
 * RETURNS: boolean
 *          true  --> stop succeed
 *          false --> stop fail
============================================================================**/
bool slave_i2c_interrupt(st_i2c_slave_config *ptdConfig) 
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdConfig->channel);
    uint8_t u8RegTemp;

    u8RegTemp = I2C_DEFAULT;   
    if(NULL != ptdReg)
    {
        if(true == slave_i2c_stop(ptdConfig->channel))
        {
            /* 1. Updated the interrupt status */
            /* Enable/Disable Error interrupt */
            if(true == (*ptdConfig).inte.error_int)
            {		
                u8RegTemp = u8RegTemp | SERCOM_I2CS_INTFLAG_ERROR_Msk;
            }
            else
            {
                u8RegTemp = u8RegTemp & ~SERCOM_I2CS_INTFLAG_ERROR_Msk;
            }
            /* Enable/Disable Address match interrupt */
            if(true == (*ptdConfig).inte.addr_matched)
            {		
                u8RegTemp = u8RegTemp | SERCOM_I2CS_INTFLAG_AMATCH_Msk;
            }
            else
            {
                u8RegTemp = u8RegTemp & ~SERCOM_I2CS_INTFLAG_AMATCH_Msk;
            }
            /* Enable/Disable Data ready interrupt */
            if(true == (*ptdConfig).inte.data_ready)
            {		
                u8RegTemp = u8RegTemp | SERCOM_I2CS_INTFLAG_DRDY_Msk;
            }
            else
            {
                u8RegTemp = u8RegTemp & ~SERCOM_I2CS_INTFLAG_DRDY_Msk;
            }
            /* Enable/Disable Stop receive interrupt */
            if(true == (*ptdConfig).inte.stop_receive)
            {		
                u8RegTemp = u8RegTemp | SERCOM_I2CS_INTFLAG_PREC_Msk;
            }
            else
            {
                u8RegTemp = u8RegTemp & ~SERCOM_I2CS_INTFLAG_PREC_Msk;
            }
            /* 2. Writing into the SFR */
            ptdReg->I2CS.SERCOM_INTENSET = u8RegTemp;
                
            if(u8RegTemp != ptdReg->I2CS.SERCOM_INTENSET)
            {
                /* should not be here */
                bReturn = false;
            }
            else
            {
                /* Normal case */
                NVIC_SetPriority(SERCOM0_IRQn, 3);
                NVIC_EnableIRQ(SERCOM0_IRQn);    
                bReturn = true;
            }
        }
        else
        {
            bReturn = false;
        }
    }
    else
    {
        bReturn = false;
	}

    return bReturn;
}

/** ===========================================================================
 * FUNCTION: get_slave_i2c_status
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * ch           en_i2c_channel          Input   The target channel, 0 ~ 5 for J18A
 * 
 * RETURNS: uint16, the content of STATUS SFR data
============================================================================**/
uint16_t get_slave_i2c_status(en_i2c_channel eCh) 
{    
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
    return ptdReg->I2CS.SERCOM_STATUS;
}
#if 0
uint8_t get_slave_i2c_flag(en_i2c_channel eCh) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
    return ptdReg->I2CS.SERCOM_INTFLAG;
}
#endif
/** ===========================================================================
 * FUNCTION: clear_slave_i2c_flag
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * ch           en_i2c_channel          Input   The target channel, 0 ~ 5 for J18A
 * clrflag      uint8_t                 Input   SERCOM_I2CS_INTFLAG_PREC_Msk   0x01
                                                SERCOM_I2CS_INTFLAG_AMATCH_Msk 0x02
                                                SERCOM_I2CS_INTFLAG_DRDY_Msk   0x04
                                                SERCOM_I2CS_INTFLAG_ERROR_Msk  0x80
 * 
 * RETURNS: boolean
            true  --> clear interrupt flag succeed
            false --> clear interrupt flag fail
============================================================================**/
bool clear_slave_i2c_flag(en_i2c_channel eCh, uint8_t u8ClrFlag) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    bool bReturn;
    
    if(NULL != ptdReg)
    {
        ptdReg->I2CS.SERCOM_INTFLAG = u8ClrFlag;
        bReturn = true;
    }
    else
    {
        bReturn = false;
    }

    (void)ptdReg->I2CS.SERCOM_INTFLAG;
    return bReturn;
}
/** ===========================================================================
 * FUNCTION: slave_i2c_transmitte
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * dev          st_i2c_slave_config *   Input   the instance of i2c module
 * buf          uint8_t *               Input   tx data buffer
 * 
 * RETURNS: boolean
            true  --> tx succeed
            false --> tx fail
============================================================================**/
bool slave_i2c_transmitte(st_i2c_slave_config *ptdConfig, uint8_t *pu8Buffer) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdConfig->channel);
    bool bReturn;
    
    if(NULL != ptdReg)
    {   
        ptdReg->I2CS.SERCOM_DATA = *pu8Buffer;
        bReturn = true;
    }
    else
    {
        bReturn = false;
    }
   
    (void)ptdReg->I2CS.SERCOM_DATA;
    return bReturn;
}
/** ===========================================================================
 * FUNCTION: slave_i2c_read
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * dev          st_i2c_slave_config *   Input   the instance of i2c module
 * buf          uint8_t *               Output  rx data buffer
 * 
 * RETURNS: boolean
            true  --> rx succeed
            false --> rx fail
============================================================================**/
bool slave_i2c_read(st_i2c_slave_config *ptdConfig, st_ring_buffer *ptdRingBuffer) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdConfig->channel);
    bool bReturn;
    
    if(ptdReg != NULL)
    {
        (void)slave_i2c_ringbuffer_push(ptdRingBuffer, (uint8_t)ptdReg->I2CS.SERCOM_DATA);
        bReturn = true;
    }
    else
    {
        (void)ptdRingBuffer;
        bReturn = false;
    }

    return bReturn;
}
/** ===========================================================================
 * FUNCTION: slave_i2c_data_ready_wait
 * 
 * ARGUMENTS:
 * ARGUMENT     TYPE                    I/O     DESCRIPTION
 * --------     ----                    ---     ---------------
 * dev          st_i2c_slave_config *   Input   the instance of i2c module
 * 
 * 
 * RETURNS: boolean
            true  --> rx succeed
            false --> rx fail
============================================================================**/
bool slave_i2c_data_ready_wait(st_i2c_slave_config *ptdConfig) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdConfig->channel);
    uint32_t u32TimeoutTemp = 12000U;
    uint32_t u32RegTemp;
    bool bReturn;

    if(NULL != ptdReg)
    {   
        do
        {
            u32RegTemp = ptdReg->I2CS.SERCOM_INTFLAG & (SERCOM_I2CS_INTFLAG_DRDY_Msk | SERCOM_I2CS_INTFLAG_ERROR_Msk | SERCOM_I2CS_INTFLAG_PREC_Msk);
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }while((u32RegTemp == 0x00U) && (u32TimeoutTemp > 0U));
        
        if(u32TimeoutTemp > 0U)
        {
            bReturn = true;
        }
        else
        {
            bReturn = false;
        }
    }
    else
    {
        bReturn = false;
    }
   
    return bReturn;   
}

void slave_i2c_ringbuffer_init(st_ring_buffer *ptdRingBuffer)
{
   (void)memset(ptdRingBuffer->u8Buf, 0U, sizeof(ptdRingBuffer->u8Buf));
   ptdRingBuffer->u16Length = 0U;
   ptdRingBuffer->u16LengthMax = sizeof(ptdRingBuffer->u8Buf);
   ptdRingBuffer->u16Head = 0U;
   ptdRingBuffer->u16Tail = 0U;
}

bool slave_i2c_ringbuffer_pull(st_ring_buffer *ptdRingBuffer, uint8_t *pu8Temp, uint16_t u16Size)
{
    uint16_t u16Counter;
    bool bReturn;
    
    if(ptdRingBuffer->u16Length < u16Size)
    {
        bReturn = false;
    }
    else
    {
        for(u16Counter = 0U; u16Counter < u16Size; u16Counter++)
        {
            *(pu8Temp + u16Counter) = ptdRingBuffer->u8Buf[ ptdRingBuffer->u16Head];
            ptdRingBuffer->u8Buf[ ptdRingBuffer->u16Head] = 0U;

            if(ptdRingBuffer->u16Head == (ptdRingBuffer->u16LengthMax - 1))
            {
                ptdRingBuffer->u16Head = 0U;
            }
            else
            {
                ptdRingBuffer->u16Head = ptdRingBuffer->u16Head + 1U;
            }
            ptdRingBuffer->u16Length = ptdRingBuffer->u16Length - 1U;
        }
        bReturn = false;
    }
    
    return bReturn;
}

bool slave_i2c_ringbuffer_push(st_ring_buffer *ptdRingBuffer, uint8_t u8Data)
{   
    bool bReturn = true;
    
    if(ptdRingBuffer->u16Length > ptdRingBuffer->u16LengthMax)
    {
        bReturn = false;
    }
    else
    {
        ptdRingBuffer->u8Buf[ptdRingBuffer->u16Tail] = u8Data;

        if(ptdRingBuffer->u16Tail == (ptdRingBuffer->u16LengthMax - 1))
        {
            ptdRingBuffer->u16Tail = 0U;
        }
        else
        {
            ptdRingBuffer->u16Tail = ptdRingBuffer->u16Tail + 1U;
        }
        ptdRingBuffer->u16Length = ptdRingBuffer->u16Length + 1U;     
        bReturn = true;
    }
    return bReturn;
}
/* *****************************************************************************
 End of File
 */
