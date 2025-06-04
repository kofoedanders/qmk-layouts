/* Copyright 2019 COSEYFANNITUTTI
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H

// Home row mods macro
#define HRML(k1,k2,k3,k4) MT(MOD_LSFT, k1), MT(MOD_LALT, k2), MT(MOD_LCTL, k3), MT(MOD_LGUI, k4)
#define HRMR(k1,k2,k3,k4) MT(MOD_RGUI, k1), MT(MOD_RCTL, k2), MT(MOD_RALT, k3), MT(MOD_RSFT, k4)

// Custom keycodes
enum custom_keycodes {
    ALT_L = SAFE_RANGE,
    ALT_W,
    ALT_Q,
    HYPER_R,
    HYPER_U
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ALT_L:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("l"));
        }
        return false;
    case ALT_W:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("w"));
        }
        return false;
    case ALT_Q:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("q"));
        }
        return false;
    case HYPER_R:
    case HYPER_U:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_LCTL);
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        }
        return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: QWERTY base layer
    [0] = LAYOUT_all(
        ALT_L,       KC_W,       KC_E,       HYPER_R,    KC_T,       KC_Y,       HYPER_U,    KC_I,       KC_O,       ALT_W,      KC_P,       KC_BSPC,
       _______, MT(MOD_LSFT, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LGUI, KC_F), KC_G, KC_H, MT(MOD_RGUI, KC_J), MT(MOD_RCTL, KC_K), MT(MOD_RALT, KC_L), MT(MOD_RSFT, KC_ENT), 
        KC_LSFT,     ALT_Q,      KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_RSFT,
        KC_LCTL,     KC_LGUI,    KC_LALT,    LT(1, KC_SPC), LT(1, KC_SPC), LT(1, KC_SPC), LT(2, KC_BSPC), OSM(MOD_LSFT), LT(3, KC_ENT) ),

    // Layer 1: LEFTTHUMB 
    [1] = LAYOUT_all(
        KC_ESC,      KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    XXXXXXX,    KC_DEL,
        KC_CIRC,     KC_AMPR,    KC_ASTR,    KC_BSLS,    KC_PIPE,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
        _______,     KC_TILD,    KC_GRV,     XXXXXXX,    XXXXXXX,    KC_Q,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_GRV,     _______,
        _______,     _______,    _______,    _______,    _______,    _______,    KC_TAB,     _______,    _______ ),

    // Layer 2: RTHUMB 
    [2] = LAYOUT_all(
        KC_ASTR,     KC_7,       KC_8,       KC_9,       KC_PLUS,    KC_RBRC,    KC_RPRN,    KC_RCBR,    KC_QUOT,    KC_MINS,    XXXXXXX,    _______,
        KC_SLSH,     KC_4,       KC_5,       KC_6,       KC_MINS,    KC_LBRC,    KC_LPRN,    KC_LCBR,    KC_DQUO,    KC_UNDS,    XXXXXXX,
        _______,     KC_COMM,    KC_1,       KC_2,       KC_3,       KC_EQL,     KC_COLN,    KC_SCLN,    KC_LT,      KC_GT,      KC_QUES,    _______,
        _______,     _______,    _______,    KC_0,       KC_0,       KC_0,       _______,    KC_TAB,     _______ ),

    // Layer 3: FUNC
    [3] = LAYOUT_all(
        QK_BOOT,     KC_F7,      KC_F8,      KC_F9,      KC_F12,     LGUI(LSFT(KC_4)), LALT(LCTL(KC_H)), LALT(LCTL(KC_J)), LALT(LCTL(KC_K)), LALT(LCTL(KC_L)), XXXXXXX, QK_BOOT,
        XXXXXXX,     KC_F4,      KC_F5,      KC_F6,      KC_F11,     XXXXXXX,    RCTL(KC_LEFT), RCTL(KC_DOWN), RCTL(KC_UP), RCTL(KC_RIGHT), XXXXXXX,
        _______,     QK_BOOT,    KC_F1,      KC_F2,      KC_F3,      KC_F10,     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    QK_BOOT,    _______,
        _______,     _______,    _______,    _______,    _______,    _______,    KC_TAB,     _______,    _______ )
};
