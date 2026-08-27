/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

struct keypress_anim_widget {
    sys_snode_t node;
    lv_obj_t *obj;
};

int keypress_anim_widget_init(struct keypress_anim_widget *widget, lv_obj_t *parent);
lv_obj_t *keypress_anim_widget_obj(struct keypress_anim_widget *widget);

/* Advances the animation by one frame. Safe to call from any thread. */
void keypress_anim_widget_pulse(void);
