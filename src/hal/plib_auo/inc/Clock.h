/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef CLOCK_H    /* Guard against multiple inclusion */
#define CLOCK_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "main.h"
#include "hal/inc/hal_common.h"

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */
    /*return status code*/
#ifndef CLOCK_RETURN_CODE
    #define CLOCK_RETURN_CODE
    #define DEFAULT                                         0x00U
    #define ENABLE_32KXOSC                                  0x01U
    #define ENABLE_32KOSC                                   0x02U
    #define ENABLE_HSXOSC                                   0x01U
    #define ENABLE_HSOSC                                    0x02U
    #define ENABLE_FDPLL                                    0x01U
    #define ENABLE_GCLK                                     0x01U
    #define ENABLE_GCLKEND                                  0x02U
    #define PERIPHERAL_NUM_CHECK                          0x0080U
    #define GCLK_TO_PERIPHERAL_OK                           0x01U
    #define AHBCLOCK_OK                                     0x01U
    #define LDR_SET_OK                                      0x01U
    #define LDR_SET_FAIL                                    0x00U     
    #define CLOCK_INIT_OK                                   0x01U
    #define CLOCK_INIT_FAIL                                 0x00U
#endif

    #define NVM_SOFTWARE_CALIBRATION_AREAMAPPING        0x806020U
    
    #define GCLKENABLE0                                        0U
    #define GCLKENABLE1                                        1U
    #define GCLKENABLE2                                        2U
    #define GCLKENABLE3                                        3U
    #define GCLKENABLE4                                        4U
    #define GCLKENABLE5                                        5U
    #define GCLKENABLE6                                        6U
    #define GCLKENABLE7                                        7U
    #define GCLKENABLE8                                        8U

    #define GCLKGEN0                                           0U
    #define GCLKGEN1                                           1U
    #define GCLKGEN2                                           2U
    #define GCLKGEN3                                           3U
    #define GCLKGEN4                                           4U
    #define GCLKGEN5                                           5U
    #define GCLKGEN6                                           6U
    #define GCLKGEN7                                           7U
    #define GCLKGEN8                                           8U
   
    #define DIV1                                               1U
    #define DIV2                                               2U

    #define XOSC                                            0x00U  /*XOSC oscillator output*/
    #define GCLK_IN                                         0x01U  /*Generator input pad (GCLK_IO)*/
    #define GCLK_GEN1                                       0x02U  /*Generic clock generator 1 output*/
    #define OSCULP32K                                       0x03U  /*OSCULP32K oscillator output*/
    #define OSC32K                                          0x04U  /*OSC32K oscillator output*/
    #define XOSC32K                                         0x05U  /*XOSC32K oscillator output*/
    #define OSC48M                                          0x06U  /*OSC48M oscillator output*/
    #define DPLL96M                                         0x07U  /*DPLL96M output*/
    
    /*FDPLL Selection*/
    #define LDR_OVERFLOW                                  0x1000U
    #define LDR_FRAC_MASK                                    0xFU
    #define LDR_MASK                                       0xFFFU
    #define FDPLL_PRESCALER_MASK                             0x3U
    #define DEFAULT_LTIME                                      0U
    #define DEFAULT_FILTER                                     0U
    /*RTC Clock Selection*/
    #define RTC_ULP1K                                          0U  
    #define RTC_ULP32K                                         1U  
    #define RTC_OSC1K                                          2U  
    #define RTC_OSC32K                                         3U  
    #define RTC_XOSC1K                                         4U  
    #define RTC_XOSC32K                                        5U  

    
    #define OSC48M_DIV1                                      0x0U
    #define OSC48M_DIV2                                      0x1U
    #define OSC48M_DIV3                                      0x2U
    #define OSC48M_DIV4                                      0x3U
    #define OSC48M_DIV5                                      0x4U
    #define OSC48M_DIV6                                      0x5U
    #define OSC48M_DIV7                                      0x6U
    #define OSC48M_DIV8                                      0x7U
    #define OSC48M_DIV9                                      0x8U
    #define OSC48M_DIV10                                     0x9U
    #define OSC48M_DIV11                                     0xAU
    #define OSC48M_DIV12                                     0xBU
    #define OSC48M_DIV13                                     0xCU
    #define OSC48M_DIV14                                     0xDU
    #define OSC48M_DIV15                                     0xEU
    #define OSC48M_DIV16                                     0xFU
    
    #define OSC32K_CAL_POS                                    12U
    #define CAL48M_5V_POS                                     19U
    #define CAL48M_3V3_POS                                    41U

    #define OSC32K_MASK                                     0x7fU
    #define CAL48M_MASK                                 0x3fffffU

    
    #define GCLKSTARTMASK                                    0x1U

    #define UseNormal32KOsc                                  0x0U

    //#define Enable48MInternalOsc                    0x01U
    //#define EnableHSCrystalOsc                      0x02U
    //#define EnableFDPLL                             0x04U
    //#define EnableLSCrystalOsc                      0x08U
    //#define Enable32KHighAccuacyInternalOsc         0x10U
    //#define Enable32KXOsc                           0x20U
    /*GCLK connect to perpherial number*/
    #define GCLK_DPLL                                          0U  /*FDPLL96M input clock source for reference*/
    #define GCLK_DPLL_32K                                      1U  /*FDPLL96M 32kHz clock for FDPLL96M internal clock timer*/
    #define GCLK_EIC                                           2U  /*EIC*/
    #define GCLK_FREQM_MSR                                     3U  /*FREQM Measure*/
    #define GCLK_FREQM_REF                                     4U  /*FREQM Reference*/  
    #define GCLK_TSENS                                         5U  /*TSENS*/
    #define GCLK_EVSYS_CHANNEL_0                               6U  /*EVSYS_CHANNEL_0*/
    #define GCLK_EVSYS_CHANNEL_1                               7U  /*EVSYS_CHANNEL_1*/
    #define GCLK_EVSYS_CHANNEL_2                               8U  /*EVSYS_CHANNEL_2*/
    
    #define GCLK_EVSYS_CHANNEL_3                               9U  /*EVSYS_CHANNEL_3*/
    #define GCLK_EVSYS_CHANNEL_4                              10U  /*EVSYS_CHANNEL_4*/
    #define GCLK_EVSYS_CHANNEL_5                              11U  /*EVSYS_CHANNEL_5*/
    #define GCLK_EVSYS_CHANNEL_6                              12U  /*EVSYS_CHANNEL_6*/
    #define GCLK_EVSYS_CHANNEL_7                              13U  /*EVSYS_CHANNEL_7*/
    #define GCLK_EVSYS_CHANNEL_8                              14U  /*EVSYS_CHANNEL_8*/
    #define GCLK_EVSYS_CHANNEL_9                              15U  /*EVSYS_CHANNEL_9*/
    #define GCLK_EVSYS_CHANNEL_10                             16U  /*EVSYS_CHANNEL_10*/
    #define GCLK_EVSYS_CHANNEL_11                             17U  /*EVSYS_CHANNEL_11*/
    
    #define GCLK_SERCOM_0_1_2_3_4_SLOW                        18U /*SERCOM[0,1,2,3,4]_SLOW*/
    
    #define GCLK_SERCOM0_CORE                                19U /*SERCOM0_CORE*/
    #define GCLK_SERCOM1_CORE                                20U /*SERCOM1_CORE*/
    #define GCLK_SERCOM2_CORE                                21U /*SERCOM2_CORE*/
    #define GCLK_SERCOM3_CORE                                22U /*SERCOM3_CORE*/
    #define GCLK_SERCOM4_CORE                                23U /*SERCOM4_CORE*/
   
    #define GCLK_SERCOM5_SLOW                                24U /*SERCOM5_SLOW*/
    #define GCLK_SERCOM5_CORE                                25U /*SERCOM5_CORE*/
   
    #define GCLK_CAN0                                        26U /*CAN0*/
    #define GCLK_CAN1                                        27U /*CAN1*/
    
    #define GCLK_TCC0_TCC1                                   28U /*TCC0,TCC1*/
    #define GCLK_TCC2                                        29U /*TCC2*/
    
    #define GCLK_TC0_TC1                                     30U /* TC0,TC1*/
    
    #define GCLK_TC2_TC3                                     31U /*TC2,TC3 */ 
    #define GCLK_TC4                                         32U /*TC4*/
    #define GCLK_ADC0                                        33U /*ADC0*/
    #define GCLK_ADC1                                        34U /*ADC1*/
    
    #define GCLK_SDADC                                       35U /*SDADC*/
    #define GCLK_DAC                                         36U /*DAC*/
    #define GCLK_PTC                                         37U /*PTC*/
    #define GCLK_CCL                                         38U /*CCL*/
    /*39 - Reserved*/
    #define GCLK_AC                                          40U /*AC*/
    #define GCLK_SERCOM6_CORE                                41U /*SERCOM6_CORE*/
    #define GCLK_SERCOM7_CORE                                42U /*SERCOM7_CORE*/
    #define GCLK_TC5                                         43U /*TC5*/
    #define GCLK_TC6                                         44U /*TC6*/
    #define GCLK_TC7                                         45U /*TC7*/
    /*----------OSC48M Setting--------------------------------------------------*/
    #define OSC48M_STARTUPTIME_31US                         0x0U
    
    #define OSC32K_STARTUPTIME_92MS                         0x0U

    #define XOSC32K_STARTUPTIME_60MS                        0x0U
    
    #define GAIN_DEFUALT                                    0x2U
    
 /*AHB clock mask*/   
#if SAMC2XN_SERISES ==TRUE
    #define Clk_AHB_NESSARY                              0x3CFFU
#else 
    #define Clk_AHB_NESSARY                              0x1CFFU
#endif
    #define Clk_AHB_MASK                             0x00000001U
    #define Clk_AHB_APBD                      (Clk_AHB_MASK<<13)
    #define Clk_AHB_DIVAS                     (Clk_AHB_MASK<<12)
    #define Clk_AHB_PAC                       (Clk_AHB_MASK<<10)
    #define Clk_AHB_CAN1                       (Clk_AHB_MASK<<9)
    #define Clk_AHB_CAN0                       (Clk_AHB_MASK<<8)
    #define Clk_AHB_DMAC                       (Clk_AHB_MASK<<7)
    #define Clk_AHB_HSRAM                      (Clk_AHB_MASK<<6)
    #define Clk_AHB_NVMCTRL                    (Clk_AHB_MASK<<5)
    #define Clk_AHB_HMATRIXHS                  (Clk_AHB_MASK<<4)
    #define Clk_AHB_DSU                        (Clk_AHB_MASK<<3)
    #define Clk_AHB_APBC                       (Clk_AHB_MASK<<2)
    #define Clk_AHB_APBB                       (Clk_AHB_MASK<<1)
    #define Clk_AHB_APBA                       (Clk_AHB_MASK<<0)
    
    #define Clk_APBA_TSENS                    (Clk_AHB_MASK<<12)
    #define Clk_APBA_FREQM                    (Clk_AHB_MASK<<11)
    #define Clk_APBA_EIC                      (Clk_AHB_MASK<<10)
    #define Clk_APBA_RTC                       (Clk_AHB_MASK<<9)
    #define Clk_APBA_WDT                       (Clk_AHB_MASK<<8)
    #define Clk_APBA_GCLK                      (Clk_AHB_MASK<<7)
    #define Clk_APBA_SUPC                      (Clk_AHB_MASK<<6)
    #define Clk_APBA_OSC32K                    (Clk_AHB_MASK<<5)
    #define Clk_APBA_OSCCTRL                   (Clk_AHB_MASK<<4)
    #define Clk_APBA_RSTC                      (Clk_AHB_MASK<<3)
    #define Clk_APBA_MCLK                      (Clk_AHB_MASK<<2)
    #define Clk_APBA_PM                        (Clk_AHB_MASK<<1)
    #define Clk_APBA_PAC                       (Clk_AHB_MASK<<0)
    #define Clk_APBC_CCL                      (Clk_AHB_MASK<<23)
    #define Clk_APBC_PTC                      (Clk_AHB_MASK<<22)
    #define Clk_APBC_DAC                      (Clk_AHB_MASK<<21)
    #define Clk_APBC_AC                       (Clk_AHB_MASK<<20)
    #define Clk_APBC_SDADC                    (Clk_AHB_MASK<<19)
    #define Clk_APBC_ADC1                     (Clk_AHB_MASK<<18)
    #define Clk_APBC_ADC0                     (Clk_AHB_MASK<<17)
    #define Clk_APBC_TC4                      (Clk_AHB_MASK<<16)
    #define Clk_APBC_TC3                      (Clk_AHB_MASK<<15)
    #define Clk_APBC_TC2                      (Clk_AHB_MASK<<14)
    #define Clk_APBC_TC1                      (Clk_AHB_MASK<<13)
    #define Clk_APBC_TC0                      (Clk_AHB_MASK<<12)
    #define Clk_APBC_TCC2                     (Clk_AHB_MASK<<11)
    #define Clk_APBC_TCC1                     (Clk_AHB_MASK<<10)
    #define Clk_APBC_TCC0                      (Clk_AHB_MASK<<9)
    
    
    #define Clk_APBC_SERCOM5                   (Clk_AHB_MASK<<6)
    #define Clk_APBC_SERCOM4                   (Clk_AHB_MASK<<5)
    #define Clk_APBC_SERCOM3                   (Clk_AHB_MASK<<4)
    #define Clk_APBC_SERCOM2                   (Clk_AHB_MASK<<3)
    #define Clk_APBC_SERCOM1                   (Clk_AHB_MASK<<2)
    #define Clk_APBC_SERCOM0                   (Clk_AHB_MASK<<1)
    #define Clk_APBC_EYSYS                     (Clk_AHB_MASK<<0)

    #define Clk_APBD_TC7                       (Clk_AHB_MASK<<4)
    #define Clk_APBD_TC6                       (Clk_AHB_MASK<<3)
    #define Clk_APBD_TC5                       (Clk_AHB_MASK<<2)
    #define Clk_APBD_SERCOM7                   (Clk_AHB_MASK<<1)
    #define Clk_APBD_SERCOM6                   (Clk_AHB_MASK<<0)

    #define SYNCBUSYBIT_SHIFT                                 2U
    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    typedef struct 
    {
        uint8_t u8Enable48MInternalOsc;
        uint8_t u8EnableHSCrystalOsc;                      
        uint8_t u8EnableFDPLL;              
        uint8_t u8EnableLSCrystalOsc;
        uint8_t u8Enable32KHighAccuacyInternalOsc;           
        uint8_t u8EnableOSCClkFault;
        uint8_t u8SetOSCClkFaultPresc;
        uint8_t u8EnableOsc;
        uint16_t u16FDPLLSrc;
        uint16_t u16FDPLL_LDR;
        uint8_t  u8FDPLL_LDRFrac;
        uint8_t  u8FDPLL_LDRPresc;
        uint8_t  u8FDPLL_RefClk;
        uint32_t u32EnableAHBClk;
        uint32_t u32EnableAPBAClk;
        uint32_t u32EnableAPBBClk;
        uint32_t u32EnableAPBCClk;
        uint32_t u32EnableAPBDClk;
    }SystemClock_InitTypeDef;
    
    typedef struct
    {
        uint16_t u16EnableNumGCLK;
        uint16_t u16GCLKDIV;
        uint16_t u16GCLKSrcSelect;
    }SystemClock_GCLKTypeDef;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */
uint8_t Clock_OSCCtrl_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting);
uint8_t Clock_OSC32KCtrl_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting);
uint8_t Clock_FDPLL_Initialize(SystemClock_InitTypeDef *CurrentSystemClockSetting);
uint8_t Clock_GCLKN_Initialize(SystemClock_GCLKTypeDef *CurrentGCLKSetting);
uint8_t Clock_AHBClock_Enable(SystemClock_InitTypeDef *CurrentSystemClockSetting);
uint8_t Clock_GCLKToPeri(uint16_t u16PeripheralNum,uint16_t u16GCLKGENValue);
uint8_t Clock_DisableHSCOsc(void);
    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* CLOCK_H */

/* *****************************************************************************
 End of File
 */
