/*
 * vim:ts=4:sw=4:expandtab
 *
 * mmw - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * scratchpad.h: Scratchpad functions (TODO: more description)
 *
 */
#pragma once

#include <config.h>

#include "data.h"

/**
 * Moves the specified window to the __mwm_scratch workspace, making it floating
 * and setting the appropriate scratchpad_state.
 *
 * Gets called upon the command 'move scratchpad'.
 *
 */
void scratchpad_move(Con *con);

/**
 * Either shows the top-most scratchpad window (con == NULL) or shows the
 * specified con (if it is scratchpad window).
 *
 * When called with con == NULL and the currently focused window is a
 * scratchpad window, this serves as a shortcut to hide it again (so the user
 * can press the same key to quickly look something up).
 *
 */
bool scratchpad_show(Con *con);

/**
 * When starting mwm initially (and after each change to the connected outputs),
 * this function fixes the resolution of the __mwm pseudo-output. When that
 * resolution is not set to a function which shares a common divisor with every
 * active output’s resolution, floating point calculation errors will lead to
 * the scratchpad window moving when shown repeatedly.
 *
 */
void scratchpad_fix_resolution(void);
