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
#include "app/NodesInterface/SourceIcExtFlashUpdate.h"
#if (SOURCE_IC_EXT_FLASH_UPDATE_CLASS_EN == ENABLE_ON)

#include "app/inc/SourceIcM.h"
#include "app/inc/EepRomM.h"
#include "app/inc/CrcApp.h"
#include "app/inc/FunApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t u8ReadBackBuf[SRC_EXT_FLS_READ_BACK_BUF_LEN] = {0U};

uint32_t u32LocalCrc = INIT_CRC32;
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
void SourceIcExtFlashUpdate_ParamInit(void)
{
    u32LocalCrc = INIT_CRC32;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcExtFlashUpdate_EarseFunc(void)
{
    uint8_t ret = OP_SUCCESS;
    ret &= SourceIcM_EnterExtFlsBypassMode();
    return ret;
}


/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcExtFlashUpdate_CheckEarseBlock(uint32_t addr,uint32_t len)
{
    uint8_t ret;
    
    ret = OP_SUCCESS;
    
    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcExtFlashUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = OP_SUCCESS;

    if((addr + len) <= SIZE_SOURCE_IC_FW)
    {
        (void)memset(u8ReadBackBuf,0U,SRC_EXT_FLS_READ_BACK_BUF_LEN);

        if (SourceIcExtFlashUpdate_CheckEarseBlock(addr,len) != OP_SUCCESS)
        {
            ret = OP_ERR;
        }
        else if(TRUE != EepRomM_Write(addr,len,buf))
        {
            __NOP();
            ret = OP_ERR;
        }
#if (SRC_IC_UPDATE_READ_BACK_CHECK_FUNC == ENABLE_ON)
        else if(TRUE != EepRomM_Read(addr,len,u8ReadBackBuf))
        {
            ret = OP_ERR;
        }
        else if(memcmp(buf,u8ReadBackBuf,len) != 0)
        {
            ret = OP_ERR;
        }
#endif
        else
        {
            u32LocalCrc = CrcApp_Crc32_Calculation(buf, len, u32LocalCrc);
            ret = OP_SUCCESS;
        }
    }
    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcExtFlashUpdate_CheckFunc(uint32_t u32HostCrc)
{
    uint8_t ret;
    if(u32LocalCrc == u32HostCrc)
    {
        ret = OP_ERR;
    }
    else
    {
        ret = OP_SUCCESS;
    }

    return ret;
}

#endif
