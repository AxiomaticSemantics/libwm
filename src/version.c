/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * Stores the latest Git commit identifier so that it can be linked into i3
 * and used dynamically without recompiling every object file.
 *
 */
#include <config.h>

const char *mwm_version = MWM_VERSION;
