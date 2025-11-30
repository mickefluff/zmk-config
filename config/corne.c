#include <zephyr/kernel.h>
#include <zephyr/display/cfb.h>
#include <zmk/display.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/usb.h>
#include <zmk/ble.h>
#include <zmk/wpm.h>
#include <zmk/keymap.h>

static int current_layer = 0;

int zmk_wpm_get_state(void);

static bool proc_layerstate_listener(const zmk_event_t *eh) {
    current_layer = zmk_keymap_highest_layer_active();
    return false;
}

ZMK_LISTENER(layer_listener, proc_layerstate_listener);
ZMK_SUBSCRIPTION(layer_listener, zmk_keymap_state_changed);

#ifdef CONFIG_ZMK_DISPLAY

static void draw_layer_status(struct zmk_disp_work_cont *cont) {
    struct display_device *display = cont->display;

    switch (current_layer) {
        case 0: // Default layer - show WPM
        {
            char wpm_str[32];
            int wpm = zmk_wpm_get_state();
            snprintf(wpm_str, sizeof(wpm_str), "⌨ WPM: %d", wpm);
            zmk_disp_put_lstr(display, 0, 0, ZMK_DISP_ALIGN_LEFT, wpm_str, true);
            break;
        }
        case 3: // Gaming layer - show gaming symbol
            zmk_disp_put_lstr(display, 0, 0, ZMK_DISP_ALIGN_LEFT, "🎮 GAMING 🎮", true);
            break;
        default:
            zmk_disp_put_lstr(display, 0, 0, ZMK_DISP_ALIGN_LEFT, zmk_keymap_layer_name(current_layer), true);
            break;
    }
}

static struct zmk_disp_work_cont disp_work;

static int corne_display_init(void) {
    disp_work.work.handler = draw_layer_status;
    return zmk_display_work_register(&disp_work);
}

SYS_INIT(corne_display_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

#endif


