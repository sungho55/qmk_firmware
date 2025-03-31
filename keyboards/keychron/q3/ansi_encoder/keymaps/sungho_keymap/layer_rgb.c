#include "rgb_matrix.h"

static uint8_t keys_pressed = 0;
#define DEFAULT_RGB_MODE RGB_MATRIX_JELLYBEAN_RAINDROPS

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(DEFAULT_RGB_MODE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keys_pressed == 0) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
        }
        keys_pressed++;
    } else {
        if (keys_pressed > 0) {
            keys_pressed--;
            if (keys_pressed == 0) {
                rgb_matrix_mode_noeeprom(DEFAULT_RGB_MODE);
            }
        }
    }
    return true;
}

void suspend_power_down_user(void) {
    rgb_matrix_set_color_all(0, 0, 0);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_mode_noeeprom(DEFAULT_RGB_MODE);
}