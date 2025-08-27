#include QMK_KEYBOARD_H

static bool handle_shift_enter(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_ENT && (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) && !(get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LWIN)))) {
        if (record->event.pressed) {
            uint8_t saved_mods = get_mods();
            clear_mods();
            tap_code16(LALT(KC_ENT));
            set_mods(saved_mods & ~(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));
        }
        return false;
    }
    return true;
}

bool process_claude_keys(uint16_t keycode, keyrecord_t *record) {
    // Only process claude keys when WIN_BASE is the default layer
    if (get_highest_layer(default_layer_state) != WIN_BASE) {
        return true;
    }
    
    if (!handle_shift_enter(keycode, record)) return false;
    return true;
}