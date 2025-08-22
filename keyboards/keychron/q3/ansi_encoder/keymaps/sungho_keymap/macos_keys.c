#include QMK_KEYBOARD_H

static bool ctrl_tab_active = false;
static bool ctrl_grave_active = false;

static bool handle_ctrl_tab(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_TAB && record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LCTL)) {
            if (!ctrl_tab_active) {
                del_mods(MOD_BIT(KC_LCTL));
                register_code(KC_LWIN);
                ctrl_tab_active = true;
            }
            register_code(KC_TAB);
            return false;
        }
    }
    if (keycode == KC_TAB && !record->event.pressed && ctrl_tab_active) {
        unregister_code(KC_TAB);
        return false;
    }
    return true;
}

static bool handle_ctrl_grave(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_GRV && record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LCTL)) {
            if (!ctrl_grave_active) {
                del_mods(MOD_BIT(KC_LCTL));
                register_code(KC_LWIN);
                ctrl_grave_active = true;
            }
            register_code(KC_GRV);
            return false;
        }
    }
    if (keycode == KC_GRV && !record->event.pressed && ctrl_grave_active) {
        unregister_code(KC_GRV);
        return false;
    }
    return true;
}

static bool handle_ctrl_arrows(uint16_t keycode, keyrecord_t *record) {
    if (get_mods() & MOD_BIT(KC_LCTL)) {
        if (keycode == KC_LEFT && record->event.pressed) {
            del_mods(MOD_BIT(KC_LCTL));
            register_code(KC_HOME);
            add_mods(MOD_BIT(KC_LCTL));
            return false;
        }
        if (keycode == KC_LEFT && !record->event.pressed) {
            unregister_code(KC_HOME);
            return false;
        }
        if (keycode == KC_RGHT && record->event.pressed) {
            del_mods(MOD_BIT(KC_LCTL));
            register_code(KC_END);
            add_mods(MOD_BIT(KC_LCTL));
            return false;
        }
        if (keycode == KC_RGHT && !record->event.pressed) {
            unregister_code(KC_END);
            return false;
        }
    }
    return true;
}


static bool handle_ctrl_release(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LCTL && !record->event.pressed) {
        if (ctrl_tab_active) {
            unregister_code(KC_LWIN);
            ctrl_tab_active = false;
            return false;
        }
        if (ctrl_grave_active) {
            unregister_code(KC_LWIN);
            ctrl_grave_active = false;
            return false;
        }
    }
    return true;
}

bool process_macos_keys(uint16_t keycode, keyrecord_t *record) {
    if (!handle_ctrl_tab(keycode, record)) return false;
    if (!handle_ctrl_grave(keycode, record)) return false;
    if (!handle_ctrl_arrows(keycode, record)) return false;
    if (!handle_ctrl_release(keycode, record)) return false;
    return true;
}