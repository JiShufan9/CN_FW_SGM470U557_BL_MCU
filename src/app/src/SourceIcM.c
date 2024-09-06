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
#include "app/inc/SourceIcM.h"
#if (SOURCE_IC_M_CLASS_EN == ENABLE)

#include "app/inc/I2cMasterApp.h"
#include "app/inc/FunApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t SourceIcTxBuf[10];
uint8_t SourceIcRxBuf[10];

/* ************************************************************************** */
/* Section: Static Functions Declaration                                      */
/* ************************************************************************** */
//static uint8_t SourceIcM_ReadDtc(uint8_t result[]);
/* ************************************************************************** */
/* Section: Functions Definition                                              */
/* ************************************************************************** */
#if 0 
void SourceIcM_MainFunction(void)
{
//    uint8_t buf[12] = {0};
    // SourceIcM_ReadDtc(buf);
    
}
#endif


/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcM_PageSelect(uint8_t u8PageCmd)
{
    uint8_t ret = TRUE;
    I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,ADDR_SOURCE_IC);
    SourceIcTxBuf[0] = 0x1EU;
    SourceIcTxBuf[1] = u8PageCmd;
    ret &= I2cMasterApp_Tx(I2C_MASTER_SERCOM_2, SourceIcTxBuf, 2U);
    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#if 0
uint8_t SourceIcM_ReadICVersion(uint8_t idx,uint8_t result)
{
    uint8_t ret;


    return ret;
}
#endif
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :    Read System Version And Display Initial CodeVersion
                                   
********************************************************************************/
#if 1
uint8_t SourceIcM_ReadVersionInfo(uint8_t *result)
{
    uint8_t ret;
    if(TRUE != SourceIcM_PageSelect(CMD1_PZ)) 
    {
        ret = FALSE;
    }
    else
    {
        I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,ADDR_SOURCE_IC);
        SourceIcTxBuf[0] = 0x01U;
        ret = I2cMasterApp_Rx(I2C_MASTER_SERCOM_2, SourceIcTxBuf, 1U,result,1U);
    }

    return ret;
}
#endif
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#if 0
uint8_t SourceIcM_ReadDtc(uint8_t idx,uint8_t *result)
{
    uint8_t ret;

    return ret;
}
#endif

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#if 1
uint8_t SourceIcM_ReadFlashCrcInd(uint8_t *result)
{
    uint8_t ret;

    if(TRUE != SourceIcM_PageSelect(CMD2_P2))
    {
        ret = FALSE;
    }
    else
    {
        I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,ADDR_SOURCE_IC);
        SourceIcTxBuf[0] = 0x1CU;
        ret = I2cMasterApp_Rx(I2C_MASTER_SERCOM_2, SourceIcTxBuf, 1U,result,1U);
        if(TRUE == ret)
        {
            (*result) = ( (*result) & 0x02U) >> 1U; /* ER_C01 EEPROM Checksum/CRC Error Indicator bit */
        }
    }

    return ret;
}
#endif
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcM_EnterExtFlsBypassMode(void)
{
    uint8_t ret = TRUE;
    if(TRUE != SourceIcM_PageSelect(CMD2_P0))
    {
        ret = FALSE;
    }
    else
    {
        I2cMasterApp_SetDesI2cAddr(I2C_MASTER_SERCOM_2,ADDR_SOURCE_IC);
        SourceIcTxBuf[0] = 0x01U;
        SourceIcTxBuf[1] = 0x92U;
        ret = I2cMasterApp_Tx(I2C_MASTER_SERCOM_2, SourceIcTxBuf, 2U);
    }

    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcM_ExitExtFlsBypassMode(void)
{
    uint8_t ret;
    if(TRUE != SourceIcM_PageSelect(CMD2_P0))
    {
        ret = FALSE;
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}

#endif
