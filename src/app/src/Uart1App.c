/******************************************************************************
;       Program		: Uart1App.c 
;       Function	: Declare and Define Debug SERCOM1 UART Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 08
;       Author		: Fenderson Lu
;       Describe 	: Code Gen Debug UART function. 
;					  Include SERCOM1_UART and STDIO_UART components.
;					  UART_TX = PB30
;					  UART_RX = PB31
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"
#include "app/inc/Uart1App.h"
/*---------------------------- Declare Global Variable ----------------------*/	
#if DEBUG_UART
static uint8_t gu8StrShowBuff[SIZE_SHOW_STR] = {0U};
static uint8_t gu8ValShowBuff[SIZE_SHOW_VAL] = {0U}; 
static uint16_t gu16StrShowLen; 
#endif
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;	Function Name			:	uint8_t Uart1App_Init(uint8_t u8Para)
;	Function Description	:	Initialize debug UART function.
;	Parameters				:	[u8Para] - NOTHING
;	Return Values			:	NOTHING
;	Source ID				:	GM_BL_UART-001
******************************************************************************/
#if DEBUG_UART
uint8_t Uart1App_Init(uint8_t u8Para)
{
	/* SERCOM1 Debug UART - DEBUG_TX_PB30, DEBUG_RX_PB31 */
	PORT_REGS->GROUP[portDEBUG_TX].PORT_PINCFG[pinDEBUG_TX] = 0x1U;
	PORT_REGS->GROUP[portDEBUG_RX].PORT_PINCFG[pinDEBUG_RX] = 0x1U;
	PORT_REGS->GROUP[PORT_B].PORT_PMUX[15] = 0x22U;

	Sercom1_Uart_Init();	/* DEBUG UART */

	(void)(u8Para);
	return u8Para;
}
#endif

/******************************************************************************
;	Function Name			:	static void Uart1App_Send(void *buffer, const size_t size)
;	Function Description	:	Send UART packets.
;	Parameters				:	[*Buffer] - Input data.
;								[Len] - Buffer length.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-002
******************************************************************************/
#if DEBUG_UART
static void Uart1App_Send(void *Buffer, const size_t Len)
{
    uint32_t u32TimeoutTemp = 12000U;
    
	while((Sercom1_Uart_Tx_Ready() == false) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }
    
	(void)Sercom1_Uart_Write(Buffer, Len);
    
    u32TimeoutTemp = 12000U;
	while((Sercom1_Uart_Tx_Complete() == false) && (u32TimeoutTemp > 0U))
    {
        u32TimeoutTemp = u32TimeoutTemp - 1U;
    }
}
#endif

/******************************************************************************
;	Function Name			:	static void Uart1App_Val_To_ASCII(uint32_t u32Value, uint8_t u8Mode)
;	Function Description	:	Values to ASCII.
;	Parameters				:	[u32Value] - Source values.
;								[u8Mode] - Mode Select.
;										  (1) SHOW_HEX : Show hex format.
;										  (2) SHOW_DEC : Show dec format.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-003
******************************************************************************/
#if DEBUG_UART
static void Uart1App_Val_To_ASCII(uint32_t u32Value, uint8_t u8Mode)
{
	uint32_t u32Index;

	switch(u8Mode)
	{
		case SHOW_HEX:
			/* Hex show range are 32-bits */
			gu8ValShowBuff[HEX_HEAD_1] = (uint8_t)(SHOW_ASCII_ZERO);	/* show head "0" */
			gu8ValShowBuff[HEX_HEAD_2] = (uint8_t)(SHOW_ASCII_X);	/* show head "x" */

			/* 8 digit hex */
			gu8ValShowBuff[HEX_VAL_H] = (uint8_t)((u32Value & 0xF0000000U) >> (uint32_t)(SHIFT_BIT_28));
			gu8ValShowBuff[HEX_VAL_M0] = (uint8_t)((u32Value & 0x0F000000U) >> (uint32_t)(SHIFT_BIT_24));
			gu8ValShowBuff[HEX_VAL_M1] = (uint8_t)((u32Value & 0x00F00000U) >> (uint32_t)(SHIFT_BIT_20));
			gu8ValShowBuff[HEX_VAL_M2] = (uint8_t)((u32Value & 0x000F0000U) >> (uint32_t)(SHIFT_BIT_16));
			gu8ValShowBuff[HEX_VAL_M3] = (uint8_t)((u32Value & 0x0000F000U) >> (uint32_t)(SHIFT_BIT_12));
			gu8ValShowBuff[HEX_VAL_M4] = (uint8_t)((u32Value & 0x00000F00U) >> (uint32_t)(SHIFT_BIT_8));
			gu8ValShowBuff[HEX_VAL_M5] = (uint8_t)((u32Value & 0x000000F0U) >> (uint32_t)(SHIFT_BIT_4));
			gu8ValShowBuff[HEX_VAL_L] = (uint8_t)(u32Value & 0x0000000FU);
			
			for(u32Index=(HEX_VAL_H); u32Index<(uint32_t)(SHOW_PARA_HEX); u32Index++)
			{
				if(gu8ValShowBuff[u32Index] >= (uint8_t)(SHOW_STR_A))
				{
					gu8ValShowBuff[u32Index] += (uint8_t)(SHOW_ASCII_CAPS);	/* show ASCII string "A ~ Z" */
				}
				else
				{
					gu8ValShowBuff[u32Index] += (uint8_t)(SHOW_ASCII_NUM);	/* show "0" ~ "9" */
				}
			}
			Uart1App_Send(&gu8ValShowBuff[0U], (uint8_t)(SHOW_PARA_HEX));
		break;
		case SHOW_DEC:
			/* Define Value is uint32_t (0~4294967295), Show range are 0 ~ 999999 */
			gu8ValShowBuff[DEC_VAL_H] = (uint8_t)(u32Value / 100000U) | (uint8_t)(SHOW_ASCII_NUM);						
			gu8ValShowBuff[DEC_VAL_M0] = (uint8_t)((u32Value % 100000U) / 10000U) | (uint8_t)(SHOW_ASCII_NUM);		
			gu8ValShowBuff[DEC_VAL_M1] = (uint8_t)((u32Value % 10000U) / 1000U) | (uint8_t)(SHOW_ASCII_NUM);		
			gu8ValShowBuff[DEC_VAL_M2] = (uint8_t)((u32Value % 1000U) / 100U) | (uint8_t)(SHOW_ASCII_NUM);			
			gu8ValShowBuff[DEC_VAL_M3] = (uint8_t)((u32Value % 100U) / 10U) | (uint8_t)(SHOW_ASCII_NUM);			
			gu8ValShowBuff[DEC_VAL_L] = (uint8_t)(u32Value % 10U) | (uint8_t)(SHOW_ASCII_NUM);	
			
			for(u32Index=0U; u32Index<(uint32_t)(SHOW_PARA_DEC); u32Index++)
			{
				if(gu8ValShowBuff[u32Index] != (uint8_t)(SHOW_ASCII_ZERO))
				{
					break;
				}
			}
			Uart1App_Send(&gu8ValShowBuff[u32Index], (SHOW_PARA_DEC - u32Index));
		break;
		default:
			/* NOTHING */
		break;
	}	
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_String_Show(const char *u8String)
;	Function Description	:	Show message.
;	Parameters				:	[*u8String] - Message string.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-004
******************************************************************************/
#if DEBUG_UART
void Uart1App_String_Show(const char *u8String)
{
	while(*u8String != (uintptr_t)(NULL))			/* Compute String length */
	{
		gu8StrShowBuff[gu16StrShowLen++] = (uint8_t)(*u8String);
		(void)(*u8String++);
		if (gu16StrShowLen >= (uint8_t)(SIZE_SHOW_STR-1U))
		{
			gu8StrShowBuff[SIZE_SHOW_STR-1U] = 0U;
			break;
		}	
	}

	Uart1App_Send(&gu8StrShowBuff[0U], gu16StrShowLen);
	gu16StrShowLen = 0U;	
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_String_Value_Show(const char *u8String, uint32_t u32Value, uint8_t u8Mode)
;	Function Description	:	Show message and values.
;	Parameters				:	[*u8String] - Message packets.
;								[u32Value] - Input values.
;								[u8Mode] - Select mode.
;										  (1) SHOW_HEX : Show hex format.
;										  (2) SHOW_DEC : Show dec format.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-005
;	Description				:	Ex.	Uart1App_String_Value_Show("Val = ", 0x55U, (uint8_t)(SHOW_HEX))
;									Uart1App_String_Value_Show("Val = ", 530U, (uint8_t)(SHOW_DEC))
******************************************************************************/
#if DEBUG_UART
void Uart1App_String_Value_Show(const char *u8String, uint32_t u32Value, uint8_t u8Mode)
{
	Uart1App_String_Show(u8String);
	Uart1App_Val_To_ASCII(u32Value, u8Mode);
	Uart1App_String_Show("\r");
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_Boot_Keys_Show(uint32_t u32Value1, uint32_t u32Value2, uint32_t u32Value3)
;	Function Description	:	Show boot keys message.
;	Parameters				:	[u32Value1] - Input boot key 0 value.
;								[u32Value2] - Input boot key 1 value.
;								[u32Value3] - Input session key value.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-006
******************************************************************************/
#if DEBUG_UART
void Uart1App_Boot_Keys_Show(uint32_t u32Value1, uint32_t u32Value2, uint32_t u32Value3)
{
	Uart1App_String_Show("(BKey0, BKey1, SKey) = (");
	Uart1App_Val_To_ASCII(u32Value1, (uint8_t)(SHOW_HEX));
	Uart1App_String_Show(", ");
	Uart1App_Val_To_ASCII(u32Value2, (uint8_t)(SHOW_HEX));
	Uart1App_String_Show(", ");
	Uart1App_Val_To_ASCII(u32Value3, (uint8_t)(SHOW_HEX));
	Uart1App_String_Show(")\r");
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_Crc_Show(uint32_t u32Value1, uint32_t u32Value2)
;	Function Description	:	Show CRC32 compare values.
;	Parameters				:	[u32Value1] - Input calculate CRC32 values.
;								[u32Value2] - Input App memory CRC32 values.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-007
******************************************************************************/
#if DEBUG_UART
void Uart1App_Crc_Show(uint32_t u32Value1, uint32_t u32Value2)
{
	Uart1App_String_Show("(CalculateCrc32, AppMemCrc32) = ( ");
	Uart1App_Val_To_ASCII(u32Value1, (uint8_t)(SHOW_HEX));
	Uart1App_String_Show(", ");
	Uart1App_Val_To_ASCII(u32Value2, (uint8_t)(SHOW_HEX));
	Uart1App_String_Show(")\r");
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_MCU_Ver_Show(const char *u8String1, const char *u8String2)
;	Function Description	:	Show MCU version.
;	Parameters				:	[*u8String1] - Input message.
;								[*u8String2] - Input MCU version message.
;	Return Values			:	NONA
;	Source ID				:	GM_BL_UART-008
******************************************************************************/
#if DEBUG_UART
void Uart1App_MCU_Ver_Show(const char *u8String1, const char *u8String2)
{
	Uart1App_String_Show(u8String1);
	Uart1App_String_Show(u8String2);
	Uart1App_String_Show("\r");
}
#endif

/******************************************************************************
;	Function Name			:	void Uart1App_Hw_Ver_Show(void)
;	Function Description	:	Show HW version.
;	Parameters				:	void
;	Return Values			:	void
;	Source ID				:	SGM_BL_UART-009
******************************************************************************/
#if DEBUG_UART
void Uart1App_Hw_Ver_Show(void)
{
	Uart1App_String_Show("HW Ver : ");		
	Uart1App_Val_To_ASCII((uint32_t)PinIOApp_HwVer_Get(), (uint8_t)(SHOW_HEX));

	switch(PinIOApp_HwStatusFlag_Get())
	{
		case NONLOCAL_DIMMING:
			Uart1App_String_Show(" (Non-local Dimming)");
			Uart1App_String_Show("\r");
		break;
		case LOCAL_DIMMING:
			Uart1App_String_Show(" (Local Dimming)");	
			Uart1App_String_Show("\r");
		break;
		default:
			Uart1App_String_Show(" (FAILURE)");	
			Uart1App_String_Show("\r");
		break;
	}
}
#endif
/*---------------------------------------------------------------------------*/ 
