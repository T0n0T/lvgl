#include "mydemo/mydemo.h"
#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    lv_porting_init();
    printf("LVGL porting init\n");

    // lv_demo_widgets();
    my_demo_create(lv_scr_act());

    while (1) {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }
}
