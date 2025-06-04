#include QMK_KEYBOARD_H

enum ferris_layers {
    _COLEMAK,
    _RTHUMB,
    _LEFTTHUMB,    
    _FUNC
};

enum ferris_tap_dances {
  TD_Q_ESC
};

//aliases for Navigation layer
#define CLFT   LCTL(KC_LEFT) // move cursor one word back
#define CRGT   LCTL(KC_RGHT) // move cursor one word forward
#define CUT   LCMD(KC_X)
#define COPY   LCMD(KC_C)
#define PASTE   LCMD(KC_V)
#define UNDO   LCMD(KC_Z)
#define REDO   LSG(KC_Z)

#define ALTGRV   LCMD(KC_GRV)

//Norwegian letters, EurKeys layout
#define AA   LALT(KC_W)
#define AE   LALT(KC_Q)
#define OE   LALT(KC_L)

#define SftSpc LSFT_T(KC_SPC)

// Left-hand home row mods
#define SFT_A LSFT_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define CTL_S LCTL_T(KC_S)
#define CMDT CMD_T(KC_T)


// Right-hand home row mods
#define SFT_O RSFT_T(KC_O)
#define ALT_I LALT_T(KC_I)
#define CTL_E RCTL_T(KC_E)
#define CMD_N CMD_T(KC_N)


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_planck_grid(
    OE   , KC_W  ,  KC_F  ,   KC_P ,    KC_B,   _______, _______, KC_J ,   KC_L ,   KC_U ,    KC_Y, AA ,
    SFT_A , ALT_R  , CTL_S   ,   CMDT , KC_G,   _______, _______, KC_M ,  CMD_N , CTL_E ,  ALT_I ,  SFT_O ,
    KC_Z  , KC_X ,  KC_C ,   KC_D,    KC_V,    _______, _______, KC_K ,   KC_H , KC_COMM, KC_DOT , AE ,  
    _______, _______, _______,KC_LCMD,LT(_LEFTTHUMB,KC_SPACE), _______, _______, LT(_RTHUMB, KC_BSPC),LT(_FUNC,KC_TAB), _______, _______,   _______
),

[_LEFTTHUMB] = LAYOUT_planck_grid(
    KC_EXLM ,  KC_AT , KC_HASH, KC_DLR , KC_PERC,  _______, _______, KC_ESC,_______ ,A(KC_RGHT) , A(KC_LEFT) , _______,
LSFT_T(KC_CIRC), KC_AMPR, KC_PAST,KC_BSLS , KC_PIPE,   _______, _______,  _______,KC_LEFT,KC_DOWN, KC_UP  , KC_RGHT,
    KC_TILDE,KC_GRV,_______,_______   , KC_Q,   _______, _______, _______,_______,_______, _______, _______, 
    _______, _______, _______, _______,  _______,  _______, _______, ALT_TAB, LCMD(KC_GRV),  _______, _______,   _______
),

[_RTHUMB] = LAYOUT_planck_grid(
    KC_PAST ,  KC_7  ,  KC_8  ,  KC_9  ,KC_PLUS ,   _______, _______, KC_RBRC ,KC_RPRN ,KC_RCBR ,KC_QUOT , KC_MINS,
    KC_PSLS ,  KC_4  ,  KC_5  ,  KC_6  ,KC_MINS ,   _______, _______, KC_LBRC , KC_LPRN,KC_LCBR , KC_DQT , KC_UNDS, 
    KC_COMM ,  KC_1 ,   KC_2  ,  KC_3  ,KC_EQL  ,   _______, _______, KC_COLN , KC_SCLN, KC_LT  , KC_GT  , KC_QUES, 
    _______, _______, _______ ,  KC_0, KC_ENT   ,   _______, _______, _______,  _______, _______, _______,   _______
),
[_FUNC] = LAYOUT_planck_grid(
    QK_BOOT,  KC_F7  ,  KC_F8  ,  KC_F9  ,KC_F12 ,   _______, _______, RSG(KC_4) ,LCA(KC_H),LCA(KC_J) ,LCA(KC_K) , LCA(KC_L), 
    _______ , KC_F4  ,  KC_F5  ,  KC_F6  ,KC_F11 ,   _______, _______, _______ , C(KC_LEFT),C(KC_DOWN) ,C(KC_UP) , C(KC_LEFT),
    _______ , KC_F1  ,  KC_F2  ,  KC_F3  ,KC_F10  ,  _______, _______, _______ , _______, _______  , _______  ,_______,
    _______, _______, _______ ,  OSM(MOD_MEH), LCMD(KC_SPACE),   _______, _______, _______,  _______, _______, _______,   _______
)
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LCMD);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LCMD);
      is_alt_tab_active = false;
    }
  }
}