/******************************************************************************
;       Program		: FlashRwApp.h
;       Function	: Declare and Define Flash R/W Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 16
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef FlashRwApp_H
#define FlashRwApp_H
/*---------------------------- Define Constant -------------------------------*/
#define		SIZE_ERASE_256B				256U
#define		SIZE_READ_THRESHOLD			256U	
#define		SIZE_A_PAGE					SIZE_A_PAGE_64B
#define		SIZE_A_PAGE_64B				64U	
#define		SIZE_A_PAGE_256B			64U
#define		SIZE_FIDM_VER				4U
#define 	FLASH_RW_APP_LOCK_TEST		false
/*---------------------------- Enum Declare ----------------------------------*/
enum FlashRwAppStatus
{
	FLASH_FINISH = 0U,
	FLASH_FAIL = 1U
};
enum ByteOrder
{
	BYTE_L = 0U,
	BYTE_M0 = 1U,
	BYTE_M1 = 2U,
	BYTE_H = 3U
};
enum FidmVerPackets{
	NONLOCAL_FIDM_VER_H = 0U,
	NONLOCAL_FIDM_VER_L = 1U,
	LOCAL_FIDM_VER_H = 2U,	
	LOCAL_FIDM_VER_L = 3U	
};
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t FlashRwApp_64B_Page_Write(uint32_t u32StartAddr, uint8_t *pu8DataBuff);
extern uint8_t FlashRwApp_256B_Erase(uint32_t u32StartAddr, uint32_t u32PageShift);
extern uint8_t FlashRwApp_Read(uint32_t u32DestAddr, uint32_t u32ReadByteLen, uint8_t *pu8DataBuff);
extern uint8_t FlashRwApp_FIDM_Ver_Check(uint8_t u8Para);
extern uint16_t FlashRwApp_FIDM_Ver_Get(void);
#endif

