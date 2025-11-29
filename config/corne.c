#ifdef CONFIG_ZMK_DISPLAY

#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

#include <lvgl.h>

static uint8_t current_layer = 0;

static int on_layer_change(const zmk_event_t *eh) {
    struct zmk_layer_state_changed *ev = as_zmk_layer_state_changed(eh);
    if (ev != NULL) {
        current_layer = ev->layer;
    }
    return 0;
}

ZMK_LISTENER(corne_display, on_layer_change);
ZMK_SUBSCRIPTION(corne_display, zmk_layer_state_changed);

void zmk_disp_put_lv_objs(lv_obj_t *root) {
    lv_obj_t *label = lv_label_create(root);
    
    // Create layer indicator
    switch(current_layer) {
        case 0:
            lv_label_set_text(label, "Layer1: QWERTY");
            break;
        case 1:
            lv_label_set_text(label, "Layer2: LOWER");
            break;
        case 2:
            lv_label_set_text(label, "Layer3: RAISE");
            break;
        case 3:
            lv_label_set_text(label, "⌨ NUMPAD ⌨");
            break;
        default:
            lv_label_set_text(label, "Layer: Unknown");
    }
    
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

#endif

