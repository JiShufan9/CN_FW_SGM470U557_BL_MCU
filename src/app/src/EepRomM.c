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
uint8_t EepRomM_WriteByte(uint8_t u8I2cAddr,uint8_t u8Offset,uint8_t data)
{
    uint8_t ret = TRUE;
    I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,u8I2cAddr);
    EepI2cTxBuf[0] = u8Offset;
    EepI2cTxBuf[1] = data;
    ret &= I2cMasterApp_Tx(I2C_MASTER_SERCOM_2, EepI2cTxBuf, 2U);
    (void)FunApp_Delay_Millisecond(5U, MODE_ISR);

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
            uint8_t unAlignLen = (u8Offset) - ((u8Offset / 16U) * 16u) ;
            if ((unAlignLen == 0U) && (len - u32FinishedLen) >= EEP_PAGE_SIZE)
            {
                u32WriteLen = EEP_PAGE_SIZE;
                EepI2cTxBuf[0] = u8Offset;
                (void)memcpy((EepI2cTxBuf + 1u), (buf + u32FinishedLen),u32WriteLen);
                ret &= I2cMasterApp_Tx(I2C_MASTER_SERCOM_2, EepI2cTxBuf, (u32WriteLen + 1U));
                (void)FunApp_Delay_Millisecond(5U, MODE_ISR);

                if(ret != TRUE)
                {
                    break;
                }
                else
                {
                    u8Offset += u32WriteLen;
                    u32FinishedLen += u32WriteLen;
                    u8I2cAddr = GET_EEP_ADDR(addr + u32FinishedLen);
                }
            }
            else
            {
                if((unAlignLen != 0U) && ((len - u32FinishedLen) >= (16u - unAlignLen)))
                {
                    u32WriteLen = 16u - unAlignLen;
                }
                else
                {
                    u32WriteLen = (len - u32FinishedLen);
                }
                
                for (uint32_t i = 0; i < u32WriteLen; i++)
                {
                    ret &= EepRomM_WriteByte(u8I2cAddr,u8Offset,*(buf + u32FinishedLen));
                    if(ret != TRUE)
                    {
                        break;
                    }
                    else
                    {
                        u8Offset += 1U;
                        u32FinishedLen += 1U;
                        u8I2cAddr = GET_EEP_ADDR(addr + u32FinishedLen);
                    }
                }
                
            }
        }
        
        
    }
    
    return ret;
}

#endif
