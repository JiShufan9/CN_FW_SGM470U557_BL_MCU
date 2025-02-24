/******************************************************************************
;       Program     : I2c0SlaveApp.h
;       Function    : Declare and Define I2C Slave Function
;       Chip        : Microchip ATSAMC21N17A
;       Clock       : Internal 48MHz
;       Date        : 2021 / 07 / 12
;       Author      : Fenderson Lu
******************************************************************************/
#ifndef I2c0SlaveApp_H
#define I2c0SlaveApp_H
/*---------------------------- Include Library -------------------------------*/
#include "hal/inc/I2CSDriver.h"
#include "app/inc/MainApp.h"
/*---------------------------- Define Constant -------------------------------*/
#define     ADDR_SLAVE                  0x12U
#define     TIMES_APP_MEM               (uint32_t)(SIZE_APP_BASE / LEN_READ_MEM)        /* SIZE_APP_MEM / SIZE_APP_MEM_BLOCK = 64KB/64B = 1024 times, read APP memory 64KB memory */
#define     ERASE_KEY                   0xA5U
#define     GM_STYLE        1
#define     BOSCH_STYLE     2
#define     CMD_STYLE       BOSCH_STYLE

/* SGM Command Set */
#define     CMD_HW_VER_GET              (uint8_t)(0x00U)
#define     CMD_FIDM_VER_GET            (uint8_t)(0x02U)
#define     CMD_TP_ID_GET               (uint8_t)(0x04U)
#define     CMD_DISPLAY_ID_GET          (uint8_t)(0x05U)
#define     CMD_DISPLAY_BL_CONTROL      (uint8_t)(0x20U)
#define     CMD_UPGRADE_FW_PARAMETER    (uint8_t)(0xC8U)
#define     CMD_FORCE_RST               (uint8_t)(0x31U)
#define     CMD_FIDM_PROGRAM_UPDATE     (uint8_t)(0x34U)
#define     CMD_BL_STATUS               (uint8_t)(0x80U)
#define     CMD_APP_MEM_UNLOCK          (uint8_t)(0x84U)
#define     CMD_APP_MEM_ERASE           (uint8_t)(0x88U)
#define     CMD_FLASH_PAGE_WRITE        (uint8_t)(0x8DU)

#define     CMD_SIZE                    (uint8_t)(12U)
/* ==================== Cmd Length ====================== */
#define CMD_OTHER_MAX                   1U
/* Write command */
#define CMD_DISPLAY_BL_MAX              6U
#define CMD_DATA_START                  1U
#if(CMD_STYLE==BOSCH_STYLE)
#define CMD_FORCE_RST_MAX               2U
#define CMD_MEM_UNLOCK_MAX              5U
#define CMD_MEM_ERASE_MAX               6U
// #define CMD_FLASH_WRITE_MAX             72U
#define CMD_FLASH_WRITE_MAX             2056U
#define CMD_DATA_SIZE_MAX               74U
#define CMD_DATA_LENGTH                 3U
#define CMD_DATA_CRC_L                  4U
#define CMD_DATA_CRC_H                  5U
#elif(CMD_STYLE==GM_STYLE)
#define CMD_FORCE_RST_MAX               4U
#define CMD_MEM_UNLOCK_MAX              7U
#define CMD_MEM_ERASE_MAX               8U
#define CMD_FLASH_WRITE_MAX             74U
#define CMD_DATA_SIZE_MAX               76U
#define CMD_DATA_LENGTH                 5U
#define CMD_DATA_CRC_L                  6U
#define CMD_DATA_CRC_H                  7U
#endif


/* Program Size Setting */
#define     UNIT_KB             1024U
#define     SIZE_64B            64U
#define     SIZE_256B           256U
#define     SIZE_2048B          2048U    
#define     SIZE_1KB            (1U * UNIT_KB)
#define     SIZE_4KB            (4U * UNIT_KB)
#define     SIZE_64KB           (64U * UNIT_KB)
#define     SIZE_128KB          (128U * UNIT_KB)
#define     SIZE_256KB          (256U * UNIT_KB)
#define     SIZE_APP_BASE       SIZE_64KB           /* APP memory size */
#define     SET_APP_BLOCK       SIZE_64B
#define     SIZE_APP_MEM_BLOCK  SET_APP_BLOCK       /* APP memory block */

/* Length Assign */
#define     LEN_ERASE           (uint32_t)(SIZE_APP_BASE/SIZE_256B) /* ERASE unit are 256B. APP size is 64K. */
#define     LEN_BL_STATUS       2U
#define     LEN_CUSTOMER_ID     (uint32_t)(SIZE_FW_CHKSUM)
#define     LEN_APP_CRC32       SIZE_APP_CRC32
#define     LEN_READ_MEM        SET_APP_BLOCK                       /* Read unit is 64B */
#define     LEN_RESERVED        32U                                 /* Reserved 32 bytes for Customer_ID, MCU_Ver and MCU_CRC32 */
#define     LEN_LAST            1U

/* UART Packets Length */
#define     LEN_CRC16       2U
#define     LEN_CRC16_L     1U
#define     LEN_CRC16_H     1U
#define     LEN_IRQ_STATUS  1U

/* IRQ Response */
#define     IRQ_STATUS_RESPONSE_DISABLE     (uint8_t)(0x00U)
#define     IRQ_STATUS_RESPONSE_ENABLE      (uint8_t)(0x01U)

/* Memory Address Setting */
#define     ADDR_APP_START      0x8000U     /* 0x4000U for 16KB, 0x8000U for 32KB */
#define     ADDR_CUSTOMER_ID    0x17FE0U    /* 0x13FE0 ~ 0x13FE7 (8 bytes) for 16KB, 0x17FE0 ~ 0x17FE7 (8 bytes) for 32KB */    
#define     ADDR_FIDM_VER       0x17FF0U    /* 0x13FF0 ~ 0x13FF7 (8 bytes) for 16KB, 0x17FF0 ~ 0x17FF7 (8 bytes) for 32KB */
#define     ADDR_APP_CRC32      0x17FFCU    /* 0x13FFC ~ 0x13FFF (4 bytes) for 16KB, 0x17FFC ~ 0x17FFF (4 bytes) for 32KB */

#define ADDR_START              0u
#define SIZE_TOTAL_BASE         (833U * UNIT_KB)

/* Bootloader Status Flags Packets - Bootloader Status 1 */
#define     SET_BL_ACTIVE               0x01U
#define     SET_APP_UNLOCK              0x02U
#define     SET_APP_ERASE               0x04U
#define     SET_FLASH_WRITE_SUCCESS     0x08U
#define     SET_SESSION_KEY_ERR         0x10U
#define     SET_ERASE_KEY_ERR           0x20U
#define     SET_CRC16_ERR               0x40U
#define     SET_VOLT_ERR                0x80U

/* Bootloader Status Flags Packets - Bootloader Status 2 */
#define     SET_PROGRAMMING_ERROR       0x01U
#define     SET_UNKNOWN_ERROR           0x02U

/*IRQ Control */
#define     SET_IRQ_RELEASE             0x00U
#define     SET_IRQ_ASSERT              0x01U

#define I2C_NONE       0U
#define I2C_READ       1U
#define I2C_WRITE      2U

/* BL Control */
#define CMD_COUNTER_FILTER  0x0FU
#define DIAGNOSIS_COUNTER   0xF0U
#define BM_VALUE_SIZE   2U
#define BACKLIGHT_100NITS   0x1E1EU
#define BACKLIGHT_FILTER_MAX    0xFFFCU 

#define BL_CMD_INDEX_DA     0U
#define BL_CMD_INDEX_CRC    1U
#define BL_CMD_INDEX_DID    2U
#define BL_CMD_INDEX_DATAL  3U
#define BL_CMD_INDEX_DATAH  4U
#define BL_CMD_INDEX_CT     5U

#define BL_CMD_CRC_SIZE     0x0004U

/*OTA每帧数据长度	2048Bytes*/
#define SINGLE_PACKET_DATA_LEN_LSB				0x00U
#define SINGLE_PACKET_DATA_LEN_MSB				0x08U
/*OTA轮询间隔	5ms*/
#define POLLING_INTERVAL_LSB					0x05U
#define POLLING_INTERVAL_MSB					0x00U

#define RESERVED								0x00U

/*---------------------------- Declare Enum ---------------------------------*/
enum SizeAssign{
    SIZE_FW_CHKSUM = 8U,
    SIZE_APP_CRC32 = 4U
};

enum DeviceId{
    ID_TP = 0x99U,
    ID_DISPLAY = 0xC7U
};

enum DefaultValures{
    DEFAULT_BL_STATUS_1 = 0x00U,
    DEFAULT_BL_STATUS_2 = 0x00U,
    DEFAULT_CLEAR_VALUES = 0x00U
};

enum ResetDevice{
    RST_TOUCH = 0x01U,
    RST_FIDM = 0x02U
};

enum WritePackets{
    /* Boot Keys */
    P_CMD = 0U,
    P_BOOT_KEY0_L = 1U,
    P_BOOT_KEY0_H = 2U,
    P_BOOT_KEY1_L = 3U,
    P_BOOT_KEY1_H = 4U,

    /* Program Update (PU) */
    PU_CMD = 0U,
    PU_BOOT_KEY0_L = 1U,
    PU_BOOT_KEY0_H = 2U,
    PU_BOOT_KEY1_L = 3U,
    PU_BOOT_KEY1_H = 4U,
#if(CMD_STYLE == GM_STYLE)
    PU_ADDR_0 = 5U,
    PU_ADDR_1 = 6U,
    PU_ADDR_2 = 7U,
    PU_DATA = 8U,
    PU_CRC16_L = 72U,
    PU_CRC16_H = 73U,
#elif (CMD_STYLE == BOSCH_STYLE)
    PU_ADDR_0 = 3U,
    PU_ADDR_1 = 4U,
    PU_ADDR_2 = 5U,
    PU_DATA = 6U,
    PU_CRC16_L = 70U,
    PU_CRC16_H = 71U,
#endif  

    /* Erase */
    W_CMD = 0U,
#if(CMD_STYLE==GM_STYLE)    
    W_ERASE_KEY = 5U,
#elif(CMD_STYLE==BOSCH_STYLE)
    W_ERASE_KEY = 3U,
#endif    

/* IRQ */
    IRQ_CMD = 0U,
    IRQ_DATA = 1U,

/* Force Reset */
    FR_CMD = 0U,
    FR_DATA = 1U
}; 

enum ReadPackets{
/* Display Backlight Duty Cycle */
    R_BL_DUTY_L = 1U,
    R_BL_DUTY_H = 2U,

/* App CRC32 */
    R_APP_CRC32_L = 0U,
    R_APP_CRC32_M_L = 1U,
    R_APP_CRC32_M_H = 2U,
    R_APP_CRC32_H = 3U, 

/* App CRC16 */
    R_CRC16_L = 0U,
    R_CRC16_H = 1U, 

/* Bootloader Status */
    R_BL_STATUS_1 = 0U,
    R_BL_STATUS_2 = 1U,
    R_IRQ_STATUS = 2U,  

/* Hardware Version */
    R_HW_VER_L = 0U,
    R_HW_VER_H = 1U,

/* FIDM Firmware Version */
    R_FIDM_VER_L = 0U,
    R_FIDM_VER_H = 1U,

/* Controller ID */
    R_TP_MCU_ID = 0U,
    R_DISPLAY_ID = 0U,

/* Upgrade Firmware Parameter*/
    R_CRC8 = 0U,
    R_SINGLE_PACKET_DATA_LEN_LSB = 1U,
    R_SINGLE_PACKET_DATA_LEN_MSB = 2U,
    R_POLLING_INTERVAL_LSB = 3U,
    R_POLLING_INTERVAL_MSB = 4U,
    R_Reserved0 = 5U,
    R_Reserved1 = 6U
};
/*---------------------------- Support Function ------------------------------*/
#define     I2c0SlaveApp_Irq_Disable(u8Irq)     (NVIC_DisableIRQ(u8Irq))
/*---------------------------- Data Structure --------------------------------*/
/*---------------------------- Declare Function ------------------------------*/
extern uint8_t I2c0SlaveApp_Init(void);
extern uint8_t I2c0SlaveApp_BL_Status1_Clear(uint8_t u8Status);
extern uint8_t I2c0SlaveApp_BL_Status2_Clear(uint8_t u8Status);
extern bool I2c0SlaveApp_Crc32_Check(uint32_t u32Size);
extern uint8_t I2c0SlaveApp_BL_Status1_Set(uint8_t u8Status);
#if 0
extern uint8_t I2c0SlaveApp_BL_Programming_Error_Set(uint8_t u8Status);
#endif
extern uint8_t I2c0SlaveApp_Rx_TASK_Process(void);
extern uint8_t I2c0SlaveApp_Slave_Rx_Compare(uint32_t u32StartAddr, uint32_t u32CompareSize, uint8_t *pu8SrcBuff);
extern uint8_t I2c0SlaveApp_Rx_Program_Process(void);
extern uint8_t I2cSlaveApp_Slave_DeInitial(void);
extern bool I2c0SlaveApp_Callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT event, uintptr_t contextHandle);
extern uint16_t I2cSlaveApp_GetHostBL(void);
#endif
