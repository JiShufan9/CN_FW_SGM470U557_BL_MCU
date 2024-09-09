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
#include "app/NodesInterface/TconUpdate.h"
#if (TCON_UPDATE_CLASS_EN == ENABLE_ON)

#include    "app/inc/I2cMasterApp.h"
#include    "app/inc/TconM.h"
#include    "app/inc/FunApp.h"
#include "app/inc/CrcApp.h"
#include "app/NodesInterface/NodeUpdate.h"
/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t TconUpdate_u8WriteBuffer[TCON_WRITE_BUF_LEN];
uint8_t u8WriteBufLen;

uint8_t TconUpdate_u8ReadBackBuffer[TCON_READ_BACK_BUF_LEN];
uint8_t TconUpdate_BinCrc[TCON_FW_START_ADDR];

static uint32_t u32TconLocalCrc = INIT_CRC32;
/* ************************************************************************** */
/* Section: Static Functions Declaration                                      */
/* ************************************************************************** */
void TconUpdate_ParamInit(void)
{
    u32TconLocalCrc = INIT_CRC32;
}

/* ************************************************************************** */
/* Section: Functions Definition                                              */
/* ************************************************************************** */
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t TconUpdate_EarseFunc(void)
{
    uint8_t ret;
    uint8_t isSuccess = TRUE;
    isSuccess &= TconM_SetIcAccessKey(); //AN Step 2: Set TCON IC register ICSET_ACCESS_KEY enable.
#if 0
    isSuccess &= TconM_WriteByte(0x01, 0x70, 0xA5); //AN Step 3: Set TCON IC register
    isSuccess &= TconM_WriteByte(0x01, 0x8C, 0x03); //AN Step 4: Set TCON IC register
#else
    isSuccess &= TconM_SetMagic();
#endif
    isSuccess &= TconM_WriteByte(0x03, 0x05, 0xBB); //AN Step 5: Use CMD to enter Bypass Mode Via Transform Circuit

    isSuccess &= TconM_ReleasePowerDown(); //AN Step 7-1: Set Flash release from Power Down
    isSuccess &= TconM_WriteEnable(); //AN Step 7-2: Set Write Enable
    isSuccess &= TconM_CheckStatus(0x02, 0x02); //AN Step 7-2: Check Status Register
    isSuccess &= TconM_WriteStatus(0x00); //AN Step 7-3: Set "BP" bits and "SRP" bit of Status Register as non-protected.
    isSuccess &= TconM_CheckStatus(0xFF, 0x00); //AN Step 7-4

#if (TCON_UPDATE_ERASE_WHEN_WRITE_EN != ENABLE_ON)
    isSuccess &= TconM_WriteEnable(); //AN Step 7-5
    isSuccess &= TconM_CheckStatus(0x02, 0x02); //AN Step 7-5
    isSuccess &= TconM_ChipErase(); //AN Step 7-6
    isSuccess &= TconM_CheckStatus(0xFF, 0x00); // check if busy    AN Step 7-7
#endif

    ret = OP_SUCCESS;
    return ret;
}
#if (TCON_UPDATE_ERASE_WHEN_WRITE_EN == ENABLE_ON)
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t TconUpdate_CheckEarseBlock(uint32_t addr,uint32_t len)
{
    uint8_t ret;
    if ((addr % TCON_EXT_FLS_BLOCK_SIZE) != 0U)
    {
        ret = OP_SUCCESS;
    }
    else if(TconM_SectorErase(addr) != TRUE)
    {
        ret = OP_ERR;
    }
    else if(TRUE != TconM_CheckStatus(0xFF, 0x00))
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

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t TconUpdate_Program(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = TRUE;

    if(addr == 0U)
    {
        TconUpdate_BinCrc[0] = *(buf + 0);
        TconUpdate_BinCrc[1] = *(buf + 1);
        ret &= TconM_Program((buf + TCON_FW_START_ADDR), (addr + TCON_FW_START_ADDR), (len - TCON_FW_START_ADDR));
    }
    else
    {
        ret &= TconM_Program(buf, addr, len);
    }

    return ret;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t TconUpdate_ProgramCrc(uint32_t addr,uint32_t len)
{
    uint8_t ret = TRUE;

    if((addr + len) == SIZE_TCON_FW)
    {
        ret &= TconM_Program(TconUpdate_BinCrc, 0U, TCON_FW_START_ADDR);
    }

    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
static uint8_t TconUpdate_ReadBackCheck(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = TRUE;
    uint32_t u32ReadAddr;
    uint32_t u32ReadLen;
    uint32_t u32Offset;

    if(addr == 0x0U)
    {
        u32ReadAddr = TCON_FW_START_ADDR;
        u32ReadLen = len - TCON_FW_START_ADDR;
        u32Offset = TCON_FW_START_ADDR;
    }
    else
    {
        u32ReadAddr = addr;
        u32ReadLen = len;
        u32Offset = 0U;
    }

    (void)memset(TconUpdate_u8ReadBackBuffer,0U,TCON_READ_BACK_BUF_LEN);

    ret &= TconM_Read(u32ReadAddr, u32ReadLen, TconUpdate_u8ReadBackBuffer);

    if (memcmp((buf + u32Offset),TconUpdate_u8ReadBackBuffer,u32ReadLen) != 0)
    { 
        ret &= FALSE;
    }



    return ret;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t TconUpdate_UpdateFunc(uint32_t addr,uint32_t len,uint8_t * buf)
{
    uint8_t ret = OP_ERR;

    if((addr + len) <= SIZE_TCON_FW)
    {
#if (TCON_UPDATE_ERASE_WHEN_WRITE_EN == ENABLE_ON)
        if (OP_SUCCESS != TconUpdate_CheckEarseBlock(addr,len))
        {
            /* code */
            ret = OP_ERR;
        }
        else if(TRUE != TconUpdate_Program( addr, len,buf))
#else
        if (TRUE != TconUpdate_Program(addr, len, buf))
#endif
        {
            ret = OP_ERR;
        }
#if (TCON_UPDATE_READ_BACK_CHECK_EN == ENABLE_ON)
        else if (TRUE != TconUpdate_ReadBackCheck(addr, len, buf))
        {
            ret = OP_ERR;
        }
#endif
        else if(TRUE != TconUpdate_ProgramCrc(addr, len))
        {
            ret = OP_ERR;
        }
        else
        {
            u32TconLocalCrc = CrcApp_Crc32_Calculation(buf, len, u32TconLocalCrc);
			if((addr + len) == SIZE_TCON_FW)
            {
                u32TconLocalCrc = (~u32TconLocalCrc);
                if(u32TconLocalCrc != NodeUpdate_GetBlockCrc(NODE_ID_TCON))
                {
                    ret = OP_ERR;
                }
                else
                {
                    ret = OP_SUCCESS;
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
uint8_t TconUpdate_CheckFunc(uint32_t u32HostCrc)
{
    uint8_t ret;
    uint8_t isSuccess = TRUE;
#if (TCON_UPDATE_ERASE_WHEN_WRITE_EN != ENABLE_ON)
    // int startAddr2 = 0x00, size2 = 0x02;
    // isSuccess &= TconM_Program(binContent, startAddr2, size2); //AN Step 7-12~7-14
#endif

    isSuccess &= TconM_WriteEnable(); //AN Step 7-15
    isSuccess &= TconM_CheckStatus(0x02, 0x02); //AN Step 7-15

    isSuccess &= TconM_WriteStatus(0x9C); //AN Step 7-16: Set "BP" bits and "SRP" bit of Status Register as protected
    isSuccess &= TconM_CheckStatus(0xFF, 0x9C); //AN Step 7-17 

#if (TCON_UPDATE_ERASE_WHEN_WRITE_EN != ENABLE_ON)
    // isSuccess &= TconM_Read(startAddr2, size2, out byte[] readBuffer2); //AN Step 7-18
    // bool isCompareSuccess2 = binContent.SequenceEqual(readBuffer2);
#endif


    isSuccess &= TconM_PowerDown(); //AN Step 7-19: Set Flash into Power Down
    isSuccess &= TconM_WriteByte(0x03, 0x05, 0x00); //AN Step 9: Set TCON IC register 0x0305 = 00h (CMDSYS_SW[7:0]=00h)
	isSuccess &= TconM_WriteByte(0x01, 0x8C, 0x00); //AN Step 10: Set TCON IC register
    isSuccess &= TconM_WriteByte(0x01, 0x70, 0x00); //AN Step 11: Set TCON IC register
	
	isSuccess &= TconM_WriteByte(0xEF, 0x01, 0x00); //AN Step 12: Disable ICSET_ACCESS_KEY
    isSuccess &= TconM_WriteByte(0xEF, 0x02, 0x00); 

    ret = OP_SUCCESS;
    return ret;
}

#endif
