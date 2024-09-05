/* ************************************************************************** 
;        Program    :   FlashLogApp.c
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
#include "app/inc/EepRomM.h"

#if (EEP_CLASS_EN == ENABLE_ON)
#include "app/inc/I2cMasterApp.h"
#include "app/inc/FunApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t EepI2cTxBuf[20U];
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
uint8_t EepRomM_Read(uint32_t addr,uint32_t len,uint8_t* buf)
{
    uint8_t ret = TRUE;
    uint8_t u8I2cAddr;
    uint8_t u8Offset;
    if((addr + len) <= EEP_SIZE)
    {
        u8I2cAddr = GET_EEP_ADDR(addr);
        u8Offset = addr & 0xFFU;
        I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,u8I2cAddr);
        EepI2cTxBuf[0] = u8Offset;
        ret &= I2cMasterApp_Rx(I2C_MASTER_SERCOM_2, EepI2cTxBuf, 1U, buf, len);
    }
    return ret;

}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t EepRomM_Write(uint32_t addr,uint32_t len,uint8_t* buf)
{
    uint8_t ret = TRUE;
    uint8_t u8I2cAddr;
    uint8_t u8Offset;
    if((addr + len) <= EEP_SIZE)
    {
        u8I2cAddr = GET_EEP_ADDR(addr);
        u8Offset = addr & 0xFFU;
        I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,u8I2cAddr);

        uint32_t u32FinishedLen = 0U;
        while (u32FinishedLen < len)
        {
            uint32_t u32WriteLen;
            if ((len - u32FinishedLen) >= EEP_PAGE_SIZE)
            {
                u32WriteLen = EEP_PAGE_SIZE;
            }
            else
            {
                u32WriteLen = (len - u32FinishedLen);
            }
            
            EepI2cTxBuf[0] = u8Offset;
            (void)memcpy((EepI2cTxBuf + 1u), (buf + u32FinishedLen),u32WriteLen);
            ret &= I2cMasterApp_Tx(I2C_MASTER_SERCOM_2, EepI2cTxBuf, (u32WriteLen + 1U));
            (void)FunApp_Delay_Millisecond(5U, MODE_SYSTICK);

            if(ret != TRUE)
            {
                break;
            }
            else
            {
                u8Offset += u32WriteLen;
                u32FinishedLen += u32WriteLen;
            }
        }
        
        
    }
    
    return ret;
}

#endif
