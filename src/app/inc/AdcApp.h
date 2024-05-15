/******************************************************************************
;       Program		: AdcApp.h
;       Function	: Declare and define ADC0 Ch1
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 10
;       Author		: Joel Wang
******************************************************************************/
#ifndef AdcApp_H
#define AdcApp_H
/*---------------------------- Debug Support ---------------------------------*/
#define	DEBUG_BAT_ADC		false
#define	DEBUG_BAT_VOL		false
#define DEBUG_HWVER_ADC     false
#define DEBUG_HWVER_GET     true
/*---------------------------- Define Constant -------------------------------*/
#define ADC0_CH1_BATT       ADC_INPUTCTRL_MUXPOS_AIN1
#define ADC1_CH2_BATT       ADC_INPUTCTRL_MUXPOS_AIN2
#define ADC1_CH0_HW_VER     ADC_INPUTCTRL_MUXPOS_AIN0
#define	SIZE_BATT_VOLT		27U
#define	SIZE_HW_VER         10U
#define	BASE_HW_VER         1U
#define	BASE_HW_VER_H       0U

#define	HW_VER_MAX          10U
#define	HW_VER_MAX_H        1U
#define	HW_VER_MAX_L        0U

#define	DEBOUNCE_ADC_BYPASS		2U
#define	DEBOUNCE_VOLT			3U
#define	DEBOUNCE_BOOT_VOLT		3U

#define	THRESHLOD_VOLT_PROTECT	BAT_VOLT_9

/*---------------------------- Declare Enum ----------------------------------*/
enum AdcSwitch
{
	ADC_DISABLE,
	ADC_ENABLE
};

enum BatteryState
{
	STATE_BAT_INIT = 0U,
	STATE_BAT_BOOT = 1U,
	STATE_BAT_NORMAL = 2U,
	STATE_BAT_PROTECT = 3U,
	STATE_BAT_MAX
};

#define	STEPS_BATT_VOLT		27U
#define	INDEX_VOLT			BAT_VOLT_30
enum BatteryVolt
{
	BAT_VOLT_4 = 4U,
	BAT_VOLT_5 = 5U,
	BAT_VOLT_6 = 6U,
	BAT_VOLT_7 = 7U,
	BAT_VOLT_8 = 8U,
	BAT_VOLT_9 = 9U,
	BAT_VOLT_10 = 10U,
	BAT_VOLT_11 = 11U,
	BAT_VOLT_12 = 12U,
	BAT_VOLT_13 = 13U,
	BAT_VOLT_14 = 14U,
	BAT_VOLT_15 = 15U,
	BAT_VOLT_16 = 16U,
	BAT_VOLT_17 = 17U,
	BAT_VOLT_18 = 18U,
	BAT_VOLT_19 = 19U,
	BAT_VOLT_20 = 20U,
	BAT_VOLT_21 = 21U,
	BAT_VOLT_22 = 22U,
	BAT_VOLT_23 = 23U,
	BAT_VOLT_24 = 24U,
	BAT_VOLT_25 = 25U,
	BAT_VOLT_26 = 26U,
	BAT_VOLT_27 = 27U,
	BAT_VOLT_28 = 28U,
	BAT_VOLT_29 = 29U,
	BAT_VOLT_30 = 30U
};
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t AdcApp_Init(void);
extern uint8_t AdcApp_Start(void);
extern uint8_t AdcApp_Converstion_Ready(void);
extern uint8_t AdcApp_Turn_OnOff_Switch(uint8_t u8Switch);
extern uint8_t AdcApp_Battery_Volt_Transfer(void);
extern uint8_t AdcApp_Battery_Volt_Protect_Process(void);
extern uint32_t AdcApp_AdcCaptureEnableCnt_Get(void);
extern uint32_t AdcApp_AdcCaptureEnableCnt_Set(uint32_t ulValue);
extern uint8_t AdcApp_AdcToVolt_Get(void);
extern bool AdcApp_AdcDebounceFlag_Set(bool bSwitch);
extern bool AdcApp_AdcDebounceFlag_Get(void);
extern uint8_t AdcApp_HW_Version_Transfer(void);
extern uint16_t AdcApp_AdcToHWVersion_Get(void);
#endif
