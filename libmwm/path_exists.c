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
 * Checks if the given path exists by calling stat().
 *
 */
bool path_exists(const char *path) {
    struct stat buf;
    return (stat(path, &buf) == 0);
}
