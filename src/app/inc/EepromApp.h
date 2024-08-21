/****************************************************************************************
;       Program		: EepromApp.h
;       Function	: 
;       Date		: 2020 / 07 / 09
;       Author		: Jack.Wu
;       Describe	: 
*****************************************************************************************/


#ifndef EEPROMAPP_H
#define EEPROMAPP_H

#include "main.h"
#include "hal/inc/FmcDriver.h"

#define EEPROM_READ_WAIT_CLOCK_TIME     2U


#define EEPROM_REGION_0_WAKEUP_COUNT            0x00000000U
#define EEPROM_REGION_1_REBOOT_COUNT            0x00000100U
#define EEPROM_REGION_2_DIAGNOSIS_BL            0x00000200U
/* #define EEPROM_REGION_3_FW_VERSION              0x00000300U */
/* #define EEPROM_REGION_4_SW_PART_NUMBER          0x00000400U */
#define EEPROM_REGION_5_HW_PN_L        			0x00000500U
#define EEPROM_REGION_5_HW_PN_H        			0x00000510U
#define EEPROM_REGION_5_BL_MAX        		    0x00000600U
/* #define EEPROM_REGION_6_FACTORY_INFO            0x00000600U */
#define EEPROM_REGION_7_WDG                     0x00000700U                     /* WDG need to check */
/* #define EEPROM_REGION_8_                        0x00000800U */


#define EEPROM_DATA_LENGTH_1                    0x00000001U





void EepromApp_Initial(void);
uint32_t EepromApp_Read(uint32_t u32AddrOffset, uint32_t u32Len);
void EepromApp_Write(uint32_t u32AddrOffset, uint32_t u32Data);
void EepromApp_Erase(uint32_t u32AddrOffset);


#endif

