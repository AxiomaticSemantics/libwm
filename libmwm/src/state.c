#include "state.h"

#include <ev.h>

/* We keep the xcb_prepare watcher around to be able to enable and disable it
 * temporarily for drag_pointer(). */
struct ev_prepare *xcb_prepare_main;
