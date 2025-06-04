#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ferris_layers {
    _COLEMAK,
    _NUM,
    _NAV,
    _SYM,    
    _FUNC
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

#define NUM_OSSHF TD(NUMOSSHF)


bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALTTAB,
  NUMOSSHF //Nav when held one shot mod shift on
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(tap_dance_state_t *state);

void NUMOSSHF_finished(tap_dance_state_t *state, void *user_data);
void NUMOSSHF_reset(tap_dance_state_t *state, void *user_data);



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT( 
    OE  , KC_W  ,  KC_F  ,   KC_P ,   KC_B,         KC_J ,   KC_L ,   KC_U ,    KC_Y, AA ,
    SFT_A , ALT_R  , CTL_S , CMDT ,  KC_G ,        KC_M ,  CMD_N , CTL_E ,  ALT_I ,  SFT_O , 
    KC_Z  , KC_X ,  KC_C ,   KC_D,    KC_V,         KC_K ,   KC_H , KC_COMM, KC_DOT , AE , 
            LT(_SYM,KC_TAB),LT(_NAV,KC_SPACE),       NUM_OSSHF,LT(_FUNC,KC_BSPC)
  ),

  [_SYM] = LAYOUT( 
    KC_EXLM ,  KC_AT , KC_HASH, KC_DLR , KC_PERC,      KC_RBRC , KC_RPRN,KC_RCBR ,KC_QUOT , KC_MINS,
    KC_CIRC , KC_AMPR, KC_PAST,KC_BSLS , KC_PIPE,      KC_LBRC , KC_LPRN,KC_LCBR , KC_DQT , KC_UNDS,  
    KC_TILDE,KC_GRV  ,_______ ,KC_PSLS , KC_Q,         KC_COLN , KC_SCLN, KC_LT  , KC_GT  , KC_QUES,
                                    _______, _______, _______, _______  
  ),

  [_NAV] = LAYOUT(
    _______ , _______, _______ , _______  ,_______,      KC_ESC ,KC_HOME ,A(KC_RGHT), A(KC_LEFT) , KC_END,
    KC_LSFT , KC_LALT, KC_LCTL, KC_LGUI  ,_______,      _______,KC_LEFT ,KC_DOWN   , KC_UP  , KC_RGHT,      
    UNDO    , CUT    , COPY    , PASTE    ,REDO   ,      _______,_______ , _______ , _______ ,_______,
                                    _______, _______, ALTTAB, ALTGRV 
  ),

  [_NUM] = LAYOUT( /* [> RAISE <] */
    KC_PAST ,  KC_7  ,  KC_8  ,  KC_9  ,KC_PLUS ,           _______ , _______, _______  , _______  ,_______,
    KC_PSLS ,  KC_4  ,  KC_5  ,  KC_6  ,KC_MINS ,           _______ , KC_RGUI, KC_RCTL  , KC_RALT  ,KC_RSFT,
    KC_COMM ,  KC_1 ,   KC_2  ,  KC_3  ,KC_EQL  ,           _______ , _______, _______  , _______  ,_______,
                                    KC_0, KC_ENT,           _______, _______  
  ),
  [_FUNC] = LAYOUT( /* [> RAISE <] */
    QK_BOOT,  KC_F7  ,  KC_F8  ,  KC_F9  ,KC_F12 ,           RSG(KC_4) ,LCA(KC_H),LCA(KC_J) ,LCA(KC_K) , LCA(KC_L), 
    _______ ,  KC_F4  ,  KC_F5  ,  KC_F6  ,KC_F11 ,           _______ , C(KC_H),C(KC_J) ,C(KC_K) , C(KC_L), 
    _______ ,  KC_F1 ,   KC_F2  ,  KC_F3  ,KC_F10  ,           _______ , _______, _______  , _______  ,_______, 
                                    OSM(MOD_MEH), LCMD(KC_SPACE), _______, _______  
  )
};


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}


void NUMOSSHF_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUM); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term

            break;
        default:
            break;
    }
}

void NUMOSSHF_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            clear_oneshot_mods();layer_off(_NUM); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [NUMOSSHF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NUMOSSHF_finished, NUMOSSHF_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALTTAB:
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