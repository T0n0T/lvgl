/**
 * @file mydemo.c
 * @author T0n0T (823478402@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-02-29
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
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x343247), 0);
    lv_obj_t *tabview = lv_tabview_create(parent);
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_LEFT);
    lv_tabview_set_tab_bar_size(tabview, 100);

    lv_obj_t *bar = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_radius(bar, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0x43c9b0), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x404040), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(bar, bar_cb, LV_EVENT_ALL, NULL);

    static lv_style_t style_tabs;
    lv_style_init(&style_tabs);
    lv_style_set_radius(&style_tabs, 5);
    lv_style_set_bg_color(&style_tabs, lv_color_hex(0x43c9b0));
    lv_style_set_text_color(&style_tabs, lv_color_hex(0x404040));

    // lv_obj_add_style(bar, &style_tabs, LV_PART_ANY | LV_STATE_DEFAULT);

    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");
    lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "Tab 4");
    lv_obj_t *tab5 = lv_tabview_add_tab(tabview, "Tab 5");

    // lv_obj_add_style(tab1, &style_tabs, LV_STATE_DEFAULT);
    // lv_obj_add_style(tab2, &style_tabs, LV_STATE_FOCUSED);
    // lv_obj_add_style(tab3, &style_tabs, LV_STATE_FOCUSED);
    // lv_obj_add_style(tab4, &style_tabs, LV_STATE_FOCUSED);
    // lv_obj_add_style(tab5, &style_tabs, LV_STATE_FOCUSED);
}