/* ************************************************************************** */
/** Descriptive File Name

	@Company
		Company Name

	@File Name
		filename.c

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
#include "hal/plib_auo/inc/Sercom2I2CMaster.h"
#include "hal/plib_auo/inc/I2CCommon.h"

//#include "hal/plib_auo/inc/SercomI2CMasterCommon.h"
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
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
		banner.
 */

/* ************************************************************************** */

/** 
	@Function
		int ExampleLocalFunctionName ( int param1, int param2 ) 

	@Summary
		Brief one-line description of the function.

	@Description
		Full description, explaining the purpose and usage of the function.
		<p>
		Additional description in consecutive paragraphs separated by HTML 
		paragraph breaks, as necessary.
		<p>
		Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

	@Precondition
		List and describe any required preconditions. If there are no preconditions,
		enter "None."

	@Parameters
		@param param1 Describe the first parameter to the function.
		
		@param param2 Describe the second parameter to the function.

	@Returns
		List (if feasible) and describe the return values of the function.
		<ul>
			<li>1   Indicates an error occurred
			<li>0   Indicates an error did not occur
		</ul>

	@Remarks
		Describe any special behavior not described above.
		<p>
		Any additional remarks.

	@Example
		@code
		if(ExampleFunctionName(1, 2) == 0)
		{
				return 3;
		}
 */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
		banner.
 */

// *****************************************************************************

/** ===========================================================================
	@Function
		static sercom_registers_t *i2c_channel_reg(en_i2c_channel eCh) 

	@Summary
		Parser the coresponding SFR address.

	@Input
		* en_i2c_channel ch --> specific SERCOM channel

	@Output
		* sercom_registers_t --> the pointer of SFR
============================================================================**/
sercom_registers_t *i2c_channel_reg(en_i2c_channel eCh)
{
	sercom_registers_t *ptdReg;

	if(SERCOM_CH0 == eCh)
    {
		ptdReg = SERCOM0_REGS;
	}
	else if(SERCOM_CH1 == eCh)
    {
		ptdReg = SERCOM1_REGS;
	}
	else if(SERCOM_CH2 == eCh)
    {
		ptdReg = SERCOM2_REGS;
	}
	else if(SERCOM_CH3 == eCh)
    {
		ptdReg = SERCOM3_REGS;
	}
	else if(SERCOM_CH4 == eCh)
    {
		ptdReg = SERCOM4_REGS;
	}
	else if(SERCOM_CH5 == eCh)
    {
		ptdReg = SERCOM5_REGS;
	}
	else
	{
        ptdReg = NULL;
	}
	
	return (sercom_registers_t *)ptdReg;
}

bool i2c_io_setup(en_i2c_channel eCh)
{
	bool bReturn;

	if(SERCOM_CH0 == eCh)
    {
		PORT_REGS->GROUP[0].PORT_PINCFG[8] |= 0x1U; /* PA8 i2c slave sda */
		PORT_REGS->GROUP[0].PORT_PINCFG[9] |= 0x1U; /* PA9 i2c slave scl*/
		PORT_REGS->GROUP[0].PORT_PMUX[4] |= 0x22U;
        bReturn = true;
	}
	else if(SERCOM_CH1 == eCh)
    {
        bReturn = false;
	}
	else if(SERCOM_CH2 == eCh)
    {
        bReturn = false;
	}
	else if(SERCOM_CH3 == eCh)
    {
        PORT_REGS->GROUP[0].PORT_PINCFG[22] = 0x1U; /* PA22 i2c slave sda */
        PORT_REGS->GROUP[0].PORT_PINCFG[23] = 0x1U; /* PA23 i2c slave scl*/
        PORT_REGS->GROUP[0].PORT_PMUX[11] = 0x22U;
        bReturn = true;
	}
	else if(SERCOM_CH4 == eCh)
    {
        bReturn = false;
	}
	else if(SERCOM_CH5 == eCh)
    {
        PORT_REGS->GROUP[1].PORT_PINCFG[16] = 0x1U; /* PB16 i2c slave sda */
        PORT_REGS->GROUP[1].PORT_PINCFG[17] = 0x1U; /* PB17 i2c slave scl*/
        PORT_REGS->GROUP[1].PORT_PMUX[8] = 0x22U;
        bReturn = true;
	}
	else
    {
		bReturn = false;
	}

	return bReturn;
}
#if 0
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
#endif
bool wait_slave_sync(sercom_registers_t *ptdReg)
{
    uint32_t u32TimeoutTemp = 12000U;
    bool bReturn;
    while((0U != ptdReg->I2CS.SERCOM_SYNCBUSY) && (0U < u32TimeoutTemp))
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
#if 0
bool wait_sync(sercom_registers_t *ptdReg)
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
#endif
/* *****************************************************************************
 End of File
 */
