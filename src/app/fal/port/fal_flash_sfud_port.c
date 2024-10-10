/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include "fal.h"
#include "sfud.h"

#ifdef FAL_USING_SFUD_PORT

#ifndef FAL_USING_NOR_FLASH_DEV_NAME
#define FAL_USING_NOR_FLASH_DEV_NAME             "SourceIcExtFlash"
#endif

extern int SfudIf_init(void);
extern int SfudIf_read(uint32_t offset, uint8_t *buf, size_t size);
extern int SfudIf_write(uint32_t offset, const uint8_t *buf, size_t size);
extern int SfudIf_erase(uint32_t offset, size_t size);

static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev nor_flash0 =
{
    .name       = FAL_USING_NOR_FLASH_DEV_NAME,
    .addr       = 0,
    .len        = 256 * 1024,
    .blk_size   = 4096,
    .ops        = {SfudIf_init, SfudIf_read, SfudIf_write, SfudIf_erase},
    .write_gran = 1
};

int SfudIf_init(void)
{
    int ret;
    /* bare metal platform */
    sfud_dev = sfud_get_device(SFUD_SOURCE_IC_EXT_FLS_INDEX);

    if (NULL == sfud_dev)
    {
        ret = -1;
    }
    else
    {
        /* update the flash chip information */
        nor_flash0.blk_size = sfud_dev->chip.erase_gran;
        nor_flash0.len = sfud_dev->chip.capacity;
        ret = 0;
    }
    return ret;
}

int SfudIf_read(uint32_t offset, uint8_t *buf, size_t size)
{
    //assert(sfud_dev);
    //assert(sfud_dev->init_ok);
    int ret;
    if(sfud_read(sfud_dev, (nor_flash0.addr + offset), size, buf) != SFUD_SUCCESS)
    {
        ret = -1;
    }
    else
    {
        ret = 1;
    }

    return ret;
}

int SfudIf_write(uint32_t offset, const uint8_t *buf, size_t size)
{
    //assert(sfud_dev);
    //assert(sfud_dev->init_ok);
    int ret;
    if (sfud_write(sfud_dev, nor_flash0.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        ret = -1;
    }
    else
    {
        ret = 1;
    }

    return ret;
}

int SfudIf_erase(uint32_t offset, size_t size)
{
    //assert(sfud_dev);
    //assert(sfud_dev->init_ok);
    int ret;
    if (sfud_erase(sfud_dev, nor_flash0.addr + offset, size) != SFUD_SUCCESS)
    {
        ret = -1;
    }
    else
    {
        ret = 1;
    }

    return ret;
}
#endif /* FAL_USING_SFUD_PORT */

