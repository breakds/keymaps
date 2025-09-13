/* Copyright 2023 Yiancar-Designs
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
#include "../../../lib/rdr_lib/rdr_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,     KC_R,       KC_T,      KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,  
        KC_ESC,  KC_A,    KC_S,      KC_D,     KC_F,       KC_G,      KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  
        KC_LSFT, KC_Z,    KC_X,      KC_C,     KC_V,       KC_B,      KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_UP ,   KC_ENT,
        MO(2),   KC_DEL,  KC_LCTL,   KC_LALT,  KC_LGUI,               KC_SPC,   KC_RGUI, KC_SLSH, KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,     KC_R,       KC_T,      KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,  
        KC_ESC,  KC_A,    KC_S,      KC_D,     KC_F,       KC_G,      KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  
        KC_LSFT, KC_Z,    KC_X,      KC_C,     KC_V,       KC_B,      KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_UP ,   KC_ENT,
        MO(3),   KC_DEL,  KC_LCTL,   KC_LGUI,  KC_LALT,               KC_SPC,   KC_RGUI, KC_SLSH, KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [2] = LAYOUT_tkl_ansi(
        MD_USB,  MD_BLE1, MD_BLE2,   MD_BLE3,  MD_24G,     RGB_MOD,   TO(1),    TO(0),   KC_LBRC, KC_RBRC,  KC_BSLS,  RGB_RTOG,  
        KC_GRV,  KC_1,    KC_2,      KC_3,     KC_4,       KC_5,      KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  
        KC_LSFT, KC_INS,  KC_DEL,    KC_HOME,  KC_END,     KC_PGUP,   KC_PGDN,  KC_M,    KC_COMM, KC_DOT,   RGB_VAI , QK_BAT,
        KC_NO,   KC_DEL,  KC_LCTL,   KC_LALT,  KC_LGUI,               U_EE_CLR, KC_RGUI, KC_EQL,  RGB_SPD,  RGB_VAD,  RGB_SPI
    ),
    [3] = LAYOUT_tkl_ansi(
        MD_USB,  MD_BLE1, MD_BLE2,   MD_BLE3,  MD_24G,     RGB_MOD,   TO(1),    TO(0),   KC_LBRC, KC_RBRC,  KC_BSLS,  RGB_RTOG,  
        KC_GRV,  KC_1,    KC_2,      KC_3,     KC_4,       KC_5,      KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  
        KC_LSFT, KC_INS,  KC_DEL,    KC_HOME,  KC_END,     KC_PGUP,   KC_PGDN,  KC_M,    KC_COMM, KC_DOT,   RGB_VAI , QK_BAT,
        KC_NO,   KC_DEL,  KC_LCTL,   KC_LGUI,  KC_LALT,               U_EE_CLR, KC_RGUI, KC_EQL,  RGB_SPD,  RGB_VAD,  RGB_SPI
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [1] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_SPD, RGB_SPI) }
};

#endif

/* Prevent Bluetooth sleep timeout */
void prevent_bluetooth_sleep(void) {
    extern uint16_t Usb_Change_Mode_Delay;
    extern bool Usb_Change_Mode_Wakeup;
    
    /* Only in Bluetooth/2.4G modes, reset timeout every 30 seconds to prevent sleep */
    if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
        static uint16_t counter = 0;
        counter++;
        
        /* Reset every ~30 seconds (assuming this runs ~100 times/sec) */
        if (counter >= 3000) {
            Usb_Change_Mode_Delay = 0;
            Usb_Change_Mode_Wakeup = false;
            counter = 0;
        }
    }
}

/* Use matrix_scan_user as our hook since housekeeping_task_user is already defined in geonix40.c */
void matrix_scan_user(void) {
    prevent_bluetooth_sleep();
}

