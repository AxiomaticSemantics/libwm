/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm-bar - an xcb-based status- and ws-bar for mwm
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 * ipc.c: Communicating with mwm
 *
 */
#pragma once

#include <config.h>

#include <stdint.h>

/*
 * Initiate a connection to mwm.
 * socket_path must be a valid path to the ipc_socket of mwm
 *
 */
void init_connection(const char *socket_path);

/*
 * Destroy the connection to mwm.
 *
 */
void destroy_connection(void);

/*
 * Sends a message to mwm.
 * type must be a valid MWM_IPC_MESSAGE_TYPE (see mwm/ipc.h for further information)
 *
 */
int mwm_send_msg(uint32_t type, const char *payload);

/*
 * Subscribe to all needed mwm-events
 *
 */
void subscribe_events(void);
