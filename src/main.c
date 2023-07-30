#include "porting/lv_porting.h"
#include "lvgl.h"
#include "demos/lv_demos.h"
#include "examples/lv_examples.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
    lv_porting_init();

    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello world!!!!!!");
    lv_obj_center(label);

    // lv_demo_music();
    int a = 0;
    char ch[15];
    while (1) {
        lv_timer_handler();
        a++;
        sprintf(ch, "hello!=%d=", a);
        lv_label_set_text(label, ch);
        lv_porting_delay();
    }
}
