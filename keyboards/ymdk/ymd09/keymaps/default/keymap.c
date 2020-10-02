#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(LWIN(KC_L), KC_CALC,       KC_F22,
               KC_F23,     LT(1,KC_F24),  KC_MPLY,
               KC_F21,     LT(2,KC_VOLD), KC_VOLU),

  [1] = LAYOUT(RGB_TOG, RGB_VAI, RGB_MOD,
               RGB_HUI, KC_TRNS, RGB_SAI,
               RGB_HUD, RGB_VAD, RGB_SAD),

  [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_MUTE),

};
