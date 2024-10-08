/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm-bar - an xcb-based status- and ws-bar for mwm
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 */
#pragma once

#include "common.h"

typedef struct trayclient trayclient;

TAILQ_HEAD(tc_head, trayclient);

struct trayclient {
    xcb_window_t win; /* The window ID of the tray client */
    bool mapped;      /* Whether this window is mapped */
    int xe_version;   /* The XEMBED version supported by the client */

    char *class_class;
    char *class_instance;

    TAILQ_ENTRY(trayclient) tailq; /* Pointer for the TAILQ-Macro */
};
