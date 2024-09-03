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

#include "app/inc/SourceIcSpiIf.h"
#include "app/inc/FunApp.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
TuSourceIcCmd SourceIcCmdArr[2] = {0U};

/* ************************************************************************** */
/* Section: Static Functions Declaration                                      */
/* ************************************************************************** */
static uint8_t SourceIcM_ProcessCmd(TuSourceIcCmd * cmd);
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
static uint8_t SourceIcM_ProcessCmd(TuSourceIcCmd * cmd)
{
    uint8_t ret = TRUE;
    uint8_t * pDes;
    uint8_t * pSrc;
    uint8_t u8TempReadBuf[32U] = {0};
    u8TempReadBuf[0] |= cmd -> _c[0];
    if(cmd -> _s.WRFlag == FLAG_W)
    {   
        if(cmd -> _s.u8DataLen <= (SOURCE_IC_CMD_BUF_MAX - 1u))
        {
            pDes = &u8TempReadBuf[1];
            pSrc = cmd -> _s.u8Buf;
            (void)memcpy(pDes,pSrc,cmd -> _s.u8DataLen);
        }
        else
        {
            pDes = &u8TempReadBuf[1];
            pSrc = cmd -> _s.u8Buf;
            (void)memcpy(pDes,pSrc, (SOURCE_IC_CMD_BUF_MAX - 1u));
        }
        ret = SourceIcSpiIf_SpiWriteRead(u8TempReadBuf, (((uint8_t)(cmd -> _s.u8DataLen)) + 1u), NULL, 0U);
    }
    else
    {
        if(cmd -> _s.u8DataLen <= (SOURCE_IC_CMD_BUF_MAX - 1u))
        {
            /* nothing */
        }
        else
        {
            cmd -> _s.u8DataLen = (SOURCE_IC_CMD_BUF_MAX - 1u);
        }
        ret = SourceIcSpiIf_SpiWriteRead(u8TempReadBuf, 1u, u8TempReadBuf, (uint8_t)(cmd -> _s.u8DataLen));
    }
    
   

    if((ret == TRUE) && (cmd -> _s.WRFlag == FLAG_R))
    {
        (void)memcpy(cmd -> _s.u8Buf,u8TempReadBuf,cmd -> _s.u8DataLen);
        __NOP();
        __NOP();
    }

    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static void SourceIcM_SetCmd(uint8_t CmdIdx,uint8_t idx,uint8_t addr,uint8_t WrFlag, uint8_t dataLen)
{
    SourceIcCmdArr[CmdIdx]._s.Addr = addr;
    SourceIcCmdArr[CmdIdx]._s.WRFlag = WrFlag;
    SourceIcCmdArr[CmdIdx]._s.u8DataLen = dataLen;
    (void)memset(SourceIcCmdArr[CmdIdx]._s.u8Buf, 0U, SOURCE_IC_CMD_BUF_MAX);
    if(idx == 0U)
    {
        SourceIcCmdArr[CmdIdx]._s.DesId = DESID_PRIMARY;
    }
    else
    {
        SourceIcCmdArr[CmdIdx]._s.DesId = DESID_SECONDARY;
    }
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcM_Write(uint8_t idx,uint8_t addr,uint8_t value)
{
    uint8_t ret;

    SourceIcM_SetCmd(1U, idx, addr, FLAG_W, 1u);
    SourceIcCmdArr[1]._s.u8Buf[0] = value;
    ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[1]);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    
    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
// LDRA_EXCLUDE_START 72 D
static uint8_t SourceIcM_WriteAndCheck(uint8_t idx,uint8_t addr,uint8_t value)
{
    uint8_t ret;

    SourceIcM_SetCmd(1U, idx, addr, FLAG_W, 1u);
    SourceIcCmdArr[1]._s.u8Buf[0] = value;
    ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[1]);
    if((ret == TRUE))
    {
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        SourceIcM_SetCmd(0U, idx, addr, FLAG_R, 1u);
        ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[0]);
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        if((ret == TRUE) && (SourceIcCmdArr[0]._s.u8Buf[0] != value))
        {
            ret = FALSE;
        }
    }
    
    return ret;
}
// LDRA_EXCLUDE_END 72 D

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t SourceIcM_PageSelect(uint8_t idx,uint8_t u8PageCmd)
{
    return SourceIcM_WriteAndCheck(idx,PAGE_SELECT_REG,u8PageCmd);
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
    ret = SourceIcM_PageSelect(idx,CMD1_Page0);
    if(ret == FALSE)
    {
        /* nothing */
    }
    else
    {
        SourceIcM_SetCmd(0U, idx, 0x00U, FLAG_R, 1u);
        ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[0]);
        if((ret == TRUE))
        {
            result = SourceIcCmdArr[0]._s.u8Buf[0];
        }
    }

    return ret;
}
#endif
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :    Read System Version And Display Initial CodeVersion
                                   
********************************************************************************/
#if 0
uint8_t SourceIcM_ReadVersionInfo(uint8_t idx,uint8_t *result)
{
    uint8_t ret;
    ret = SourceIcM_PageSelect(idx,CMD1_Page0);
    if(ret == FALSE)
    {
        /* nothing */
    }
    else
    {
        SourceIcM_SetCmd(0U, idx, 0x16U, FLAG_R, 3u);
        ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[0]);
        if((ret == TRUE))
        {
            UTIL_MEMCPY(result, SourceIcCmdArr[0]._s.u8Buf, 3u);
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
uint8_t SourceIcM_ReadDtc(uint8_t idx,uint8_t *result)
{
    uint8_t ret;
    ret = SourceIcM_PageSelect(idx,CMD2_PageB);
    if(ret == FALSE)
    {
        /* nothing */
    }
    else
    {
        SourceIcM_SetCmd(0U, idx, 0x00U, FLAG_R, 11u);

        ret = SourceIcM_ProcessCmd(&SourceIcCmdArr[0]);
        if((ret == TRUE))
        {
            (void)memcpy(result, SourceIcCmdArr[0]._s.u8Buf, 11u);
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
uint8_t SourceIcM_EnterExtFlsBypassMode(uint8_t idx)
{
    uint8_t ret = TRUE;
    if(TRUE != SourceIcM_PageSelect(idx,CMD2_Page0))
    {
        ret = FALSE;
    }
    else if(TRUE != SourceIcM_Write(idx,0x01U,0x96U)) /* FLASH control source selection */
    {
        ret = FALSE;
    }
    else
    {
        ret = TRUE;
    }

    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t SourceIcM_ExitExtFlsBypassMode(uint8_t idx)
{
    uint8_t ret;
    if(TRUE != SourceIcM_PageSelect(idx,CMD2_Page0))
    {
        ret = FALSE;
    }
    else if(TRUE != SourceIcM_Write(idx,0x01U,0x04U)) /* Global reset setting */
    {
        ret = FALSE;
    }
    else
    {
        ret = TRUE;
    }
    return ret;
}

#endif
