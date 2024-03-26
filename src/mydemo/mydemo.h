/**
 * @file mydemo.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __MYDEMO_H__
#define __MYDEMO_H__

#include "lvgl.h"
#include <stdio.h>

void my_demo_create(lv_obj_t * parent);
void my_serial_demo(lv_obj_t * parent);
void my_animate_demo(lv_point_t *p, lv_anim_ready_cb_t ready_cb);

#endif // !__MYDEMO_H__

