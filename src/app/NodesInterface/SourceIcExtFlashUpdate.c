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

#include "app/sfud/inc/sfud.h"
#include "app/fal/inc/fal.h"
#include "app/inc/SourceIcM.h"
#include "app/inc/CrcApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
const struct fal_partition * psSourceIcConfPart = NULL;

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
    uint8_t ret;
    
    // if(SourceIcM_EnterExtFlsBypassMode(SOURCE_IC_IDX_MASTER) == OP_SUCCESS)
    // { 
    

        
        (void)SourceIcM_EnterExtFlsBypassMode(SOURCE_IC_IDX_MASTER);
        (void)sfud_init();
        (void)fal_init();
        psSourceIcConfPart = fal_partition_find(SOURCE_IC_FLS_PART_NAME);
        if(psSourceIcConfPart != NULL)
        {
            ret = OP_SUCCESS;
        }
        else
        {
             ret = OP_ERR;
             __NOP();
             __NOP();
        }
            
    // }
    // else
    // {
    //     ret = OP_ERR;
    //     __NOP();
    //     __NOP();
    // }

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
    if ((addr % SOURCE_IC_EXT_FLS_BLOCK_SIZE) != 0U)
    {
        ret = OP_SUCCESS;
    }
    else if(fal_partition_erase(psSourceIcConfPart, addr, len) < 0)
    {
        __NOP();
        ret = OP_ERR;
    }
    else
    {
        ret = OP_SUCCESS;
    }
    
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
    uint8_t ret = OP_ERR;

    if((addr + len) <= SIZE_SOURCE_IC_FW)
    {
        (void)memset(u8ReadBackBuf,0U,SRC_EXT_FLS_READ_BACK_BUF_LEN);

        if (SourceIcExtFlashUpdate_CheckEarseBlock(addr,len) != OP_SUCCESS)
        {
            __NOP();
            ret = OP_ERR;
        }
        else if(fal_partition_write(psSourceIcConfPart, addr,  buf,  len) < 0)
        {
            __NOP();
            ret = OP_ERR;
        }
#if (SRC_IC_UPDATE_READ_BACK_CHECK_FUNC == ENABLE_ON)
        else if(fal_partition_read(psSourceIcConfPart, addr,  u8ReadBackBuf,  len) < 0)
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
