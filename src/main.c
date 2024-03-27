#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"
#include "mydemo/mydemo.h"
#include "ui/ui.h"
#include <stdio.h>

extern lv_indev_t *keyboard_indev;

void add_keypad(lv_group_t *group)
{
    lv_indev_set_group(keyboard_indev, group);
}

int main(int argc, char const *argv[])
{
    lv_porting_init();
    printf("LVGL porting init\n");

    // ui_init();
    // my_demo_create(lv_scr_act());
    mydemo_init(lv_scr_act(), add_keypad, NULL);
    // my_animate_demo(NULL, NULL);
    // lv_example_ffmpeg_1();
    // lv_example_arc_1();
    // lv_demo_keypad_encoder();

    lv_porting_looper();
}
