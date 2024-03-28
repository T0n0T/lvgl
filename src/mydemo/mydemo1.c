/**
 * @file mydemo1.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-03-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mydemo.h"

static lv_obj_t *g_main_container;
static lv_obj_t *g_menu_braids;
static lv_obj_t *g_menu_plane;
static lv_obj_t *g_terminal_plane;

#define MENU_BRAIDS_BTN_WIDTH 30

void mydemo_init1(lv_obj_t *parent, void (*connect_to_keypad)(lv_group_t *group), void *interface)
{
    g_main_container = lv_obj_create(parent);
    lv_obj_clear_flag(g_main_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(g_main_container, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_remove_style_all(g_main_container); /*Make it transparent*/
    lv_obj_set_size(g_main_container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scroll_snap_y(g_main_container, LV_SCROLL_SNAP_CENTER); /*Snap the children to the center*/

    /*Create a container for the player*/
    g_menu_braids = lv_obj_create(g_main_container);
    lv_obj_clear_flag(g_menu_braids, LV_OBJ_FLAG_SNAPABLE);
    lv_obj_set_y(g_menu_braids, 0);
    lv_obj_set_size(g_menu_braids, LV_HOR_RES, LV_VER_RES + MENU_BRAIDS_BTN_WIDTH);
    lv_obj_set_scroll_dir(g_menu_braids, LV_DIR_VER);
    lv_obj_set_style_border_width(g_menu_braids, 0, 0);
    lv_obj_set_style_pad_all(g_menu_braids, 0, 0);
    // lv_obj_set_style_bg_opa(g_menu_braids, LV_OPA_TRANSP, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(g_menu_braids, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_shadow_width(g_menu_braids, 5, LV_PART_MAIN);
    lv_obj_set_style_shadow_spread(g_menu_braids, 3, LV_PART_MAIN);
    lv_obj_set_style_shadow_color(g_menu_braids, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_shadow_ofs_x(g_menu_braids, 4, LV_PART_MAIN);
    lv_obj_set_style_shadow_ofs_y(g_menu_braids, 3, LV_PART_MAIN);

    g_menu_plane = lv_obj_create(g_main_container);
    lv_obj_remove_style_all(g_menu_plane);
    lv_obj_clear_flag(g_menu_plane, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(g_menu_plane, LV_PCT(100), LV_VER_RES);
    lv_obj_set_y(g_menu_plane, 0);
    lv_obj_set_style_bg_color(g_menu_plane, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_opa(g_menu_plane, LV_OPA_50, 0);

    g_terminal_plane = lv_obj_create(g_main_container);
    lv_obj_remove_style_all(g_terminal_plane);
    lv_obj_clear_flag(g_terminal_plane, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(g_terminal_plane, LV_PCT(100), LV_VER_RES);
    lv_obj_set_y(g_terminal_plane, LV_VER_RES);
    lv_obj_set_style_bg_color(g_terminal_plane, lv_color_hex(0x0000ff), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_terminal_plane, LV_OPA_50, 0);
    lv_obj_move_background(g_terminal_plane);
}
