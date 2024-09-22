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

#include <config.h>

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_keysyms.h>

#include "libmwm.h"
#include "mwm.h"
#include "data.h"
#include "assignments.h"
#include "bindings.h"
#include "click.h"
#include "commands_parser.h"
#include "con.h"
#include "config_directives.h"
#include "config_parser.h"
#include "configuration.h"
#include "tree.h"
#include "util.h"
#include "drag.h"
#include "ewmh.h"
#include "floating.h"
#include "handlers.h"
#include "ipc.h"
#include "move.h"
#include "output.h"
#include "randr.h"
#include "resize.h"
#include "scratchpad.h"
#include "sync.h"
#include "state.h"
#include "tiling_drag.h"
#include "gaps.h"
#include "window.h"
#include "workspace.h"
#include "x.h"
#include "xcb.h"
#include "xcursor.h"
#include "log.h"
#include "manage.h"
#include "key_press.h"
#include "load_layout.h"
#include "render.h"
#include "match.h"
#include "regex.h"
#include "startup.h"
#include "commands.h"
#include "fake_outputs.h"
#include "restore_layout.h"

#include "display_version.h"
#include "sighandler.h"
