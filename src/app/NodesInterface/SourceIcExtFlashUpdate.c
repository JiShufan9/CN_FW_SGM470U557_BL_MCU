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
#include "app/inc/FunApp.h"
#include "app/NodesInterface/NodeUpdate.h"
#include "app/inc/SourceIcSpiIf.h"

/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
const struct fal_partition * psSourceIcConfPart = NULL;

uint8_t u8ReadBackBuf[SRC_EXT_FLS_READ_BACK_BUF_LEN] = {0U};
uint8_t u8WPCDataBuf[WPC_DATA_LEN] = {0U};

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
    if(TRUE == SourceIcM_EnterExtFlsBypassMode(SOURCE_IC_IDX_MASTER))
    { 
        (void)FunApp_Delay_Millisecond(10U, MODE_SYSTICK);
        (void)sfud_init();
        (void)fal_init();
        psSourceIcConfPart = fal_partition_find(SOURCE_IC_FLS_PART_NAME);
        if(psSourceIcConfPart != NULL)
        {
#if NOT_CHANGE_WPC_DATA_EN
            if(fal_partition_read(psSourceIcConfPart, WPC_DATA_START_ADDR,  u8WPCDataBuf,  WPC_DATA_LEN) < 0)
            {
                ret = OP_ERR;
            }
            else
#endif
            {
                ret = OP_SUCCESS;
            }

        }
        else
        {
            ret = OP_ERR;
        }
            
    }
    else
    {
        ret = OP_ERR;
    }

    return ret;
}


/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#define     SourceIcExtFlashUpdate_Clipping(ClippingStartAddr,ClippingLen,OpSection1,OpSection2,OpSection3)\
if(ClippingStartAddr < startAddr)\
{\
    u32IteratorStart = startAddr;\
}\
else\
{\
    u32IteratorStart = ClippingStartAddr;\
}\
if((startAddr + validLen) < (ClippingStartAddr + ClippingLen))\
{\
    u32IteratorEnd = startAddr + validLen;\
}\
else\
{\
    u32IteratorEnd = ClippingStartAddr + ClippingLen;\
}\
if(u32IteratorStart <= u32IteratorEnd)\
{\
    if(startAddr < ClippingStartAddr)\
    {\
        uint32_t u32TempLen = (ClippingStartAddr - startAddr);\
        OpSection1(ClippingStartAddr,ClippingLen)\
    }\
    if((ClippingStartAddr + ClippingLen) < (startAddr + validLen))\
    {\
        uint32_t u32TempLen = (startAddr + validLen) - (ClippingStartAddr + ClippingLen);\
        OpSection2(ClippingStartAddr,ClippingLen)\
    }\
    OpSection3(ClippingStartAddr,ClippingLen)\
}


#define WriteDataOpSection1(ClippingStartAddr,ClippingLen) \
    do{\
		if(fal_partition_write(psSourceIcConfPart, startAddr,  buf,  u32TempLen) < 0)\
		{\
			ret &= FALSE;\
		}\
    }while(0);

#define WriteDataOpSection2(ClippingStartAddr,ClippingLen) \
    do{\
		if(fal_partition_write(psSourceIcConfPart, (ClippingStartAddr + ClippingLen),  (buf + validLen - u32TempLen),  u32TempLen) < 0)\
		{\
			ret &= FALSE;\
		}\
    }while(0);

#define WriteDataOpSection3(ClippingStartAddr,ClippingLen) \
    do{\
		if(fal_partition_write(psSourceIcConfPart, u32IteratorStart,  (u8WPCDataBuf + u32IteratorStart - WPC_DATA_START_ADDR), (u32IteratorEnd - u32IteratorStart)) < 0)\
		{\
			ret &= FALSE;\
		}\
    }while(0);

#define CmpDataOpSection1(ClippingStartAddr,ClippingLen) \
    do{\
        if(memcmp(buf1,buf2,u32TempLen) != 0)\
        {\
            ret &= FALSE;\
        }\
    }while(0);

#define CmpDataOpSection2(ClippingStartAddr,ClippingLen) \
    do{\
        if(memcmp((buf1 + validLen - u32TempLen ),(buf2 + validLen - u32TempLen) ,u32TempLen) != 0)\
        {\
            ret &= FALSE;\
        }\
    }while(0);

#define CmpDataOpSection3(ClippingStartAddr,ClippingLen) \
    do{\
        if(memcmp((u8WPCDataBuf + u32IteratorStart -  WPC_DATA_START_ADDR),(buf2 + u32IteratorStart - startAddr) ,(u32IteratorEnd - u32IteratorStart)) != 0)\
        {\
            ret &= FALSE;\
        }\
    }while(0);

static uint8_t SourceIcExtFlashUpdate_WirteData(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = TRUE;
#if NOT_CHANGE_WPC_DATA_EN
    /* do not change WPC data --- START */
    uint32_t u32IteratorStart;
    uint32_t u32IteratorEnd;
    uint32_t startAddr;
    uint32_t validLen;

    startAddr = addr;
    validLen = len;

    SourceIcExtFlashUpdate_Clipping(WPC_DATA_START_ADDR, WPC_DATA_LEN,WriteDataOpSection1,WriteDataOpSection2,WriteDataOpSection3)
    else
    {
#endif
        if(fal_partition_write(psSourceIcConfPart, addr,  buf,  len) < 0)
        {
            ret &= FALSE;
        }
#if NOT_CHANGE_WPC_DATA_EN
        
    }
#endif
    /* do not change WPC data --- END */
    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcExtFlashUpdate_CmpData(uint8_t* buf1,uint8_t * buf2, uint32_t addr ,uint32_t len)
{
    uint8_t ret = TRUE;
#if NOT_CHANGE_WPC_DATA_EN
    uint32_t u32IteratorStart;
    uint32_t u32IteratorEnd;
    uint32_t startAddr;
    uint32_t validLen;

    startAddr = addr;
    validLen = len;

    SourceIcExtFlashUpdate_Clipping(WPC_DATA_START_ADDR, WPC_DATA_LEN, CmpDataOpSection1, CmpDataOpSection2, CmpDataOpSection3)
    else
    {
#endif
            if(memcmp(buf1,buf2,len) != 0)
            {
                ret &= FALSE;
            }
           
#if NOT_CHANGE_WPC_DATA_EN
        
    }
#endif
    

    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
#if (SRC_IC_EARSE_TYPE == SECTOR_EARSE)
static uint8_t SourceIcExtFlashUpdate_CheckEarseBlock(uint32_t addr,uint32_t len)
{
    uint8_t ret;
    if ((addr % SOURCE_IC_EXT_FLS_BLOCK_SIZE) != 0U)
    {
        ret = OP_SUCCESS;
    }
#if NOT_CHANGE_WPC_DATA_EN
	else if((addr >= WPC_DATA_START_ADDR) && (addr <= (WPC_DATA_START_ADDR + WPC_DATA_LEN)))
	{
        ret = OP_SUCCESS;
    }
#endif
    else if(fal_partition_erase(psSourceIcConfPart, addr, SOURCE_IC_EXT_FLS_BLOCK_SIZE) < 0)
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
/* *****************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
****************************************************************************** */

static uint8_t SourceIcExtFlashUpdate_CheckEarseChip(uint32_t addr,uint32_t len)
{
    uint8_t ret;
    if (addr != 0U)
    {
        ret = OP_SUCCESS;
    }
    else if(fal_partition_erase(psSourceIcConfPart, 0U, 256U*1024U) < 0)
    {
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
    uint8_t ret = OP_SUCCESS;

    if((addr + len) <= SIZE_SOURCE_IC_FW)
    {
        (void)memset(u8ReadBackBuf,0U,SRC_EXT_FLS_READ_BACK_BUF_LEN);
#if (SRC_IC_EARSE_TYPE == SECTOR_EARSE)
        if (SourceIcExtFlashUpdate_CheckEarseBlock(addr,len) != OP_SUCCESS)
        {
            ret = OP_ERR;
        }
#else
        if (SourceIcExtFlashUpdate_CheckEarseChip(addr,len) != OP_SUCCESS)
        {
            ret = OP_ERR;
        }
#endif
        else if(TRUE != SourceIcExtFlashUpdate_WirteData(addr,len,buf))
        {
            ret = OP_ERR;
            __NOP();
        }
#if (SRC_IC_UPDATE_READ_BACK_CHECK_FUNC == ENABLE_ON)
        else if(fal_partition_read(psSourceIcConfPart, addr,  u8ReadBackBuf,  len) < 0)
        {
            ret = OP_ERR;
            __NOP();
        }
        else if(TRUE != SourceIcExtFlashUpdate_CmpData(buf,u8ReadBackBuf,addr,len))
        {
            ret = OP_ERR;
            __NOP();
        }
#endif
        else
        {
            u32LocalCrc = CrcApp_Crc32_Calculation(buf, len, u32LocalCrc);
            if((addr + len) == SIZE_SOURCE_IC_FW)
            {
                u32LocalCrc = (~u32LocalCrc);
                if(u32LocalCrc != NodeUpdate_GetBlockCrc(NODE_ID_SOURCE_IC))
                {
                    ret = OP_ERR;
                    __NOP();
                }
            }
            else
            {
                ret = OP_SUCCESS;
            }
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
