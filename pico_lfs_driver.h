#pragma once

#include "lfs.h"
#include <pico/stdlib.h>
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (256 * 1024)

extern struct lfs_config cfg;

__attribute__((section(".ram_code"))) int lfs_read(const struct lfs_config *c, 
                                                   lfs_block_t block,
                                                   lfs_off_t off, 
                                                   void *buffer, 
                                                   lfs_size_t size);

__attribute__((section(".ram_code"))) int lfs_prog(const struct lfs_config *c,
                                                   lfs_block_t block,
                                                   lfs_off_t off,
                                                   const void *buffer,
                                                   lfs_size_t size);


__attribute__((section(".ram_code"))) int lfs_erase(const struct lfs_config *c,
                                                    lfs_block_t block);


__attribute__((section(".ram_code"))) int lfs_sync(const struct lfs_config *c);
