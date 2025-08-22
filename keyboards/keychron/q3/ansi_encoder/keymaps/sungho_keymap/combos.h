#pragma once

#include QMK_KEYBOARD_H

enum combo_events {
    SHIFT_SPACE_ENTER,
    COMBO_LENGTH
};

const uint16_t PROGMEM shift_space_combo[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[] = {
    [SHIFT_SPACE_ENTER] = COMBO(shift_space_combo, KC_ENT)
};