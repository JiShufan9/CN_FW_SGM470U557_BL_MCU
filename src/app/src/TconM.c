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
#include "app/inc/TconM.h"

#if (TCON_M_EN == ENABLE_ON)


/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app/inc/I2cMasterApp.h"
#include "app/inc/FunApp.h"

/* ************************************************************************** */
/* Section: Global Variable                                                   */
/* ************************************************************************** */
uint8_t TconM_u8TxBuf[70];
uint8_t TconM_u8RxBuf[70];
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
uint8_t TconM_WriteByte(uint8_t page, uint8_t address, uint8_t data)
{
    uint8_t result = TRUE;
    TconM_u8TxBuf[0] = page;
    TconM_u8TxBuf[1] = address;
    TconM_u8TxBuf[2] = data;

    if(true != I2cMasterApp_Tx(I2C_MASTER_SERCOM_4, TconM_u8TxBuf, 3U))
    {
        result = FALSE;
        __NOP();
        __NOP();
    }
    return result;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t TconM_ReadByte(uint8_t page, uint8_t address, uint8_t* readValue)
{
    uint8_t result = TRUE;
    TconM_u8TxBuf[0] = page;
    TconM_u8TxBuf[1] = address;

    if(true != I2cMasterApp_Rx(I2C_MASTER_SERCOM_4, TconM_u8TxBuf, 2U, TconM_u8RxBuf, 1U))
    {
        result = FALSE;
        __NOP();
        __NOP();
    }
    else
    {
        (* readValue) = TconM_u8RxBuf[0];
    }
    return result;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t TconM_SetIcAccessKey(void)
{
    uint8_t result = TRUE;
    uint8_t returnData = 0U;
    result &= TconM_WriteByte(0xEFU, 0x01U, 0x5AU);
    result &= TconM_WriteByte(0xEFU, 0x02U, 0x28U);
    result &= TconM_ReadByte(0xEFU, 0x03U, &returnData);
    if (returnData != 0x01U) // IC ACCESS KEY FAIL
    {
        result = FALSE;
    }
    return result;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     
                                   
********************************************************************************/
uint8_t TconM_SetMagic(void)
{
    uint8_t ret;
    TconM_u8TxBuf[0] = 0x01U;
    TconM_u8TxBuf[1] = 0x70U;
    TconM_u8TxBuf[2] = 0xA5U;
    (void)memset(&TconM_u8TxBuf[3], 0x03U, 31u);
    if(true == I2cMasterApp_Tx(I2C_MASTER_SERCOM_4, TconM_u8TxBuf, 34U))
    {
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
  Function Descripttion        :     It can be used to release the device from the power-down state
                                   
********************************************************************************/
uint8_t TconM_ReleasePowerDown(void)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0xABU);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x07U);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     Although the standby current during normal operation is relatively low, standby current can be further reduced with the Power-down instruction.
                                   
********************************************************************************/
uint8_t TconM_PowerDown(void)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0xB9U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x07U);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     The Chip Erase instruction sets all memory within the device to the erased state of all 1s (FFh). A Write Enable instruction must be executed before the device will accept the Chip Erase Instruction 
                                   
********************************************************************************/
uint8_t TconM_ChipErase(void)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0xC7U/* 0x60U */);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x07U);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     The Sector Erase instruction . A Write Enable instruction must be executed before the device will accept the Sector Erase Instruction 
                                   
********************************************************************************/
uint8_t TconM_SectorErase(uint32_t u32SectorAddr)
{
    uint8_t result = TRUE;
    uint8_t u8SectorAddr_H = (u32SectorAddr >> 16) & 0xFFU;
    uint8_t u8SectorAddr_M = (u32SectorAddr >> 8) & 0xFFu;
    uint8_t u8SectorAddr_L = (u32SectorAddr & 0xFFU);
   
    result &= TconM_WriteEnable(); 
    result &= TconM_CheckStatus(0x02, 0x02); 

    result &= TconM_WriteByte(0xFFU, 0x05U, 0x20U);
    result &= TconM_WriteByte(0xFFU, 0x06U, u8SectorAddr_H);
    result &= TconM_WriteByte(0xFFU, 0x07U, u8SectorAddr_M);
    result &= TconM_WriteByte(0xFFU, 0x08U, u8SectorAddr_L);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x1FU);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);

    return result;
}
/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     Must be set prior to every Page Program, Sector Erase, Block Erase, Chip Erase, Write Status Register and Erase/Program Security Registers instruction
                                   
********************************************************************************/
uint8_t TconM_WriteEnable(void)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0x06U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x07U);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     Compare status register with Nth bit 
                                   
********************************************************************************/
uint8_t TconM_CheckStatus(uint8_t checkBit, uint8_t expectedValue)  //todo 不要死等
{
    uint8_t result = FALSE;
    uint8_t retry = 100U;
    uint8_t data;
    while (TconM_ReadStatus(&data) && retry > 0)
    {
        if ((data & checkBit) == expectedValue)
        {
            result = TRUE;
            break;
        }
        retry--;
        (void)FunApp_Delay_Millisecond(10U, MODE_SYSTICK);
    }
    if(result == FALSE)
    {
        __NOP();
        __NOP();
        __NOP();
    }
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :    The Read Status Register instruction may be used at any time, even while a Program, Erase or Write status Register cycle is in progress. 
                                    This allows the BUSY status bit to be checked to determine when the cycle is complete and if the device can accept another instruction
                                   
********************************************************************************/
uint8_t TconM_ReadStatus(uint8_t* returnByte)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0x05U);
    result &= TconM_WriteByte(0xFFU, 0x06U, 0x00U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x0FU);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x89U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    result &= TconM_ReadByte(0xFFU, 0x06U, returnByte);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :    This instruction allows you to change various configuration settings and parameters of the flash memory, 
                                    such as protection settings, memory organization, and operation modes.
                                   
********************************************************************************/
uint8_t TconM_WriteStatus(uint8_t data)
{
    uint8_t result = TRUE;
    result &= TconM_WriteByte(0xFFU, 0x05U, 0x01U);
    result &= TconM_WriteByte(0xFFU, 0x06U, data);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
    result &= TconM_WriteByte(0xFFU, 0x04U, 0x0FU);
    result &= TconM_WriteByte(0xFFU, 0x03U, 0x09U);
    result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
    (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     The Page Program instruction allows from one byte to 256 bytes (a page) of data to be programmed at previously erased (FFh) memory locations
                                   
********************************************************************************/
uint8_t TconM_Program(uint8_t* binBuffer, uint32_t addr, uint32_t size)
{
    uint8_t result = TRUE;
    uint8_t isPageAlign = FALSE;
    if ((addr & 0xFFU) == 0U)
    {
        isPageAlign = TRUE;
    }
    
    if (isPageAlign == FALSE)
    {
        uint32_t firstSize = 0x100U - (addr & 0xFFU); //one page size is 256-byte
        if(firstSize > size)
        {
            firstSize = size;
        }
        result &= TconM_ProgramData(binBuffer, addr, firstSize);
        if (result == TRUE)
        {  
            addr += firstSize;
            size -= firstSize;
        }
    }
    if (result == TRUE)
    {
        result &= TconM_ProgramData(binBuffer, addr, size);
    }
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     Program Flow
                                    CheckStatus -> WriteEnable -> CheckStatus -> Page Program -> CheckStatus (Repeat)
                                   
********************************************************************************/
uint8_t TconM_ProgramData(uint8_t* binBuffer, uint32_t addr, uint32_t size)
{
    uint8_t result = TRUE;
    uint32_t tempSize = size;
    uint16_t maxWriteBuffer = 64U;
    while (tempSize > 0)
    {
        result &= TconM_WriteEnable();           //                          AN Step 7-8
        result &= TconM_CheckStatus(0x02, 0x02); // Is write enable work     AN Step 7-8
        if (result == FALSE)
        {
            __NOP();
            __NOP();
        }

#if (BURST_MODE_EN != ENABLE_ON)
        result &= TconM_WriteByte(0xFF, 0x05, 0x02);
        result &= TconM_WriteByte(0xFF, 0x06, (uint8_t)((addr >> 16) & 0xFFU));
        result &= TconM_WriteByte(0xFF, 0x07, (uint8_t)((addr >> 8) & 0xFFU));
        result &= TconM_WriteByte(0xFF, 0x08, (uint8_t)((addr) & 0xFFU));
#endif
        uint16_t writeLen = tempSize > maxWriteBuffer ? maxWriteBuffer : tempSize;
        tempSize -= writeLen;
#if (BURST_MODE_EN != ENABLE_ON)
        uint8_t firstProgramDataAddr = 0x09U;
        for (uint16_t i = 0u; i < writeLen; i++)
        {
            result &= TconM_WriteByte(0xFFU, firstProgramDataAddr, *(binBuffer + addr));
            firstProgramDataAddr ++;
            addr ++;
        }
#else
        TconM_u8TxBuf[0] = 0xFFU;
        TconM_u8TxBuf[1] = 0x05U;
        TconM_u8TxBuf[2] = 0x02U;
        TconM_u8TxBuf[3] = (uint8_t)((addr >> 16) & 0xFFU);
        TconM_u8TxBuf[4] = (uint8_t)((addr >> 8) & 0xFFU);
        TconM_u8TxBuf[5] = (uint8_t)((addr) & 0xFFU);
        (void)memcpy(&TconM_u8TxBuf[6],(binBuffer + size - writeLen - tempSize),writeLen);
        if(true ==  I2cMasterApp_Tx(I2C_MASTER_SERCOM_4, TconM_u8TxBuf, (writeLen + 6U)))
        {
            result &= TRUE;
            addr += writeLen;
        }
        else
        {
            result &= FALSE;
        }
#endif

        uint16_t packageBitSize = (writeLen + 4U) * 8U - 1U;
        uint8_t packageBitlo = (uint8_t)((packageBitSize) & 0xFFU);
        uint8_t packageBithi = (uint8_t)(((packageBitSize >> 7) & 0x06U) | 0x21U/* 0x1U */);
        result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
        result &= TconM_WriteByte(0xFFU, 0x04U, packageBitlo);
        result &= TconM_WriteByte(0xFFU, 0x03U, packageBithi);
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        result &= TconM_CheckStatus(0xFFU, 0x00U);                      //    AN Step 7-10
        if (result == FALSE)
        {
            __NOP();
            __NOP();
            break;
        }
            
    }
    return result;
}

/*******************************************************************************
  Function Name                :    
  Parameters                   :    
  Return Values                :    
  Function Descripttion        :     The Read Data instruction allows one or more data bytes to be sequentially read from the memory
                                   
********************************************************************************/
uint8_t TconM_Read(uint32_t addr, uint32_t size, uint8_t* buffer)
{
    uint8_t result = TRUE;
    uint16_t maxReadBuffer = 64U;
    uint32_t tempSize = size;
#if (BURST_MODE_EN != ENABLE_ON)
    uint8_t returnData;
#endif
    while (TRUE)
    {
        result &= TconM_WriteByte(0xFFU, 0x05U, 0x03U);
        result &= TconM_WriteByte(0xFFU, 0x06U, (uint8_t)((addr >> 16) & 0xFFU));
        result &= TconM_WriteByte(0xFFU, 0x07U, (uint8_t)((addr >> 8) & 0xFFU));
        result &= TconM_WriteByte(0xFFU, 0x08U, (uint8_t)((addr) & 0xFFU));
        result &= TconM_WriteByte(0xFFU, 0x00U, 0xF0U);
        uint16_t len = tempSize > maxReadBuffer ? maxReadBuffer : tempSize;
        tempSize -= len;
        uint16_t packageBitSize = (len + 4) * 8 - 1;
        result &= TconM_WriteByte(0xFFU, 0x04U, (uint8_t)((packageBitSize) & 0xFFU));
        result &= TconM_WriteByte(0xFFU, 0x03U, (uint8_t)(((packageBitSize >> 7) & 0x06U) | 0xA1U)); // SPI_Len[8:9]
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        result &= TconM_WriteByte(0xFFU, 0x00U, 0xF1U);
        (void)FunApp_Delay_Millisecond(3U, MODE_SYSTICK);
        uint8_t startAddr = 0x09U;
#if (BURST_MODE_EN != ENABLE_ON)
        for (uint16_t i = 0; i < len; i++)
        {
            result &= TconM_ReadByte(0xFF, startAddr++, &returnData);
            *(buffer + addr) = returnData;
            addr++;
        }
#else
        TconM_u8TxBuf[0] = 0xFFU;
        TconM_u8TxBuf[1] = startAddr;
        if(true ==  I2cMasterApp_Rx(I2C_MASTER_SERCOM_4, TconM_u8TxBuf, 2U, (buffer + size - len - tempSize), len))
        {
            startAddr += len;
            result &= TRUE;
            // (void)memcpy(buffer,TconM_u8RxBuf,len);
        }
        else
        {
            result &= FALSE;
        }
#endif
        if (result == FALSE)
        {
            break;
        }
        if (tempSize == 0)
        {
            break;
        }
    }
    return result;
}

#endif
