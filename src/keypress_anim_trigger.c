/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>

#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/split/central.h>

/*
 * Name of the peripheral-side behavior (see config/corne_right.overlay) that
 * advances the keypress animation widget. Must match its devicetree `label`
 * property and fit within ZMK_SPLIT_RUN_BEHAVIOR_DEV_LEN (9 bytes incl. NUL).
 *
 * Central is the only side that observes keypresses from *both* halves (the
 * peripheral only knows about its own physical keys), so it is responsible
 * for remotely invoking this behavior on every connected peripheral whenever
 * any key, on either half, is pressed.
 */
#define ANIM_PULSE_BEHAVIOR_DEV "ANIMKEY"

static int keypress_anim_trigger_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);

    if (ev == NULL || !ev->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    struct zmk_behavior_binding binding = {
        .behavior_dev = ANIM_PULSE_BEHAVIOR_DEV,
    };
    struct zmk_behavior_binding_event event = {
        .position = ev->position,
        .timestamp = ev->timestamp,
    };

    for (int i = 0; i < ZMK_SPLIT_CENTRAL_PERIPHERAL_COUNT; i++) {
        zmk_split_central_invoke_behavior(i, &binding, event, true);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(keypress_anim_trigger, keypress_anim_trigger_listener);
ZMK_SUBSCRIPTION(keypress_anim_trigger, zmk_position_state_changed);
