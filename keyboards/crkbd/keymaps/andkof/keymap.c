#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum crkbd_layers {
    _COLEMAK,
    _RTHUMB,
    _LEFTTHUMB,    
    _FUNC
};


enum crkbd_tap_dances {
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
  [_COLEMAK] = LAYOUT( 
    _______, OE  , KC_W  ,  KC_F  ,   KC_P ,    KC_B,         KC_J ,   KC_L ,   KC_U ,    KC_Y, AA , _______,
    _______, SFT_A , ALT_R  , CTL_S   ,   CMDT ,   KC_G ,         KC_M ,  CMD_N , CTL_E ,  ALT_I ,  SFT_O , _______,
    _______, KC_Z  , KC_X ,  KC_C ,   KC_D,    KC_V,         KC_K ,   KC_H , KC_COMM, KC_DOT , AE , _______,
              KC_LCMD,LT(_LEFTTHUMB,KC_SPACE),_______,       _______, LT(_RTHUMB, KC_BSPC),LT(_FUNC,KC_TAB)
  ),

  [_LEFTTHUMB] = LAYOUT( /* [> LOWER <] */
    _______,KC_EXLM ,  KC_AT , KC_HASH, KC_DLR , KC_PERC,      KC_ESC,_______ ,A(KC_RGHT) , A(KC_LEFT) , _______,_______,
_______, LSFT_T(KC_CIRC) , KC_AMPR, KC_PAST,KC_BSLS , KC_PIPE,      _______,KC_LEFT,KC_DOWN, KC_UP  , KC_RGHT,_______,
    _______, KC_TILDE,KC_GRV,_______,_______   , KC_Q,       _______,_______,_______, _______, _______,_______,
                                    KC_TRNS, KC_TRNS,_______,_______, ALT_TAB, LCMD(KC_GRV)  
  ),

  [_RTHUMB] = LAYOUT( /* [> RAISE <] */
    _______ ,KC_PAST ,  KC_7  ,  KC_8  ,  KC_9  ,KC_PLUS ,           KC_RBRC ,KC_RPRN ,KC_RCBR ,KC_QUOT , KC_MINS,_______, 
    _______ ,KC_PSLS ,  KC_4  ,  KC_5  ,  KC_6  ,KC_MINS ,           KC_LBRC , KC_LPRN,KC_LCBR , KC_DQT , KC_UNDS,_______,
    _______ ,KC_COMM ,  KC_1 ,   KC_2  ,  KC_3  ,KC_EQL  ,           KC_COLN , KC_SCLN, KC_LT  , KC_GT  , KC_QUES,_______,
                                    KC_0, KC_ENT,_______,           _______,KC_TRNS, KC_TRNS  
  ),
  [_FUNC] = LAYOUT( /* [> RAISE <] */
    _______,QK_BOOT,  KC_F7  ,  KC_F8  ,  KC_F9  ,KC_F12 ,           RSG(KC_4) ,LCA(KC_H),LCA(KC_J) ,LCA(KC_K) , LCA(KC_L),_______, 
    _______,_______ ,  KC_F4  ,  KC_F5  ,  KC_F6  ,KC_F11 ,           _______ , C(KC_LEFT),C(KC_DOWN) ,C(KC_UP) , C(KC_LEFT),_______,
    _______,_______ ,  KC_F1 ,   KC_F2  ,  KC_F3  ,KC_F10  ,           _______ , _______, _______  , _______  ,_______,_______,
                                    OSM(MOD_MEH), LCMD(KC_SPACE),_______,_______, _______, _______  
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