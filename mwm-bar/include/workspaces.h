/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm-bar - an xcb-based status- and ws-bar for i3
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 * workspaces.c: Maintaining the workspace lists
 *
 */
#pragma once

#include "common.h"

#include <xcb/xproto.h>

typedef struct mwm_ws mwm_ws;

TAILQ_HEAD(ws_head, mwm_ws);

/*
 * Parse the received JSON string
 *
 */
void parse_workspaces_json(const unsigned char *json, size_t size);

/*
 * free() all workspace data structures
 *
 */
void free_workspaces(void);

struct mwm_ws {
    uintptr_t id;              /* Workspace ID - C pointer to a workspace container */
    int num;                   /* The internal number of the ws */
    char *canonical_name;      /* The true name of the ws according to the ipc */
    mwmString *name;           /* The name of the ws that is displayed on the bar */
    int name_width;            /* The rendered width of the name */
    bool visible;              /* If the ws is currently visible on an output */
    bool focused;              /* If the ws is currently focused */
    bool urgent;               /* If the urgent hint of the ws is set */
    struct mwm_output *output; /* The current output of the ws */

    TAILQ_ENTRY(mwm_ws) tailq; /* Pointer for the TAILQ-Macro */
};
