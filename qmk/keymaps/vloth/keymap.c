#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  VSAVE,
  VDEL,
};

enum combos {
  KL_ALT,
  SD_ALT,
};

const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [KL_ALT] = COMBO(kl_combo, KC_LALT),
  [SD_ALT] = COMBO(sd_combo, KC_RALT),
};

#define KC_XXXXX KC_NO
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_LZ LSFT_T(KC_Z)
#define KC_GE LGUI_T(KC_ENT)
#define KC_RT RSFT_T(KC_TAB)
#define KC_CQ LCTL_T(KC_QUOT)
#define KC_CE LGUI(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_QWERTY] = LAYOUT( 
   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  		  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  \
//|------+------+------+------+------|     |------+------+------+------+-------|
   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  		  KC_H,  KC_J,  KC_K,  KC_L,  KC_CQ, \
//|------+------+------+------+------|     |------+------+------+------+-------|
   KC_LZ, KC_X,  KC_C,  KC_V,  KC_B, 			  KC_N,  KC_M,  KC_COMM,KC_DOT,KC_RT,\
//|------+------+------+------+------|     |------+------+------+------+-------|
                        LOWER, KC_SPC,      KC_GE, RAISE \
                    //|-------+------|     |------+------|
),

[_LOWER] = LAYOUT( 
   KC_1,  KC_2,  KC_3,  KC_4,   KC_5,  		  KC_6,   KC_7,   KC_8,   KC_9,    KC_0,   \
//|------+-------+------+------+------|    |-------+-------+-------+-------+---------|
   KC_ESC,VDEL, VSAVE,  KC_NO, KC_LGUI,		  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT, KC_BSPC,\
//|------+-------+------+------+------|    |-------+-------+-------+-------+---------|
   KC_ESC,KC_NO, KC_NO,  KC_NO, KC_NO, 		  KC_GRV,KC_TILD,KC_PIPE, KC_SLSH, KC_QUES,\
//|------+-------+------+------+------|    |-------+-------+-------+-------+---------|
                        LOWER, KC_NO,       KC_CE, KC_COLN \
                     //|-------+------|    |------+------|
),

[_RAISE] = LAYOUT( \
//,-----------------------------------------.    ,-----------------------------------------.
   KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,		KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
//|------+------+------+------+------+------|    |------+------+------+------+------+------|
   KC_NO, KC_NO, KC_NO, KC_COLN, KC_SCLN, KC_MINUS, KC_EQL, KC_LCBR, KC_RCBR, KC_BSPC, \
//|------+------+------+------+------+------|    |------+------+------+------+------+------|
   KC_LSFT,  KC_NO,  KC_NO,  KC_NO,  KC_BSLS,	KC_UNDS,  KC_PLUS, KC_LBRC, KC_RBRC,KC_DEL,  \
//|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
         			LOWER,  KC_RGUI,	KC_LGUI, RAISE \
),

[_ADJUST] =  LAYOUT( \
//,-----------------------------------------.    ,-----------------------------------------.
 KC_F1 , KC_F2 , KC_F3 , KC_F4,   KC_F5,   	KC_F6 , KC_F7 , KC_F8,  KC_F9, KC_F10, \
//|------+------+------+------+------+------|    |------+------+------+------+------+------|
 KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO ,   KC__MUTE,KC__VOLDOWN, KC__VOLUP, KC_NO, KC_NO,\
//|------+------+------+------+------+------|    |------+------+------+------+------+------|
 KC_NO, KC_NO,  KC_NO, KC_NO, KC_CAPSLOCK ,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,\
//|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
          				LOWER,  KC_RGUI, KC_ALTKN, RAISE  \
 ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
  if (record->event.pressed) {
    // persistant_default_layer_set(1UL<<_QWERTY);
    set_single_persistent_default_layer(_QWERTY);
  }
  return false;
  break;
    case LOWER:
  if (record->event.pressed) {
    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  } else {
    layer_off(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
  return false;
  break;
    case RAISE:
  if (record->event.pressed) {
    layer_on(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  } else {
    layer_off(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
  }
  return false;
  break;
    case ADJUST:
  if (record->event.pressed) {
    layer_on(_ADJUST);
  } else {
    layer_off(_ADJUST);
  }
  return false;
  break;
    case VSAVE:
  if (record->event.pressed) {
    SEND_STRING(":wa"SS_TAP(X_ENT));
  } else {
    // layer_off(_ADJUST);
  }
  return false;
  break;
    case VDEL:
  if (record->event.pressed) {
    SEND_STRING(":bd"SS_TAP(X_ENT));
  } else {
    // layer_off(_ADJUST);
  }
  return false;
  break;
  }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

