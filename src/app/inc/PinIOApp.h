/******************************************************************************
;       Program		: PinIOApp.h
;       Function	: Define IO Pin Function
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 10
;       Author		: Joel Wang
******************************************************************************/
#ifndef PinIOAPP_H
#define PinIOAPP_H
/*---------------------------- Include Library ------------------------------*/
#include "hal/inc/PortDriver.h"
/*---------------------------- Delcare Content  ----------------------------*/
#define	PARA_ODD_EVEN_NUM	2U
/* Hw VerPins */
#define		SET_PCBA_A3		0x1000U
#define		SET_PCBA_A2		0x0100U	
#define		SET_PCBA_A1		0x0010U
#define		SET_PCBA_A0		0x0001U

/*---------------------------- IPC I/O Pin Definition ---------------------------*/	

#define	portXRES_TP_R		PORT_A
#define	pinXRES_TP_R		BIT1

#define	portBATT_SENSE_EN	PORT_A
#define	pinBATT_SENSE_EN	BIT2

#define	portBATT_SENSE_ADC	PORT_A
#define	pinBATT_SENSE_ADC	BIT3

#define	portI2C_SDA_DES_SLAVE	PORT_A
#define	pinI2C_SDA_DES_SLAVE	BIT8

#define	portI2C_SCL_DES_SLAVE	PORT_A
#define	pinI2C_SCL_DES_SLAVE	BIT9

#define	portMPQ3365A_EN	PORT_A
#define	pinMPQ3365A_EN		BIT10

#define	portXRES_TP				PORT_A
#define	pinXRES_TP				BIT18

#define	portTCON_RESET			PORT_A
#define	pinTCON_RESET			BIT20

#define	portMPQ3365A_PWMI		PORT_A
#define	pinMPQ3365A_PWMI		BIT21

#define	portPCBA_A3				PORT_A
#define	pinPCBA_A3				BIT27
#define IO_PCBA_A3				IO_PIN_PA27

#define	portPCBA_A2				PORT_A
#define	pinPCBA_A2				BIT28
#define	IO_PCBA_A2				IO_PIN_PA28

#define	portPCBA_A0				PORT_B
#define	pinPCBA_A0				BIT0
#define	IO_PCBA_A0				IO_PIN_PB00

#define	portPCBA_A1				PORT_B
#define	pinPCBA_A1				BIT1
#define	IO_PCBA_A1				IO_PIN_PB01

#define	portPDB					PORT_B
#define	pinPDB					BIT4

#define	portMCU_3V3_EN			PORT_B
#define	pinMCU_3V3_EN			BIT6

#define	portWAKE_REQUEST_V_RCV	PORT_B
#define	pinWAKE_REQUEST_V_RCV	BIT10

#define	portXON					PORT_B
#define	pinXON					BIT19

#define	portTCON_BIST		PORT_B
#define	pinTCON_BIST		BIT20

#define	portDRIVER_RESET	PORT_B
#define	pinDRIVER_RESET		BIT22

#define	portDUAL_NRST		PORT_B
#define	pinDUAL_NRST		BIT24

#define	portDUAL_CLKIN		PORT_B
#define	pinDUAL_CLKIN		BIT25

#define	portDEBUG_TX		PORT_B
#define	pinDEBUG_TX			BIT30

#define	portDEBUG_RX		PORT_B
#define	pinDEBUG_RX			BIT31

#define	portMCU_INT			PORT_C
#define	pinMCU_INT			BIT0

#define	portMCU_1V35_EN		PORT_C
#define	pinMCU_1V35_EN		BIT19

#define	portMCU_1V8_EN		PORT_C
#define	pinMCU_1V8_EN		BIT16

#define	portMCU_WD_RESET	PORT_C
#define	pinMCU_WD_RESET		BIT24

#define	portLCD_BIAS		PORT_C
#define	pinLCD_BIAS			BIT25

#define	portMCU_1V1_EN		PORT_C
#define	pinMCU_1V1_EN		BIT28

#define	portVCUWakeC			PORT_A      /* pin 38 */
#define	pinVCUWakeC             BIT6
#define	IO_VCUWakeC             IO_PIN_PA06

#define PINIO_LAYOUT TRUE
#define PINIO_SGM TRUE
#define PINIO_IPC FALSE
#define PINIO_ICS FALSE

enum PinSet
{
	SET_PIN_BIT0 = 0x01U,
	SET_PIN_BIT1 = 0x02U,
	SET_PIN_BIT2 = 0x04U,
	SET_PIN_BIT3 = 0x08U,
	SET_PIN_BIT4 = 0x10U,
	SET_PIN_BIT5 = 0x20U,
	SET_PIN_BIT6 = 0x40U,
	SET_PIN_BIT7 = 0x80U,
	SET_PIN_BIT8 = 0x0100U,
	SET_PIN_BIT9 = 0x0200U,
	SET_PIN_BIT10 = 0x0400U,
	SET_PIN_BIT11 = 0x0800U,
	SET_PIN_BIT12 = 0x1000U,
	SET_PIN_BIT13 = 0x2000U,
	SET_PIN_BIT14 = 0x4000U,
	SET_PIN_BIT15 = 0x8000U,
	SET_PIN_BIT16 = 0x010000U,
	SET_PIN_BIT17 = 0x020000U,
	SET_PIN_BIT18 = 0x040000U,
	SET_PIN_BIT19 = 0x080000U,
	SET_PIN_BIT20 = 0x100000U,
	SET_PIN_BIT21 = 0x200000U,
	SET_PIN_BIT22 = 0x400000U,
	SET_PIN_BIT23 = 0x800000U,
	SET_PIN_BIT24 = 0x01000000U,
	SET_PIN_BIT25 = 0x02000000U,
	SET_PIN_BIT26 = 0x04000000U,
	SET_PIN_BIT27 = 0x08000000U,
	SET_PIN_BIT28 = 0x10000000U,
	SET_PIN_BIT29 = 0x20000000U,
	SET_PIN_BIT30 = 0x40000000U,
	SET_PIN_BIT31 = 0x80000000U
};

enum GpioPort
{
	PORT_A = 0, 
	PORT_B = 1,
	PORT_C = 2
};

enum GpioPin
{
	BIT0 = 0U,
	BIT1 = 1U,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7,
	BIT8,
	BIT9,
	BIT10,
	BIT11,
	BIT12,
	BIT13,
	BIT14,
	BIT15,
	BIT16, 
	BIT17,
	BIT18,
	BIT19,
	BIT20, 
	BIT21,
	BIT22,
	BIT23,
	BIT24, 
	BIT25,
	BIT26,
	BIT27,
	BIT28,
	BIT29,
	BIT30,
	BIT31
};

enum SysPower
{
	SYS_PWR_OFF = 0U,
	SYS_PWR_ON = 1U
};

enum ProcessStatus
{
	PINIO_FINISH = 0U,
	PINIO_FAIL = 1U
};

enum PanelType
{
    PANEL_DEFAULT = 0U,
	INCHES_EDGE_11 = 1U,
	INCHES_DIRECT_11 = 2U,
    INCHES_EDGE_15 = 3U,
    INCHES_DIRECT_15 = 4U,
    INCHES_EDGE_16_8 = 5U,
    INCHES_DIRECT_16_8 = 6U,
    PANEL_TYPE_ERROR = 7U
};

enum PinLevel{
	PIN_LEVEL_HIGH = 1U,
	PIN_LEVEL_LOW = 0U
};

enum HwStatus{
	LOCAL_DIMMING = 0x01U,
	NONLOCAL_DIMMING = 0x02U
};
/*---------------------------- Declare Function -----------------------------*/
#if (PINIO_LAYOUT == PINIO_SGM)
extern uint8_t PinIOApp_Init(uint8_t u8Para);
extern uint8_t PinIOApp_Project_HW_Check(uint8_t u8Para);
#elif (PINIO_LAYOUT == PINIO_IPC)
extern uint8_t PinIOApp_Init_IPC(uint8_t u8Para);
extern uint8_t PinIOApp_IPC_Project_HW_Check(uint8_t u8Para);
#elif (PINIO_LAYOUT == PINIO_ICS)
extern uint8_t PinIOApp_Init_ICS(uint8_t u8Para);
extern uint8_t PinIOApp_ICS_Project_HW_Check(uint8_t u8Para);
#endif
extern bool PinIOApp_High(int8_t i8Port, uint8_t u8Pin);
extern bool PinIOApp_Low(int8_t i8Port, uint8_t u8Pin);
extern bool PinIOApp_System_Power(uint8_t u8Switch);


extern uint8_t PinIOApp_Hw_Ver_Check(uint8_t u8Para);
extern uint16_t PinIOApp_HwVer_Get(void);
extern uint8_t PinIOApp_HwStatusFlag_Get(void);
#endif

