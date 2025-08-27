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

static bool shift_super_active = false;

static bool handle_super_key_with_shift(uint16_t keycode, keyrecord_t *record) {
    // Handle SUPER key press/release when SHIFT is held
    if (keycode == KC_LWIN) {
        if (record->event.pressed && (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
            // SHIFT is held and SUPER is pressed - suppress SUPER and mark as active
            shift_super_active = true;
            return false;
        }
        if (!record->event.pressed && shift_super_active) {
            // SUPER is released while shift_super_active - suppress release
            shift_super_active = false;
            return false;
        }
    }
    
    // Reset shift_super_active when SHIFT is released
    if ((keycode == KC_LSFT || keycode == KC_RSFT) && !record->event.pressed && shift_super_active) {
        shift_super_active = false;
    }
    
    return true;
}

static bool handle_super_arrows(uint16_t keycode, keyrecord_t *record) {
    // Handle SUPER+Up/Down for moving lines (Option+Up/Down in VS Code)
    if ((keycode == KC_UP || keycode == KC_DOWN) && ((get_mods() & MOD_BIT(KC_LWIN)) || shift_super_active) && !(get_mods() & MOD_BIT(KC_LCTL))) {
        if (record->event.pressed) {
            uint8_t saved_mods = get_mods();
            bool shift_held = saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
            clear_mods();
            if (shift_held) {
                tap_code16(LSFT(LALT(keycode)));
            } else {
                tap_code16(LALT(keycode));
            }
            set_mods(saved_mods);
        }
        return false;
    }
    
    // Handle SUPER+Left/Right for word navigation
    if ((keycode == KC_LEFT || keycode == KC_RGHT) && ((get_mods() & MOD_BIT(KC_LWIN)) || shift_super_active) && !(get_mods() & MOD_BIT(KC_LCTL))) {
        if (record->event.pressed) {
            uint8_t saved_mods = get_mods();
            bool shift_held = saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
            clear_mods();
            if (shift_held) {
                tap_code16(LSFT(LCTL(keycode)));
            } else {
                tap_code16(LCTL(keycode));
            }
            set_mods(saved_mods);
        }
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

// static bool handle_ctrl_shift_4(uint16_t keycode, keyrecord_t *record) {
//     if (keycode == KC_4 && (get_mods() & MOD_BIT(KC_LCTL)) && (get_mods() & MOD_BIT(KC_LSFT))) {
//         if (record->event.pressed) {
//             clear_mods();
//             tap_code(KC_PSCR);
//             add_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
//         }
//         return false;
//     }
//     return true;
// }

static bool handle_super_c(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_C && (get_mods() & MOD_BIT(KC_LWIN)) && !(get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)))) {
        if (record->event.pressed) {
            del_mods(MOD_BIT(KC_LWIN));
            tap_code16(LCTL(KC_C));
            add_mods(MOD_BIT(KC_LWIN));
        }
        return false;
    }
    return true;
}

static bool handle_shift_space(uint16_t keycode, keyrecord_t *record) {
    // Only handle SHIFT+SPACE (SPACE pressed while SHIFT is already held)
    if (keycode == KC_SPC && record->event.pressed && (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
        // Store current modifiers, remove shift, send SPACE, restore modifiers
        uint8_t saved_mods = get_mods();
        clear_mods();
        tap_code(KC_SPC);
        set_mods(saved_mods);
        return false;
    }
    
    return true;
}

static bool handle_ctrl_space(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_SPC && (get_mods() & MOD_BIT(KC_LCTL)) && !(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) {
        if (record->event.pressed) {
            // Send Windows key to open Start menu
            uint8_t saved_mods = get_mods();
            clear_mods();
            tap_code(KC_LWIN);
            set_mods(saved_mods);
        }
        return false;
    }
    return true;
}

static bool handle_ctrl_q(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_Q && (get_mods() & MOD_BIT(KC_LCTL))) {
        if (record->event.pressed) {
            clear_mods();
            tap_code16(LALT(KC_F4));
            add_mods(MOD_BIT(KC_LCTL));
        }
        return false;
    }
    return true;
}

static bool handle_caps_lock(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_CAPS) {
        if (record->event.pressed) {
            tap_code16(LGUI(KC_SPC));
        }
        return false;
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
    // Only process macOS keys when WIN_BASE is the default layer
    if (get_highest_layer(default_layer_state) != WIN_BASE) {
        return true;
    }
    
    if (!handle_super_key_with_shift(keycode, record)) return false;
    if (!handle_ctrl_tab(keycode, record)) return false;
    if (!handle_ctrl_grave(keycode, record)) return false;
    if (!handle_super_arrows(keycode, record)) return false;
    if (!handle_ctrl_arrows(keycode, record)) return false;
    // if (!handle_ctrl_shift_4(keycode, record)) return false;
    if (!handle_super_c(keycode, record)) return false;
    if (!handle_ctrl_q(keycode, record)) return false;
    if (!handle_ctrl_space(keycode, record)) return false;
    if (!handle_shift_space(keycode, record)) return false;
    if (!handle_caps_lock(keycode, record)) return false;
    if (!handle_ctrl_release(keycode, record)) return false;
    return true;
}