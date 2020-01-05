#include QMK_KEYBOARD_H

#define _CALC_0 0
#define _CALC_1  1


enum custom_keycodes {
  NP = SAFE_RANGE,
  BL,
  CALC_SIN,
  CALC_ASIN,
  CALC_COS,
  CALC_ACOS,
  CALC_TAN,
  CALC_ATAN,
  CALC_POW,
  CALC_LCSL,
  CALC_PPLS_P,
  CALC_PMNS_P,
  CALC_PAST_P,
  CALC_PSLS_P,
  CALC_RRR,
  CALC_SQ,
  CALC_EXP,
};

void unary_bracketed(char *str){
	//send_string(const char *str)
	send_string(str);
	SEND_STRING("()"SS_TAP(X_LEFT));
}

void binary_bracketed_kc(uint16_t keycode) {
	SEND_STRING("()");
	tap_code(keycode);
	SEND_STRING("()"SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
}

void binary_bracketed_str(char *str){
	SEND_STRING("()");
	send_string(str);
	SEND_STRING("()"SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch (keycode) {
		case CALC_SIN:
			unary_bracketed("sin");
			break;
		case CALC_ASIN:
			unary_bracketed("asin");
			break;
		case CALC_COS:
			unary_bracketed("cos");
			break;
		case CALC_ACOS:
			unary_bracketed("acos");
			break;
		case CALC_TAN:
			unary_bracketed("tan");
			break;
		case CALC_ATAN:
			unary_bracketed("atan");
			break;
		case CALC_LCSL:
			register_code(KC_LCTL);
			register_code(KC_LSFT);
			tap_code(KC_LEFT);
			unregister_code(KC_LSFT);
			unregister_code(KC_LCTL);
			break;
		case CALC_PPLS_P:
			binary_bracketed_kc(KC_PPLS);
			break;
		case CALC_PMNS_P:
			binary_bracketed_kc(KC_PMNS);
			break;
		case CALC_PAST_P:
			binary_bracketed_kc(KC_PAST);
			break;
		case CALC_PSLS_P:
			binary_bracketed_kc(KC_PSLS);
			break;
		case CALC_RRR:
			tap_code(KC_RIGHT);
			tap_code(KC_RIGHT);
			tap_code(KC_RIGHT);
		case CALC_SQ:
			SEND_STRING("**2");
			break;
		case CALC_EXP:
			binary_bracketed_str("**");
			break;
		}
	} else {
	}
  return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Qwerty
	 * ,-----------------------------------------.
	 * |   0  |   1  |   4  |   7  | SIN  | ESC  |
	 * |------+------+------+------+------+------|
	 * |   .  |   2  |   5  |   8  | COS  | TAB  |---,
	 * |------+------+------+------+------+------|USB|
	 * |   =  |   3  |   6  |   9  | TAN  | BS   |---'
	 * |------+------+------+------+------+------|
	 * |   +  |   -  |   *  |   /  |   -  | FN   |
	 * `-----------------------------------------'
	 */
	[_CALC_0] = LAYOUT( \
			KC_KP_0, KC_KP_1, KC_KP_4, KC_KP_7,    CALC_SIN, MO(_CALC_1) ,  \
			KC_DOT , KC_KP_2, KC_KP_5, KC_KP_8,    CALC_COS, CALC_SQ     ,  \
			KC_ENT , KC_KP_3, KC_KP_6, KC_KP_9,    CALC_TAN, CALC_EXP    ,  \
			KC_PPLS, KC_PMNS, KC_PAST, KC_PSLS, KC_KP_MINUS, KC_ESC         \
			),
	[_CALC_1] = LAYOUT( \
			_______    , _______    , KC_LEFT    , _______    , CALC_ASIN, _______, \
			_______    , _______    , CALC_LCSL  , CALC_RRR   , CALC_ACOS, _______, \
			KC_EQL     , _______    , KC_RIGHT   , _______    , CALC_ATAN, _______, \
			CALC_PPLS_P, CALC_PMNS_P, CALC_PAST_P, CALC_PSLS_P, _______  , _______  \
			)
};

/*
//	[_BL] = LAYOUT( \
//		  BL_BRTG, _______, _______, _______, CALC_ASIN, _______, \
//		  _______, BL_OFF,  BL_TOGG, BL_ON,   CALC_ACOS, _______, \
//		  _______, _______, _______, _______, CALC_ATAN, _______, \
//		  BL_DEC,  BL_DEC,  BL_INC,  BL_INC,  _______, _______  \
//		)
*/
