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

void bar_cb(lv_event_t *e)
{
    printf("event: %d\n", e->code);
}

void my_demo_create(lv_obj_t *parent)
{
    lv_obj_t *tabview = lv_tabview_create(parent, LV_DIR_LEFT, 80);
    lv_tabview_add_tab(tabview, "tab1");
    lv_tabview_add_tab(tabview, "tab2");
    lv_tabview_add_tab(tabview, "tab3");

    lv_obj_t *bar = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_radius(bar, 5, LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x43c9b0),  LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x404040), LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0xAC4C1F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x9B371F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(bar, 100, LV_PART_ITEMS | LV_STATE_CHECKED);
    // lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
    lv_obj_add_event_cb(bar, bar_cb, LV_EVENT_COVER_CHECK, NULL);
}