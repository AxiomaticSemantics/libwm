/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm-bar - an xcb-based status- and ws-bar for mwm
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 * outputs.c: Maintaining the outputs list
 *
 */
#pragma once

#include <config.h>

#include <xcb/xcb.h>
#include <cairo/cairo-xcb.h>

#include "common.h"

typedef struct mwm_output mwm_output;

SLIST_HEAD(outputs_head, mwm_output);
extern struct outputs_head* outputs;

/*
 * Parse the received JSON string
 *
 */
void parse_outputs_json(const unsigned char* json, size_t size);

/*
 * Initiate the outputs list
 *
 */
void init_outputs(void);

/*
 * free() all outputs data structures.
 *
 */
void free_outputs(void);

/*
 * Returns the output with the given name
 *
 */
mwm_output* get_output_by_name(char* name);

/*
 * Returns true if the output has the currently focused workspace
 *
 */
bool output_has_focus(mwm_output* output);

struct mwm_output {
    char* name;   /* Name of the output */
    bool active;  /* If the output is active */
    bool primary; /* If it is the primary output */
    bool visible; /* If the bar is visible on this output */
    int ws;       /* The number of the currently visible ws */
    rect rect;    /* The rect (relative to the root window) */

    /* Off-screen buffer for preliminary rendering of the bar. */
    surface_t buffer;
    /* Off-screen buffer for pre-rendering the statusline, separated to make clipping easier. */
    surface_t statusline_buffer;
    /* How much of statusline_buffer's horizontal space was used on last statusline render. */
    int statusline_width;
    /* The actual window on which we draw. */
    surface_t bar;

    struct ws_head* workspaces;  /* The workspaces on this output */
    struct tc_head* trayclients; /* The tray clients on this output */

    SLIST_ENTRY(mwm_output) slist; /* Pointer for the SLIST-Macro */
};
