/* ************************************************************************** */
/** Descriptive File Name

  @Company
    AUO

  @File Name
    hal_slave_i2c.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "definitions.h"
#include "hal/inc/I2CMDriver.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
/** ===========================================================================
  @Function
    bool master_i2c_init(st_i2c_master_config *config)

  @Summary
    Initialization of i2c master device

  @Remarks
    Detail description of "st_i2c_master_config" are listed in I2CMDriver.h
============================================================================**/
/******************************************************************************
;Author: Orlando Huang
;Description: N/A
;Return Parameter: {*}
;param {sercom_registers_t} *ptdReg
******************************************************************************/
static bool master_wait_sync(sercom_registers_t *ptdReg)
{
  uint32_t u32TimeoutTemp = 12000U;
  bool bReturn;
  while((0U != ptdReg->I2CM.SERCOM_SYNCBUSY) && (0U < u32TimeoutTemp))
  {
      u32TimeoutTemp = u32TimeoutTemp - 1U;
  }
  if(u32TimeoutTemp > 0U)
  {
      bReturn = true;
  }
  else
  {
      bReturn = false;
  }
  return bReturn;
}
/******************************************************************************
;Author: Orlando Huang
;Description: N/A
;Return Parameter: {*}
;param {st_i2c_master_config} *ptdConfig
******************************************************************************/
bool master_i2c_init(st_i2c_master_config *ptdConfig) 
{
  bool bReturn;
  sercom_registers_t *ptdReg = NULL;

  ptdReg = i2c_channel_reg(ptdConfig->channel);
  if(NULL != ptdReg)
  {
    (void)i2c_io_setup(ptdConfig->channel);
    if(true == master_i2c_stop(ptdConfig->channel))
    {
      uint32_t u32Setup;
      /* Reset the module */
      ptdReg->I2CM.SERCOM_CTRLA = SERCOM_I2CM_CTRLA_SWRST_Msk ;
      (void)master_wait_sync(ptdReg);

      /* Disable smart mode enable to fix i2c shut down,when losting rx ack without into I2C master irq function */
      ptdReg->I2CM.SERCOM_CTRLB = SERCOM_I2CM_CTRLB_RESETVALUE;
      (void)master_wait_sync(ptdReg);
      
      SERCOM_I2CM_CallbackRegister(ptdConfig->callback, (uintptr_t)NULL, ptdConfig->channel);
      /* Baud rate - Master Baud Rate*/
      ptdReg->I2CM.SERCOM_CTRLA &= SERCOM_I2CM_CTRLA_SPEED_Msk; 
      ptdReg->I2CM.SERCOM_CTRLA |= SERCOM_I2CM_CTRLA_SPEED((ptdConfig->speed));
      /* Enable CLK Timeout Handler*/
      ptdReg->I2CM.SERCOM_CTRLA |= SERCOM_I2CM_CTRLA_MEXTTOEN(1U);
      u32Setup = (uint32_t)(ptdConfig->baudrate * 1000U);
      (void)SERCOM_I2C_TransferSetup(&u32Setup,0U,ptdConfig->channel);
      (void)master_i2c_start(ptdConfig->channel);
      SERCOM_I2CM_Initialize(ptdConfig->channel);
      (void)master_i2c_interrupt(ptdConfig);
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
  (void)ptdReg->I2CM.SERCOM_CTRLA;
  (void)ptdReg->I2CM.SERCOM_CTRLB;

  return bReturn;
}

/** ===========================================================================
  @Function
    bool master_i2c_start(en_i2c_channel channel)

  @Summary
    Start the master i2c module

  @Input/Output
    input:  sercom channel
    output: true --> Start succeed.
            false --> Start failed.
============================================================================**/
bool master_i2c_start(en_i2c_channel eCh) 
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
	if(NULL != ptdReg)
    {
      /* Enable peripheral */
      ptdReg->I2CM.SERCOM_CTRLA |= SERCOM_I2CM_CTRLA_ENABLE_Msk | SERCOM_I2CM_CTRLA_MODE_I2C_MASTER | SERCOM_I2CM_CTRLA_SDAHOLD_75NS;
      (void)master_wait_sync(ptdReg);
      
      /* Initial Bus State: IDLE */
      ptdReg->I2CM.SERCOM_STATUS = SERCOM_I2CM_STATUS_BUSSTATE(0x01U); 
      (void)master_wait_sync(ptdReg);
      bReturn = true;
    }
    else
    {
	  	/* channel assigned error */
		  bReturn = false;
    }

    (void)ptdReg->I2CM.SERCOM_CTRLA;
    (void)ptdReg->I2CM.SERCOM_STATUS;
    return bReturn;
}

/** ===========================================================================
  @Function
    bool master_i2c_stop(en_i2c_channel channel)

  @Summary
    Stop the master i2c module

  @Input/Output
    input:  sercom channel
    output: true --> stop succeed.
            false --> stop failed.
============================================================================**/
bool master_i2c_stop(en_i2c_channel eCh) 
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(eCh);
    
    if(NULL != ptdReg)
    {
      /* Disable peripheral */
      ptdReg->I2CM.SERCOM_CTRLA &= ~SERCOM_I2CM_CTRLA_ENABLE_Msk ;
      (void)master_wait_sync(ptdReg);
      bReturn = true;
    }
    else
    {
      bReturn = false;
    }
    
    (void)ptdReg->I2CM.SERCOM_CTRLA;
    return bReturn;
}

bool i2c_nvic_enable(en_i2c_channel eCh)
{
    bool bReturn;
    
    /* Enable NIVC */
    if(SERCOM_CH1 == eCh)
    {
        NVIC_SetPriority(SERCOM1_IRQn, 3U);
        NVIC_EnableIRQ(SERCOM1_IRQn);  
        bReturn = true;
    }
    else if(SERCOM_CH2 == eCh)
    {
        NVIC_SetPriority(SERCOM2_IRQn, 3U);
        NVIC_EnableIRQ(SERCOM2_IRQn);    
        bReturn = true;
    }
    else if(SERCOM_CH3 == eCh)
    {
        NVIC_SetPriority(SERCOM3_IRQn, 3U);
        NVIC_EnableIRQ(SERCOM3_IRQn);    
        bReturn = true;
    }
    else if(SERCOM_CH4 == eCh)
    {
        NVIC_SetPriority(SERCOM4_IRQn, 3U);
        NVIC_EnableIRQ(SERCOM4_IRQn);
        bReturn = true;
    }
    else if(SERCOM_CH5 == eCh)
    {
        NVIC_SetPriority(SERCOM5_IRQn, 3U);
        NVIC_EnableIRQ(SERCOM5_IRQn);
        bReturn = true;
    }
    else
    {
        bReturn = false ;
    }
    
    return bReturn;
}
/** ===========================================================================
  @Function
    bool master_i2c_interrupt(st_i2c_master_config *i2cm)

  @Summary
    Setup the interrupt features of master i2c 

  @Input/Output
    input:  sercom channel
    output: true --> setup succeed.
            false --> setup failed.
============================================================================**/
bool master_i2c_interrupt(st_i2c_master_config *ptdDev)
{
    bool bReturn;
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdDev->channel);
    uint8_t u8TmpReg = (uint8_t)I2C_DEFAULT;
    
    if(NULL != ptdReg)
    {
      if(true == (*ptdDev).inte.error_int)
      {		
        u8TmpReg = u8TmpReg | SERCOM_I2CM_INTENSET_ERROR_Msk;
      }
      else
      {
        u8TmpReg = u8TmpReg & ~SERCOM_I2CM_INTENSET_ERROR_Msk;
      }
          
      if(true == (*ptdDev).inte.master_on_bus)
      {		
        u8TmpReg = u8TmpReg | SERCOM_I2CM_INTENSET_MB_Msk;
      }
      else
      {
        u8TmpReg = u8TmpReg & ~SERCOM_I2CM_INTENSET_MB_Msk;
      }
          
      if(true == (*ptdDev).inte.slave_on_bus)
      {		
        u8TmpReg = u8TmpReg | SERCOM_I2CM_INTENSET_SB_Msk;
      }
      else
      {
        u8TmpReg = u8TmpReg & ~SERCOM_I2CM_INTENSET_SB_Msk;
      }
      
      ptdReg->I2CM.SERCOM_INTENSET = u8TmpReg;

      if(ptdReg->I2CM.SERCOM_INTENSET != u8TmpReg)
      {
        bReturn = false;
      }
      else
      {
        bReturn = i2c_nvic_enable(ptdDev->channel);
      }
      
    }
    else
    {
      bReturn = false;
	  }
  
    (void)ptdReg->I2CM.SERCOM_INTENSET;
    return bReturn;
}

/** ===========================================================================
  @Function
    bool master_i2c_transmitte(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Wlen) 

  @Summary
    Write the data to target device.

  @Input
    * dev --> i2c master device instance
    * buf --> the output data
    * wlen --> length of writing

  @Output
    * bool rt --> return code
        * true = write succeed
        * false = write fail
============================================================================**/
bool master_i2c_transmitte(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Wlen) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdDev->channel);
    bool bReturn;
    
    if(NULL != ptdReg)
    {
      if(false == SERCOM_I2C_Write((uint16_t)ptdDev->addr, pu8Buf, u32Wlen, ptdDev->channel))
      {
          bReturn = false;
      }
      else
      {
          bReturn = true; /* Normal case */
      }
    }
    else
    {
      bReturn = false;
    }
	
    return bReturn;
}
#if I2CMDRIVER_ENABLE_WRITEREAD
bool master_i2c_writeread(st_i2c_master_config *ptdDev, uint8_t *pu8WBuf, uint32_t u32Wlen, uint8_t *pu8RBuf, uint32_t u32Rlen) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdDev->channel);
    bool bReturn;
    
    if(NULL != ptdReg)
    {
      if(false == SERCOM_I2C_WriteRead((uint16_t)ptdDev->addr, pu8WBuf, u32Wlen, pu8RBuf, u32Rlen, ptdDev->channel))
      {
          bReturn = false;
      }
      else
      {
          bReturn = true;
      }
    }
    else
    {
      bReturn = false;
    }

    return bReturn;
}
#endif

/** ===========================================================================
  @Function
    bool master_i2c_read(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Rlen) 

  @Summary
    Read out the received data from reg.

  @Input
    * dev --> i2c master device instance
    * rBuf --> store the received data
    * rlen --> length of reading

  @Output
    * bool rt --> return code
        * true = read succeed
        * false = read fail
============================================================================**/
#if I2CMDRIVER_ENABLE_READ
bool master_i2c_read(st_i2c_master_config *ptdDev, uint8_t *pu8Buf, uint32_t u32Rlen) 
{
    sercom_registers_t *ptdReg = i2c_channel_reg(ptdDev->channel);
    bool bReturn;
    
    if(NULL != ptdReg)
    {
        if(false == SERCOM_I2C_Read((uint16_t)ptdDev->addr, pu8Buf, u32Rlen, ptdDev->channel))
        {
            bReturn = false;
        }
        else
        {
            bReturn = true;
        }
    }
    else
    {
        bReturn = false;
    }

    return bReturn;
}
#endif
#if 0
/** ===========================================================================
  @Function
    uint16_t get_master_i2c_status(en_i2c_channel ch) 

  @Summary
    Return the STATUS SFR to caller

  @Input/Output
    input: sercom channel
    output: SFR SERCOM_STATUS data in uint16_t type
============================================================================**/
uint16_t get_master_i2c_status(en_i2c_channel eCh) 
{
    return (uint16_t)SERCOM_I2CM_IsBusy(eCh);
}
#endif

/* *****************************************************************************
 End of File
 */
