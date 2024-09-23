/* ************************************************************************** 
;        Program    :   .h
;        Function   :   
;        chip       :   
;        clock      :   
;        Date       :   2024 / 05 / 29
;        Author     :   chenaoli
;        Description:      
;    
 *****************************************************************************/

#ifndef __SOURCE_IC_SPI_H__
#define __SOURCE_IC_SPI_H__

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "main.h"

#define SOURCE_IC_SPI_CLASS_EN          ENABLE
#if (SOURCE_IC_SPI_CLASS_EN == ENABLE)
/* ************************************************************************** */
/* Section: Macro Definition                                                  */
/* ************************************************************************** */
#define SPI_INTERRUPT_MODE      ENABLE_OFF

#define FLAG_W  0u
#define FLAG_R  1u

#define DEISID_ALL      3U
#define DESID_TERTIARY  2U
#define DESID_SECONDARY 1U
#define DESID_PRIMARY   0U

#define SOURCE_IC_CMD_BUF_MAX 16u

#define PAGE_SELECT_REG 0x1EU
/* page define start */
#define CMD0_Page1  0x01U /* Digital Gamma (Current LUT R) */
#define CMD0_Page2  0x02U /* Digital Gamma (Current LUT R) */
#define CMD0_Page3  0x03U /* Digital Gamma (Current LUT G) */
#define CMD0_Page4  0x04U /* Digital Gamma (Current LUT G) */
#define CMD0_Page5  0x05U /* Digital Gamma (Current LUT B) */
#define CMD0_Page6  0x06U /* Digital Gamma (Current LUT B) */
#define CMD0_Page7  0x07U /* Digital Gamma (Current Gamma Positive) */
#define CMD0_Page8  0x08U /* Digital Gamma (Current Gamma Positive) */
#define CMD0_Page9  0x09U /* Digital Gamma (Current Gamma Negative) */
#define CMD0_PageA  0x0AU /* Digital Gamma (Current Gamma Negative) */
#define CMD1_Page0  0x10U /* Voltage */
#define CMD1_Page1  0x11U /* Digital Gamma (Target LUT R) */
#define CMD1_Page2  0x12U /* Digital Gamma (Target LUT R) */
#define CMD1_Page3  0x13U /* Digital Gamma (Target LUT G) */
#define CMD1_Page4  0x14U /* Digital Gamma (Target LUT G) */
#define CMD1_Page5  0x15U /* Digital Gamma (Target LUT B) */
#define CMD1_Page6  0x16U /* Digital Gamma (Target LUT B) */
#define CMD1_Page7  0x17U /* Digital Gamma (Target Gamma Positive) */
#define CMD1_Page8  0x18U /* Digital Gamma (Target Gamma Positive) */
#define CMD1_Page9  0x19U /* Digital Gamma (Target Gamma Negative) */
#define CMD1_PageA  0x1AU /* Digital Gamma (Target Gamma Negative) */
#define CMD1_PageB  0x1BU /* I/F, Resolution */
#define CMD1_PageC  0x1CU /* Interface Setting */
#define CMD1_PageF  0x1FU /* User ID */
#define CMD2_Page0  0x20U /* GRB, STBYB, BIST, Temperature Compensation */
#define CMD2_Page1  0x21U /* I/F Control, OTP related */
#define CMD2_Page2  0x22U /* ASIL ASIL */
#define CMD2_Page3  0x23U /* ASIL ASIL */
#define CMD2_Page4  0x24U /* CGIN Width Detection ASIL */
#define CMD2_Page7  0x27U /* OTP related */
#define CMD2_Page9  0x29U /* ASIL ASIL */
#define CMD2_PageB  0x2BU /* ASIL FLAG, IC Status ASIL */
#define CMD3_Page0  0x30U /* Power Control */
#define CMDD_Page9  0xD9U /* VIDEO CRC ASIL */
#define CMDD_PageA  0xDAU /* VIDEO CRC ASIL */
#define CMDD_PageB  0xDBU /* VIDEO CRC ASIL */
#define CMDD_PageC  0xDCU /* VIDEO CRC ASIL */

/* page define end */

/* ************************************************************************** */
/* Section: Enum                                                              */
/* ************************************************************************** */


/* ************************************************************************** */
/* Section: Struct Typedef                                                    */
/* ************************************************************************** */
typedef union
{
    uint8_t _c[1];
    struct 
    {
        uint8_t Addr    : 5;
        uint8_t DesId   : 2;
        uint8_t WRFlag  : 1;
        
        uint8_t u8DataLen; /* not inlcude cmd byte */
        uint8_t u8Buf[SOURCE_IC_CMD_BUF_MAX];
    }_s;
}TuSourceIcCmd;


/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */



/* ************************************************************************** */
/* Section: Interface Functions                                               */
/* ************************************************************************** */
void SourceIcSpiIf_Init(void);
// void SourceIcSpiIf_MainFunction(void);
uint8_t SourceIcSpiIf_SpiWriteRead(const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,size_t read_size);
uint8_t SourceIcSpiIf_BypassOp(uint8_t txBuf[],uint8_t u8TxLen,uint8_t rxBuf[],uint8_t u8RxLen);

#endif
#endif
