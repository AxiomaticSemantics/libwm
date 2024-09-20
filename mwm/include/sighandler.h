/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 deried tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 */
#pragma once

#include <config.h>

/**
 * Configured a signal handler to gracefully handle crashes and allow the user
 * to generate a backtrace and rescue their session.
 *
 */
void setup_signal_handler(void);
