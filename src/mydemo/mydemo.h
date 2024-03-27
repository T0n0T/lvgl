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

void my_demo_create(lv_obj_t *parent, void (*add_inputdev_to_group)(lv_group_t* group));
void mydemo_init(lv_obj_t *parent, void (*connect_to_keypad)(lv_group_t *group), void *interface);
void my_animate_demo(lv_point_t *p);

#endif // !__MYDEMO_H__

