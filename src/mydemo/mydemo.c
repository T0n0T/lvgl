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

/**
 * @brief static variable
 *
 */
static uint8_t     g_anim_ready_flag;
static lv_anim_t   g_anim_arc;
static lv_style_t  g_terminal_style;
static lv_group_t *g_terminal_group;
static lv_obj_t   *g_terminal_obj;
static lv_obj_t   *g_menu_obj;

static lv_obj_t *g_terminal_screen;
static lv_obj_t *g_menu_screen;

static void anmi_arc_set_angle(void *obj, int32_t v);
static void anmi_arc_ready_cb(struct _lv_anim_t *anim);
static void terminal_ev_cb(lv_event_t *e);
static void menu_ev_cb(lv_event_t *e);
static void menu_background_ev_cb(lv_event_t *e);

/**
 * @brief global function
 *
 */

void my_demo_create(lv_obj_t *parent, void (*add_inputdev_to_group)(lv_group_t *group))
{
    lv_obj_t *tabview = lv_tabview_create(parent, LV_DIR_LEFT, 80);
    lv_obj_t *tab1    = lv_tabview_add_tab(tabview, "tab1");
    lv_tabview_add_tab(tabview, "tab2");
    lv_tabview_add_tab(tabview, "tab3");

    lv_obj_t *bar = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_radius(bar, 5, LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0x43c9b0), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x404040), LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(bar, lv_color_hex(0xAC4C1F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(bar, lv_color_hex(0x9B371F), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(bar, 100, LV_PART_ITEMS | LV_STATE_CHECKED);
}

void my_animate_demo(lv_point_t *p)
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

    lv_anim_set_var(&g_anim_arc, arc);
    lv_anim_start(&g_anim_arc);
}

void mydemo_init(lv_obj_t *parent, void (*connect_to_keypad)(lv_group_t *group), void *interface)
{
    /** init animate */
    lv_anim_init(&g_anim_arc);
    lv_anim_set_time(&g_anim_arc, 500);
    lv_anim_set_values(&g_anim_arc, 0, 100);
    lv_anim_set_ready_cb(&g_anim_arc, anmi_arc_ready_cb);
    lv_anim_set_exec_cb(&g_anim_arc, anmi_arc_set_angle);

    /** init style */
    lv_style_init(&g_terminal_style);
    lv_style_set_border_color(&g_terminal_style, lv_color_hex(0xcdcfe));
    lv_style_set_border_opa(&g_terminal_style, LV_OPA_COVER);
    lv_style_set_border_width(&g_terminal_style, 2);

    lv_style_set_shadow_width(&g_terminal_style, 5);
    lv_style_set_shadow_spread(&g_terminal_style, 3);
    lv_style_set_shadow_opa(&g_terminal_style, 100);
    lv_style_set_shadow_color(&g_terminal_style, lv_color_hex(0xcdcfe));
    lv_style_set_radius(&g_terminal_style, 10);

    // lv_obj_t *test = lv_obj_create(parent);
    // lv_obj_add_style(test, &g_terminal_style, LV_PART_MAIN);

    /**
     * @brief init group
     * touch keypad to our textarea
     */
    g_terminal_group = lv_group_create();
    connect_to_keypad(g_terminal_group);

    /** Create an LVGL Text Area Widget for Terminal */
    g_terminal_screen = lv_scr_act();

    g_terminal_obj = lv_textarea_create(g_terminal_screen);
    lv_obj_add_style(g_terminal_obj, &g_terminal_style, LV_PART_MAIN);
    lv_obj_set_size(g_terminal_obj, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_grow(g_terminal_obj, 1);
    lv_group_add_obj(g_terminal_group, g_terminal_obj);
    /**
     * @brief Construct g_anim_arc new lv obj add event cb object
     * user_data is used to transparent our interface, such as serial,ble,ssh
     */
    lv_obj_add_event_cb(g_terminal_obj, terminal_ev_cb, LV_EVENT_ALL | LV_EVENT_PREPROCESS, interface);

    /**
     * @brief menu obj
     *
     */
    g_menu_screen = lv_obj_create(NULL);
    // lv_obj_set_style_bg_opa(g_menu_screen, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_add_event_cb(g_menu_screen, menu_background_ev_cb, LV_EVENT_FOCUSED, NULL);
    g_menu_obj = lv_tileview_create(g_menu_screen);
    lv_obj_set_size(g_menu_obj, LV_PCT(60), LV_PCT(60));
    lv_obj_center(g_menu_obj);
    lv_obj_set_style_bg_color(g_menu_obj, lv_color_hex(0xeeffcc), LV_PART_MAIN);
    lv_obj_add_style(g_menu_obj, &g_terminal_style, LV_PART_MAIN);
    lv_obj_add_flag(g_menu_obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_style(g_menu_obj, NULL, LV_PART_SCROLLBAR);

    /**
     * @brief serial group
     *
     */
    lv_obj_t *serial_tile  = lv_tileview_add_tile(g_menu_obj, 0, 0, LV_DIR_HOR);
    lv_obj_t *serial_label = lv_label_create(serial_tile);
    lv_label_set_text(serial_label, "SERIAL");
    lv_obj_center(serial_label);

    lv_obj_t *ble_tile  = lv_tileview_add_tile(g_menu_obj, 1, 0, LV_DIR_HOR);
    lv_obj_t *ble_label = lv_label_create(ble_tile);
    lv_label_set_text(ble_label, "BLE");
    lv_obj_center(ble_label);

    lv_obj_t *ssh_tile  = lv_tileview_add_tile(g_menu_obj, 2, 0, LV_DIR_HOR);
    lv_obj_t *ssh_label = lv_label_create(ssh_tile);
    lv_label_set_text(ssh_label, "SSH");
    lv_obj_center(ssh_label);

    lv_obj_add_event_cb(g_menu_obj, menu_ev_cb, LV_EVENT_ALL, interface);
}

/**
 * @brief static function
 *
 */
static void anmi_arc_set_angle(void *obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void anmi_arc_ready_cb(struct _lv_anim_t *anim)
{
    printf("animate over\n");
    if (g_anim_ready_flag) {
        lv_obj_del(anim->var);
        g_anim_ready_flag = !g_anim_ready_flag;
    }

    lv_scr_load_anim(g_menu_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 500, 0, false);
    lv_obj_center(g_menu_obj);
    // lv_obj_clear_flag(g_menu_obj, LV_OBJ_FLAG_HIDDEN);
    // lv_group_focus_obj(g_menu_obj);
}

static void terminal_ev_cb(lv_event_t *e)
{
    if (e->code == LV_EVENT_KEY) {
        printf("LV_EVENT_KEY %s\n", (char *)lv_event_get_param(e));
        e->stop_processing = true;
    }
    if (e->code == LV_EVENT_INSERT) {
        printf("LV_EVENT_INSERT %s\n", (char *)lv_event_get_param(e));
    }
    if (e->code == LV_EVENT_RELEASED) {
        if (g_anim_ready_flag) {
            lv_obj_del(g_anim_arc.var);
            g_anim_ready_flag = !g_anim_ready_flag;
        }
    }
    if (e->code == LV_EVENT_LONG_PRESSED) {
        printf("LV_EVENT_LONG_PRESSED\n");
        if (!g_anim_ready_flag) {
            lv_indev_t *dev = (lv_indev_t *)lv_event_get_param(e);
            my_animate_demo(&dev->proc.types.pointer.act_point);
            g_anim_ready_flag = !g_anim_ready_flag;
        }
    }
}

static void menu_ev_cb(lv_event_t *e)
{
    if (e->code == LV_EVENT_DEFOCUSED) {
        printf("LV_EVENT_DEFOCUSED\n");
        // lv_obj_add_flag(g_menu_obj, LV_OBJ_FLAG_HIDDEN);
    }
    if (e->code == LV_EVENT_FOCUSED) {
        printf("LV_EVENT_FOCUSED\n");
    }
    if (e->code == LV_EVENT_SCROLL) {
        printf("LV_EVENT_SCROLL\n");
    }
    if (e->code == LV_EVENT_PRESSING) {
        lv_obj_t   *obj   = lv_event_get_target(e);
        lv_indev_t *indev = lv_indev_get_act();
        if (indev == NULL) return;
        if (lv_indev_get_type(indev) != LV_INDEV_TYPE_POINTER) return;

        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);

        int32_t x = lv_obj_get_x_aligned(obj) + vect.x;
        int32_t y = lv_obj_get_y_aligned(obj) + vect.y;
        lv_obj_set_pos(obj, x, y);
    }
}

static void menu_background_ev_cb(lv_event_t *e)
{
    printf("Exit MENU\n");
    lv_scr_load(g_terminal_screen);
}