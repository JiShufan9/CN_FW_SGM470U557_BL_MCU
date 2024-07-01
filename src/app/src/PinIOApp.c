/******************************************************************************
;       Program		: PinIOApp.c
;       Function	: GPIO Configure and Setting 
;       Chip		: Microchip ATSAMC21N17A
;       Clock		: Internal 48MHz
;       Date		: 2021 / 06 / 08
;       Author		: Joel Wang & Fenderson Lu
******************************************************************************/
/*---------------------------- Include File ---------------------------------*/
#include "app/inc/MainApp.h"	
#include "app/inc/PinIOApp.h"
/*---------------------------- Declare External Var -------------------------*/
static uint8_t u8HwStatusFlag;
/*---------------------------- Start Program --------------------------------*/
/******************************************************************************
;       Function Name			:	bool PinIOApp_High(int8_t i8Port, uint8_t u8Pin)
;       Function Description	:	Set pin is level high.
;       Parameters				:	[u8Port] - Input GPIO port.
;									[u8Pin] - Input GPIO pin.
;       Return Values			:	true
;		Source ID				:	GM_BL_PINIO-002
******************************************************************************/
bool PinIOApp_High(int8_t i8Port, uint8_t u8Pin)
{
    bool bStatus;

    if(i8Port == PORT_A)
    {
        PORT_REGS->GROUP[PORT_A].PORT_OUTSET = (0x00000001U << u8Pin);
        bStatus = true;
    }
    else if(i8Port == PORT_B)
    {
        PORT_REGS->GROUP[PORT_B].PORT_OUTSET = (0x00000001U << u8Pin);
        bStatus = true;    
    }
    else if(i8Port == PORT_C)
    {
        PORT_REGS->GROUP[PORT_C].PORT_OUTSET = (0x00000001U << u8Pin);
        bStatus = true;    
    }
    else
    {
        bStatus = false;
    }
    return bStatus;
}

/******************************************************************************
;       Function Name			:	bool PinIOApp_Low(int8_t i8Port, uint8_t u8Pin)
;       Function Description	:	Set pin is level low.
;       Parameters				:	[u8Port] - Input GPIO port.
;									[u8Pin] - Input GPIO pin.
;       Return Values			:	true
;		Source ID				:	GM_BL_PINIO-003
******************************************************************************/
bool PinIOApp_Low(int8_t i8Port, uint8_t u8Pin)
{
    bool bStatus;
    if((i8Port == PORT_A) || (i8Port == PORT_B)|| (i8Port == PORT_C))
    {
        PORT_REGS->GROUP[i8Port].PORT_OUTCLR = (1U << u8Pin);
        bStatus = true;
    }
    else
    {
        bStatus = false;
    }
    return bStatus;
}
/******************************************************************************
;       Function Name			:	bool PinIOApp_System_Power(uint8_t u8Switch)
;       Function Description	:	Switch system power on or off.
;       Parameters				:	[u8Switch] - Set system power on or off.
;       Return Values			:	true
;		Source ID				:	GM_BL_PINIO-006
******************************************************************************/
bool PinIOApp_System_Power(uint8_t u8Switch)
{
	switch(u8Switch)
	{
		case SYS_PWR_ON:
            (void)PinIOApp_Low(portMPQ3365A_EN, pinMPQ3365A_EN);
            (void)PinIOApp_Low(portWAKE_REQUEST_V_RCV, pinWAKE_REQUEST_V_RCV);          /* Disable WakeUp Host Pin */
            (void)PinIOApp_High(portBATT_SENSE_EN, pinBATT_SENSE_EN);       
            (void)PinIOApp_High(portMCU_3V3_EN, pinMCU_3V3_EN);
            (void)FunApp_Delay_Millisecond(10, MODE_SYSTICK);   /* Delay 10ms */                 
            (void)PinIOApp_High(portMCU_1V8_EN, pinMCU_1V8_EN);                 
            (void)PinIOApp_High(portMCU_1V1_EN, pinMCU_1V1_EN);
            (void)PinIOApp_High(portLCD_BIAS,pinLCD_BIAS);
            (void)PinIOApp_High(portMCU_1V35_EN,pinMCU_1V35_EN);
            (void)FunApp_Delay_Millisecond(2, MODE_SYSTICK);    /* Delay 2ms */
            (void)PinIOApp_High(portPDB, pinPDB);
            (void)PinIOApp_High(portMCU_INT, pinMCU_INT);
            (void)FunApp_Delay_Millisecond(2, MODE_SYSTICK);                            /* Delay 2ms */
            (void)PinIOApp_High(portXON, pinXON);
            (void)FunApp_Delay_Millisecond(26, MODE_SYSTICK);                        /* Delay 8ms */     
            (void)PinIOApp_High(portXRES_TP, pinXRES_TP);
            (void)PinIOApp_High(portTCON_RESET, pinTCON_RESET); 
            (void)PinIOApp_High(portDRIVER_RESET, pinDRIVER_RESET);
            (void)FunApp_Delay_Millisecond(8, MODE_SYSTICK);    /* Delay 1ms */         
            (void)PinIOApp_High(portMPQ3365A_PWMI, pinMPQ3365A_PWMI);     
            (void)FunApp_Delay_Millisecond(2, MODE_SYSTICK);    /* Delay 2ms */ 
            (void)PinIOApp_High(portMPQ3365A_EN, pinMPQ3365A_EN);        
		break;
		
		case SYS_PWR_OFF:
            (void)PinIOApp_Low(portWAKE_REQUEST_V_RCV, pinWAKE_REQUEST_V_RCV);
            (void)PinIOApp_Low(portMCU_INT, pinMCU_INT);
            (void)PinIOApp_Low(portMPQ3365A_EN, pinMPQ3365A_EN);
            (void)PinIOApp_Low(portMPQ3365A_EN, pinMPQ3365A_EN);
            (void)PinIOApp_Low(portMPQ3365A_PWMI, pinMPQ3365A_PWMI);
            (void)FunApp_Delay_Millisecond(1, MODE_SYSTICK);    /* Delay 1ms */
            (void)FunApp_Delay_Millisecond(1, MODE_SYSTICK);    /* Delay 1ms */
            (void)PinIOApp_Low(portDRIVER_RESET, pinDRIVER_RESET);
            (void)PinIOApp_Low(portTCON_RESET, pinTCON_RESET);
            (void)PinIOApp_Low(portXRES_TP, pinXRES_TP);
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK);  /* Delay 1ms */
            (void)PinIOApp_Low(portXON, pinXON);
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK);  /* Delay 1ms */
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK);  /* Delay 1ms */
            (void)PinIOApp_Low(portPDB, pinPDB);
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK);  /* Delay 1ms */
            (void)PinIOApp_Low(portMCU_1V35_EN, pinMCU_1V35_EN);
            (void)PinIOApp_Low(portLCD_BIAS, pinLCD_BIAS);
            (void)PinIOApp_Low(portMCU_1V1_EN, pinMCU_1V1_EN);
            (void)PinIOApp_Low(portMCU_1V8_EN, pinMCU_1V8_EN);
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK); /* Delay 1ms */
            (void)PinIOApp_Low(portMCU_3V3_EN, pinMCU_3V3_EN);
            (void)PinIOApp_Low(portBATT_SENSE_EN, pinBATT_SENSE_EN);
            (void)FunApp_Delay_Millisecond(1U, MODE_SYSTICK); /* Delay 5ms */                           				
		break;
        
		default:
			/* NOTHING */
		break;
	}
    
	(void)(u8Switch);
	return true;
}

/******************************************************************************
;       Function Name			:	uint8_t PinIOApp_Init_IPC(uint8_t u8Para)
;       Function Description	:	Initialize all pin.
;       Parameters				:	[u8Para] - NOTHING
;       Return Values			:	NOTHING
;		Source ID				:	GM_BL_PINIO-005
******************************************************************************/
uint8_t PinIOApp_Init(uint8_t u8Para)
{
   /************************** GROUP 0 Initialization *************************/
   PORT_REGS->GROUP[0].PORT_DIR = 0x01FEB416U;
   PORT_REGS->GROUP[1].PORT_OUT = 0x02050BA0U;
   PORT_REGS->GROUP[0].PORT_PINCFG[3] = 0x3U;
   PORT_REGS->GROUP[0].PORT_PINCFG[5] = 0x1U;
   PORT_REGS->GROUP[0].PORT_PINCFG[6] = 0x3U;
   PORT_REGS->GROUP[0].PORT_PINCFG[7] = 0x1U;
   PORT_REGS->GROUP[0].PORT_PINCFG[8] = 0x1U;
   PORT_REGS->GROUP[0].PORT_PINCFG[9] = 0x1U;
   PORT_REGS->GROUP[0].PORT_PINCFG[11] = 0x2U;
   PORT_REGS->GROUP[0].PORT_PINCFG[16] = 0x2U;
   PORT_REGS->GROUP[0].PORT_PINCFG[17] = 0x2U;
   PORT_REGS->GROUP[0].PORT_PINCFG[25] = 0x2U;
   PORT_REGS->GROUP[0].PORT_PINCFG[27] = 0x2U;
   PORT_REGS->GROUP[0].PORT_PINCFG[28] = 0x2U;

   PORT_REGS->GROUP[0].PORT_PMUX[1] = 0x10U;
   PORT_REGS->GROUP[0].PORT_PMUX[2] = 0x10U;
   PORT_REGS->GROUP[0].PORT_PMUX[3] = 0x10U;
   PORT_REGS->GROUP[0].PORT_PMUX[4] = 0x22U;
   PORT_REGS->GROUP[0].PORT_PMUX[6] = 0x22U;

   /************************** GROUP 1 Initialization *************************/
   PORT_REGS->GROUP[1].PORT_DIR = 0x035CCF54U;
   PORT_REGS->GROUP[1].PORT_OUT = 0x00AB3089U;
   PORT_REGS->GROUP[1].PORT_PINCFG[0] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[1] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[3] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[5] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[7] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[9] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[12] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[13] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[16] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[17] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[21] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[23] = 0x2U;
   PORT_REGS->GROUP[1].PORT_PINCFG[30] = 0x1U;
   PORT_REGS->GROUP[1].PORT_PINCFG[31] = 0x1U;

   PORT_REGS->GROUP[1].PORT_PMUX[1] = 0x10U;
   PORT_REGS->GROUP[1].PORT_PMUX[6] = 0x22U;
   PORT_REGS->GROUP[1].PORT_PMUX[8] = 0x22U;
   PORT_REGS->GROUP[1].PORT_PMUX[15] = 0x22U;

   /************************** GROUP 2 Initialization *************************/
   PORT_REGS->GROUP[2].PORT_DIR = 0x122B2267U;
   PORT_REGS->GROUP[2].PORT_OUT = 0x0C00F089U;
   PORT_REGS->GROUP[2].PORT_PINCFG[3] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[5] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[7] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[8] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[10] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[11] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[12] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[14] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[15] = 0x1U;
   PORT_REGS->GROUP[2].PORT_PINCFG[18] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[20] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[24] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[26] = 0x2U;
   PORT_REGS->GROUP[2].PORT_PINCFG[27] = 0x2U;

   PORT_REGS->GROUP[2].PORT_PMUX[1] = 0x10U;
   PORT_REGS->GROUP[2].PORT_PMUX[4] = 0x22U;
   PORT_REGS->GROUP[2].PORT_PMUX[5] = 0x22U;
   PORT_REGS->GROUP[2].PORT_PMUX[6] = 0x22U;
   PORT_REGS->GROUP[2].PORT_PMUX[7] = 0x22U;
                
	(void)(u8Para);
	return  (u8Para);
}

/******************************************************************************
;       Function Name           :   uint8_t PinIOApp_Hw_Ver_Check(uint8_t u8Para)
;       Function Description    :   Check HW version.
;       Parameters              :   [u8Para] - NOTHING
;       Return Values           :   NOTHING
;       Source ID               :   SGM_BL_PINIO-008
******************************************************************************/
uint8_t PinIOApp_Hw_Ver_Check(uint8_t u8Para)
{
    if(PortDrvier_PinRead(IO_PCBA_A3) == (uint8_t)(PIN_LEVEL_HIGH))
    {
        u8HwStatusFlag = (uint8_t)(NONLOCAL_DIMMING);       /* A3 Pin is level high, the HW non-local dimming version */
    }
    else
    {
        u8HwStatusFlag = (uint8_t)(LOCAL_DIMMING);          /* A3 Pin is level low, the HW is local dimming version */
    }

    (void)(u8Para);
    return u8Para;
}


/******************************************************************************
;       Function Name           :   uint8_t PinIOApp_HwStatusFlag_Get(void)
;       Function Description    :   Get HW status.
;       Parameters              :   voio
;       Return Values           :   HW status
;                                   0x01 = Local dimming.
;                                   0x02 = Non-local dimming.
;       Source ID               :   SGM_BL_PINIO-010
******************************************************************************/
uint8_t PinIOApp_HwStatusFlag_Get(void)
{
    return u8HwStatusFlag;
}
