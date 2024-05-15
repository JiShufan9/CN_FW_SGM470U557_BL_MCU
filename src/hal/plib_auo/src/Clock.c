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

#include "hal/plib_auo/inc/Clock.h"

/* TODO:  Include other files here if needed. */


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

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
uint8_t Clock_OSCCtrl_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting)
{
    uint8_t u8Status;
    uint64_t calibValueTemp;
    uint16_t u16RegTemp;
    uint32_t u32TimeoutTemp;
    
    if(CurrentSystemClockSetting != NULL)
    {
        /*HS external Oscillator*/
        if(CurrentSystemClockSetting->u8EnableHSCrystalOsc == YES)
        {
            /* Configure External Oscillator */
            u16RegTemp = OSCCTRL_REGS->OSCCTRL_XOSCCTRL;
            u16RegTemp &= ((~OSCCTRL_XOSCCTRL_ONDEMAND_Msk) & (~OSCCTRL_XOSCCTRL_STARTUP_Msk) & (~OSCCTRL_XOSCCTRL_GAIN_Msk) & (~OSCCTRL_XOSCCTRL_XTALEN_Msk) & (~OSCCTRL_XOSCCTRL_ENABLE_Msk));
            u16RegTemp |= OSCCTRL_XOSCCTRL_STARTUP(OSC48M_STARTUPTIME_31US) | OSCCTRL_XOSCCTRL_GAIN(GAIN_DEFUALT) | OSCCTRL_XOSCCTRL_XTALEN_Msk | OSCCTRL_XOSCCTRL_ENABLE_Msk;
            OSCCTRL_REGS->OSCCTRL_XOSCCTRL = u16RegTemp;

            u32TimeoutTemp = 12000U;
            while(((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_XOSCRDY_Msk) != OSCCTRL_STATUS_XOSCRDY_Msk) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            if(u32TimeoutTemp != 0U )
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_TIMEOUT; 
            }
        }
        else 
        {
            u8Status = DRIVER_TRUE; 
        }

        if(u8Status == DRIVER_TRUE)
        {
            /*48MInternal Oscillator*/
            if(CurrentSystemClockSetting->u8Enable48MInternalOsc == YES)
            {
                calibValueTemp = *(uint64_t*)NVM_SOFTWARE_CALIBRATION_AREAMAPPING;
                uint32_t calibValue = (uint32_t)((calibValueTemp >> CAL48M_3V3_POS ) & CAL48M_MASK);
                OSCCTRL_REGS->OSCCTRL_CAL48M = calibValue;

                /* Selection of the Division Value */
                OSCCTRL_REGS->OSCCTRL_OSC48MDIV = OSCCTRL_OSC48MDIV_DIV(OSC48M_DIV1);

                u32TimeoutTemp = 12000U;
                while(((OSCCTRL_REGS->OSCCTRL_OSC48MSYNCBUSY & OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk) == OSCCTRL_OSC48MSYNCBUSY_OSC48MDIV_Msk) && (u32TimeoutTemp > 0U))
                {
                    u32TimeoutTemp = u32TimeoutTemp - 1U;
                }

                if(u32TimeoutTemp != 0U )
                {
                    u32TimeoutTemp = 12000U;
                    while(((OSCCTRL_REGS->OSCCTRL_STATUS & OSCCTRL_STATUS_OSC48MRDY_Msk) != OSCCTRL_STATUS_OSC48MRDY_Msk) && (u32TimeoutTemp > 0U))
                    {
                        u32TimeoutTemp = u32TimeoutTemp - 1U;
                    }

                    if(u32TimeoutTemp != 0U )
                    {
                        u8Status = DRIVER_TRUE;
                    }
                    else
                    {
                        u8Status = DRIVER_TIMEOUT; 
                    }
                }
                else
                {
                    u8Status = DRIVER_TIMEOUT; 
                }        
            }
            else
            {
                 u8Status = DRIVER_TRUE;
            }
        }
        else
        {
           ;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
  
    return u8Status;
}
uint8_t Clock_OSC32KCtrl_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting)
{
    uint8_t u8Status;
    uint32_t calibValueTemp;
    uint32_t u32TimeoutTemp;
    
    if(CurrentSystemClockSetting != NULL)
    {
        /****************** XOSC32K initialization  ******************************/
        if(CurrentSystemClockSetting->u8EnableLSCrystalOsc == YES)
        {    
            /* Configure 32K External Oscillator */
            OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = OSC32KCTRL_XOSC32K_STARTUP(XOSC32K_STARTUPTIME_60MS) | OSC32KCTRL_XOSC32K_ENABLE_Msk | OSC32KCTRL_XOSC32K_EN1K_Msk | OSC32KCTRL_XOSC32K_EN32K_Msk | OSC32KCTRL_XOSC32K_XTALEN_Msk;

            u32TimeoutTemp = 12000U;
            while(((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_XOSC32KRDY_Msk) != OSC32KCTRL_STATUS_XOSC32KRDY_Msk) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            if(u32TimeoutTemp != 0U )
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_TIMEOUT; 
            }
        }
        else
        {
            u8Status = DRIVER_PARAMETER_ERROR;
        }

        if(u8Status == DRIVER_TRUE)
        {
            /****************** OSC32K Initialization  ******************************/
            if(CurrentSystemClockSetting->u8Enable32KHighAccuacyInternalOsc == YES)
            {
                calibValueTemp = (*(uint32_t*)NVM_SOFTWARE_CALIBRATION_AREAMAPPING);
                uint32_t calibValue = ((calibValueTemp >> OSC32K_CAL_POS ) & OSC32K_MASK);

                /* Configure 32K RC oscillator */
                OSC32KCTRL_REGS->OSC32KCTRL_OSC32K = OSC32KCTRL_OSC32K_CALIB(calibValue) | OSC32KCTRL_OSC32K_STARTUP(OSC32K_STARTUPTIME_92MS) | OSC32KCTRL_OSC32K_ENABLE_Msk | OSC32KCTRL_OSC32K_EN1K_Msk | OSC32KCTRL_OSC32K_EN32K_Msk ;

                u32TimeoutTemp = 12000U;
                while(((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_OSC32KRDY_Msk) != OSC32KCTRL_STATUS_OSC32KRDY_Msk) && (u32TimeoutTemp > 0U))
                {
                    u32TimeoutTemp = u32TimeoutTemp - 1U;
                }

                if(u32TimeoutTemp != 0U )
                {
                    OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(RTC_ULP1K);
                    u8Status = DRIVER_TRUE;
                }
                else
                {
                    u8Status = DRIVER_TIMEOUT; 
                }
            }
            else
            {
                /* Without configure 32K Accurcy RC oscillator */
                OSC32KCTRL_REGS->OSC32KCTRL_OSC32K = UseNormal32KOsc;
                OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(RTC_ULP1K);        
                u8Status = DRIVER_TRUE;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    return u8Status;
}
#if 0
uint8_t Clock_FDPLL_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting)
{
    uint8_t u8Status;
    uint8_t u8TempRestore;
    uint16_t u16TempRestore;
    uint32_t u32TimeoutTemp;
    
    if(CurrentSystemClockSetting->u8EnableFDPLL == YES)
    {          
        OSCCTRL_REGS->OSCCTRL_DPLLCTRLA &= (~OSCCTRL_DPLLCTRLA_ENABLE_Msk);
        
        (void)Clock_GCLKToPeri((uint16_t)GCLK_DPLL,(uint16_t)CurrentSystemClockSetting->u16FDPLLSrc);

        /****************** DPLL Initialization  *********************************/

        /* Configure DPLL    */
        u8TempRestore = (uint8_t)CurrentSystemClockSetting->u8FDPLL_RefClk;
        OSCCTRL_REGS->OSCCTRL_DPLLCTRLB = (OSCCTRL_DPLLCTRLB_FILTER(DEFAULT_FILTER) | OSCCTRL_DPLLCTRLB_LTIME(DEFAULT_LTIME)| OSCCTRL_DPLLCTRLB_REFCLK(u8TempRestore)) ;
       
        u16TempRestore = (uint16_t)CurrentSystemClockSetting->u16FDPLL_LDR;
        u8TempRestore = (uint8_t)CurrentSystemClockSetting->u8FDPLL_LDRFrac;
        OSCCTRL_REGS->OSCCTRL_DPLLRATIO =(OSCCTRL_DPLLRATIO_LDRFRAC(u8TempRestore) | OSCCTRL_DPLLRATIO_LDR(u16TempRestore));
        
        u32TimeoutTemp = 12000U;
        while(((OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) == OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }
        
        if(u32TimeoutTemp != 0U )
        {
            /* Selection of the DPLL Pre-Scalar */
            u8TempRestore = (uint8_t)CurrentSystemClockSetting->u8FDPLL_LDRPresc;
            OSCCTRL_REGS->OSCCTRL_DPLLPRESC = OSCCTRL_DPLLPRESC_PRESC(u8TempRestore);

            u32TimeoutTemp = 12000U;
            while(((OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk) == OSCCTRL_DPLLSYNCBUSY_DPLLPRESC_Msk) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }
            
            if(u32TimeoutTemp != 0U )
            {
                /* Selection of the DPLL Enable */
                OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk;
                
                u32TimeoutTemp = 12000U;
                while(((OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) == OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) && (u32TimeoutTemp > 0U))
                {
                    u32TimeoutTemp = u32TimeoutTemp - 1U;
                }
                
                if(u32TimeoutTemp != 0U )
                {
                    u32TimeoutTemp = 12000U;
                    while(((OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) != (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) && (u32TimeoutTemp > 0U))
                    {
                        u32TimeoutTemp = u32TimeoutTemp - 1U;
                    }
                    if(u32TimeoutTemp != 0U)
                    {
                        u8Status = DRIVER_TRUE;
                    }
                    else
                    {
                        u8Status = DRIVER_TIMEOUT; 
                    }
                }
                else
                {
                    u8Status = DRIVER_TIMEOUT; 
                }
                
            }
            else
            {
                u8Status = DRIVER_TIMEOUT; 
            }
        }
        else
        {
            u8Status = DRIVER_TIMEOUT; 
        }          
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
#endif
uint8_t Clock_GCLKN_Initialize(SystemClock_GCLKTypeDef *CurrentGCLKSetting)
{   
    uint8_t u8Status;
    uint16_t u16GCLKNum;
    uint16_t u16TempRestore1;
    uint16_t u16TempRestore2;
    uint32_t u32TimeoutTemp;
    
    if(CurrentGCLKSetting != NULL)
    {
        switch(CurrentGCLKSetting->u16EnableNumGCLK)
        {   
            case GCLKENABLE0:
                u16GCLKNum = GCLKENABLE0;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE1:
                u16GCLKNum = GCLKENABLE1;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE2:
                u16GCLKNum = GCLKENABLE2;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE3:
                u16GCLKNum = GCLKENABLE3;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE4:
                u16GCLKNum = GCLKENABLE4;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE5:
                u16GCLKNum = GCLKENABLE5;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE6:
                u16GCLKNum = GCLKENABLE6;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE7:
                u16GCLKNum = GCLKENABLE7;
                u8Status = DRIVER_TRUE;
                break;
            case GCLKENABLE8:
                u16GCLKNum = GCLKENABLE8;
                u8Status = DRIVER_TRUE;
                break;
            default:
                u16GCLKNum = GCLKENABLE0;
                u8Status = DRIVER_PARAMETER_ERROR;
                break;
        }

        if(u8Status == DRIVER_TRUE)
        {
            u16TempRestore1 = (uint16_t)CurrentGCLKSetting->u16GCLKDIV;
            u16TempRestore2 = (uint16_t)CurrentGCLKSetting->u16GCLKSrcSelect;
            GCLK_REGS->GCLK_GENCTRL[u16GCLKNum] = GCLK_GENCTRL_DIV(u16TempRestore1) | GCLK_GENCTRL_SRC(u16TempRestore2) | GCLK_GENCTRL_GENEN_Msk;

            u32TimeoutTemp = 12000U;
            while(((GCLK_REGS->GCLK_SYNCBUSY & (GCLKSTARTMASK<<(u16GCLKNum+SYNCBUSYBIT_SHIFT))) == (GCLKSTARTMASK<<(u16GCLKNum+SYNCBUSYBIT_SHIFT))) && (u32TimeoutTemp > 0U))
            {
                u32TimeoutTemp = u32TimeoutTemp - 1U;
            }

            if(u32TimeoutTemp != 0U )
            {
                u8Status = DRIVER_TRUE;
            }
            else
            {
                u8Status = DRIVER_TIMEOUT; 
            }  
        }
        else
        {
            ;
        }
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
/*******************************************************************************
   Function Name                :   Clock_GCLKToPeri
   Parameters                   :   u16PeripheralNum
                                    u16GCLKGENValue
   Return Values                :   Nothing
   Function Descripttion        :   Connect GCLK clock to using peripheral 
 *******************************************************************************/
uint8_t Clock_GCLKToPeri(uint16_t u16PeripheralNum,uint16_t u16GCLKGENValue)
{
    uint8_t u8Status;
    uint32_t u32TimeoutTemp;
    
    if(u16PeripheralNum < PERIPHERAL_NUM_CHECK)
    {
        /* Selection of the Generator and write Lock for EIC */
        GCLK_REGS->GCLK_PCHCTRL[u16PeripheralNum] = GCLK_PCHCTRL_GEN(u16GCLKGENValue)  | GCLK_PCHCTRL_CHEN_Msk;
        
        u32TimeoutTemp = 12000U;
        while(((GCLK_REGS->GCLK_PCHCTRL[u16PeripheralNum] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk) && (u32TimeoutTemp > 0U))
        {
            u32TimeoutTemp = u32TimeoutTemp - 1U;
        }

        if(u32TimeoutTemp != 0U )
        {
            u8Status = DRIVER_TRUE;
        }
        else
        {
            u8Status = DRIVER_TIMEOUT; 
        } 
    }
    else
    {
        u8Status = DRIVER_PARAMETER_ERROR;
    }
    
    return u8Status;
}
/*******************************************************************************
   Function Name                :   SystemClock_AHBClock_Enable
   Parameters                   :   CurrentSystemClockSetting
                                    
   Return Values                :   Nothing
   Function Descripttion        :   This must be called one time
 *******************************************************************************/
uint8_t Clock_AHBClock_Enable(SystemClock_InitTypeDef *CurrentSystemClockSetting)
{   
    uint8_t u8Status = DEFAULT;
    (void) CurrentSystemClockSetting;
#if SAMC2XN_SERISES == TRUE
    if(((*CurrentSystemClockSetting).u32EnableAHBClk  &  Clk_AHB_NESSARY) ==Clk_AHB_NESSARY)
    {
        /* Configure the AHB Bridge Clocks */
        //MCLK_REGS->MCLK_AHBMASK = 0x1cff;
        MCLK_REGS->MCLK_AHBMASK = (*CurrentSystemClockSetting).u32EnableAHBClk;
        /* Configure the APBD Bridge Clocks */
        //MCLK_REGS->MCLK_APBDMASK = 0x21000;
        MCLK_REGS->MCLK_APBDMASK = (*CurrentSystemClockSetting).u32EnableAPBDClk;
        u8Status |= AHBCLOCK_OK;
    }
    else
    {
        u8Status &= ~AHBCLOCK_OK;
    }
#else
    if(((*CurrentSystemClockSetting).u32EnableAHBClk  &  Clk_AHB_NESSARY) ==Clk_AHB_NESSARY)
    {
        /* Configure the AHB Bridge Clocks */
        MCLK_REGS->MCLK_AHBMASK = (*CurrentSystemClockSetting).u32EnableAHBClk;
        
        /* Configure the APBD Bridge Clocks */
        u8Status = DRIVER_TRUE;
    }
    else
    {
        u8Status = DRIVER_FALSE;
    }
#endif
    /* Configure the APBC Bridge Clocks */
    MCLK_REGS->MCLK_APBCMASK = (*CurrentSystemClockSetting).u32EnableAPBCClk; 
    
    /* Configure the APBA Bridge Clocks */
    MCLK_REGS->MCLK_APBCMASK = 0x65852;
    return u8Status;
}
#if 0
uint8_t Clock_DisableHSCOsc(void)
{
    uint16_t u16Temp;
    uint8_t u8Status;
    
    u16Temp = OSCCTRL_REGS->OSCCTRL_XOSCCTRL;
    u16Temp &= ~OSCCTRL_XOSCCTRL_XTALEN_Msk;
    OSCCTRL_REGS->OSCCTRL_XOSCCTRL = u16Temp;
    
    if((OSCCTRL_REGS->OSCCTRL_XOSCCTRL & OSCCTRL_XOSCCTRL_XTALEN_Msk) == OSCCTRL_XOSCCTRL_XTALEN_Msk)
    {
        u8Status = DRIVER_WRITE_ERROR;
    }
    else
    {
        u8Status = DRIVER_TRUE;
    }
    
    return u8Status;
}
#endif
/* *****************************************************************************
 End of File
 */
