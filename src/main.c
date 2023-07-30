#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"

int main(int argc, char const *argv[])
{
    lv_porting_init();

    // lv_obj_t *label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, "Hello world!!!!!!");
    // lv_obj_center(label);

    lv_demo_music();

    while (1) {
        lv_timer_handler();
        lv_porting_delay();
    }
}
