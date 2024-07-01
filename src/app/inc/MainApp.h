/******************************************************************************
;       Program		: MainApp.h
;       Function	: Declare Task and Schedule Function & Variable
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 11 / 16
;       Author		: Orlando Huang
******************************************************************************/
#ifndef MAINAPP_H
#define MAINAPP_H
/*---------------------------- Include File ---------------------------------*/
#include "main.h"
#include "app/inc/PinIOApp.h"
#include "app/inc/FunApp.h"
#include "app/inc/I2c0SlaveApp.h"
#include "app/inc/Uart1App.h"
#include "app/inc/InitApp.h"
#include "app/inc/AdcApp.h"
#include "app/inc/WakeCtrlApp.h"
#include "app/inc/SysTickApp.h"
#include "app/inc/WatchDogApp.h"
#include "app/inc/I2cMasterApp.h"
#include "hal/inc/PwmDriver.h"
/*---------------------------- Define Constant ------------------------------*/
#define		BL_VER				"F1.3.1"

#define		LOOP_MAX			0xFFFFFFFFU
#define		TIME_BL_ACTIVE		1U
/*---------------------------- Support Function -----------------------------*/
#define		DEBUG_UART			false
#define		WRITE_COUNT_TEST    false
#define		SYS_TICK			true
#define		VTOS				true
#define		NVIC_ENABLE			true
#define		FLASH_ERASE			true
#define		FLASH_WRITE			true
#define		FLASH_READ			true
#define		PWM2_OUTPUT			false
#define		ADC_BATT			true
#define		I2C0_SLAVE			true
#define     CRC16_CHECK         true
#define     CRC32_CHECK         true
#define		WDT_RST				true
#define     HW_VERSION          true

/*---------------------------- Declare Enum ---------------------------------*/
/* Bit Shift */
#define		SHIFT_BIT_0			0U
#define		SHIFT_BIT_1			1U
#define		SHIFT_BIT_2			2U
#define		SHIFT_BIT_3			3U
#define		SHIFT_BIT_4			4U
#define		SHIFT_BIT_5			5U
#define		SHIFT_BIT_6			6U
#define		SHIFT_BIT_7			7U
#define		SHIFT_BIT_8			8U
#define		SHIFT_BIT_9			9U
#define		SHIFT_BIT_10		10U
#define		SHIFT_BIT_11		11U
#define		SHIFT_BIT_12		12U
#define		SHIFT_BIT_13		13U
#define		SHIFT_BIT_14		14U
#define		SHIFT_BIT_15		15U
#define		SHIFT_BIT_16		16U
#define		SHIFT_BIT_17		17U
#define		SHIFT_BIT_18		18U
#define		SHIFT_BIT_19		19U
#define		SHIFT_BIT_20		20U
#define		SHIFT_BIT_21		21U
#define		SHIFT_BIT_22		22U
#define		SHIFT_BIT_23		23U
#define		SHIFT_BIT_24		24U
#define		SHIFT_BIT_25		25U
#define		SHIFT_BIT_26		26U
#define		SHIFT_BIT_27		27U
#define		SHIFT_BIT_28		28U
#define		SHIFT_BIT_29		29U
#define		SHIFT_BIT_30		30U
#define		SHIFT_BIT_31		31U
#define		SHIFT_BIT_32		32U

/* ============ ISR Priority ============ */
#define PRIORITY_HIGHEST                    0U
#define PRIORITY_1                          1U
#define PRIORITY_2                          2U
#define PRIORITY_LOWEST                     3U

/* TCON */
#define TCON_Rx_Buffer_Size	32U   
#define TCON_Tx_Buffer_Size 16U

enum StateMachine
{
BL_STARTUP = 0U,
BL_PREINIT = 1U, 
BL_INIT = 2U,
BL_TASK = 3U,
BL_UPDATE = 4U,
BL_SLEEP = 5U,
BL_WAKEUP_CHECK = 6U,
BL_IRQ_ERR = 7U,
};

enum Switch{
	DISABLE = 0U,
	ENABLE = 1U
};

/* Display ID */
typedef enum DisplayIDType
{   
    C304_DISPLAY_ID 	= 0xC7U,
	IPC_EDGE_CS2_HW3	= 0x19U,
	IPC_EDGE_CS3_HW3	= 0x19U,
	IPC_DIRECT_CS2_HW3	= 0x24U,
	IPC_DIRECT_CS3_HW3	= 0x24U,
	ICS_16_8 = 0x11U,
	ICS_15 = 0x10U,
	TYPE_ERR = 0xFFU,
}DisplayID;

/* TCON CMD Address */
typedef enum TconCommandAddrType
{
	TCONDutyCmdAddr = 0x0AU,
	TCONDimmCmdAddr = 0x04U
}TconCommandAddr;

/* TCON Protocol */
typedef struct
{
    uint8_t u8DevID;
    uint8_t u8Address;
    uint8_t u8Magic_Code;
    uint8_t u8RxLen;
    uint8_t u8TxLen;
    uint8_t u8TconRxBuf[TCON_Rx_Buffer_Size];
    uint8_t u8TconTxBuf[TCON_Tx_Buffer_Size];
}st_TCON_TypeDef;

/* Backlight Type */
typedef enum BacklightFormType
{
	BACKLIGHT_EDGE_BACKLIGHT = 0x1AU,
	BACKLIGHT_LOCAL_BACKLIGHT = 0x1BU
}BacklightType;
/*---------------------------- Declare Function -----------------------------*/
void MainApp_SetDisplayID(DisplayID dID);
uint8_t MainApp_getDisplayID(void);
void MainApp_SetBacklightType(BacklightType blType);
uint8_t MainApp_GetBacklightType(void);
bool MainApp_BLControl(void);
extern uint8_t MainApp_Task_1ms(uint8_t u8Para);
extern uint8_t MainApp_Task_1s(uint8_t u8Para);
void mainApp_SetBacklightDimmingType(void);
#endif
