/******************************************************************************
;       Program		: CrcApp.h
;       Function	: CRC Calculation Functions 
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 04 / 21
;       Author		: Frank Chen & Fenderson Lu
******************************************************************************/
#ifndef CrcApp_H
#define CrcApp_H 
/*---------------------------- Define Constant ------------------------------*/
#define		INIT_CRC32		0xFFFFFFFFU
#define		SIZE_CRC32		256U
#define		SIZE_CRC16		256U
/*---------------------------- CRC8 ------------------------------*/
#define I2C_CRC8_POLY                           0x1DU    
#define I2C_CRC8_INIT_VALUE                     0x00U     
#define I2C_CRC8_XOR                            0x00U

/*---------------------------- Declare Function -----------------------------*/
uint32_t CrcApp_Crc32_Calculation(uint8_t *pData, uint32_t u32Len, uint32_t u32Crc32);
uint16_t CrcApp_Crc16_Calculation(uint8_t *pData, uint32_t u32Len);
uint8_t CrcApp_Crc8_Calculation(uint8_t *pData, uint16_t u16Len);
#endif





