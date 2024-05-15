/******************************************************************************
;       Program		: main.h
;       Function	: Declare Main Function & Variable
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 03 / 24
;       Author		: Fenderson Lu
******************************************************************************/
#ifndef MAIN_H
#define MAIN_H
/*---------------------------- Include Library ------------------------------*/
#include <stdlib.h>		/* Defines EXIT_FAILURE */
#include "device.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>	/* Defines true */
#include <stddef.h>		/* Defines NULL */
/*---------------------------- Switch Support Function ----------------------*/
#define		MICROCHIP_ARM_ENV	true
#define     AUTO_MATCH_ADDRESS  true
/*---------------------------- Define Constant ------------------------------*/
#define 	NOTHING				(uint8_t)(0U)
#define 	SAMC2XN_SERISES		0x00U
#define 	YES					0xFFU
#define 	NO					0x00U
#define 	TRUE				0x01U
#define 	FALSE				0x00U
#define 	ENABLE_ON			1U
#define 	ENABLE_OFF			0U
/*---------------------------- Declare Enum ---------------------------------*/
enum Status
{
	STATUS_FINISH = 0U,
	STATUS_FAIL = 1U,
	STATUS_WAIT = 2U,
	STATUS_BUSY = 3U
};
/*---------------------------- Declare Function -----------------------------*/
#endif

