/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <lvgl.h>

#include <zmk/display/status_screen.h>
#include <zmk/display/widgets/peripheral_status.h>

#include "keypress_anim_widget.h"

static struct zmk_widget_peripheral_status peripheral_status_widget;
static struct keypress_anim_widget anim_widget;

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    zmk_widget_peripheral_status_init(&peripheral_status_widget, screen);
    lv_obj_align(zmk_widget_peripheral_status_obj(&peripheral_status_widget), LV_ALIGN_TOP_LEFT, 0,
                 0);

    keypress_anim_widget_init(&anim_widget, screen);
    lv_obj_align(keypress_anim_widget_obj(&anim_widget), LV_ALIGN_BOTTOM_MID, 0, 0);

    return screen;
}
