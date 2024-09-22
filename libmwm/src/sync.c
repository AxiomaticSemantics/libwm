/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * sync.c: mwm sync protocol: https://i3wm.org/docs/testsuite.html#i3_sync
 *
 */

#include "libmwm.h"
#include "config_directives.h"
#include "mwm-atoms_rest.xmacro.h"

void sync_respond(xcb_window_t window, uint32_t rnd) {
    DLOG("[mwm sync protocol] Sending random value %d back to X11 window 0x%08x\n", rnd, window);

    void *reply = scalloc(32, 1);
    xcb_client_message_event_t *ev = reply;

    ev->response_type = XCB_CLIENT_MESSAGE;
    ev->window = window;
    ev->type = A_MWM_SYNC;
    ev->format = 32;
    ev->data.data32[0] = window;
    ev->data.data32[1] = rnd;

    xcb_send_event(conn, false, window, XCB_EVENT_MASK_NO_EVENT, (char *)ev);
    xcb_flush(conn);
    free(reply);
}
