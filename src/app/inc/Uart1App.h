/******************************************************************************
;       Program		: Uart1App.h
;       Function	: Declare and Define SERCOM1 UART Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 04
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef Uart1App_H
#define Uart1App_H
/*---------------------------- Include Library -------------------------------*/
#include "peripheral/sercom/usart/plib_sercom1_usart.h"
/*---------------------------- Define Constant -------------------------------*/
#define     SHOW_PARA_HEX           10U
#define     SHOW_PARA_DEC           6U
#define     SHOW_ASCII_ZERO         0x30U
#define     SHOW_ASCII_X            0x78U
#define     SHOW_ASCII_NUM          0x30U
#define     SHOW_ASCII_CAPS         0x37U
#define     SHOW_STR_A              0x0AU

#define     SIZE_SHOW_VAL           20U
#define     SIZE_SHOW_STR           50U
/*---------------------------- Support Code Gen Function ---------------------*/
#define		Sercom1_Uart_Init()                 (SERCOM1_USART_Initialize())
#define		Sercom1_Uart_Write(buffer, size)    (SERCOM1_USART_Write((buffer), (size)))
#define		Sercom1_Uart_Tx_Ready()             (SERCOM1_USART_TransmitterIsReady())
#define		Sercom1_Uart_Tx_Complete()          (SERCOM1_USART_TransmitComplete())
/*---------------------------- Declare Constant ------------------------------*/
enum ShowMode{
	SHOW_HEX,
	SHOW_DEC
};

enum HexNum{
	HEX_HEAD_1,
	HEX_HEAD_2,
	HEX_VAL_H,
	HEX_VAL_M0,
	HEX_VAL_M1,
	HEX_VAL_M2,
	HEX_VAL_M3,
	HEX_VAL_M4,
	HEX_VAL_M5,
	HEX_VAL_L
};

enum DecNum{
	DEC_VAL_H,
	DEC_VAL_M0,
	DEC_VAL_M1,
	DEC_VAL_M2,
	DEC_VAL_M3,
	DEC_VAL_L
};
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t Uart1App_Init(uint8_t u8Para);
extern void Uart1App_String_Show(const char *u8String);
extern void Uart1App_String_Value_Show(const char *u8String, uint32_t u32Value, uint8_t u8Mode);
extern void Uart1App_Boot_Keys_Show(uint32_t u32Value1, uint32_t u32Value2, uint32_t u32Value3);
extern void Uart1App_Crc_Show(uint32_t u32Value1, uint32_t u32Value2);
extern void Uart1App_MCU_Ver_Show(const char *u8String1, const char *u8String2);
void Uart1App_Val_To_ASCII(uint32_t u32Value, uint8_t u8Mode);
#endif
