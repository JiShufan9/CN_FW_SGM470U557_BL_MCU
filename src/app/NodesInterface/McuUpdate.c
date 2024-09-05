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
#include "app/NodesInterface/McuUpdate.h"

#if (MCU_UPDATE_CLASS_EN == ENABLE_ON)
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/FlashRwApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Static Functions Declaration                                      */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Functions Definition                                              */
/* ************************************************************************** */
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t McuUpdate_EarseFunc(void)
{
    uint8_t ret;
    uint32_t u32Index;

    for(u32Index=0U; u32Index< LEN_ERASE; u32Index++)
    {
        (void)FlashRwApp_256B_Erase((uint32_t)(ADDR_APP_START), u32Index);  /* Erase APP code size */
    }
    
    (void)FunApp_Delay_Millisecond(50U, MODE_SYSTICK);                 /* Delaly 500ms, waiting for the MCU erase finish */

    ret = OP_SUCCESS;
    return ret;
    
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t McuUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret;
    if((addr + len) <= SIZE_APP_BASE)
    {
        FlashRwApp_64B_Page_Write((addr + ADDR_APP_START), buf);
    }

    (void)len;
    ret = OP_SUCCESS;
    return ret;
    
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t McuUpdate_CheckFunc(uint32_t u32HostCrc)
{
    uint8_t ret;

    ret = OP_SUCCESS;
    return ret;
}

#endif
