/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * sync.c: mwm sync protocol: https://i3wm.org/docs/testsuite.html#mwm_sync
 *
 */
#pragma once

#include <xcb/xcb.h>

void sync_respond(xcb_window_t window, uint32_t rnd);
