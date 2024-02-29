#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"
#include <libs/ffmpeg/lv_example_ffmpeg.h>
#include <stdio.h>
#include <widgets/lv_example_widgets.h>

int main(int argc, char const *argv[])
{
    lv_porting_init();
    printf("LVGL porting init\n");

    // lv_demo_widgets();
    lv_example_ffmpeg_2();

    while (1) {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }
}
