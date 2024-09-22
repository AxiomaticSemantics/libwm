/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 */
#include "libmwm.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Reports whether str represents the enabled state (1, true, …).
 *
 */
bool boolstr(const char *str) {
    return (strcasecmp(str, "1") == 0 ||
            strcasecmp(str, "true") == 0 ||
            strcasecmp(str, "on") == 0 ||
            strcasecmp(str, "enable") == 0 ||
            strcasecmp(str, "active") == 0);
}
