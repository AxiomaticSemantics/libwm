/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 */
#include "libmwm.h"

#include <err.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Returns the name of a temporary file with the specified prefix.
 *
 */
char *get_process_filename(const char *prefix) {
    /* dir stores the directory path for this and all subsequent calls so that
     * we only create a temporary directory once per mwm instance. */
    static char *dir = NULL;
    if (dir == NULL) {
        /* Check if XDG_RUNTIME_DIR is set. If so, we use XDG_RUNTIME_DIR/mwm */
        if ((dir = getenv("XDG_RUNTIME_DIR"))) {
            char *tmp;
            sasprintf(&tmp, "%s/mwm", dir);
            dir = tmp;
            /* mkdirp() should prevent race between multiple mwm instances started
             * in parallel from causing problem */
            if (mkdirp(dir, 0700) == -1) {
                warn("Could not mkdirp(%s)", dir);
                errx(EXIT_FAILURE, "Check permissions of $XDG_RUNTIME_DIR = '%s'",
                     getenv("XDG_RUNTIME_DIR"));
                perror("mkdirp()");
                return NULL;
            }
        } else {
            /* If not, we create a (secure) temp directory using the template
             * /tmp/mwm-<user>.XXXXXX */
            struct passwd *pw = getpwuid(getuid());
            const char *username = pw ? pw->pw_name : "unknown";
            sasprintf(&dir, "/tmp/mwm-%s.XXXXXX", username);
            /* mkdtemp modifies dir */
            if (mkdtemp(dir) == NULL) {
                perror("mkdtemp()");
                return NULL;
            }
        }
    }
    char *filename;
    sasprintf(&filename, "%s/%s.%d", dir, prefix, getpid());
    return filename;
}
