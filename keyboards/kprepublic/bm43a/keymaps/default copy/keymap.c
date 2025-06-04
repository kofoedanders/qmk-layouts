/* Copyright 2019 mechmerlin
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
    _QWERTY,
    _SPACE,
    _BACKSPACE,
    _NAV
};

//Norwegian letters, EurKeys layout
#define AA   NO_LBRC
#define AE   NO_QUOT
#define OE   NO_SCLN

enum custom_keycodes {
    M1 = SAFE_RANGE,
};

 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG,
        LT(_NAV, KC_LCTL),  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    KC_ENT,
        KC_LSFT,     NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,   NO_QUES,
        KC_LCTL, KC_LALT, KC_LGUI, LT(_SPACE, KC_SPC), LT(_BACKSPACE,KC_BSPC), NO_OSTR, NO_AE  , NO_SCLN, NO_QUOT
    ),
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______,   _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,                _______,             _______, _______, _______, _______
    ),
    [_SPACE] = LAYOUT(
        NO_TILD, NO_EXLM, NO_AT, NO_HASH, NO_DLR, NO_PERC, NO_CIRC, NO_AMPR, NO_ASTR, NO_PLUS,NO_MINS,NO_EQL,
        NO_LPRN,   NO_LCBR, NO_LBRC, _______,   _______, _______, _______, NO_RBRC, NO_RCBR, NO_RPRN, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, NO_SLSH,
        _______, _______, _______, _______,                _______,             _______, _______, NO_COLN, NO_DQUO
    ),
    [_BACKSPACE] = LAYOUT(
        KC_ESC,   NO_Q, NO_7, NO_8, NO_9, NO_PLUS, _______, _______, KC_F9, KC_F10, KC_F11, KC_F12,
        NO_GRV ,   NO_ASTR, NO_4, NO_5,   NO_6, NO_MINS, _______, KC_5, KC_F6, KC_F7, KC_F8,
        NO_COMM,     NO_1, NO_2, NO_3, _______, NO_EQL, _______, KC_F1, KC_F2, KC_F3, KC_F4,
        _______, _______, NO_COMM, NO_0,                _______,             _______, _______, _______, QK_BOOT
   
    )
};