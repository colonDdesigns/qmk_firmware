/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
uint8_t mode;
uint8_t speed;
uint8_t hue;
uint8_t sat;
uint8_t val;

enum bdn9_layers {
    _BASE = 0, 
    _LIGHT
};

enum encoder_names {
  _LEFT,
  _RIGHT,
};

enum bdn9_keycodes {
    RGB_VAI_NE = SAFE_RANGE,
    RGB_VAD_NE,
    RGB_SPI_NE,
    RGB_SPD_NE,
    RGB_STI_NE,
    RGB_STD_NE,
    RGB_SAVE
};

enum bdn9_dances {
    TD_PWR,
};

void keyboard_post_init_user(void) {
    mode = rgblight_get_mode();
    speed = rgblight_get_speed();
    hue = rgblight_get_hue();
    sat = rgblight_get_sat();
    val = rgblight_get_val();
}

void pwr_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            rgblight_mode_eeprom_helper(3, false);
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
        case 2:
            rgblight_mode_eeprom_helper(3, false);
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 3:
            rgblight_mode_eeprom_helper(3, false);
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case 4:
            rgblight_mode_eeprom_helper(3, false);
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
   }
}

void pwr_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->interrupted) {}
        else {
    switch (state->count) {
        case 1:
            tap_code16(LGUI(KC_L)); // lock tap_code(LWIN(KC_L)); 
            break;
        case 2:
            tap_code16(KC_SLEP); // sleep tap_code(KC_SLEP);
            break;
        case 3:
            tap_code16(KC_PWR); // shut down tap_code(KC_PWR);
            break;
        case 4:
            tap_code(KC_ENT);
            wait_ms(100);
            SEND_STRING("4561");
            break;
    }
}
}

void pwr_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
        rgblight_sethsv_eeprom_helper(hue, sat, val, false);
        rgblight_mode_eeprom_helper(mode, false);
        rgblight_set_speed(speed);
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PWR] = ACTION_TAP_DANCE_FN_ADVANCED(pwr_dance_each, pwr_dance_finished, pwr_dance_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_VAI_NE:
            if (record->event.pressed) {
                rgblight_increase_val_noeeprom();   
            }
            break;
        case RGB_VAD_NE:
            if (record->event.pressed) {
                rgblight_decrease_val_noeeprom();   
            }
            break;
        case RGB_SPI_NE:
            if (record->event.pressed) {
                rgblight_increase_speed_noeeprom();   
            }
            break;
        case RGB_SPD_NE:
            if (record->event.pressed) {
                rgblight_decrease_speed_noeeprom();   
            }
            break;
        case RGB_STI_NE:
            if (record->event.pressed) {
                rgblight_step_noeeprom();   
            }
            break;
        case RGB_STD_NE:
            if (record->event.pressed) {
                rgblight_step_reverse_noeeprom();   
            }
            break;
        case RGB_SAVE:
            if (!record->event.pressed) {
                mode = rgblight_get_mode();
                speed = rgblight_get_speed();
                hue = rgblight_get_hue();
                sat = rgblight_get_sat();
                val = rgblight_get_val();
                rgblight_sethsv_eeprom_helper(hue, sat, val, true);
                rgblight_mode_eeprom_helper(mode, true);
                rgblight_set_speed(speed); 
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Layer: Base
        ┌───────────┐  ┌───────────┐
        │   Mixer   │  │  Volume   │
        │  Dn   Up  │  │  Dn   Up  │
        ├────────┬──┴──┴──┬────────┤
        │ LAYER  │ PWR TD │  Mute  │
        ├────────┼────────┼────────┤
        │  Prev  │ Pause  │  Next  │
        ├────────┼────────┼────────┤
        │ Deafen │ Output │ Mute   |
        └────────┴────────┴────────┘
     */
    [_BASE] = LAYOUT(
        TG(_LIGHT), TD(TD_PWR), KC_MUTE,
        KC_MPRV  , KC_MPLY  , KC_MNXT,
        LCA(KC_F3), LCA(KC_F4), LCA(KC_F5)
    ),
    /*
        Layer: Light
        ┌───────────┐  ┌───────────┐
        │    Hue    │  │    Sat    │
        │   D   I   │  │   D   I   │
        ├────────┬──┴──┴──┬────────┤
        │ LAYER  │RGB Save│ Toggle │
        ├────────┼────────┼────────┤
        │ Speed I│ Step I │  Val I │
        ├────────┼────────┼────────┤
        │ Speed D│ Step D │  Val D |
        └────────┴────────┴────────┘
     */
    [_LIGHT] = LAYOUT(
        _______ , RGB_SAVE, RGB_TOG,
        RGB_SPI_NE, RGB_STI_NE, RGB_VAI_NE,
        RGB_SPD_NE, RGB_STD_NE, RGB_VAD_NE
    ),
    
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            if (index == _LEFT) {
                if (clockwise) {
                    tap_code(KC_F6);
                } else {
                    tap_code(KC_F7);
                }
            }
            else if (index == _RIGHT) {
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
            }
            break;
        case _LIGHT:
          if (index == _LEFT) {
                if (clockwise) {
                    rgblight_decrease_hue_noeeprom();
                } else {
                    rgblight_increase_hue_noeeprom();
                }
            }
            else if (index == _RIGHT) {
                if (clockwise) {
                    rgblight_decrease_sat_noeeprom();
                } else {
                    rgblight_increase_sat_noeeprom();
                }
            }
            break;
    }
    return false;
}