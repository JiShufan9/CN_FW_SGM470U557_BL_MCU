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
#define     SourceIcExtFlashUpdate_Clipping(ClippingStartAddr,ClippingLen,OpSection1,OpSection2)\
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
        OpSection1(ClippingStartAddr,ClippingLen,OpSection1,OpSection2)\
    }\
    if((ClippingStartAddr + ClippingLen) < (startAddr + validLen))\
    {\
        uint32_t u32TempLen = (startAddr + validLen) - (ClippingStartAddr + ClippingLen);\
        OpSection2(ClippingStartAddr,ClippingLen,OpSection1,OpSection2)\
    }\
}

#define WriteDataOpSection1(ClippingStartAddr,ClippingLen,OpSection1,OpSection2) \
    do{\
        ret &= EepRomM_Write(startAddr, u32TempLen, buf);\
    }while(0);

#define WriteDataOpSection2(ClippingStartAddr,ClippingLen,OpSection1,OpSection2) \
    do{\
        ret &= EepRomM_Write((ClippingStartAddr + ClippingLen), u32TempLen,(buf + validLen - u32TempLen));\
    }while(0);

#define CmpDataOpSection1(ClippingStartAddr,ClippingLen,OpSection1,OpSection2) \
    do{\
        if(memcmp(buf1,buf2,u32TempLen) != 0)\
        {\
            ret &= FALSE;\
        }\
    }while(0);

#define CmpDataOpSection2(ClippingStartAddr,ClippingLen,OpSection1,OpSection2) \
    do{\
        if(memcmp((buf1 + validLen - u32TempLen ),(buf2 + validLen - u32TempLen) ,u32TempLen) != 0)\
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

    SourceIcExtFlashUpdate_Clipping(WPC_DATA_START_ADDR, WPC_DATA_LEN,WriteDataOpSection1,WriteDataOpSection2)
    else
    {
        SourceIcExtFlashUpdate_Clipping(WPC_CRC_START_ADDR, WPC_CRC_LEN,WriteDataOpSection1,WriteDataOpSection2)
        else
        {
#endif
            ret &= EepRomM_Write(addr,len,buf);
#if NOT_CHANGE_WPC_DATA_EN
        }
        
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

    SourceIcExtFlashUpdate_Clipping(WPC_DATA_START_ADDR, WPC_DATA_LEN, CmpDataOpSection1, CmpDataOpSection2)
    else
    {
        SourceIcExtFlashUpdate_Clipping(WPC_CRC_START_ADDR, WPC_CRC_LEN, CmpDataOpSection1, CmpDataOpSection2)
        else
        {
#endif
            if(memcmp(buf1,buf2,len) != 0)
            {
                ret &= FALSE;
            }
           
#if NOT_CHANGE_WPC_DATA_EN
        }
        
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
#define   GetBoundary(start,end) \
if((addr) < (start))\
{\
    u32TempAddr = (start); \
}\
else\
{\
    u32TempAddr = (addr);\
}\
if(((addr) + (len) - 1U) < (end))\
{\
    u32TempEnd = ((addr) + (len) - 1U);\
}\
else\
{\
    u32TempEnd = (end);\
}\


//static uint8_t SourceIcExtFlashUpdate_CrcCalculate(uint32_t addr,uint32_t len,uint8_t * buf)
//{
//    uint8_t ret = OP_SUCCESS;
////    uint32_t u32TempAddr;
////    uint32_t u32TempEnd;
//    
//    /* 3F7h Checksum / CRC _LUT (RT) R14Dh~R1CAh */
//    // GetBoundary(0x002U,0x146U);
//    // if(u32TempAddr <= u32TempEnd)
//    // {
//        
//    // }
//    
//    return ret;
//}
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
        else if(TRUE != SourceIcExtFlashUpdate_WirteData(addr,len,buf))
        {
            ret = OP_ERR;
        }
#if (SRC_IC_UPDATE_READ_BACK_CHECK_FUNC == ENABLE_ON)
        else if(TRUE != EepRomM_Read(addr,len,u8ReadBackBuf))
        {
            ret = OP_ERR;
        }
        else if(TRUE != SourceIcExtFlashUpdate_CmpData(buf,u8ReadBackBuf,addr,len))
        {
            ret = OP_ERR;
        }
#endif
        // else if(OP_SUCCESS != SourceIcExtFlashUpdate_CrcCalculate(addr,len,u8ReadBackBuf))
        // {
        //     ret = OP_ERR;
        // }
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
