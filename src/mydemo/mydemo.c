/**
 * @file mydemo.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mydemo.h"

void my_serial_demo(lv_obj_t *parent);

void bar_cb(lv_event_t *e)
{
    printf("event: %d\n", e->code);
}

void my_demo_create(lv_obj_t *parent)
{
    lv_obj_t *tabview = lv_tabview_create(parent, LV_DIR_LEFT, 80);
    lv_obj_t *tab1    = lv_tabview_add_tab(tabview, "tab1");
    lv_tabview_add_tab(tabview, "tab2");
    lv_tabview_add_tab(tabview, "tab3");

    my_serial_demo(tab1);

    lv_obj_t *bar = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_radius(bar, 5, LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0x43c9b0), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x404040), LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0xAC4C1F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x9B371F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(bar, 100, LV_PART_ITEMS | LV_STATE_CHECKED);
    // lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(bar, bar_cb, LV_EVENT_COVER_CHECK, NULL);
}

void input_callback(lv_event_t *e)
{
    
    }

void my_serial_demo(lv_obj_t *parent)
{
    static lv_style_t g_terminal_style;
    lv_style_init(&g_terminal_style);
    
    /* Create an LVGL Container with Column Flex Direction */

    lv_obj_t *g_col = lv_obj_create(parent);

    lv_obj_set_size(g_col, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(g_col, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(g_col, 0, 0); /* No padding */

    /* Create an LVGL Text Area Widget for NSH Output */

    // lv_obj_t *g_output = lv_textarea_create(g_col);
    // lv_obj_add_style(g_output, &g_terminal_style, 0);
    // lv_obj_set_width(g_output, LV_PCT(100));
    // lv_obj_set_flex_grow(g_output, 1); /* Fill the column */

    /* Create an LVGL Text Area Widget for NSH Input */

    lv_obj_t * g_input = lv_textarea_create(g_col);
    lv_obj_add_style(g_input, &g_terminal_style, 0);
    lv_obj_set_size(g_input, LV_PCT(100), LV_SIZE_CONTENT);

    /* Create an LVGL Keyboard Widget */

    // lv_obj_t *g_kb = lv_keyboard_create(g_col);
    // lv_obj_set_style_pad_all(g_kb, 0, 0); /* No padding */

    /* Register the Callback Function for NSH Input */
    extern lv_indev_t *keyboard_indev;
    lv_group_t *g = lv_group_create();
    lv_group_add_obj(g, g_input);
    lv_indev_set_group(keyboard_indev, g);
    lv_obj_add_event_cb(g_input, input_callback, LV_EVENT_ALL, NULL);

    /* Set the Keyboard to populate the NSH Input Text Area */

    // lv_keyboard_set_textarea(g_kb, g_input);

    // lv_area_t coo;
    // lv_obj_get_coords(parent, &coo);
    // printf("x:%d", coo.x1);
    // printf("y:%d", coo.y1);
    // printf("w:%d", lv_obj_get_width(parent));
    // printf("h:%d", lv_obj_get_height(parent));
    // lv_obj_align_to(terminal_text, parent, LV_ALIGN_TOP_LEFT, 0, 0);
    // lv_obj_set_size(terminal_text, lv_obj_get_width(parent), lv_obj_get_height(parent));
    // lv_obj_set_style_bg_color(terminal_text, lv_color_hex(0x1F1F1F), LV_PART_MAIN);
}