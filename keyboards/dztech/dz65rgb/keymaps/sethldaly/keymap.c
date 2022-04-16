#include QMK_KEYBOARD_H

uint8_t mode;
uint8_t speed;
uint8_t hue;
uint8_t sat;
uint8_t val;

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool altf4_timer_finished = true;
uint16_t altf4_timer = 0;
bool sni_timer_finished = true;
uint16_t sni_timer = 0;
bool sbspc_timer_finished = true;
uint16_t sbspc_timer = 0;
bool sdel_timer_finished = true;
uint16_t sdel_timer = 0;

uint8_t osm_state;
uint8_t mod_state;
uint8_t layer;

enum dz65_layers {
    _BASE = 0, 
    _EXTRA,
    _GAMING
};   

enum dz65_keycodes {
    RGB_VAI_NE = SAFE_RANGE,
    RGB_VAD_NE,
    RGB_SPI_NE,
    RGB_SPD_NE,
    RGB_STI_NE,
    RGB_STD_NE,
    RGB_HUI_NE,
    RGB_HUD_NE,
    RGB_SAI_NE,
    RGB_SAD_NE,
    RGB_SAVE,
    ALT_TAB,
};

enum dz65_dances {
    TD_AF4,
    TD_SNI,
    TD_BSPC,
    TD_DEL,
    TD_LAR,
    TD_RAR,
};

enum combo_events {
  JF_WINQ,
  SBSPC,
  SDEL,
};

const uint16_t PROGMEM search_combo[] = {KC_J, KC_F, COMBO_END};
const uint16_t PROGMEM sbspc_combo[] = {KC_LSFT, TD(TD_BSPC), COMBO_END};
const uint16_t PROGMEM sdel_combo[] = {KC_LSFT, TD(TD_DEL), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [JF_WINQ] = COMBO_ACTION(search_combo),
  [SBSPC] = COMBO_ACTION(sbspc_combo),
  [SDEL] = COMBO_ACTION(sdel_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case JF_WINQ:
      if (pressed) {
        tap_code16(LGUI(KC_Q));
      }
      break;
    case SBSPC:
      if (pressed) {
        tap_code16(LSFT(KC_HOME));
        tap_code16(KC_BSPC);
      }
      break;
    case SDEL:
      if (pressed) {
        tap_code16(LSFT(KC_END));
        tap_code16(KC_BSPC);
      }
      break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code16(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code16(KC_TAB);
      } else {
        unregister_code16(KC_TAB);
        register_code16(LSFT(KC_TAB));
        unregister_code16(LSFT(KC_TAB));
      }
      break;
    case RGB_VAI_NE:
            if (record->event.pressed) {
                rgb_matrix_increase_val_noeeprom();   
            }
            break;
    case RGB_VAD_NE:
            if (record->event.pressed) {
                rgb_matrix_decrease_val_noeeprom();   
            }
            break;
    case RGB_SAI_NE:
            if (record->event.pressed) {
                rgb_matrix_increase_sat_noeeprom();   
            }
            break;
    case RGB_SAD_NE:
            if (record->event.pressed) {
                rgb_matrix_decrease_sat_noeeprom();   
            }
            break;
    case RGB_HUI_NE:
            if (record->event.pressed) {
                rgb_matrix_increase_hue_noeeprom();   
            }
            break;
    case RGB_HUD_NE:
            if (record->event.pressed) {
                rgb_matrix_decrease_hue_noeeprom();   
            }
            break;              
    case RGB_SPI_NE:
            if (record->event.pressed) {
                rgb_matrix_increase_speed_noeeprom();   
            }
            break;
    case RGB_SPD_NE:
            if (record->event.pressed) {
                rgb_matrix_decrease_speed_noeeprom();   
            }
            break;
    case RGB_STI_NE:
            if (record->event.pressed) {
                rgb_matrix_step_noeeprom();   
            }
            break;
    case RGB_STD_NE:
            if (record->event.pressed) {
                rgb_matrix_step_reverse_noeeprom();   
            }
            break;
    case RGB_SAVE:
        if (record->event.pressed) {
                mode = rgb_matrix_get_mode();
                speed = rgb_matrix_get_speed();
                hue = rgb_matrix_get_hue();
                sat = rgb_matrix_get_sat();
                val = rgb_matrix_get_val();
                rgb_matrix_sethsv(hue, sat, val);
                rgb_matrix_mode(mode);
                rgb_matrix_set_speed(speed); 
            }
        break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 2500) {
      unregister_code16(KC_LALT);
      is_alt_tab_active = false;
        }
    }
  if (timer_elapsed(altf4_timer) > 1250) {
      altf4_timer_finished = true;
    }
  if (timer_elapsed(sni_timer) > 1250) {
      sni_timer_finished = true;
    }
  if (timer_elapsed(sbspc_timer) > 800) {
      sbspc_timer_finished = true;
    }
  if (timer_elapsed(sdel_timer) > 800) {
      sdel_timer_finished = true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /* Layer: _BASE
     * ,-----------------------------------------------------------------------------.
     * |Esc |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Backsp |Del |
     * |-----------------------------------------------------------------------------|
     * |Tab    |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] | \  |Pgup|
     * |-----------------------------------------------------------------------------|
     * |CapsL   |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |Return  |Home|
     * |-----------------------------------------------------------------------------|
     * |Shift    |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |Shift  | Up |End |
     * |-----------------------------------------------------------------------------|
     * |Ctrl |Win  |Alt  |           Space            |Alt| Layer|Ctrl |Lef| Dow|Rig |
     * `-----------------------------------------------------------------------------'
        Escape Tap Dance: Press once for Escape, twice for Close Window (Alt+F4) [Red LED]
        Tab Tap Dance: Press for Tab, Hold for Screenshot (Win+Shift+S) [Green LED]
        One Shot Mods: LSFT, LCTL, LGUI
        Alt Tab: bring up Alt+Tab menu for 2.5 sec
        Backspace Tap Dance: Press for Backspace, Hold for Backspace Word (Ctl+Bspc), Shift+Bspc for Backspace Line [Orange LED]
        Delete Tap Dance: Press for Delete, Hold for Delete Word (Ctl+Del), Shift+Del for Delete Line [Orange LED]
        Arrow Tap Dance: Press for Arrow, Hold for Arrow Word (Ctl+Arrow)
        Search Combo: Press J and F simultaneously for Search Bar (Win+Q)
     */


    [_BASE] = LAYOUT_65_ansi(
        TD(TD_AF4),     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  TD(TD_BSPC), TD(TD_DEL),
        TD(TD_SNI),     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
        OSM(MOD_LSFT),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        OSM(MOD_LCTL),  OSM(MOD_LGUI), ALT_TAB,                      KC_SPC,         TG(_GAMING), TG(_EXTRA), KC_RCTL, TD(TD_LAR), KC_DOWN, TD(TD_RAR)
  ),
        /* Layer: _EXTRA
     * ,-----------------------------------------------------------------------------.
     * |Reset| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 |F10 |    |    |      |SAVE|
     * |-----------------------------------------------------------------------------|
     * |       |Step+|Val+|Sat+|Hue+|Spd+|    |    |    |    |    |    |    |    |   |
     * |-----------------------------------------------------------------------------|
     * |        |Step-|Val-|Sat-|Hue-|Spd-|    |    |    |    |    |    |       |Paus|
     * |-----------------------------------------------------------------------------|
     * |Shift    |    |    |    |    |    |    |    |    |    |    |       |VUp |Mute|
     * |-----------------------------------------------------------------------------|
     * |     |     |     |           Toggle           |EEP RST|   |   |Prev|VDn |Next|
     * `-----------------------------------------------------------------------------'
        Save: Save RGB Settings to EEPROM
     */
    
    [_EXTRA] = LAYOUT_65_ansi(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,  _______,  _______,  RGB_SAVE,
        _______, RGB_STI_NE, RGB_VAI_NE, RGB_SAI_NE, RGB_HUI_NE, RGB_SPI_NE, _______, _______, _______, _______, _______, _______, _______, _______, _______,   
        _______, RGB_STD_NE, RGB_VAD_NE, RGB_SAD_NE, RGB_HUD_NE, RGB_SPD_NE, _______, _______, _______, _______, _______, _______, _______,          KC_MPLY,
        KC_LSFT,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE, 
        _______,        _______, _______,                            RGB_TOG,                   EEP_RST, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
        /* Layer: _GAMING
      * ,-----------------------------------------------------------------------------.
     * |Esc |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Backsp |Del |
     * |-----------------------------------------------------------------------------|
     * |Tab    |  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P |  [ |  ] | \  |Pgup|
     * |-----------------------------------------------------------------------------|
     * |CapsL   |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ; |  ' |Return  |Home|
     * |-----------------------------------------------------------------------------|
     * |Shift    |  Z |  X |  C |  V |  B |  N |  M |  , |  . |  / |Shift  | Up |End |
     * |-----------------------------------------------------------------------------|
     * |Ctrl |Win  |Alt  |           Space            |Alt| Layer|Ctrl |Lef| Dow|Rig |
     * `-----------------------------------------------------------------------------'
     */
    
    [_GAMING] = LAYOUT_65_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    _______, _______,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    mod_state = get_mods();
    osm_state = get_oneshot_mods();
    
    if (layer_state_is(_EXTRA)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(63, 0xFF, 0xFF, 0xFF);
    }
    if (layer_state_is(_GAMING)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(62, 0xFF, 0, 0);
    }
    if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
        RGB_MATRIX_INDICATOR_SET_COLOR(44, 0xFF, 0xFF, 0xFF);
    }
    if ((mod_state | osm_state) & MOD_MASK_CTRL) {
        RGB_MATRIX_INDICATOR_SET_COLOR(58, 0xFF, 0xFF, 0xFF);
    }
    if ((mod_state | osm_state) & MOD_MASK_GUI) {
        RGB_MATRIX_INDICATOR_SET_COLOR(59, 0xFF, 0xFF, 0xFF);
    }
    if ((mod_state | osm_state) & MOD_MASK_ALT) {
        RGB_MATRIX_INDICATOR_SET_COLOR(60, 0xFF, 0xFF, 0xFF);
    }
    if (!altf4_timer_finished) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0xFF, 0, 0);
    }
    if (!sni_timer_finished) {
        RGB_MATRIX_INDICATOR_SET_COLOR(15, 0, 0xFF, 0);
    }
    if (!sbspc_timer_finished) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(3, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(4, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(6, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(7, 0xFF, 0xA5, 0);
    }
    if (!sdel_timer_finished) {
        RGB_MATRIX_INDICATOR_SET_COLOR(7, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(8, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(9, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(10, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(11, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(12, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(13, 0xFF, 0xA5, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 0xFF, 0xA5, 0);
    }
}

void bspc_tap(qk_tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    osm_state = get_oneshot_mods();

    if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
        sbspc_timer = timer_read();
        sbspc_timer_finished = false;
        tap_code16(LSFT(KC_HOME));
        tap_code16(KC_BSPC);
      } else {tap_code16(KC_BSPC);
        }
}
void bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_code16(LCTL(KC_BSPC));
    }
}
void bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
        unregister_code16(LCTL(KC_BSPC));
}


void del_tap(qk_tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    osm_state = get_oneshot_mods();
    
    if ((mod_state | osm_state) & MOD_MASK_SHIFT) {
        sdel_timer = timer_read();
        sdel_timer_finished = false;
        tap_code16(LSFT(KC_END));
        tap_code16(KC_DEL);
      } else {tap_code16(KC_DEL);
          }
}
void del_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_code16(LCTL(KC_DEL));
    }
}
void del_reset(qk_tap_dance_state_t *state, void *user_data) {
        unregister_code16(LCTL(KC_DEL));
}

void lar_tap(qk_tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_LEFT);
}
void lar_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_code16(LCTL(KC_LEFT));
    }
}
void lar_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code16(LCTL(KC_LEFT));
}

void rar_tap(qk_tap_dance_state_t *state, void *user_data) {
    tap_code16(KC_RIGHT);
}
void rar_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        register_code16(LCTL(KC_RIGHT));
    }
}
void rar_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code16(LCTL(KC_RIGHT));
}

void sni_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->pressed && !state->interrupted) {
        tap_code16(SGUI(KC_S));
        sni_timer = timer_read();
        sni_timer_finished = false;
    } else {
        tap_code16(KC_TAB);
    }
}

void af4_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_ESC);
    } else if (state->count == 2)  {
        register_code16(LALT(KC_F4));
        altf4_timer = timer_read();
        altf4_timer_finished = false;
    }
}

void af4_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_ESC);
    } else if (state->count == 2)  {
        unregister_code16(LALT(KC_F4));
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(bspc_tap, bspc_finished, bspc_reset, 110),
    [TD_DEL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(del_tap, del_finished, del_reset, 110),
    [TD_LAR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(lar_tap, lar_finished, lar_reset, 115),
    [TD_RAR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(rar_tap, rar_finished, rar_reset, 115),
    [TD_AF4] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, af4_finished, af4_reset, 175),
    [TD_SNI] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, sni_finished, NULL, 225),
};

