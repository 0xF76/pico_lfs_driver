#include "pico_lfs_driver.h"

struct lfs_config cfg = {
    .context = NULL,
    .read = lfs_read,
    .prog = lfs_prog,
    .erase = lfs_erase,
    .sync = lfs_sync,
    .read_size = 256,
    .prog_size = 256,
    .block_size = 4096,
    .block_count = 128,
    .block_cycles = 500,
    .cache_size = 256,
    .lookahead_size = 16
};

__attribute__((section(".ram_code"))) int lfs_read(const struct lfs_config *c,
                                                   lfs_block_t block,
                                                   lfs_off_t off,
                                                   void *buffer,
                                                   lfs_size_t size) {

    memcpy(buffer, (const void*)(XIP_BASE + FLASH_TARGET_OFFSET + block * c->block_size + off), size);
    return 0;
}

__attribute__((section(".ram_code"))) int lfs_prog(const struct lfs_config *c,
                                                   lfs_block_t block,
                                                   lfs_off_t off,
                                                   const void *buffer,
                                                   lfs_size_t size) {

    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(FLASH_TARGET_OFFSET + block * c->block_size + off, buffer, size);
    restore_interrupts(ints);
    return 0;
}

__attribute__((section(".ram_code"))) int lfs_erase(const struct lfs_config *c, lfs_block_t block) {

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET + block * c->block_size, c->block_size);
    restore_interrupts(ints);
    return 0;
}

__attribute__((section(".ram_code"))) int lfs_sync(const struct lfs_config *c) {
    
    return 0;
}
