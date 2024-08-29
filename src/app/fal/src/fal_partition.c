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
#include <string.h>
#include <stdlib.h>

/* partition magic word */
#define FAL_PART_MAGIC_WORD         0x45503130U
#define FAL_PART_MAGIC_WORD_H       0x4550U
#define FAL_PART_MAGIC_WORD_L       0x3130U

struct part_flash_info
{
    const struct fal_flash_dev *flash_dev;
};

/**
 * FAL partition table config has defined on 'fal_cfg.h'.
 * When this option is disable, it will auto find the partition table on a specified location in flash partition.
 */


/* check partition table definition */
#if !defined(FAL_PART_TABLE)
#error "You must defined FAL_PART_TABLE on 'fal_cfg.h'"
#endif

#if 0
#ifdef __CC_ARM                        /* ARM Compiler */
    #define SECTION(x)                 __attribute__((section(x)))
    #define USED                       __attribute__((used))
#elif defined (__IAR_SYSTEMS_ICC__)    /* for IAR Compiler */
    #define SECTION(x)                 @ x
    #define USED                       __root
#elif defined (__GNUC__)               /* GNU GCC Compiler */
    #define SECTION(x)                 __attribute__((section(x)))
    #define USED                       __attribute__((used))
#else
    #error not supported tool chain
#endif /* __CC_ARM */
#endif
//USED static const struct fal_partition partition_table_def[] SECTION("FalPartTable") = FAL_PART_TABLE;
static const struct fal_partition partition_table_def[1] = FAL_PART_TABLE;
static const struct fal_partition *partition_table = NULL;
/* partition and flash object information cache table */
static struct part_flash_info part_flash_cache[sizeof(partition_table_def) / sizeof(partition_table_def[0])] = { 0U };


static uint8_t fal_partition_init_ok = 0U;
static size_t partition_table_len = 0U;

#ifndef FAL_OPTIMIZE_SIZE_MODE
/**
 * print the partition table
 */
#if 0
void fal_show_part_table(void)
{
    const char *item1 = "name", *item2 = "flash_dev";
    size_t i, part_name_max = strlen(item1), flash_dev_name_max = strlen(item2);
    const struct fal_partition *part;

    if (partition_table_len > 0U)
    {
        for (i = 0U; i < partition_table_len; i++)
        {
            part = &partition_table[i];
            if (strlen(part->name) > part_name_max)
            {
                part_name_max = strlen(part->name);
            }
            if (strlen(part->flash_name) > flash_dev_name_max)
            {
                flash_dev_name_max = strlen(part->flash_name);
            }
        }
    }
    /* log_i("==================== FAL partition table ===================="); */
    /* log_i("| %-*.*s | %-*.*s |   offset   |    length  |", part_name_max, FAL_DEV_NAME_MAX, item1, flash_dev_name_max,
            FAL_DEV_NAME_MAX, item2); */
    /* log_i("-------------------------------------------------------------"); */
    for (i = 0U; i < partition_table_len; i++)
    {
        part = &partition_table[i];

        /* log_i("| %-*.*s | %-*.*s | 0x%08lx | 0x%08x |", part_name_max, FAL_DEV_NAME_MAX, part->name, flash_dev_name_max,
                FAL_DEV_NAME_MAX, part->flash_name, part->offset, part->len); */
    }
    /* log_i("============================================================="); */
}
#endif
#endif

static int check_and_update_part_cache(const struct fal_partition *table, size_t len)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev;
    size_t i;

    for (i = 0U; i < len; i++)
    {
        flash_dev = fal_flash_device_find(table[i].flash_name);
        if (flash_dev == NULL)
        {
            /* log_d("Warning: Do NOT found the flash device(%s).", table[i].flash_name); */
            continue;
        }

        if (table[i].offset >= flash_dev->len)
        {
            /* log_e("Initialize failed! Partition(%s) offset address(%ld) out of flash bound(<%d).",
                    table[i].name, table[i].offset, flash_dev->len); */
            partition_table_len = 0U;

            ret = -1;
            break;
        }

        part_flash_cache[i].flash_dev = flash_dev;
    }

    return ret;
}

/**
 * Initialize all flash partition on FAL partition table
 *
 * @return partitions total number
 */

int fal_partition_init(void)
{
    int result;
    if (fal_partition_init_ok > 0U)
    {
        /* nothing */
    }
    else
    {
        partition_table = &partition_table_def[0];
        partition_table_len = sizeof(partition_table_def) / sizeof(partition_table_def[0]);

        /* check the partition table device exists */
        if (check_and_update_part_cache(partition_table, partition_table_len) != 0)
        {
            /* nothing */
        }
        else
        {
            fal_partition_init_ok = 1U;
        }

#if FAL_DEBUG
#if 0
        fal_show_part_table();
#endif
#endif

    }

    if(partition_table_len > 0U)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}

/**
 * find the partition by name
 *
 * @param name partition name
 *
 * @return != NULL: partition
 *            NULL: not found
 */
const struct fal_partition * pFalPartition = NULL;
const struct fal_partition *fal_partition_find(const char *name)
{
    //assert(fal_partition_init_ok);

    size_t i;

    for (i = 0U; i < partition_table_len; i++)
    {
        if ((strcmp(name, partition_table[i].name)) == 0)
        {
                pFalPartition = &partition_table[i];
                break;
        }
    }

    return pFalPartition;
}

static const struct fal_flash_dev *flash_device_find_by_part(const struct fal_partition *part)
{
    //assert(part >= partition_table);
    //assert(part <= &partition_table[partition_table_len - 1U]);

    return part_flash_cache[part->u32Index].flash_dev;
}

/**
 * get the partition table
 *
 * @param len return the partition table length
 *
 * @return partition table
 */
#if 0
const struct fal_partition *fal_get_partition_table(size_t *len)
{
    //assert(fal_partition_init_ok);
    //assert(len);

    *len = partition_table_len;

    return partition_table;
}
#endif

/**
 * set partition table temporarily
 * This setting will modify the partition table temporarily, the setting will be lost after restart.
 *
 * @param table partition table
 * @param len partition table length
 */
#if 0
void fal_set_partition_table_temp(struct fal_partition *table, size_t len)
{
    //assert(fal_partition_init_ok);
    //assert(table);

    (void)check_and_update_part_cache(table, len);

    partition_table_len = len;
    partition_table = table;
}
#endif
/**
 * read data from partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf read buffer
 * @param size read size
 *
 * @return >= 0: successful read data size
 *           -1: error
 */
int fal_partition_read(const struct fal_partition *part, uint32_t addr, uint8_t *buf, size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    //assert(part);
    //assert(buf);

    if ((addr + size) > (part->len))
    {
        /* log_e("Partition read error! Partition address out of bound."); */
        ret = -1;
    }
    else
    {

        flash_dev = flash_device_find_by_part(part);
        if (flash_dev == NULL)
        {
            /* log_e("Partition read error! Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name); */
            ret = -1;
        }
        else
        {

            ret = flash_dev->ops.read(part->offset + addr, buf, size);
            if (ret < 0)
            {
                /* log_e("Partition read error! Flash device(%s) read error!", part->flash_name); */
            }
        }
    }
    return ret;
}

/**
 * write data to partition
 *
 * @param part partition
 * @param addr relative address for partition
 * @param buf write buffer
 * @param size write size
 *
 * @return >= 0: successful write data size
 *           -1: error
 */
int fal_partition_write(const struct fal_partition *part, uint32_t addr, const uint8_t *buf, size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    //assert(part);
    //assert(buf);

    if ((addr + size) > (part->len))
    {
        /* log_e("Partition write error! Partition address out of bound."); */
        ret = -1;
    }
    else
    {
        flash_dev = flash_device_find_by_part(part);
        if (flash_dev == NULL)
        {
            /* log_e("Partition write error!  Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name); */
            ret = -1;
        }
        else
        {

            ret = flash_dev->ops.write(part->offset + addr, buf, size);
            if (ret < 0)
            {
                /* log_e("Partition write error! Flash device(%s) write error!", part->flash_name); */
            }
        }
    }
    return ret;
}

/**
 * erase partition data
 *
 * @param part partition
 * @param addr relative address for partition
 * @param size erase size
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
int fal_partition_erase(const struct fal_partition *part, uint32_t addr, size_t size)
{
    int ret = 0;
    const struct fal_flash_dev *flash_dev = NULL;

    //assert(part);

    if ((addr + size) > (part->len))
    {
        /* log_e("Partition erase error! Partition address out of bound."); */
        ret = -1;
    }
    else
    {
        flash_dev = flash_device_find_by_part(part);
        if (flash_dev == NULL)
        {
            /* log_e("Partition erase error! Don't found flash device(%s) of the partition(%s).", part->flash_name, part->name); */
            ret = -1;
        }
        else
        {
            ret = flash_dev->ops.erase(part->offset + addr, size);
            if (ret < 0)
            {
                /* log_e("Partition erase error! Flash device(%s) erase error!", part->flash_name); */
            }
        }
    }
    return ret;
}

/**
 * erase partition all data
 *
 * @param part partition
 *
 * @return >= 0: successful erased data size
 *           -1: error
 */
#if 0
int fal_partition_erase_all(const struct fal_partition *part)
{
    return fal_partition_erase(part, 0, part->len);
}
#endif
