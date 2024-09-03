/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016-2018, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: serial flash operate functions by SFUD lib.
 * Created on: 2016-04-23
 */

#include "sfud.h"
#include <string.h>

/* send dummy data for read data */
#define DUMMY_DATA                               0xFF

#ifndef SFUD_FLASH_DEVICE_TABLE
#error "Please configure the flash device information table in (in sfud_cfg.h)."
#endif

/* user configured flash device information table */
static sfud_flash flash_table[1] = SFUD_FLASH_DEVICE_TABLE;
#ifndef SFUD_OPTIMIZE_SIZE_MODE
/* supported manufacturer information table */
static const sfud_mf mf_table[] = SFUD_MF_TABLE;
#endif

#ifdef SFUD_USING_FLASH_INFO_TABLE
/* supported flash chip information table */
static const sfud_flash_chip flash_chip_table[] = SFUD_FLASH_CHIP_TABLE;
#endif



static sfud_err software_init(const sfud_flash *flash);
static sfud_err hardware_init(sfud_flash *flash);
static sfud_err page256_or_1_byte_write(const sfud_flash *flash, uint32_t addr, size_t size, uint16_t write_gran,
        const uint8_t *data);
static sfud_err wait_busy(const sfud_flash *flash);
static sfud_err reset(const sfud_flash *flash);
static sfud_err read_jedec_id(sfud_flash *flash);
static sfud_err set_write_enabled(const sfud_flash *flash, bool enabled);
static sfud_err set_4_byte_address_mode(sfud_flash *flash, bool enabled);
static void make_address_byte_array(const sfud_flash *flash, uint32_t addr, uint8_t *array);

/* ../port/sfup_port.c */
#ifdef SFUD_DEBUG_MODE
extern void sfud_log_debug(const char *file, const long line, const char *format, ...);
#endif
#ifndef SFUD_OPTIMIZE_SIZE_MODE
// extern void sfud_log_info(const char *format, ...);   reserved
#endif

/**
 * SFUD initialize by flash device
 *
 * @param flash flash device
 *
 * @return result
 */
static sfud_err sfud_device_init(sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;

    
    /* hardware initialize */
    result = hardware_init(flash);
    if (result == SFUD_SUCCESS) {
        result = software_init(flash);
    }
    if (result == SFUD_SUCCESS) {
        flash->init_ok = true;
        /* SFUD_INFO("%s flash device initialized successfully.", flash->name); */
    } else {
        flash->init_ok = false;
        __NOP();
        __NOP();
        /* SFUD_INFO("Error: %s flash device initialization failed.", flash->name); */
    }

    return result;
}

/**
 * SFUD library initialize.
 *
 * @return result
 */
sfud_err sfud_init(void) {
    sfud_err cur_flash_result, all_flash_result = SFUD_SUCCESS;
    size_t i;

    /* SFUD_DEBUG("Start initialize Serial Flash Universal Driver(SFUD) V%s.", SFUD_SW_VERSION); */
    /* initialize all flash device in flash device table */
    for (i = 0U; i < (sizeof(flash_table) / sizeof(sfud_flash)); i++) {
        /* initialize flash device index of flash device information table */
        flash_table[i].index = i;
        cur_flash_result = sfud_device_init(&flash_table[i]);

        if (cur_flash_result != SFUD_SUCCESS) {
            all_flash_result = cur_flash_result;
        }
    }

    return all_flash_result;
}

/**
 * get flash device by its index which in the flash information table
 *
 * @param index the index which in the flash information table  @see flash_table
 *
 * @return flash device
 */
sfud_flash * pSfudFlash;
sfud_flash *sfud_get_device(size_t index) {
    
    if (index < sfud_get_device_num()) {
        pSfudFlash = &flash_table[index];
    } else {
        pSfudFlash = NULL;
    }
    return pSfudFlash;
}

/**
 * get flash device total number on flash device information table  @see flash_table
 *
 * @return flash device total number
 */
size_t sfud_get_device_num(void) {
    return sizeof(flash_table) / sizeof(sfud_flash);
}

/**
 * get flash device information table  @see flash_table
 *
 * @return flash device table pointer
 */
#if 0
const sfud_flash *sfud_get_device_table(void) {
    return flash_table;
}
#endif


/**
 * hardware initialize
 */
static sfud_err hardware_init(sfud_flash *flash) {

    sfud_err result = SFUD_SUCCESS;
    size_t i;

    SFUD_ASSERT(flash);

    result = sfud_spi_port_init(flash);
    if (result != SFUD_SUCCESS) {
        /* nothing */
    }
    else
    {



        /* SPI write read function must be initialize */
        SFUD_ASSERT(flash->spi.wr);
        /* if the user don't configure flash chip information then using SFDP parameter or static flash parameter table */
        if ((flash->chip.capacity == 0U) || (flash->chip.write_mode == 0U) || (flash->chip.erase_gran == 0U)
                || (flash->chip.erase_gran_cmd == 0U)) {
            /* read JEDEC ID include manufacturer ID, memory type ID and flash capacity ID */
            result = read_jedec_id(flash);
            if (result != SFUD_SUCCESS) {
                /* nothing */
            }
            else
            {



#ifdef SFUD_USING_FLASH_INFO_TABLE
                    /* read SFDP parameters failed then using SFUD library provided static parameter */
                    for (i = 0U; i < (sizeof(flash_chip_table) / sizeof(sfud_flash_chip)); i++) {
                        if ((flash_chip_table[i].mf_id == flash->chip.mf_id)
                                && (flash_chip_table[i].type_id == flash->chip.type_id)
                                && (flash_chip_table[i].capacity_id == flash->chip.capacity_id)) {
                            flash->chip.name = flash_chip_table[i].name;
                            flash->chip.capacity = flash_chip_table[i].capacity;
                            flash->chip.write_mode = flash_chip_table[i].write_mode;
                            flash->chip.erase_gran = flash_chip_table[i].erase_gran;
                            flash->chip.erase_gran_cmd = flash_chip_table[i].erase_gran_cmd;
                            break;
                        }
                    }
#endif



            }
        }
        if (result == SFUD_SUCCESS) 
        {
            if ((flash->chip.capacity == 0U) || (flash->chip.write_mode == 0U) || (flash->chip.erase_gran == 0U)
                    || (flash->chip.erase_gran_cmd == 0U)) {
                /* SFUD_INFO("Warning: This flash device is not found or not supported."); */
                result = SFUD_ERR_NOT_FOUND;
            } else {
#ifndef SFUD_OPTIMIZE_SIZE_MODE
                    const char *flash_mf_name = NULL;
                    /* find the manufacturer information */
                    for (i = 0U; i < (sizeof(mf_table) / sizeof(sfud_mf)); i++) {
                        if (mf_table[i].id == flash->chip.mf_id) {
                            flash_mf_name = mf_table[i].name;
                            break;
                        }
                    }
                    /* print manufacturer and flash chip name */
                    if ((flash_mf_name != NULL) && (flash->chip.name != NULL)) {
                        /* SFUD_INFO("Found a %s %s flash chip. Size is %ld bytes.", flash_mf_name, flash->chip.name,
                                flash->chip.capacity); */
                    } else if (flash_mf_name != NULL) {
                        /* SFUD_INFO("Found a %s flash chip. Size is %ld bytes.", flash_mf_name, flash->chip.capacity); */
                    } else {
                        /* SFUD_INFO("Found a flash chip. Size is %ld bytes.", flash->chip.capacity); */
                    }
#endif
            }
            if (result == SFUD_SUCCESS) 
            {
                /* reset flash device */
                result = reset(flash);
                if (result == SFUD_SUCCESS) {

                    /* The flash all blocks is protected,so need change the flash status to unprotected before write and erase operate. */
                    result = sfud_write_status(flash, true, 0x00);

                    if (result == SFUD_SUCCESS) {

                        /* if the flash is large than 16MB (256Mb) then enter in 4-Byte addressing mode */
                        if (flash->chip.capacity > (1U << 24)) {
                            result = set_4_byte_address_mode(flash, true);
                        } else {
                            flash->addr_in_4_byte = false;
                        }

                    }
                }
            }
        }
    }
    return result;
}

/**
 * software initialize
 *
 * @param flash flash device
 *
 * @return result
 */
static sfud_err software_init(const sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;

    SFUD_ASSERT(flash);

    (void)flash;

    return result;
}

/**
 * read flash data
 *
 * @param flash flash device
 * @param addr start address
 * @param size read size
 * @param data read data pointer
 *
 * @return result
 */
sfud_err sfud_read(const sfud_flash *flash, uint32_t addr, size_t size, uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[5], cmd_size;

    SFUD_ASSERT(flash);
    SFUD_ASSERT(data);
    /* must be call this function after initialize OK */
    SFUD_ASSERT(flash->init_ok);
    /* check the flash address bound */
    if ((addr + size) > flash->chip.capacity) {
        /* SFUD_INFO("Error: Flash address is out of bound."); */
        result = SFUD_ERR_ADDR_OUT_OF_BOUND;
    }
    else
    {
        /* lock SPI */
        if (spi->lock != NULL) {
            spi->lock(spi);
        }

        result = wait_busy(flash);

        if (result == SFUD_SUCCESS) {

            {
                cmd_data[0] = SFUD_CMD_READ_DATA;
                make_address_byte_array(flash, addr, &cmd_data[1]);
                cmd_size = flash->addr_in_4_byte ? 5U : 4U;
                result = spi->wr(spi, cmd_data, cmd_size, data, size);
            }
        }
        /* unlock SPI */
        if (spi->unlock != NULL) {
            spi->unlock(spi);
        }
    }
    return result;
}

/**
 * erase all flash data
 *
 * @param flash flash device
 *
 * @return result
 */
sfud_err sfud_chip_erase(const sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[4];

    SFUD_ASSERT(flash);
    /* must be call this function after initialize OK */
    SFUD_ASSERT(flash->init_ok);
    /* lock SPI */
    if (spi->lock != NULL) {
        spi->lock(spi);
    }

    /* set the flash write enable */
    result = set_write_enabled(flash, true);
    if (result != SFUD_SUCCESS) {
        /* nothing */
    }
    else
    {
        cmd_data[0] = SFUD_CMD_ERASE_CHIP;
        /* dual-buffer write, like AT45DB series flash chip erase operate is different for other flash */
        if (((flash->chip.write_mode) & SFUD_WM_DUAL_BUFFER) > 0U) {
            cmd_data[1] = 0x94U;
            cmd_data[2] = 0x80U;
            cmd_data[3] = 0x9AU;
            result = spi->wr(spi, cmd_data, 4, NULL, 0);
        } else {
            result = spi->wr(spi, cmd_data, 1, NULL, 0);
        }
        if (result != SFUD_SUCCESS) {
            /* SFUD_INFO("Error: Flash chip erase SPI communicate error."); */
        }
        else
        {
            result = wait_busy(flash);
        }   
    }

    /* set the flash write disable */
    (void)set_write_enabled(flash, false);
    /* unlock SPI */
    if (spi->unlock != NULL) {
        spi->unlock(spi);
    }

    return result;
}

/**
 * erase flash data
 *
 * @note It will erase align by erase granularity.
 *
 * @param flash flash device
 * @param addr start address
 * @param size erase size
 *
 * @return result
 */
sfud_err sfud_erase(const sfud_flash *flash, uint32_t addr, size_t size) {


    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[5], cmd_size, cur_erase_cmd;
    size_t cur_erase_size;

    SFUD_ASSERT(flash);
    /* must be call this function after initialize OK */
    SFUD_ASSERT(flash->init_ok);
    /* check the flash address bound */
    if ((addr + size) > flash->chip.capacity) {
        /* SFUD_INFO("Error: Flash address is out of bound."); */
        result = SFUD_ERR_ADDR_OUT_OF_BOUND;
    }
    else
    {

        if ((addr == 0U) && (size == flash->chip.capacity)) {
            result = sfud_chip_erase(flash);
        }
        else
        {

            /* lock SPI */
            if (spi->lock != NULL) {
                spi->lock(spi);
            }

            /* loop erase operate. erase unit is erase granularity */
            while (size > 0U) {
                (void)feed_dog();
                /* if this flash is support SFDP parameter, then used SFDP parameter supplies eraser */

                {
                    cur_erase_cmd = flash->chip.erase_gran_cmd;
                    cur_erase_size = flash->chip.erase_gran;
                }
                /* set the flash write enable */
                result = set_write_enabled(flash, true);
                if (result != SFUD_SUCCESS) {
                    break;
                }
                else
                {

                    cmd_data[0] = cur_erase_cmd;
                    make_address_byte_array(flash, addr, &cmd_data[1]);
                    cmd_size = flash->addr_in_4_byte ? 5U : 4U;
                    result = spi->wr(spi, cmd_data, cmd_size, NULL, 0);
                    if (result != SFUD_SUCCESS) {
                        /* SFUD_INFO("Error: Flash erase SPI communicate error."); */
                        break;
                    }
                    else
                    {
                        result = wait_busy(flash);
                        if (result != SFUD_SUCCESS) {
                            break;
                        }
                        else
                        {
                            /* make erase align and calculate next erase address */
                            if ((addr % cur_erase_size) != 0U) {
                                if (size > (cur_erase_size - (addr % cur_erase_size))) {
                                    size -= cur_erase_size - (addr % cur_erase_size);
                                    addr += cur_erase_size - (addr % cur_erase_size);
                                } else {
                                    break;
                                }
                            } else {
                                if (size > cur_erase_size) {
                                    size -= cur_erase_size;
                                    addr += cur_erase_size;
                                } else {
                                    break;
                                }
                            }
                        }

                    }
                }
            }

            /* set the flash write disable */
            (void)set_write_enabled(flash, false);
            /* unlock SPI */
            if (spi->unlock != NULL) {
                spi->unlock(spi);
            }
        }
	}
    return result;
}

/**
 * write flash data (no erase operate) for write 1 to 256 bytes per page mode or byte write mode
 *
 * @param flash flash device
 * @param addr start address
 * @param size write size
 * @param write_gran write granularity bytes, only support 1 or 256
 * @param data write data
 *
 * @return result
 */
static sfud_err page256_or_1_byte_write(const sfud_flash *flash, uint32_t addr, size_t size, uint16_t write_gran,
        const uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    static uint8_t write_cmd_data[5 + SFUD_WRITE_MAX_PAGE_SIZE];
    uint8_t cmd_size;
    size_t data_size;

    SFUD_ASSERT(flash);
    /* only support 1 or 256 */
    SFUD_ASSERT(write_gran == 1 || write_gran == 256);
    /* must be call this function after initialize OK */
    SFUD_ASSERT(flash->init_ok);
    /* check the flash address bound */
    if ((addr + size) > flash->chip.capacity) {
        /* SFUD_INFO("Error: Flash address is out of bound."); */
        result = SFUD_ERR_ADDR_OUT_OF_BOUND;
    }
    else
    {
        /* lock SPI */
        if (spi->lock != NULL) {
            spi->lock(spi);
        }

        /* loop write operate. write unit is write granularity */
        while (size > 0U) {
            /* set the flash write enable */
            result = set_write_enabled(flash, true);
            if (result != SFUD_SUCCESS) {
                break;
            }
            write_cmd_data[0] = SFUD_CMD_PAGE_PROGRAM;
            make_address_byte_array(flash, addr, &write_cmd_data[1]);
            cmd_size = flash->addr_in_4_byte ? 5U : 4U;

            /* make write align and calculate next write address */
            if ((addr % write_gran) != 0U) {
                if (size > (write_gran - (addr % write_gran))) {
                    data_size = write_gran - (addr % write_gran);
                } else {
                    data_size = size;
                }
            } else {
                if (size > write_gran) {
                    data_size = write_gran;
                } else {
                    data_size = size;
                }
            }
            size -= data_size;
            addr += data_size;

            uint8_t * pDes = &write_cmd_data[cmd_size];
            (void)memcpy(pDes, data, data_size);

            result = spi->wr(spi, write_cmd_data, cmd_size + data_size, NULL, 0);
            if (result != SFUD_SUCCESS) {
                /* SFUD_INFO("Error: Flash write SPI communicate error."); */
                break;
            }
            result = wait_busy(flash);
            if (result != SFUD_SUCCESS) {
                break;
            }
            data += data_size;
        }


        /* set the flash write disable */
        (void)set_write_enabled(flash, false);
        /* unlock SPI */
        if (spi->unlock != NULL) {
            spi->unlock(spi);
        }
    }
    return result;
}



/**
 * write flash data (no erase operate)
 *
 * @param flash flash device
 * @param addr start address
 * @param size write size
 * @param data write data
 *
 * @return result
 */
sfud_err sfud_write(const sfud_flash *flash, uint32_t addr, size_t size, const uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;

    if (((flash->chip.write_mode) & SFUD_WM_PAGE_256B) > 0U) {
        result = page256_or_1_byte_write(flash, addr, size, 256, data);
    } 
    else
    {
        /* nothing */
    }

    return result;
}

/**
 * erase and write flash data
 *
 * @param flash flash device
 * @param addr start address
 * @param size write size
 * @param data write data
 *
 * @return result
 */
#if 0
sfud_err sfud_erase_write(const sfud_flash *flash, uint32_t addr, size_t size, const uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;

    result = sfud_erase(flash, addr, size);

    if (result == SFUD_SUCCESS) {
        result = sfud_write(flash, addr, size, data);
    }

    return result;
}
#endif

static sfud_err reset(const sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[2];

    SFUD_ASSERT(flash);

    cmd_data[0] = W25X20CV_CMD_POWER_DOWN;
    result = spi->wr(spi, cmd_data, 1U, NULL, 0);
    if (result == SFUD_SUCCESS) {
        result = wait_busy(flash);
        cmd_data[1] = W25X20CV_CMD_RELEASE_POWER_DOWN;
        result = spi->wr(spi, &cmd_data[1], 1, NULL, 0);

        if (result == SFUD_SUCCESS) {
            result = wait_busy(flash);
        }
    } 

    return result;
}

static sfud_err read_jedec_id(sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[1], recv_data[3];

    SFUD_ASSERT(flash);

    cmd_data[0] = SFUD_CMD_JEDEC_ID;
    result = spi->wr(spi, cmd_data, sizeof(cmd_data), recv_data, sizeof(recv_data));
    if (result == SFUD_SUCCESS) {
        flash->chip.mf_id = recv_data[0];
        flash->chip.type_id = recv_data[1];
        flash->chip.capacity_id = recv_data[2];
        /* SFUD_DEBUG("The flash device manufacturer ID is 0x%02X, memory type ID is 0x%02X, capacity ID is 0x%02X.",
                flash->chip.mf_id, flash->chip.type_id, flash->chip.capacity_id); */
    } else {
        /* SFUD_INFO("Error: Read flash device JEDEC ID error."); */
    }

    return result;
}

/**
 * set the flash write enable or write disable
 *
 * @param flash flash device
 * @param enabled true: enable  false: disable
 *
 * @return result
 */
static sfud_err set_write_enabled(const sfud_flash *flash, bool enabled) {
    sfud_err result = SFUD_SUCCESS;
    uint8_t cmd, register_status = 0U;

    SFUD_ASSERT(flash);

    if (enabled) {
        cmd = SFUD_CMD_WRITE_ENABLE;
    } else {
        cmd = SFUD_CMD_WRITE_DISABLE;
    }

    result = flash->spi.wr(&flash->spi, &cmd, 1, NULL, 0);

    if (result == SFUD_SUCCESS) {
        result = sfud_read_status(flash, &register_status);
    }

    if (result == SFUD_SUCCESS) {
        if (enabled && ((register_status & SFUD_STATUS_REGISTER_WEL) == 0U)) {
            /* SFUD_INFO("Error: Can't enable write status."); */
            result = SFUD_ERR_WRITE;
        } else if ((!enabled) && ((register_status & SFUD_STATUS_REGISTER_WEL) != 0U)) {
           /*  SFUD_INFO("Error: Can't disable write status."); */
            result = SFUD_ERR_WRITE;
        }
        else
        {
            /* nothing */
        }
    }

    return result;
}

/**
 * enable or disable 4-Byte addressing for flash
 *
 * @note The 4-Byte addressing just supported for the flash capacity which is large then 16MB (256Mb).
 *
 * @param flash flash device
 * @param enabled true: enable   false: disable
 *
 * @return result
 */
static sfud_err set_4_byte_address_mode(sfud_flash *flash, bool enabled) {
    sfud_err result = SFUD_SUCCESS;
    uint8_t cmd;

    SFUD_ASSERT(flash);

    /* set the flash write enable */
    result = set_write_enabled(flash, true);
    if (result != SFUD_SUCCESS) {
        /* nothing */
    }
    else
    {

    if (enabled) {
        cmd = SFUD_CMD_ENTER_4B_ADDRESS_MODE;
    } else {
        cmd = SFUD_CMD_EXIT_4B_ADDRESS_MODE;
    }

    result = flash->spi.wr(&flash->spi, &cmd, 1, NULL, 0);

    if (result == SFUD_SUCCESS) {
        flash->addr_in_4_byte = enabled ? true : false;
        /* SFUD_DEBUG("%s 4-Byte addressing mode success.", enabled ? "Enter" : "Exit"); */
    } else {
        /* SFUD_INFO("Error: %s 4-Byte addressing mode failed.", enabled ? "Enter" : "Exit"); */
    }
    }
    return result;
}

/**
 * read flash register status
 *
 * @param flash flash device
 * @param status register status
 *
 * @return result
 */
sfud_err sfud_read_status(const sfud_flash *flash, uint8_t *status) {
    uint8_t cmd = SFUD_CMD_READ_STATUS_REGISTER;

    SFUD_ASSERT(flash);
    SFUD_ASSERT(status);

    return flash->spi.wr(&flash->spi, &cmd, 1, status, 1);
}

static sfud_err wait_busy(const sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;
    uint8_t status = 0U;
    size_t retry_times = flash->retry.times;

    SFUD_ASSERT(flash);

    result = sfud_read_status(flash, &status);
    while ((result != SFUD_SUCCESS) || ((status & SFUD_STATUS_REGISTER_BUSY) != 0U)) {
        /* retry counts */
        SFUD_RETRY_PROCESS(flash->retry.delay, retry_times, result);
        result = sfud_read_status(flash, &status);
    }

    if (result == SFUD_ERR_TIMEOUT) {
        /* SFUD_INFO("Error: Flash wait busy has an error."); */
    }

    return result;
}

static void make_address_byte_array(const sfud_flash *flash, uint32_t addr, uint8_t *array) {
    uint8_t len, i;
    uint32_t u32Temp;

    SFUD_ASSERT(flash);
    SFUD_ASSERT(array);

    len = flash->addr_in_4_byte ? 4U : 3U;

    for (i = 0U; i < len; i++) {
        u32Temp = (addr >> ((len - (i + 1u)) * 8u)) & 0xFFu;
        *(array + i) = (uint8_t)u32Temp;
    }
}

/**
 * write status register
 *
 * @param flash flash device
 * @param is_volatile true: volatile mode, false: non-volatile mode
 * @param status register status
 *
 * @return result
 */
sfud_err sfud_write_status(const sfud_flash *flash, bool is_volatile, uint8_t status) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_spi *spi = &flash->spi;
    uint8_t cmd_data[2];

    SFUD_ASSERT(flash);

    if (is_volatile) {
        cmd_data[0] = SFUD_VOLATILE_SR_WRITE_ENABLE;
        result = spi->wr(spi, cmd_data, 1, NULL, 0);
    } else {
        result = set_write_enabled(flash, true);
    }

    if (result == SFUD_SUCCESS) {
        cmd_data[0] = SFUD_CMD_WRITE_STATUS_REGISTER;
        cmd_data[1] = status;
        result = spi->wr(spi, cmd_data, 2, NULL, 0);
    }

    if (result != SFUD_SUCCESS) {
        /* SFUD_INFO("Error: Write_status register failed."); */
    }

    return result;
}
