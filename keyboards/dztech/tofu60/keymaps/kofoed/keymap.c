/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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

#include "keymap_norwegian.h" 

enum layers {
    _WIN,
    _WIN2,
    _MAC,
    _MAC2,
    _FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN] = LAYOUT_all(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ALGR(KC_W), KC_RBRC, KC_NUHS,
        MO(_WIN2), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    ALGR(KC_L), ALGR(KC_Q),          KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_INS,
        KC_LCTL, KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_RGUI, KC_RALT, _______, MO(_FUNC)
    ),
    [_WIN2] = LAYOUT_all(
        QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,  KC_BSPC, KC_DEL,
        KC_TAB,  _______,RALT(KC_RIGHT), _______,LCTL(KC_R), LCTL(KC_T),    _______,    _______,    _______,    _______,    _______,    KC_LBRC, _______, KC_NUHS,
        _______, LCTL(KC_A), LCTL(KC_S), LCTL(KC_D), LCTL(KC_F),    _______,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,   KC_SCLN, KC_QUOT, LCTL(KC_ENT),
        KC_LSFT, _______, LCTL(KC_Z),    LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V),    RALT(KC_LEFT),    _______,    _______,    _______, LCTL(KC_DOT),  _______, KC_RSFT, KC_INS,
        KC_LCTL, KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_RGUI,KC_RALT,  _______,_______
    ),
    [_MAC] = LAYOUT_all(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    RALT(KC_W), KC_RBRC, KC_NUHS,
        MO(_MAC2), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    RALT(KC_L), RALT(KC_Q),          KC_ENT,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_INS,
        KC_LCTL, KC_LALT, KC_LGUI,                                     KC_SPC,                   _______, _______,  _______, MO(_FUNC)
    ),
    [_MAC2] = LAYOUT_all(
        QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,  KC_BSPC, KC_DEL,
        KC_TAB,  _______,LGUI(KC_RIGHT), _______,LGUI(KC_R), LGUI(KC_T),    _______,    _______,    _______,    _______,    _______,    KC_LBRC, _______, KC_NUHS,
        _______, LGUI(KC_A), LGUI(KC_S), LGUI(KC_D), LGUI(KC_F),    _______,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,   KC_SCLN, KC_QUOT, LGUI(KC_ENT),
        KC_LSFT, _______, LGUI(KC_Z),    LGUI(KC_X),    LGUI(KC_C),    LGUI(KC_V),    LGUI(KC_LEFT),    _______,    _______,    _______, LGUI(KC_DOT),  _______, KC_RSFT, KC_INS,
        KC_LCTL, KC_LALT, KC_LGUI,                                     KC_SPC,                    KC_RGUI,KC_RALT,  _______,_______
    ),
    [_FUNC] = LAYOUT_all(
        QK_BOOT, _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______, _______,  _______, _______,
        _______,  _______,    PDF(_WIN),    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, _______,
        _______, _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______, _______,          _______,
        _______, _______, _______,    _______,    _______,    _______,    _______,     PDF(_MAC),    _______,    _______, _______,  _______, _______, _______,
        _______, _______, _______,                                     _______,                    _______, _______,  _______, _______
    )
};


