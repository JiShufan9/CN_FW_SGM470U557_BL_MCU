/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_DEF_H_
#define _FAL_DEF_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#ifdef FDB_USING_NATIVE_ASSERT
#include <assert.h>
#endif

#define FAL_SW_VERSION                 "0.5.99"

#ifndef FAL_PRINTF
#define FAL_PRINTF                     printf
#endif

#ifndef FAL_DEBUG
#define FAL_DEBUG                      0
#endif

#if FAL_DEBUG
#ifndef FDB_USING_NATIVE_ASSERT
#ifdef assert
#undef assert
#endif
#define assert(EXPR)                                                           \
if (!(EXPR))                                                                   \
{                                                                              \
    FAL_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __func__ );        \
    while (1);                                                                 \
}
#endif

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#include <inttypes.h>
#define log_d(...)                     FAL_PRINTF("[D/FAL] (%s:%" PRIdLEAST16 ") ", __func__, __LINE__);           FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\n")

#else

#ifndef FDB_USING_NATIVE_ASSERT
#ifdef assert
#undef assert
#endif
#define assert(EXPR)                   ((void)0);
#endif

/* debug level log */
#ifdef  log_d
#undef  log_d
#endif
#define log_d(...)                      __NOP()
#endif /* FAL_DEBUG */

/* error level log */
#ifdef  log_e
#undef  log_e
#endif
#ifndef FAL_OPTIMIZE_SIZE_MODE
#define log_e(...)                     FAL_PRINTF("\033[31;22m[E/FAL] (%s:%d) ", __func__, __LINE__);FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\033[0m\n")
#else
#define log_e(...)                      __NOP()
#endif

/* info level log */
#ifdef  log_i
#undef  log_i
#endif
#ifndef FAL_OPTIMIZE_SIZE_MODE
#define log_i(...)                     FAL_PRINTF("\033[32;22m[I/FAL] ");                                FAL_PRINTF(__VA_ARGS__);FAL_PRINTF("\033[0m\n")
#else
#define log_i(...)                      __NOP()
#endif

/* FAL flash and partition device name max length */
#ifndef FAL_DEV_NAME_MAX
#define FAL_DEV_NAME_MAX 17
#endif

struct fal_flash_dev
{
    char name[FAL_DEV_NAME_MAX];

    /* flash device start address and len  */
    uint32_t addr;
    size_t len;
    /* the block size in the flash for erase minimum granularity */
    size_t blk_size;

    struct
    {
        int (*init)(void);
        int (*read)(uint32_t offset, uint8_t *buf, size_t size);
        int (*write)(uint32_t offset, const uint8_t *buf, size_t size);
        int (*erase)(uint32_t offset, size_t size);
    } ops;

    /* write minimum granularity, unit: bit. 
       1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32l4)
       0 will not take effect. */
    size_t write_gran;
};
typedef struct fal_flash_dev *fal_flash_dev_t;

/**
 * FAL partition
 */
struct fal_partition
{
    size_t u32Index;
    uint32_t magic_word;

    /* partition name */
    char name[FAL_DEV_NAME_MAX];
    /* flash device name for partition */
    char flash_name[FAL_DEV_NAME_MAX];

    /* partition offset address on flash device */
    uint32_t offset;
    size_t len;

    uint32_t reserved;
};
typedef struct fal_partition *fal_partition_t;

#endif /* _FAL_DEF_H_ */
