#include <xcb/xcb_atom.h>


#include "mwm-atoms_NET_SUPPORTED.xmacro.h"
#include "mwm-atoms_rest.xmacro.h"

/* Define all atoms as global variables */

#define xmacro(atom) xcb_atom_t A_##atom;
MWM_NET_SUPPORTED_ATOMS_XMACRO
MWM_REST_ATOMS_XMACRO
#undef xmacro

