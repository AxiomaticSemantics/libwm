/*
 * vim:ts=4:sw=4:expandtab
 *
 * wmw - an i3 derived tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * commands.c: all command functions (see commands_parser.c)
 *
 */
#pragma once

#include <config.h>

#include "commands_parser.h"

/** The beginning of the prototype for every cmd_ function. */
#define MWM_CMD Match *current_match, struct CommandResultIR *cmd_output

/**
 * Initializes the specified 'Match' data structure and the initial state of
 * commands.c for matching target windows of a command.
 *
 */
void cmd_criteria_init(MWM_CMD);

/**
 * A match specification just finished (the closing square bracket was found),
 * so we filter the list of owindows.
 *
 */
void cmd_criteria_match_windows(MWM_CMD);

/**
 * Interprets a ctype=cvalue pair and adds it to the current match
 * specification.
 *
 */
void cmd_criteria_add(MWM_CMD, const char *ctype, const char *cvalue);

/**
 * Implementation of 'move [window|container] [to] workspace
 * next|prev|next_on_output|prev_on_output'.
 *
 */
void cmd_move_con_to_workspace(MWM_CMD, const char *which);

/**
 * Implementation of 'move [window|container] [to] workspace back_and_forth'.
 *
 */
void cmd_move_con_to_workspace_back_and_forth(MWM_CMD);

/**
 * Implementation of 'move [--no-auto-back-and-forth] [window|container] [to] workspace <name>'.
 *
 */
void cmd_move_con_to_workspace_name(MWM_CMD, const char *name, const char *no_auto_back_and_forth);

/**
 * Implementation of 'move [--no-auto-back-and-forth] [window|container] [to] workspace number <number>'.
 *
 */
void cmd_move_con_to_workspace_number(MWM_CMD, const char *which, const char *no_auto_back_and_forth);

/**
 * Implementation of 'resize set <width> [px | ppt] <height> [px | ppt]'.
 *
 */
void cmd_resize_set(MWM_CMD, long cwidth, const char *mode_width, long cheight, const char *mode_height);

/**
 * Implementation of 'resize grow|shrink <direction> [<px> px] [or <ppt> ppt]'.
 *
 */
void cmd_resize(MWM_CMD, const char *way, const char *direction, long resize_px, long resize_ppt);

/**
 * Implementation of 'border normal|pixel [<n>]', 'border none|1pixel|toggle'.
 *
 */
void cmd_border(MWM_CMD, const char *border_style_str, long border_width);

/**
 * Implementation of 'nop <comment>'.
 *
 */
void cmd_nop(MWM_CMD, const char *comment);

/**
 * Implementation of 'append_layout <path>'.
 *
 */
void cmd_append_layout(MWM_CMD, const char *path);

/**
 * Implementation of 'workspace next|prev|next_on_output|prev_on_output'.
 *
 */
void cmd_workspace(MWM_CMD, const char *which);

/**
 * Implementation of 'workspace [--no-auto-back-and-forth] number <number>'
 *
 */
void cmd_workspace_number(MWM_CMD, const char *which, const char *no_auto_back_and_forth);

/**
 * Implementation of 'workspace back_and_forth'.
 *
 */
void cmd_workspace_back_and_forth(MWM_CMD);

/**
 * Implementation of 'workspace [--no-auto-back-and-forth] <name>'
 *
 */
void cmd_workspace_name(MWM_CMD, const char *name, const char *no_auto_back_and_forth);

/**
 * Implementation of 'mark [--add|--replace] [--toggle] <mark>'
 *
 */
void cmd_mark(MWM_CMD, const char *mark, const char *mode, const char *toggle);

/**
 * Implementation of 'unmark [mark]'
 *
 */
void cmd_unmark(MWM_CMD, const char *mark);

/**
 * Implementation of 'mode <string>'.
 *
 */
void cmd_mode(MWM_CMD, const char *mode);

/**
 * Implementation of 'move [window|container] [to] output <str>'.
 *
 */
void cmd_move_con_to_output(MWM_CMD, const char *name, bool move_workspace);

/**
 * Implementation of 'move [window|container] [to] mark <str>'.
 *
 */
void cmd_move_con_to_mark(MWM_CMD, const char *mark);

/**
 * Implementation of 'floating enable|disable|toggle'
 *
 */
void cmd_floating(MWM_CMD, const char *floating_mode);

/**
 * Implementation of 'split v|h|t|vertical|horizontal|toggle'.
 *
 */
void cmd_split(MWM_CMD, const char *direction);

/**
 * Implementation of 'kill [window|client]'.
 *
 */
void cmd_kill(MWM_CMD, const char *kill_mode_str);

/**
 * Implementation of 'exec [--no-startup-id] <command>'.
 *
 */
void cmd_exec(MWM_CMD, const char *nosn, const char *command);

/**
 * Implementation of 'focus left|right|up|down'.
 *
 */
void cmd_focus_direction(MWM_CMD, const char *direction);

/**
 * Implementation of 'focus next|prev sibling'
 *
 */
void cmd_focus_sibling(MWM_CMD, const char *direction);

/**
 * Implementation of 'focus tiling|floating|mode_toggle'.
 *
 */
void cmd_focus_window_mode(MWM_CMD, const char *window_mode);

/**
 * Implementation of 'focus parent|child'.
 *
 */
void cmd_focus_level(MWM_CMD, const char *level);

/**
 * Implementation of 'focus'.
 *
 */
void cmd_focus(MWM_CMD, bool focus_workspace);

/**
 * Implementation of 'fullscreen [enable|disable|toggle] [global]'.
 *
 */
void cmd_fullscreen(MWM_CMD, const char *action, const char *fullscreen_mode);

/**
 * Implementation of 'sticky enable|disable|toggle'.
 *
 */
void cmd_sticky(MWM_CMD, const char *action);

/**
 * Implementation of 'move <direction> [<amount> [px|ppt]]'.
 *
 */
void cmd_move_direction(MWM_CMD, const char *direction_str, long amount, const char *mode);

/**
 * Implementation of 'layout default|stacked|stacking|tabbed|splitv|splith'.
 *
 */
void cmd_layout(MWM_CMD, const char *layout_str);

/**
 * Implementation of 'layout toggle [all|split]'.
 *
 */
void cmd_layout_toggle(MWM_CMD, const char *toggle_mode);

/**
 * Implementation of 'exit'.
 *
 */
void cmd_exit(MWM_CMD);

/**
 * Implementation of 'reload'.
 *
 */
void cmd_reload(MWM_CMD);

/**
 * Implementation of 'restart'.
 *
 */
void cmd_restart(MWM_CMD);

/**
 * Implementation of 'open'.
 *
 */
void cmd_open(MWM_CMD);

/**
 * Implementation of 'focus output <output>'.
 *
 */
void cmd_focus_output(MWM_CMD, const char *name);

/**
 * Implementation of 'move [window|container] [to] [absolute] position [<pos_x> [px|ppt] <pos_y> [px|ppt]]
 *
 */
void cmd_move_window_to_position(MWM_CMD, long x, const char *mode_x, long y, const char *mode_y);

/**
 * Implementation of 'move [window|container] [to] [absolute] position center
 *
 */
void cmd_move_window_to_center(MWM_CMD, const char *method);

/**
 * Implementation of 'move [window|container] [to] position mouse'
 *
 */
void cmd_move_window_to_mouse(MWM_CMD);

/**
 * Implementation of 'move scratchpad'.
 *
 */
void cmd_move_scratchpad(MWM_CMD);

/**
 * Implementation of 'scratchpad show'.
 *
 */
void cmd_scratchpad_show(MWM_CMD);

/**
 * Implementation of 'swap [container] [with] id|con_id|mark <arg>'.
 *
 */
void cmd_swap(MWM_CMD, const char *mode, const char *arg);

/**
 * Implementation of 'title_format <format>'
 *
 */
void cmd_title_format(MWM_CMD, const char *format);

/**
 * Implementation of 'rename workspace <name> to <name>'
 *
 */
void cmd_rename_workspace(MWM_CMD, const char *old_name, const char *new_name);

/**
 * Implementation of 'bar mode dock|hide|invisible|toggle [<bar_id>]'
 *
 */
void cmd_bar_mode(MWM_CMD, const char *bar_mode, const char *bar_id);

/**
 * Implementation of 'bar hidden_state hide|show|toggle [<bar_id>]'
 *
 */
void cmd_bar_hidden_state(MWM_CMD, const char *bar_hidden_state, const char *bar_id);

/**
 * Implementation of 'shmlog <size>|toggle|on|off'
 *
 */
void cmd_shmlog(MWM_CMD, const char *argument);

/**
 * Implementation of 'debuglog toggle|on|off'
 *
 */
void cmd_debuglog(MWM_CMD, const char *argument);

/**
 * Implementation of 'gaps inner|outer|top|right|bottom|left|horizontal|vertical current|all set|plus|minus|toggle <px>'
 *
 */
void cmd_gaps(MWM_CMD, const char *type, const char *scope, const char *mode, const char *value);

/**
 * Implementation of 'title_window_icon <yes|no|toggle>' and 'title_window_icon <padding|toggle> <px>'
 *
 */
void cmd_title_window_icon(MWM_CMD, const char *enable, int padding);
