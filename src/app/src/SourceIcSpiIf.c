/* ************************************************************************** 
;        Program    :   .c
;        Function   :   
;        chip       :   
;        clock      :   
;        Date       :   2024 / 05 / 29
;        Author     :   chenaoli
;        Description:     
;    
 *****************************************************************************/

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app/inc/SourceIcSpiIf.h"
#if (SOURCE_IC_SPI_CLASS_EN == ENABLE)

#include "hal/inc/plib_sercom6_spi_master.h"
#include "app/inc/PinIOApp.h"
#include <string.h>
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t SourceIcSpiIf_Dummy = 0u;

/* ************************************************************************** */
/* Section: Static Functions Declaration                                      */
/* ************************************************************************** */
#if (SPI_INTERRUPT_MODE == ENABLE_ON) 
void SourceIcSpiIf_Com6IntCallback(uintptr_t context);
#endif
/* ************************************************************************** */
/* Section: Functions Definition                                              */
/* ************************************************************************** */
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
void SourceIcSpiIf_Init(void)
{
    SERCOM6_SPI_Initialize();
#if (SPI_INTERRUPT_MODE == ENABLE_ON)  /* use interrupt mode */
    SERCOM6_SPI_CallbackRegister(&SourceIcSpiIf_Com6IntCallback, (uintptr_t)NULL );
    NVIC_SetPriority(SERCOM6_IRQn,3U);
    NVIC_EnableIRQ(SERCOM6_IRQn);
#endif
    (void)PinIOApp_High(PORT_C,BIT9);
    SourceIcSpiIf_Dummy = 1u;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#if 0
void SourceIcSpiIf_MainFunction(void)
{
    
    
}
#endif

#if (SPI_INTERRUPT_MODE == ENABLE_ON)
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
// LDRA_EXCLUDE_START 35 S
static void SourceIcSpiIf_Com6IntCallback(uintptr_t context)
{
    SourceIcSpiIf_Dummy = 1u;
    (void)PinIOApp_High(PORT_C,BIT9);
    (void)context;
}
// LDRA_EXCLUDE_END 35 S
#endif
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcSpiIf_retry_delay(void) {
    uint32_t delay = 50U;
    while(delay > 0U)
    {
        delay--;
    }
    return TRUE;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
// LDRA_EXCLUDE_START 139 S
uint8_t SourceIcSpiIf_SpiWriteRead(const uint8_t *write_buf, uint8_t write_size, uint8_t *read_buf,uint8_t read_size) 
{
    uint8_t result = TRUE;
    uint32_t retry_times;
    bool bTemp;
    uint8_t u8TempRxBuf[70U] = {0U}; /* max len is 70 */

    (void)PinIOApp_Low(PORT_C,BIT9);
    (void)SourceIcSpiIf_retry_delay();
    (void)SERCOM6_SPI_WriteRead ((void *)write_buf, write_size, u8TempRxBuf, ((size_t)write_size + (size_t)read_size));

    retry_times = 0xFFFFFFFFu;
    bTemp = SERCOM6_SPI_IsBusy();
    while (true == bTemp) 
    {
#if (SPI_INTERRUPT_MODE != ENABLE_ON)
        if(false == SERCOM6_SPI_IsTransmitterBusy())
        {
            SERCOM6_SPI_InterruptHandler(); /*  */
        }
#endif
        
        if (retry_times == 0U) 
        {
            result = FALSE;
            break;
        }
        else 
        {
            retry_times --;
        }
        bTemp = SERCOM6_SPI_IsBusy();
    }

    if (result != TRUE)
    {
        (void)SourceIcSpiIf_retry_delay();
        (void)PinIOApp_High(PORT_C,BIT9);
    }
    else
    {
#if (SPI_INTERRUPT_MODE != ENABLE_ON)
        (void)SourceIcSpiIf_retry_delay();
        (void)PinIOApp_High(PORT_C,BIT9);
#endif
        (void)memcpy(read_buf,&u8TempRxBuf[write_size],read_size);
    }

    return result;
}
// LDRA_EXCLUDE_END 139 S


#if 0
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcSpiIf_BypassOp(uint8_t txBuf[],uint8_t u8TxLen,uint8_t rxBuf[],uint8_t u8RxLen)
{
    uint8_t ret;

    ret = SourceIcSpiIf_SpiWriteRead(txBuf, u8TxLen, rxBuf, u8RxLen);
    if(ret == FALSE)
    {
        /* nothing */
    }
    else
    {
        /* nothing */
    }


    return ret;
}
#endif

#endif
