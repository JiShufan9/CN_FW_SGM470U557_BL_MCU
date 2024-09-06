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
#include "app/NodesInterface/NodeUpdate.h"

#if (NODE_UPDATE_CLASS_EN == ENABLE_ON)
#include "McuUpdate.h"
#include "SourceIcExtFlashUpdate.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */

TsNode sUpdateNodeArr[] = { 
    {
        NODE_ID_MCU,
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        McuUpdate_EarseFunc,
        McuUpdate_UpdateFunc,
        McuUpdate_CheckFunc
    },
    {
        NODE_ID_SOURCE_IC,
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        0x00u,
        SourceIcExtFlashUpdate_EarseFunc,
        SourceIcExtFlashUpdate_UpdateFunc,
        SourceIcExtFlashUpdate_CheckFunc
    }
};


TsHeadInfo sHeadInfo;
uint8_t u32ValidBlockNum;
uint8_t u8HeadInfoGetFinished;

uint8_t u8FixedHeadInfoGetFinished;

uint16_t u16BlockIdTotalLen;
uint16_t u16ValidBlockIdTotalLen;
uint16_t u16ReceivedBlockIdLen;

uint16_t u16BlockPosInfoStartAddr;
uint16_t u16BlockPosInfoTotalLen;
uint16_t u16ValidBlockPosInfoTotalLen;
uint16_t u16ReceivedBlockPosInfoLen;

uint16_t u16BlockDataStartAddr;
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
uint8_t NodeUpdate_EarseFunc(void)
{
    uint8_t ret = UPDATE_STS_FAIL;
    uint8_t u8Temp;
    uint8_t count = sizeof(sUpdateNodeArr)/sizeof(TsNode);
    for (uint8_t i = 0; i < count; i++)
    {
       u8Temp = (sUpdateNodeArr[i].pEarseFunc)();
       if(u8Temp == OP_SUCCESS)
       {
            ret |= 1u << i;
       }
    }

    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     return node index,0xFF means not found
                                   
********************************************************************************/
static uint8_t NodeUpdate_FindNodeById(uint16_t u16NodeId) 
{
    uint8_t ret = 0xFFU;
    uint8_t count = sizeof(sUpdateNodeArr)/sizeof(TsNode);

    for (uint8_t i = 0; i < count; i++)
    {
        if (u16NodeId == sUpdateNodeArr[i].u16NodeId)
        {
            ret = i;
            break;
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
static uint8_t NodeUpdate_GetBinPartData(uint8_t *des,uint16_t startAddr,uint16_t validLen,uint16_t * receivedLen,uint8_t * src,uint8_t frameAddr,uint32_t frameLen)
{
    uint8_t ret;
    uint32_t u32IteratorStart;
    uint32_t u32IteratorEnd;

    if(frameAddr < startAddr)
    {
        u32IteratorStart = startAddr;
    }
    else
    {
        u32IteratorStart = frameAddr;
    }

    if((startAddr + validLen) < (frameAddr + frameLen))
    {
        
        u32IteratorEnd = startAddr + validLen;
    }
    else
    {
        u32IteratorEnd = frameAddr + frameLen;
    }

    if(u32IteratorStart <= u32IteratorEnd)
    {
        (void)memcpy((des + (*receivedLen)),(src + u32IteratorStart - frameAddr),(u32IteratorEnd - u32IteratorStart));
        (*receivedLen) += (u32IteratorEnd - u32IteratorStart);
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t NodeUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = UPDATE_STS_SUCCESS;
    uint8_t u8Temp;
    
    if (FALSE == u8HeadInfoGetFinished)
    {
        /* get bin file head info */
        if(FALSE == u8FixedHeadInfoGetFinished)
        {
            (void)memcpy(&sHeadInfo,buf,BLOCK_ID_DATA_IDX);  /* FIRST FRAME DATA LEN MAST BIGGER THAN 34 */
            uint32_t u32BlockNum = (sHeadInfo.u8BlockNum[0] << 24) + (sHeadInfo.u8BlockNum[1] << 16) + (sHeadInfo.u8BlockNum[2] << 8) + (sHeadInfo.u8BlockNum[3]);  /* MSB first */
            u16BlockIdTotalLen = u32BlockNum * BLOCK_ID_LEN;
            u16BlockPosInfoStartAddr = BLOCK_ID_DATA_IDX + u16BlockIdTotalLen;
            u16BlockPosInfoTotalLen = u32BlockNum * BLOCK_POS_INFO_LEN;
            u16BlockDataStartAddr = u16BlockPosInfoStartAddr + u16BlockPosInfoTotalLen + BLOCK_HEAD_END_FLAG_LEN;

            if (u32BlockNum > NODE_UPDATE_MAX_BLOCK_NUM)
            {
                u32ValidBlockNum = NODE_UPDATE_MAX_BLOCK_NUM;
            }
            else
            {
                u32ValidBlockNum = u32BlockNum;
            }
                
            
            u16ValidBlockIdTotalLen = u32ValidBlockNum * BLOCK_ID_LEN;
            u16ValidBlockPosInfoTotalLen = u32ValidBlockNum * BLOCK_POS_INFO_LEN;
            
            u8FixedHeadInfoGetFinished = TRUE;
        }
        
        if(u16ReceivedBlockIdLen < u16ValidBlockIdTotalLen)
        {
            NodeUpdate_GetBinPartData(sHeadInfo.u8BlockIdentify,BLOCK_ID_DATA_IDX,u16ValidBlockIdTotalLen, &u16ReceivedBlockIdLen,buf,addr,len);
        }
        
        if(u16ReceivedBlockPosInfoLen != u16ValidBlockPosInfoTotalLen)
        {
            NodeUpdate_GetBinPartData(sHeadInfo.u8BlockPosInfo, u16BlockPosInfoStartAddr, u16ValidBlockPosInfoTotalLen, &u16ReceivedBlockPosInfoLen,buf, addr, len);
        }
        
        if(u16ReceivedBlockPosInfoLen == u16ValidBlockPosInfoTotalLen)
        {
            uint8_t u8NodeIdx;
            for (uint8_t i = 0; i < u32ValidBlockNum; i++)
            {
                uint8_t u8Offset;
                uint16_t u16NodeId;
                u8Offset = i * BLOCK_ID_LEN;
                u16NodeId = (sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_NODE_ID_IDX] << 8) +\
                            sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_NODE_ID_IDX + 1U];
                u8NodeIdx = NodeUpdate_FindNodeById(u16NodeId);
                if (u8NodeIdx != 0xFFu)
                {
                    sUpdateNodeArr[u8NodeIdx].u8NodeUpdateFlag = sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_UPDATE_FLAG_IDX];//todo 策略待完善
                    sUpdateNodeArr[u8NodeIdx].u32PartationCrc = (sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_PART_CRC_IDX] << 24) + \
                                                                (sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_PART_CRC_IDX + 1U] << 16) +\
                                                                (sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_PART_CRC_IDX + 2u] << 8) +\
                                                                sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_PART_CRC_IDX + 3U];
                    sUpdateNodeArr[u8NodeIdx].u16NodeVersion =  (sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_VERSION_IDX] << 8) +\
                                                                    sHeadInfo.u8BlockIdentify[u8Offset + BLOCK_ID_VERSION_IDX + 1U];
                    uint16_t u16PosInfoOffset= i * BLOCK_POS_INFO_LEN;
                    sUpdateNodeArr[u8NodeIdx].PartationStartAddr = (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 0] << 24) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 1] << 16) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 2] << 8) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 3]);
                    sUpdateNodeArr[u8NodeIdx].PartationLen = (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 4] << 24) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 5] << 16) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 6] << 8) + (sHeadInfo.u8BlockPosInfo[u16PosInfoOffset + 7]);
                }
            }
            
            u8HeadInfoGetFinished = TRUE;
        }
    }
    

    if(TRUE == u8HeadInfoGetFinished)
    {
        uint32_t u32WriteAddr,u32WriteLen;

        u32WriteAddr = addr;
        u32WriteLen = len;
        
        uint8_t count = sizeof(sUpdateNodeArr)/sizeof(TsNode);
        for (uint8_t i = 0; i < count; i++)
        {
            if(/* (sUpdateNodeArr[u8NodeIdx].u8NodeUpdateFlag) && */(u32WriteLen > 0U) && (u32WriteAddr >= sUpdateNodeArr[i].PartationStartAddr) && ((u32WriteAddr + u32WriteLen) <= (sUpdateNodeArr[i].PartationStartAddr + sUpdateNodeArr[i].PartationLen)))
            {
                u8Temp = (sUpdateNodeArr[i].pUpdateFunc)((u32WriteAddr - sUpdateNodeArr[i].PartationStartAddr), u32WriteLen ,(buf + len - u32WriteLen));
                if(u8Temp != OP_SUCCESS)
                {
                    ret &= ~(1u << i); /* if op fail, clear flag bit */
                }
                break;
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
uint8_t NodeUpdate_CheckFunc(uint32_t u32HostCrc)  //todo  individual crc
{
    uint8_t ret = UPDATE_STS_FAIL;
    uint8_t u8Temp;
    uint8_t count = sizeof(sUpdateNodeArr)/sizeof(TsNode);
    for (uint8_t i = 0; i < count; i++)
    {
       u8Temp = (sUpdateNodeArr[i].pCheckFunc)(u32HostCrc);
       if(u8Temp == OP_SUCCESS)
       {
            ret |= 1u << i;
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
uint32_t NodeUpdate_GetBlockCrc(uint16_t NodeId)
{
    uint32_t u32BlockCrc = 0u;
    uint8_t u8NodeIdx;

    u8NodeIdx = NodeUpdate_FindNodeById(NodeId);
    if (u8NodeIdx != 0xFFu)
    {
        u32BlockCrc = sUpdateNodeArr[u8NodeIdx].u32PartationCrc;
    }
    return u32BlockCrc;
}
#endif
