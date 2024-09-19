/*
 * vim:ts=4:sw=4:expandtab
 *
 * mwm - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * string.c: Define a mwmString type to automagically handle UTF-8/UCS-2
 *           conversions. Some font backends need UCS-2 (X core fonts),
 *           others want UTF-8 (Pango).
 *
 */
#include "libmwm.h"

#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct _mwmString {
    char *utf8;
    xcb_char2b_t *ucs2;
    size_t num_glyphs;
    size_t num_bytes;
    bool pango_markup;
};

/*
 * Build an mwmString from an UTF-8 encoded string.
 * Returns the newly-allocated mwmString.
 *
 */
mwmString *mwmstring_from_utf8(const char *from_utf8) {
    return mwmstring_from_utf8_with_length(from_utf8, -1);
}

/*
 * Build an mwmString from an UTF-8 encoded string in Pango markup.
 *
 */
mwmString *mwmstring_from_markup(const char *from_markup) {
    mwmString *str = mwmstring_from_utf8(from_markup);

    /* Set the markup flag */
    str->pango_markup = true;

    return str;
}

/*
 * Build an mwmString from an UTF-8 encoded string with fixed length.
 * To be used when no proper NULL-termination is available.
 * Returns the newly-allocated mwmString.
 *
 */
mwmString *mwmstring_from_utf8_with_length(const char *from_utf8, ssize_t num_bytes) {
    mwmString *str = scalloc(1, sizeof(mwmString));

    /* g_utf8_make_valid NULL-terminates the string. */
    str->utf8 = g_utf8_make_valid(from_utf8, num_bytes);

    /* num_bytes < 0 means NULL-terminated string, need to calculate length */
    str->num_bytes = num_bytes < 0 ? strlen(str->utf8) : (size_t)num_bytes;

    return str;
}

/*
 * Build an i3String from an UTF-8 encoded string in Pango markup with fixed
 * length.
 *
 */
mwmString *mwmstring_from_markup_with_length(const char *from_markup, size_t num_bytes) {
    mwmString *str = mwmstring_from_utf8_with_length(from_markup, num_bytes);

    /* set the markup flag */
    str->pango_markup = true;

    return str;
}

/*
 * Build an i3String from an UCS-2 encoded string.
 * Returns the newly-allocated i3String.
 *
 */
mwmString *mwmstring_from_ucs2(const xcb_char2b_t *from_ucs2, size_t num_glyphs) {
    mwmString *str = scalloc(1, sizeof(mwmString));

    /* Copy the actual text to our mwmString */
    str->ucs2 = scalloc(num_glyphs, sizeof(xcb_char2b_t));
    memcpy(str->ucs2, from_ucs2, num_glyphs * sizeof(xcb_char2b_t));

    /* Store the length */
    str->num_glyphs = num_glyphs;

    str->utf8 = NULL;
    str->num_bytes = 0;

    return str;
}

/*
 * Copies the given mwmString.
 * Note that this will not free the source string.
 */
mwmString *mwmstring_copy(mwmString *str) {
    mwmString *copy = mwmstring_from_utf8(mwmstring_as_utf8(str));
    copy->pango_markup = str->pango_markup;
    return copy;
}

/*
 * Free an mwmString.
 *
 */
void mwmstring_free(mwmString *str) {
    if (str == NULL) {
        return;
    }
    free(str->utf8);
    free(str->ucs2);
    free(str);
}

static void mwmstring_ensure_utf8(mwmString *str) {
    if (str->utf8 != NULL) {
        return;
    }
    if ((str->utf8 = convert_ucs2_to_utf8(str->ucs2, str->num_glyphs)) != NULL) {
        str->num_bytes = strlen(str->utf8);
    }
}

static void mwmstring_ensure_ucs2(mwmString *str) {
    if (str->ucs2 != NULL) {
        return;
    }
    str->ucs2 = convert_utf8_to_ucs2(str->utf8, &str->num_glyphs);
}

/*
 * Returns the UTF-8 encoded version of the mwmString.
 *
 */
const char *mwmstring_as_utf8(mwmString *str) {
    mwmstring_ensure_utf8(str);
    return str->utf8;
}

/*
 * Returns the UCS-2 encoded version of the mwmString.
 *
 */
const xcb_char2b_t *mwmstring_as_ucs2(mwmString *str) {
    mwmstring_ensure_ucs2(str);
    return str->ucs2;
}

/*
 * Returns the number of bytes (UTF-8 encoded) in an mwmString.
 *
 */
size_t mwmstring_get_num_bytes(mwmString *str) {
    mwmstring_ensure_utf8(str);
    return str->num_bytes;
}

/*
 * Whether the given mwmString is in Pango markup.
 */
bool mwmstring_is_markup(mwmString *str) {
    return str->pango_markup;
}

/*
 * Set whether the mwmString should use Pango markup.
 */
void mwmstring_set_markup(mwmString *str, bool pango_markup) {
    str->pango_markup = pango_markup;
}

/*
 * Escape pango markup characters in the given string.
 */
mwmString *mwmstring_escape_markup(mwmString *str) {
    const char *text = mwmstring_as_utf8(str);
    char *escaped = g_markup_escape_text(text, -1);
    mwmString *result = mwmstring_from_utf8(escaped);
    free(escaped);
    return result;
}

/*
 * Returns the number of glyphs in an i3String.
 *
 */
size_t mwmstring_get_num_glyphs(mwmString *str) {
    mwmstring_ensure_ucs2(str);
    return str->num_glyphs;
}
