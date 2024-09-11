/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#include "fal.h"

static uint8_t fal_init_ok = 0U;

/**
 * FAL (Flash Abstraction Layer) initialization.
 * It will initialize all flash device and all flash partition.
 *
 * @return >= 0: partitions total number
 */
int fal_init(void)
{


    int result;

    /* initialize all flash device on FAL flash table */
    result = fal_flash_init();

    if (result < 0) {
        /* nothing */
    }
    else
    {
        /* initialize all flash partition on FAL partition table */
        result = fal_partition_init();
    }


    if ((result > 0) && (!(fal_init_ok > 0U)))
    {
        fal_init_ok = 1u;
        /* log_i("Flash Abstraction Layer (V%s) initialize success.", FAL_SW_VERSION); */
    }
    else if(result <= 0)
    {
        fal_init_ok = 0U;
        /* log_e("Flash Abstraction Layer (V%s) initialize failed.", FAL_SW_VERSION); */
    }
    else
    {
        /* nothing */
    }

    return result;
}

/**
 * Check if the FAL is initialized successfully
 * 
 * @return 0: not init or init failed; 1: init success
 */
#if 0
uint8_t fal_init_check(void)
{
    return fal_init_ok;
}
#endif
