/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm-bar - an xcb-based status- and ws-bar for i3
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 * mode.c: Handle "mode" event and show current binding mode in the bar
 *
 */
#pragma once

#include <config.h>

#include <xcb/xproto.h>

#include "common.h"

/* Name of current binding mode and its render width */
struct mode {
    mwmString *name;
    int name_width;
};

typedef struct mode mode;

/*
 * Parse the received JSON string
 *
 */
void parse_mode_json(const unsigned char *json, size_t size);
