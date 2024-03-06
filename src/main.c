#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"
#include "mydemo/mydemo.h"
#include "ui/ui.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    lv_porting_init();
    printf("LVGL porting init\n");

    ui_init();
    // my_demo_create(lv_scr_act());
    // lv_example_ffmpeg_1();
    // lv_example_arc_1();
    while (1) {
        lv_timer_handler();
        lv_porting_delay();
    }
}
