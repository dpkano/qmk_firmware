#include QMK_KEYBOARD_H

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
static uint32_t rgb_preview_timer = 0;
#endif
extern rgblight_config_t rgblight_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        //Layer 0 - Base Layer (F13 to F24, and One Shot Layer 1,2,3 or Toggle Layer 4)
        [0] = LAYOUT_ortho_4x4(
                KC_F13, KC_F14, KC_F15, OSL(1),
                KC_F16, KC_F17, KC_F18, OSL(2),
                KC_F19, KC_F20, KC_F21, TG(3),
                KC_F22, KC_F23, KC_F24, TG(4)
		),

        [1] = LAYOUT_ortho_4x4(
                LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), KC_TRNS,
                LALT(KC_F16), LALT(KC_F17), LALT(KC_F18), KC_TRNS,
                LALT(KC_F19), LALT(KC_F20), LALT(KC_F21), KC_TRNS,
                LALT(KC_F22), LALT(KC_F23), LALT(KC_F24), KC_TRNS
        ),

        //Layer 2 - Shift + Function Key Layer
        [2] = LAYOUT_ortho_4x4(
                LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), KC_TRNS,
                LSFT(KC_F16), LSFT(KC_F17), LSFT(KC_F18), KC_TRNS,
                LSFT(KC_F19), LSFT(KC_F20), LSFT(KC_F21), KC_TRNS,
                LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24), KC_TRNS
        ),

        //Layer 3 - Control + Function Key
        [3] = LAYOUT_ortho_4x4(
                LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), KC_NO,
                LCTL(KC_F16), LCTL(KC_F17), LCTL(KC_F18), KC_NO,
                LCTL(KC_F19), LCTL(KC_F20), LCTL(KC_F21), KC_TRNS,
                LCTL(KC_F22), LCTL(KC_F23), LCTL(KC_F24), KC_NO
        ),

        //Layer 4 - Multimedia
        [4] = LAYOUT_ortho_4x4(
                KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,
                KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,
                RESET,   KC_NO,   KC_NO,   KC_NO,
                EEP_RST, KC_NO,   TG(4),   TG(5)
        ),

        //Layer 5 - Keyboard Lights, Programming and Special Functions
        [5] = LAYOUT_ortho_4x4(
                RGB_MOD,  RGB_HUI, RGB_SAI, RGB_TOG,
                RGB_RMOD, RGB_HUD, RGB_SAD, KC_NO,
                RGB_VAI,  KC_NO,   KC_NO,   KC_NO,
                RGB_VAD,  KC_NO,   KC_NO,   KC_TRNS
        ),
};

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_GREEN}
	);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_RED}
	);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_BLUE}
	);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_WHITE}
	);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_YELLOW}
	);
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
		{0,16,HSV_PURPLE}
	);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        my_layer0_layer,
        my_layer1_layer,
        my_layer2_layer,
        my_layer3_layer,
        my_layer4_layer,
        my_layer5_layer
	);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Allow for a preview of changes when modifying RGB
# if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
  switch (keycode) {
    case RGB_TOG ... VLK_TOG:
      for (uint8_t i = 0; i < RGBLIGHT_MAX_LAYERS; i++) {
        rgblight_set_layer_state(i, false);
      }
      rgb_preview_timer = timer_read32();
      break;
  }
# endif
  return;
}

//Set the appropriate layer color
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}

void keyboard_post_init_user(void) {
	//Enable the LED layers
	rgblight_layers = my_rgb_layers;
	layer_state_set_user(layer_state);
}

void matrix_scan_user(void) {
# if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    // Allow preview for
    if (rgb_preview_timer && TIMER_DIFF_32(timer_read32(), rgb_preview_timer) > PREVIEW_TIMEOUT) {
        rgb_preview_timer = 0;
        default_layer_state_set_user(default_layer_state);
        layer_state_set_user(layer_state);
        led_update_user((led_t) host_keyboard_leds());
    }
# endif
}

//EEPROM Reset Function
void eeconfig_init_user(void) {
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_orange();  // Set it to orange by default
}

