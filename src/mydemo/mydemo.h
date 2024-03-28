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

struct protocol_interface {
    void (*init)(void*);
	void (*send_data)(uint8_t *data, uint16_t len);
};

void mydemo_init(lv_obj_t *parent, void (*connect_to_keypad)(lv_group_t *group), void *interface);
void mydemo_init1(lv_obj_t *parent, void (*connect_to_keypad)(lv_group_t *group), void *interface);
void mydemo_init2(lv_obj_t *parent, void (*add_inputdev_to_group)(lv_group_t* group), void *interface);

#endif // !__MYDEMO_H__

