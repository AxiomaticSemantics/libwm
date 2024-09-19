/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * display_version.c: displays the running i3 version, runs as part of
 *                    i3 --moreversion.
 */
#pragma once

#include <config.h>

/**
 * Connects to mwm to find out the currently running version. Useful since it
 * might be different from the version compiled into this binary (maybe the
 * user didn’t correctly install mwm or forgot to restart it).
 *
 * The output looks like this:
 * Running mwm version: 4.2-202-gb8e782c (2012-08-12, branch "next") (pid 14804)
 *
 * The mwm binary you just called: /home/michael/mwm/mwm
 * The mwm binary you are running: /home/michael/mwm/mwm
 *
 */
void display_running_version(void);
