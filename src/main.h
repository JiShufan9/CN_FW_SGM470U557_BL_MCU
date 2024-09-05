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

/*---------------------------- Define Constant ------------------------------*/
#define 	NOTHING				(uint8_t)(0U)
#define 	SAMC2XN_SERISES		0x00U
#define 	YES					0xFFU
#define 	NO					0x00U
#define 	TRUE				0x01U
#define 	FALSE				0x00U
#define 	ENABLE_ON			1U
#define 	ENABLE_OFF			0U
#define DATA_0                                          0U
#define DATA_1                                          1U
#define DATA_2                                          2U
#define DATA_3                                          3U
#define DATA_4                                          4U
#define DATA_5                                          5U

#define		OP_STS_0 	 0U
#define		OP_STS_1 	 1U
#define		OP_STS_2 	 2U
#define		OP_STS_3 	 3U
#define		OP_STS_4 	 4U
#define		OP_STS_5 	 5U
#define		OP_STS_6 	 6U
#define		OP_STS_7 	 7U
#define		OP_STS_8 	 8U

#define OP_ERR		0U
#define OP_SUCCESS	1U
/*---------------------------- Switch Support Function ----------------------*/
#define		MICROCHIP_ARM_ENV	TRUE
#define     AUTO_MATCH_ADDRESS  TRUE
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

