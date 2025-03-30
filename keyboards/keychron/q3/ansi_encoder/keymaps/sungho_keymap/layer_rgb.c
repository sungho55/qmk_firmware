#include "rgb_matrix.h"

static uint8_t saved_rgb_mode;
static uint8_t saved_rgb_hue;
static uint8_t saved_rgb_sat;
static uint8_t saved_rgb_val;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == MAC_FN) {
        saved_rgb_mode = rgb_matrix_get_mode();
        HSV hsv = rgb_matrix_get_hsv();
        saved_rgb_hue = hsv.h;
        saved_rgb_sat = hsv.s;
        saved_rgb_val = hsv.v;

        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(234, 255, 255); // Pink
    } else {
        rgb_matrix_mode_noeeprom(saved_rgb_mode);
        rgb_matrix_sethsv_noeeprom(saved_rgb_hue, saved_rgb_sat, saved_rgb_val);
    }
    return state;
}