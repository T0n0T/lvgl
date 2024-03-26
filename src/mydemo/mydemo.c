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

extern lv_indev_t *keyboard_indev;
static lv_anim_t a;
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

static void set_angle(void *obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void animate_ready_cb(struct _lv_anim_t *anim)
{
    printf("animate over");
    lv_obj_del(anim->var);
}

static void animate_fin_cb(void *var, int32_t)
{
    printf("animate stop");
}

void my_animate_demo(lv_point_t *p, lv_anim_ready_cb_t ready_cb)
{
    lv_obj_t *arc = lv_arc_create(lv_scr_act());
    lv_arc_set_rotation(arc, 90);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
    lv_obj_set_style_arc_width(arc, 3, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, 3, LV_PART_MAIN);
    lv_obj_set_style_size(arc, 20, LV_PART_MAIN);
    lv_obj_set_pos(arc, p->x, p->y);

    lv_anim_set_ready_cb(&a, ready_cb);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_start(&a);
}

void input_callback(lv_event_t *e)
{
    static uint8_t flag = 0;
    lv_obj_t *t         = lv_event_get_target(e);
    if (e->code == LV_EVENT_KEY) {
        printf("LV_EVENT_KEY %s\n", (char *)lv_event_get_param(e));
        e->stop_processing = true;
    }
    if (e->code == LV_EVENT_INSERT) {
        printf("LV_EVENT_INSERT %s\n", (char *)lv_event_get_param(e));
    }
    if (e->code == LV_EVENT_RELEASED) {
        // lv_anim_del(a.var, NULL);
        if (flag) {
            lv_obj_del(a.var);
            flag = !flag;
        }
    }
    if (e->code == LV_EVENT_LONG_PRESSED) {
        printf("LV_EVENT_LONG_PRESSED\n");
        lv_indev_t *dev = (lv_indev_t *)lv_event_get_param(e);
        my_animate_demo(&dev->proc.types.pointer.act_point, animate_ready_cb);
        flag = !flag;
    }
}

void my_serial_demo(lv_obj_t *parent)
{
    lv_group_t *g = lv_group_create();
    static lv_style_t g_terminal_style;
    lv_style_init(&g_terminal_style);

    /* Create an LVGL Container with Column Flex Direction */
    lv_obj_t *g_col = lv_obj_create(parent);

    lv_obj_set_size(g_col, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(g_col, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(g_col, 0, 0); /* No padding */

    /* Create an LVGL Text Area Widget for Terminal */
    lv_obj_t *g_input = lv_textarea_create(g_col);
    // lv_obj_t *g_input = lv_label_create(g_col);
    lv_obj_add_style(g_input, &g_terminal_style, 0);
    lv_obj_set_size(g_input, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(g_input, 1);

    /* Register the Callback Function for Input */
    lv_obj_add_event_cb(g_input, input_callback, LV_EVENT_ALL | LV_EVENT_PREPROCESS, NULL);

    lv_group_add_obj(g, g_input);
    lv_indev_set_group(keyboard_indev, g);

    lv_anim_init(&a);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, 0, 100);
}