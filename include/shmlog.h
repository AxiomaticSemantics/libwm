/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * The format of the shmlog data structure which mwm development versions use by
 * default (ringbuffer for storing the debug log).
 *
 */
#pragma once

#include <config.h>

/* Default shmlog size if not set by user. */
extern const int default_shmlog_size;

/**
 * Header of the shmlog file. Used by mwm/src/log.c and mwm/mwm-dump-log/main.c.
 *
 */
typedef struct mwm_shmlog_header {
    /* Byte offset where the next line will be written to. */
    uint32_t offset_next_write;

    /* Byte offset where the last wrap occurred. */
    uint32_t offset_last_wrap;

    /* The size of the logfile in bytes. Since the size is limited to 25 MiB
     * an uint32_t is sufficient. */
    uint32_t size;

    /* wrap counter. We need it to reliably signal to clients that we just
     * wrapped (clients cannot use offset_last_wrap because that might
     * coincidentally be exactly the same as previously). Overflows can happen
     * and don’t matter — clients use an equality check (==). */
    uint32_t wrap_count;
} mwm_shmlog_header;
