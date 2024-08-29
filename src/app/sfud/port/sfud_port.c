

#include "sfud.h"
#include <stdarg.h>

#include "hal/inc/plib_sercom6_spi_master.h"
#include <string.h>
#include "app/inc/WatchDogApp.h"
#include "app/inc/SourceIcSpiIf.h"

#ifdef SFUD_DEBUG_MODE
static char log_buf[256];
#endif

uint8_t sfud_Dummy = 0u;

uint8_t feed_dog(void)
{
    (void)WatchDogApp_Clean(NOTHING);
    return TRUE;
}

//static void spi_lock(const sfud_spi *spi) {
//    __disable_irq();
//}
//
//static void spi_unlock(const sfud_spi *spi) {
//    __enable_irq();
//}

/* about 100 microsecond delay */
uint32_t sfud_delayCnt = 50U;
static void sfud_retry_delay(void) {
    sfud_delayCnt = 50U;
    while(sfud_delayCnt > 0U)
    {
        sfud_delayCnt--;
    }

}

/**
 * SPI write data then read data
 */
// LDRA_EXCLUDE_START 35 S
static sfud_err spi_write_read(const sfud_spi *spi, const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,
        size_t read_size) {
    sfud_err result = SFUD_SUCCESS;
    /**
     * add your spi write and read code
     */

    if (write_size > 0U) {
        SFUD_ASSERT(write_buf);
    }
    if (read_size > 0U) {
        SFUD_ASSERT(read_buf);
    }

   if(TRUE != SourceIcSpiIf_SpiWriteRead(write_buf,write_size,read_buf,read_size))
   {
        result = SFUD_ERR_TIMEOUT;
   }

    (void)spi;
    return result;
}
// LDRA_EXCLUDE_END 35 S
#ifdef SFUD_USING_QSPI
/**
 * read flash data by QSPI
 */
static sfud_err qspi_read(const struct __sfud_spi *spi, uint32_t addr, sfud_qspi_read_cmd_format *qspi_read_cmd_format,
        uint8_t *read_buf, size_t read_size) {
    sfud_err result = SFUD_SUCCESS;

    /**
     * add your qspi read flash data code
     */

    return result;
}
#endif /* SFUD_USING_QSPI */



//static spi_user_data spi1 = { .spix = SPI1, .cs_gpiox = GPIOC, .cs_gpio_pin = GPIO_Pin_4 };
sfud_err sfud_spi_port_init(sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;

    /**
     * add your port spi bus and device object initialize code like this:
     * 1. rcc initialize
     * 2. gpio initialize
     * 3. spi device initialize
     * 4. flash->spi and flash->retry item initialize
     *    flash->spi.wr = spi_write_read;     Required
     *    flash->spi.qspi_read = qspi_read;     Required when QSPI mode enable
     *    flash->spi.lock = spi_lock;
     *    flash->spi.unlock = spi_unlock;
     *    flash->spi.user_data = &spix;
     *    flash->retry.delay = null;
     *    flash->retry.times = 10000;  Required
     */
    
    

    switch (flash->index) {
    case SFUD_SOURCE_IC_EXT_FLS_INDEX: 
        /* RCC 初始化 */
        // ClockApp中配置
        /* GPIO 初始化 */
        // wakeupCtrlApp中配置
        /* 同步 Flash 移植所需的接口及数据 */
        flash->spi.wr = spi_write_read;
        // flash->spi.lock = spi_lock;
        // flash->spi.unlock = spi_unlock;
        flash->spi.user_data = NULL;
        /* about 100 microsecond delay */
        flash->retry.delay = sfud_retry_delay;
        /* adout 60 seconds timeout */
        flash->retry.times = 60U * 10000U;
        break;
    default:
        /* nothing */
        break;
    }

    return result;
}

#ifdef SFUD_DEBUG_MODE
/**
 * This function is print debug info.
 *
 * @param file the file which has call this function
 * @param line the line number which has call this function
 * @param format output format
 * @param ... args
 */
void sfud_log_debug(const char *file, const long line, const char *format, ...) {
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    printf("[SFUD](%s:%ld) ", file, line);
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    printf("%s\n", log_buf);
    va_end(args);
}
#endif

#ifndef SFUD_OPTIMIZE_SIZE_MODE
/**
 * This function is print routine info.
 *
 * @param format output format
 * @param ... args
 */
//  reserved void sfud_log_info(const char *format, ...) {
//     va_list args;

     /* args point to the first variable parameter */
//     va_start(args, format);
//     printf("[SFUD]");
      /* must use vprintf to print */
//     vsnprintf(log_buf, sizeof(log_buf), format, args);
//     printf("%s\n", log_buf);
//     va_end(args);
// }
#endif


