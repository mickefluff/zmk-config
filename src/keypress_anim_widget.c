/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>

#include "keypress_anim_widget.h"

/*
 * Placeholder text-based animation frames, one per keypress. Swap these for
 * real `lv_img_dsc_t` bitmap frames (e.g. generated with LVGL's online image
 * converter, https://lvgl.io/tools/imageconverter) once you have artwork, by
 * replacing the label below with an `lv_img` object and calling
 * `lv_img_set_src()` with the frame array instead of `lv_label_set_text()`.
 */
static const char *const frames[] = {
    "  o  ", " /|\\ ", " / \\ ", "     ",
};
#define NUM_FRAMES (sizeof(frames) / sizeof(frames[0]))

static lv_obj_t *anim_label;
static uint8_t frame_index;

static void advance_frame_work_handler(struct k_work *work) {
    if (!anim_label) {
        return;
    }

    frame_index = (frame_index + 1) % NUM_FRAMES;
    lv_label_set_text(anim_label, frames[frame_index]);
}

static K_WORK_DEFINE(advance_frame_work, advance_frame_work_handler);

void keypress_anim_widget_pulse(void) { k_work_submit(&advance_frame_work); }

int keypress_anim_widget_init(struct keypress_anim_widget *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 64, 32);
    lv_obj_set_style_border_width(widget->obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(widget->obj, 0, LV_PART_MAIN);

    anim_label = lv_label_create(widget->obj);
    lv_label_set_text(anim_label, frames[0]);
    lv_obj_center(anim_label);

    return 0;
}

lv_obj_t *keypress_anim_widget_obj(struct keypress_anim_widget *widget) { return widget->obj; }
