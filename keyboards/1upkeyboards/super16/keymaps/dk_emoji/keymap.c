#include QMK_KEYBOARD_H

#include "super16.h"

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
static uint32_t rgb_preview_timer = 0;
#endif
extern rgblight_config_t rgblight_config;

enum custom_multichar_keycodes {
  SHRUG = SAFE_RANGE, // ¯\_(ツ)_/¯
  DISAPPROVAL         // (ಠ_ಠ)
};

enum tap_dance {
    TD_SLASH_ASTERISK,
    TD_ENTER_LED_CONFIG_MODE
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASH_ASTERISK] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_ASTERISK),
    [TD_ENTER_LED_CONFIG_MODE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ENTER, 5)
};

enum unicode_names {
        SLIGHTLY_SMILING_FACE,
        GRINNING_FACE_WITH_BIG_EYES,
        BEAMING_FACE_WITH_SMILING_EYES,
        WINKING_FACE,
        WINKING_FACE_WITH_TONGUE,
        UPSIDE_DOWN_FACE,
        SMILING_FACE_WITH_SMILING_EYES,
        GRIMACING_FACE,
        FACE_WITH_MONOCLE,
        FACE_WITH_HAND_OVER_MOUTH,

        SMILING_FACE_WITH_HEARTS,
        SMILING_FACE_WITH_HEART_EYES,
        FACE_BLOWING_A_KISS,
        KISSING_FACE,
        KISSING_FACE_WITH_CLOSED_EYES,
        FACE_SAVORING_FOOD,
        ZANY_FACE,
        THINKING_FACE,
        SMIRKING_FACE,
        PARTYING_FACE,
        SMILING_FACE_WITH_SUNGLASSES,
        NERD_FACE,

        SLIGHTLY_FROWNING_FACE,
        FACE_WITH_ROLLING_EYES,
        UNAUSED_FACE,
        FACE_WITH_RAISED_SYSBROW,
        NEUTRAL_FACE,
        FACE_WITHOUT_MOUTH,
        CONFUSED_FACE,
        ASTONISHED_FACE,
        FLUSHED_FACE,
        PLEADING_FACE,
        CRYING_FACE,
        YAWNING_FACE,

        WAVING_HAND,
        VULCAN_SALUTE,
        VICTORY_HAND,
        CROSSED_FINGERS,
        BACKHAND_INDEX_POINTING__LEFT,
        BACKHAND_INDEX_POINTING_RIGHT,
        BACKHAND_INDEX_POINTING_UP,
        BACKHAND_INDEX_POINTING_DOWN,
        THUMBS_UP,
        THUMBS_DOWN,
        ONCOMING_FIST,
        RADIOACTIVITY
};

const uint32_t PROGMEM unicode_map[] = {
        [SLIGHTLY_SMILING_FACE]          = 0x1F642, // 🙂
        [GRINNING_FACE_WITH_BIG_EYES]    = 0x1F603, // 😃
        [BEAMING_FACE_WITH_SMILING_EYES] = 0x1F601, // 😁
        [WINKING_FACE]                   = 0x1F609, // 😉
        [WINKING_FACE_WITH_TONGUE]       = 0x1F61C, // 😜
        [UPSIDE_DOWN_FACE]               = 0x1F643, // 🙃
        [SMILING_FACE_WITH_SMILING_EYES] = 0x1F60A, // 😊
        [GRIMACING_FACE]                 = 0x1F62C, // 😬
        [FACE_WITH_MONOCLE]              = 0x1F9D0, // 🧐
        [FACE_WITH_HAND_OVER_MOUTH]      = 0x1F92D, // 🤭

        [SMILING_FACE_WITH_HEARTS]       = 0x1F970, // 🥰 
        [SMILING_FACE_WITH_HEART_EYES]   = 0x1F60D, // 😍 	
        [FACE_BLOWING_A_KISS]            = 0x1F618, // 😘
        [KISSING_FACE]                   = 0x1F617, // 😗
        [KISSING_FACE_WITH_CLOSED_EYES]  = 0x1F61A, // 😚
        [FACE_SAVORING_FOOD]             = 0x1F60B, // 😋
        [ZANY_FACE]                      = 0x1F92A, // 🤪
        [THINKING_FACE]                  = 0x1F914, // 🤔
        [SMIRKING_FACE]                  = 0x1F60F, // 😏
        [PARTYING_FACE]                  = 0x1F973, // 🥳
        [SMILING_FACE_WITH_SUNGLASSES]   = 0x1F60E, // 😎
        [NERD_FACE]                      = 0x1F913, // 🤓

        [SLIGHTLY_FROWNING_FACE]         = 0x1F641, // 🙁
        [FACE_WITH_ROLLING_EYES]         = 0x1F644, // 🙄
        [UNAUSED_FACE]                   = 0x1F612, // 😒
        [FACE_WITH_RAISED_SYSBROW]       = 0x1F928, // 🤨
        [NEUTRAL_FACE]                   = 0x1F610, // 😐
        [FACE_WITHOUT_MOUTH]             = 0x1F636, // 😶
        [CONFUSED_FACE]                  = 0x1F615, // 😕
        [ASTONISHED_FACE]                = 0x1F632, // 😲
        [FLUSHED_FACE]                   = 0x1F633, // 😳
        [PLEADING_FACE]                  = 0x1F97A, // 🥺
        [CRYING_FACE]                    = 0x1F622, // 😢
        [YAWNING_FACE]                   = 0x1F971, // 🥱

        [WAVING_HAND]                    = 0x1F44B, // 👋
        [VULCAN_SALUTE]                  = 0x1F596, // 🖖
        [VICTORY_HAND]                   = 0x270C,  // ✌
        [CROSSED_FINGERS]                = 0x1F91E, // 🤞
        [BACKHAND_INDEX_POINTING__LEFT]  = 0x1F448, // 👈
        [BACKHAND_INDEX_POINTING_RIGHT]  = 0x1F449, // 👉
        [BACKHAND_INDEX_POINTING_UP]     = 0x1F446, // 👆
        [BACKHAND_INDEX_POINTING_DOWN]   = 0x1F447, // 👇
        [THUMBS_UP]                      = 0x1F44D, // 👍
        [THUMBS_DOWN]                    = 0x1F44E, // 👎
        [ONCOMING_FIST]                  = 0x1F44A, // 👊
        [RADIOACTIVITY]                  = 0x2622   // ☢
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_ortho_4x4(
                SHRUG,                             DISAPPROVAL,                       X(SLIGHTLY_SMILING_FACE),     TG(1),
                X(GRINNING_FACE_WITH_BIG_EYES),    X(BEAMING_FACE_WITH_SMILING_EYES), X(WINKING_FACE),              MO(2),
                X(SMILING_FACE_WITH_SMILING_EYES), X(UPSIDE_DOWN_FACE),               X(WINKING_FACE_WITH_TONGUE),  MO(3),
                X(GRIMACING_FACE),                 X(FACE_WITH_MONOCLE),              X(FACE_WITH_HAND_OVER_MOUTH), MO(4)
        ),

        [1] = LAYOUT_ortho_4x4(
                KC_7,     KC_8, KC_9,           KC_TRNS,
                KC_4,     KC_5, KC_6,           KC_DOT,
                KC_1,     KC_2, KC_3,           TD(TD_SLASH_ASTERISK),
                KC_MINUS, KC_0, LSFT(KC_EQUAL), TD(TD_ENTER_LED_CONFIG_MODE)
        ),

        [2] = LAYOUT_ortho_4x4(
                X(SMILING_FACE_WITH_HEARTS), X(SMILING_FACE_WITH_HEART_EYES),   X(FACE_BLOWING_A_KISS), KC_NO,
                X(KISSING_FACE),             X(KISSING_FACE_WITH_CLOSED_EYES),  X(FACE_SAVORING_FOOD),  KC_TRNS,
                X(SMIRKING_FACE),            X(THINKING_FACE),                  X(ZANY_FACE),           KC_NO,
                X(PARTYING_FACE),            X(SMILING_FACE_WITH_SUNGLASSES),   X(NERD_FACE),           KC_NO
        ),

        [3] = LAYOUT_ortho_4x4(
                X(SLIGHTLY_FROWNING_FACE),   X(FACE_WITH_ROLLING_EYES), X(UNAUSED_FACE),       KC_NO,
                X(FACE_WITH_RAISED_SYSBROW), X(NEUTRAL_FACE),           X(FACE_WITHOUT_MOUTH), KC_NO,
                X(FLUSHED_FACE),             X(ASTONISHED_FACE),        X(CONFUSED_FACE),      KC_TRNS,
                X(PLEADING_FACE),            X(CRYING_FACE),            X(YAWNING_FACE),       KC_NO
        ),

        [4] = LAYOUT_ortho_4x4(
                X(WAVING_HAND),     X(VULCAN_SALUTE),                 X(VICTORY_HAND),                  KC_NO,
                X(CROSSED_FINGERS), X(BACKHAND_INDEX_POINTING__LEFT), X(BACKHAND_INDEX_POINTING_RIGHT), KC_NO,
                X(THUMBS_UP),       X(BACKHAND_INDEX_POINTING_DOWN),  X(BACKHAND_INDEX_POINTING_UP),    KC_NO,
                X(THUMBS_DOWN),     X(ONCOMING_FIST),                 X(RADIOACTIVITY),                 KC_TRNS
        ),

        [5] = LAYOUT_ortho_4x4(
                RGB_MOD,  RGB_HUI, RGB_SAI, RGB_TOG,
                RGB_RMOD, RGB_HUD, RGB_SAD, KC_NO,
                RGB_VAI,  KC_NO,   KC_NO,   KC_NO,
                RGB_VAD,  KC_NO,   KC_NO,   TG(5)
        ),
};

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                {0,16,HSV_GREEN}
        );
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                {0,16,HSV_WHITE}
        );
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                {0,16,HSV_BLUE}
        );
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                {0,16,HSV_RED}
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
    if(keycode < SAFE_RANGE){
        return true;
    }

	switch (keycode) {
        case SHRUG:
            if (!record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
        case DISAPPROVAL:
            if (!record->event.pressed) {
                send_unicode_string("(ಠ_ಠ)");
            }
            break;
    }

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

