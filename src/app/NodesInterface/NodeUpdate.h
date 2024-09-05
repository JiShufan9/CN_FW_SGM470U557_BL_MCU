/* ************************************************************************** 
;        Program    :   .h
;        Function   :   
;        chip       :   
;        clock      :   
;        Date       :   2024 / 05 / 29
;        Author     :   chenaoli
;        Description:      
;    
 *****************************************************************************/

#ifndef __NODE_UPDATE_H__
#define __NODE_UPDATE_H__

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "main.h"

#define NODE_UPDATE_CLASS_EN          ENABLE_ON
#if (NODE_UPDATE_CLASS_EN == ENABLE_ON)
/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define     NODE_ID_MCU                     0x01U
#define     NODE_ID_SOURCE_IC               0x02U


#define  UPDATE_STS_FAIL                    0x00U
#define  UPDATE_STS_MCU_MASK                0x01U
#define  UPDATE_STS_SOURCE_EXT_FLS_MASK     0x02U
#define  UPDATE_STS_SUCCESS                 (UPDATE_STS_MCU_MASK  | UPDATE_STS_SOURCE_EXT_FLS_MASK)

#define BLOCK_NUM_DATA_IDX  30U
#define BLOCK_ID_DATA_IDX  34U

#define BLOCK_ID_LEN    12u
#define BLOCK_POS_INFO_LEN  8U
#define BLOCK_HEAD_END_FLAG_LEN  4U
#define NODE_UPDATE_MAX_BLOCK_NUM  3U


#define BLOCK_ID_NODE_ID_IDX    11u    
#define BLOCK_ID_UPDATE_FLAG_IDX    1u
/* ************************************************************************** */
/* Section: Enum                                                              */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Struct Typedef                                                    */
/* ************************************************************************** */
typedef uint8_t (* TpEarseFunc)(void);
typedef uint8_t (* TpUpdateFunc)(uint32_t,uint32_t,uint8_t*);
typedef uint8_t (* TpCheckFunc)(uint32_t);

typedef struct
{
    const uint8_t u8NodeId;
    uint8_t u8NodeUpdateFlag;
    uint32_t PartationStartAddr;
    uint32_t PartationLen;
    TpEarseFunc pEarseFunc;
    TpUpdateFunc pUpdateFunc;
    TpCheckFunc pCheckFunc;
}TsNode;

typedef struct NodeUpdate
{
    uint8_t u8BinFileCheckSum[4];
    uint8_t u8BinFileLen[4];
    uint8_t u8PN[20];
    uint8_t u8Version[2];
    uint8_t u8BlockNum[4];
    uint8_t u8BlockIdentify[BLOCK_ID_LEN * NODE_UPDATE_MAX_BLOCK_NUM];
    uint8_t u8BlockPosInfo[BLOCK_POS_INFO_LEN * NODE_UPDATE_MAX_BLOCK_NUM];
}TsHeadInfo;
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */



/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
uint8_t NodeUpdate_EarseFunc(void);
uint8_t NodeUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf);

#endif
#endif
