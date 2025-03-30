#pragma once

#include QMK_KEYBOARD_H

enum {
    TD_SLP,
};

void dance_sleep_finished(tap_dance_state_t *state, void *user_data);
void dance_boot_finished(tap_dance_state_t *state, void *user_data);
tap_dance_action_t tap_dance_actions[];
void dance_sleep_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && !state->pressed) {
        // do nothing
    } else if (state->pressed) {
        // Long press = sleep (Command + Control + S)
        register_mods(MOD_LCTL | MOD_LGUI);
        tap_code(KC_S);
        unregister_mods(MOD_LCTL | MOD_LGUI);
    }
}
void dance_sleep_reset(tap_dance_state_t *state, void *user_data) {
    // Nothing needed here for now
}
tap_dance_action_t tap_dance_actions[] = {
    [TD_SLP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sleep_finished, dance_sleep_reset),
};
