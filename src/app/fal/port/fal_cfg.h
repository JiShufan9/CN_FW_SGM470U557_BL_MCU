/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_


#define NOR_FLASH_DEV_NAME                   "SourceIcExtFlash"
#define SOURCE_IC_FLS_PART_NAME              "SourceIcConf"

// #define FAL_DEBUG 1

#define FAL_USING_SFUD_PORT

#define FAL_OPTIMIZE_SIZE_MODE
/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_DEVICE_TBL_LEN          1U 

#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &nor_flash0                                                     \
}
/* ====================== Partition Configuration ========================== */

/* partition table */
#define FAL_PART_TABLE                                                               \
{                                                                                    \
    {0U, FAL_PART_MAGIC_WORD, SOURCE_IC_FLS_PART_NAME, NOR_FLASH_DEV_NAME,         0U, 2U*1024U*1024U, 0U} \
}


#endif /* _FAL_CFG_H_ */
