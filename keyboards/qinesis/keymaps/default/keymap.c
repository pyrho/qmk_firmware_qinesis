#include "kb.h"

#define BASE 0 // default layer
#define QWE 1 // alternate layer
#define ALT 2 // alternate layer


typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  X_MULTI_MOD = 0,
  SOME_OTHER_DANCE
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

enum custom_keycodes {
  GUISPACE = SAFE_RANGE,
  SHIT_PW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = KEYMAP(
		KC_EQL   , KC_1   , KC_2    , KC_3     , KC_4    , KC_5           , KC_6        , KC_7        , KC_8     , KC_9   , KC_0      , KC_MINS   ,
		KC_TAB   , KC_Q   , KC_W    , KC_F     , KC_P    , KC_G           , KC_J        , KC_L        , KC_U     , KC_Y   , KC_SCOLON , KC_BSLASH ,
		KC_LCTRL , KC_A   , KC_R    , KC_S     , KC_T    , KC_D           , KC_H        , KC_N        , KC_E     , KC_I   , KC_O      , KC_QUOTE  ,
		KC_LSFT  , KC_Z   , KC_X    , KC_C     , KC_V    , KC_B           , KC_K        , KC_M        , KC_COMMA , KC_DOT , KC_SLASH  , KC_RSFT   ,

		                KC_GRV   , KC_HYPR  , KC_LEFT , KC_RIGHT           , KC_DOWN   , KC_UP , KC_LBRACKET , KC_RBRACKET ,


	KC_BSPC  , CTL_T(KC_ESCAPE) , TD(X_MULTI_MOD)  , MO(ALT)  , KC_MEH   , KC_LGUI ,     KC_LGUI , KC_RCTL, MO(ALT),TD(X_MULTI_MOD),KC_ENT    , KC_SPC

    ),

	[QWE] = KEYMAP(
		KC_EQL   , KC_1   , KC_2    , KC_3     , KC_4    , KC_5           , KC_6        , KC_7        , KC_8     , KC_9   , KC_0      , KC_MINS   ,
		KC_TAB   , KC_Q   , KC_W    , KC_E     , KC_R    , KC_T           , KC_Y        , KC_U        , KC_I     , KC_O   , KC_P      , KC_BSLASH ,
		KC_LCTRL , KC_A   , KC_S    , KC_D     , KC_F    , KC_G           , KC_H        , KC_J        , KC_K     , KC_L   , KC_SCOLON , KC_QUOTE  ,
		KC_LSFT  , KC_Z   , KC_X    , KC_C     , KC_V    , KC_B           , KC_N        , KC_M        , KC_COMMA , KC_DOT , KC_SLASH  , KC_RSFT   ,

		                KC_GRV   , KC_HYPR  , KC_LEFT , KC_RIGHT           , KC_DOWN   , KC_UP , KC_LBRACKET , KC_RBRACKET ,

	KC_BSPC  , KC_ESCAPE , KC_LALT  , MO(ALT)  , KC_LCTRL , KC_LGUI ,     KC_LGUI , KC_LCTL, MO(ALT), KC_RALT  , KC_ENT    , KC_SPC

    ),



	[ALT] = KEYMAP(
		KC_F11              , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5           , KC_F6   , KC_F7   , KC_F8   , KC_F9    , KC_F10  , KC_F12            ,
		KC_MEDIA_NEXT_TRACK , SHIT_PW , KC_TRNS , KC_MS_BTN1 , KC_MS_BTN2 , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_AUDIO_VOL_UP   ,
		KC_MEDIA_PLAY_PAUSE , KC_TRNS , KC_MS_LEFT , KC_MS_UP , KC_MS_DOWN , KC_MS_RIGHT         , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , KC_TRNS , KC_AUDIO_MUTE     ,
		KC_MEDIA_PREV_TRACK , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS         , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS  , KC_TRNS , KC_AUDIO_VOL_DOWN ,

		                      RESET     , KC_TRNS , KC_HOME , KC_END                  , KC_PGDN , KC_PGUP         , KC_TRNS , KC_TRNS ,

		KC_TRNS             , KC_TRNS , KC_TRNS , DF(QWE) , KC_TRNS , KC_TRNS         , KC_TRNS , KC_TRNS , DF(BASE) , KC_TRNS  , KC_TRNS , KC_TRNS)          ,

    /*
	[ALT] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        */
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	/* keyevent_t event = record->event; */

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case SHIT_PW:
            if (record->event.pressed) {
                SEND_STRING("Azerty12!");
                return false;
            }
            break;
        case GUISPACE:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                return false;
            }
            break;

    }
	return true; // Let QMK send the enter press/release events
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (!state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    // case SINGLE_TAP: register_code(KC_X); break;
    case SINGLE_HOLD: register_code(KC_RALT); break;
    // case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: register_code(KC_RGUI); break;
    // case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    case TRIPLE_HOLD: register_code(KC_RCTRL); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    // case SINGLE_TAP: unregister_code(KC_X); break;
    case SINGLE_HOLD: unregister_code(KC_RALT); break;
    // case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: unregister_code(KC_RGUI);
    // case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    case TRIPLE_HOLD: unregister_code(KC_RCTRL); break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [X_MULTI_MOD]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
