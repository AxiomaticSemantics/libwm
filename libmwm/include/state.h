/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * This header file includes all relevant files of mwm and the most often used
 * system header files. This reduces boilerplate (the amount of code duplicated
 * at the beginning of each source file) and is not significantly slower at
 * compile-time.
 *
 */
#pragma once

#include <xcb/xcb.h>

#include <ev.h>

/* We keep the xcb_prepare watcher around to be able to enable and disable it
 * temporarily for drag_pointer(). */
extern struct ev_prepare *xcb_prepare_main;
