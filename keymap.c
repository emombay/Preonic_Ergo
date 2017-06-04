#include "preonic.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WRKMN 0
#define _QWERTY 1
#define _COLEMAK 2
#define _LOWER 3
#define _RAISE 4
#define _NUMPAD 5
#define _CODE 6
#define _ADJUST 16
#define ALTTAB 1
#define CTRLWIN 2

// Tapdance
enum {
  TD_FUN = 0,
  TD_3EQ,
  TD_2EQ
};

enum preonic_keycodes {
  WRKMN = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Workman
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  | Save | Num  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Q  |   D  |   R  |   W  |   B  | Del  |crl/Wn|   J  |   F  |   U  |   P  |   ;  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   H  |   T  |   G  |   _  |  Meh |   Y  |   N  |   E  |   O  |   I  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shft/Z|   X  |   M  |   C  |   V  | Ctrl | Raise|   K  |   L  |   ,  |   .  |Shtf//|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Alt/Tb| LGUI | Alt  |Esc/Cd|Lower | Bksp | Entr |Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_WRKMN] = {
  {KC_1,  	     KC_2,    KC_3,    KC_4,              KC_5, 	LCTL(KC_S),TG(_NUMPAD), KC_6,    KC_7,    KC_8,    KC_9,    KC_0},
  {KC_Q,         KC_D,    KC_R,    KC_W,              KC_B,    KC_DEL,   M(CTRLWIN),  KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN},
  {KC_A,         KC_S,    KC_H,    KC_T,              KC_G,    KC_UNDS,	 MEH_T(XXX),  KC_Y,    KC_N,    KC_E,    KC_O,    KC_I},
  {SFT_T(KC_Z),  KC_X,    KC_M,    KC_C,              KC_V,    KC_LCTL,  RAISE,       KC_K,    KC_L,    KC_COMM, KC_DOT,  SFT_T(KC_SLSH)},
  {M(ALTTAB),    KC_LGUI, KC_LALT, LT(_CODE,KC_ESC),  LOWER,   KC_BSPC,  KC_ENT,      KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  |      |      |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |      |      |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shft/Z|   X  |   C  |   V  |   B  |      |      |   N  |   M  |   ,  |   .  |Shtf//|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {_______,      _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______},
  {KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,    _______,  _______,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P},
  {KC_A,         KC_S,    KC_D,    KC_F,    KC_G,    _______,  _______,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN},
  {SFT_T(KC_Z),  KC_X,    KC_C,    KC_V,    KC_B,    _______,  _______,   KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_T(KC_SLSH)},
  {_______,      _______, _______, _______, _______, _______,  _______,   _______,  _______, _______, _______,_______}
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Q  |   W  |   F  |   P  |   G  |      |      |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   D  |      |      |   H  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shft/Z|   X  |   C  |   V  |   B  |      |      |   K  |   M  |   ,  |   .  |Shtf//|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {_______,     _______, _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______},
  {KC_Q,        KC_W,    KC_F,    KC_P,    KC_G,    _______,  _______,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN},
  {KC_A,        KC_R,    KC_S,    KC_T,    KC_D,    _______,  _______,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O},
  {SFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,    _______,  _______,   KC_K,    KC_M,    KC_COMM, KC_DOT,  SFT_T(KC_SLSH)},
  {_______,     _______, _______, _______, _______, _______,  _______,   _______,  _______, _______, _______,_______}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |PrtScn|   ~  |      |      |      |      |      |      |      |      |      |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      |      |      |      |      |      |      |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Cut  |      | Copy |Paste |      | Home |  End | Prev |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Undo | Redo |      |      | PgUp | PgDn | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_F1,   KC_F2,      KC_F3,    KC_F4,          KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {KC_PSCR, KC_TILD,    _______,  _______,      _______,  _______, _______, _______, _______, _______, _______, KC_BSLS},
  {KC_TAB,  _______,    _______,  _______,      _______,  _______, _______, _______, _______, _______, _______, KC_QUOT },
  {_______, LCTL(KC_X), _______,  LCTL(KC_C),LCTL(KC_V),  _______, KC_HOME, KC_END,  KC_MPRV, _______, _______, _______},
  {_______, _______,  LCTL(KC_Z), LCTL(KC_Y),   _______,  _______, KC_PGUP, KC_PGDN, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | MsUp |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |MsLeft|MsDown|MsRght|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |  App |Lower |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Lclk | Rclk |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {_______, _______, KC_MS_U, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_APP,  LOWER,   _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  Ins |   7  |   8  |   9  |   *  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   1  |   2  |   3  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |   0  |   =  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_7,    KC_8,    KC_9,    KC_ASTR},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_3,    KC_2,    KC_1,    KC_BSLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_EQL}
},

/* Code
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   +  |   =  |   {  |   }  |   |  |      |      |      |TD_2EQ|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   &  |   -  |   (  |   )  |   `  |      |      |      |TD_3EQ|TD_FUN|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   <  |   >  |   [  |   ]  |   ~  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F9  |  F10 |  F11 |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_CODE] = {
  {_______,        _______,    _______, _______, _______, _______, _______, _______, _______,    _______,    _______, _______},
  {LSFT(KC_EQL),  KC_EQL,      KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______, TD(TD_2EQ), _______,    _______, _______},
  {LSFT(KC_7),    KC_MINS,     KC_LPRN, KC_RPRN, KC_GRV,  _______, _______, _______, TD(TD_3EQ), TD(TD_FUN), _______, _______},
  {LSFT(KC_COMM),LSFT(KC_DOT), KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______,    _______,    _______, _______},
  {KC_F9,         KC_F10,      KC_F11,  _______, _______, _______, _______, _______, _______,    _______,    _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |BACKLT|      |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Audoff|Aud on|      |      |      |WRKMN |QWERTY|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Musoff|Mus on|      |      |AGnorm|AGswap|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
  {_______, RESET,   _______, _______, _______, _______, _______, _______, BACKLIT, _______, _______, KC_DEL},
  {_______, _______, _______, AU_OFF,  AU_ON,   _______, _______, _______, WRKMN,   QWERTY,  _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  _______, _______, _______, AG_NORM, AG_SWAP, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = {
  {NOTE_B5, 20},
  {NOTE_B6, 8},
  {NOTE_DS6, 20},
  {NOTE_B6, 8}
};

float tone_WRKMN[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_QWERTY[][2]    = SONG(COLEMAK_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

static void m_tapn (uint8_t code, ...) {
  uint8_t kc = code;
  va_list ap;

  va_start(ap, code);
  do {
    register_code(kc);
    unregister_code(kc);
    wait_ms(50);
    kc = va_arg(ap, int);
  } while (kc != 0);
  va_end(ap);
}

void dance_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ===
      m_tapn(KC_EQL, KC_EQL, KC_EQL, 0);
      break;
    case 2: // !==
      register_code(KC_LSHIFT);
      m_tapn(KC_1, 0);
      unregister_code(KC_LSHIFT);
      m_tapn(KC_EQL, KC_EQL, 0);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_two_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ==
      m_tapn(KC_EQL, KC_EQL, 0);
      break;
    case 2: // !=
      register_code(KC_LSHIFT);
      m_tapn(KC_1, 0);
      unregister_code(KC_LSHIFT);
      m_tapn(KC_EQL, 0);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_fun (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // =>    
      m_tapn(KC_EQL, 0);
      register_code(KC_LSFT);
      m_tapn(KC_DOT, 0);
      unregister_code(KC_LSFT);
      break;
    case 2: // () => {}
      register_code(KC_LSFT);
      m_tapn(KC_9, KC_0, KC_SPC, 0);
      unregister_code(KC_LSFT);
      m_tapn(KC_EQL, 0);
      register_code(KC_LSFT);
      m_tapn(KC_DOT, KC_SPC, KC_LBRC, KC_RBRC, 0);
      unregister_code(KC_LSFT);
      break;
    default:
      reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_FUN] = ACTION_TAP_DANCE_FN (dance_fun)
 ,[TD_3EQ] = ACTION_TAP_DANCE_FN (dance_eq)
 ,[TD_2EQ] = ACTION_TAP_DANCE_FN (dance_two_eq)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
    case ALTTAB: 
    if (record->event.pressed) {
      return MACRO( D(LALT), D(TAB), W(200), U(TAB), END );
    } else {
      return MACRO( U(LALT), END );
    }
    break;
    case CTRLWIN: 
    if (record->event.pressed) {
      return MACRO( D(LCTL), D(LGUI), END );
    } else {
      return MACRO( U(LGUI), U(LCTL), END );
    }
    break;
    case 3: 
    if (record->event.pressed) {
      return MACRO( D(LCTL), D(LSFT), END );
    } else {
      return MACRO( U(LSFT), U(LCTL), END );
    }
    break;
    case 4: 
    if (record->event.pressed) {
      return MACRO( D(LGUI), END );
    } else {
      return MACRO( U(LGUI), END );
    }
    break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case WRKMN:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_WRKMN, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_WRKMN);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_QWERTY, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_COLEMAK);
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
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
          return false;
          break;        
      }
    return true;
};

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif