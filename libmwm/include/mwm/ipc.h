/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * This public header defines the different constants and message types to use
 * for the IPC interface to mwm (see docs/ipc for more information).
 *
 */
#pragma once

#include <stdint.h>

typedef struct mwm_ipc_header {
    /* 7 = strlen(MWM_IPC_MAGIC) */
    char magic[7];
    uint32_t size;
    uint32_t type;
} __attribute__((packed)) mwm_ipc_header_t;

/*
 * Messages from clients to mwm
 *
 */

/** Never change this, only on major IPC breakage (don’t do that) */
#define MWM_IPC_MAGIC "mwm-ipc"

/** The payload of the message will be interpreted as a command */
#define MWM_IPC_MESSAGE_TYPE_RUN_COMMAND 0

/** Requests the current workspaces from mwm */
#define MWM_IPC_MESSAGE_TYPE_GET_WORKSPACES 1

/** Subscribe to the specified events */
#define MWM_IPC_MESSAGE_TYPE_SUBSCRIBE 2

/** Requests the current outputs from mwm */
#define MWM_IPC_MESSAGE_TYPE_GET_OUTPUTS 3

/** Requests the tree layout from mwm */
#define MWM_IPC_MESSAGE_TYPE_GET_TREE 4

/** Request the current defined marks from mwm */
#define MWM_IPC_MESSAGE_TYPE_GET_MARKS 5

/** Request the configuration for a specific 'bar' */
#define MWM_IPC_MESSAGE_TYPE_GET_BAR_CONFIG 6

/** Request the mwm version */
#define MWM_IPC_MESSAGE_TYPE_GET_VERSION 7

/** Request a list of configured binding modes. */
#define MWM_IPC_MESSAGE_TYPE_GET_BINDING_MODES 8

/** Request the raw last loaded mwm config. */
#define MWM_IPC_MESSAGE_TYPE_GET_CONFIG 9

/** Send a tick event to all subscribers. */
#define MWM_IPC_MESSAGE_TYPE_SEND_TICK 10

/** Trigger an mwm sync protocol message via IPC. */
#define MWM_IPC_MESSAGE_TYPE_SYNC 11

/** Request the current binding state. */
#define MWM_IPC_MESSAGE_TYPE_GET_BINDING_STATE 12

/*
 * Messages from mwm to clients
 *
 */
#define MWM_IPC_REPLY_TYPE_COMMAND 0
#define MWM_IPC_REPLY_TYPE_WORKSPACES 1
#define MWM_IPC_REPLY_TYPE_SUBSCRIBE 2
#define MWM_IPC_REPLY_TYPE_OUTPUTS 3
#define MWM_IPC_REPLY_TYPE_TREE 4
#define MWM_IPC_REPLY_TYPE_MARKS 5
#define MWM_IPC_REPLY_TYPE_BAR_CONFIG 6
#define MWM_IPC_REPLY_TYPE_VERSION 7
#define MWM_IPC_REPLY_TYPE_BINDING_MODES 8
#define MWM_IPC_REPLY_TYPE_CONFIG 9
#define MWM_IPC_REPLY_TYPE_TICK 10
#define MWM_IPC_REPLY_TYPE_SYNC 11
#define MWM_IPC_REPLY_TYPE_GET_BINDING_STATE 12

/*
 * Events from mwm to clients. Events have the first bit set high.
 *
 */
#define MWM_IPC_EVENT_MASK (1UL << 31)

/* The workspace event will be triggered upon changes in the workspace list */
#define MWM_IPC_EVENT_WORKSPACE (MWM_IPC_EVENT_MASK | 0)

/* The output event will be triggered upon changes in the output list */
#define MWM_IPC_EVENT_OUTPUT (MWM_IPC_EVENT_MASK | 1)

/* The output event will be triggered upon mode changes */
#define MWM_IPC_EVENT_MODE (MWM_IPC_EVENT_MASK | 2)

/* The window event will be triggered upon window changes */
#define MWM_IPC_EVENT_WINDOW (MWM_IPC_EVENT_MASK | 3)

/** Bar config update will be triggered to update the bar config */
#define MWM_IPC_EVENT_BARCONFIG_UPDATE (MWM_IPC_EVENT_MASK | 4)

/** The binding event will be triggered when bindings run */
#define MWM_IPC_EVENT_BINDING (MWM_IPC_EVENT_MASK | 5)

/** The shutdown event will be triggered when the ipc shuts down */
#define MWM_IPC_EVENT_SHUTDOWN (MWM_IPC_EVENT_MASK | 6)

/** The tick event will be sent upon a tick IPC message */
#define MWM_IPC_EVENT_TICK (MWM_IPC_EVENT_MASK | 7)
