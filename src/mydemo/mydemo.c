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

static const lv_font_t * font_normal;

void my_demo_create(lv_obj_t *parent)
{
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          font_normal);
    lv_obj_t* plane = lv_obj_create(parent);
    // lv_obj_t* tv = lv_tabview_create(plane);
    // lv_obj_t * t1 = lv_tabview_add_tab(tv, "Profile");
    // lv_obj_t * t2 = lv_tabview_add_tab(tv, "Analytics");
    // lv_obj_t * t3 = lv_tabview_add_tab(tv, "Shop");
}