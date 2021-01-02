#include "dk_full_custom.h"

enum custom_keycodes {
  ENC_BTN = SAFE_RANGE,
  ENC_MODE_CHANGE,
  SET_MEDIA_CONTROLS_ENC_MODE,
  SET_YOUTUBE_CONTROLS_ENC_MODE,
  SET_EXTRA_CONTROLS_ENC_MODE,
  SET_ARROWS_CONTROLS_ENC_MODE,
  MY_TEST
};

enum encoder_modes {
	MEDIA = 0,
	YOUTUBE,
	EXTRA,
	ARROWS,
	MAX_ENC_MODES
};

enum encoder_sub_modes {
	MEDIA_VOL = 0,
	MEDIA_TRACK,
	YOUTUBE_10s,
	YOUTUBE_5s,
	YOUTUBE_1f,
	EXTRA_PAGE,
	EXTRA_HOME_END,
	ARROWS_UP_DOWN,
	ARROWS_LEFT_RIGHT
};

#define MAX_MEDIA_MODES 2
#define MAX_YOUTUBE_MODES 3
#define MAX_EXTRA_MODES 2
#define MAX_ARROWS_MODES 2

static const uint8_t maxSubModes[] = { MAX_MEDIA_MODES, MAX_YOUTUBE_MODES, MAX_EXTRA_MODES, MAX_ARROWS_MODES };

static const uint8_t mediaModes[MAX_MEDIA_MODES]     = { MEDIA_VOL, MEDIA_TRACK };
static const uint8_t youtubeModes[MAX_YOUTUBE_MODES] = { YOUTUBE_10s, YOUTUBE_5s, YOUTUBE_1f };
static const uint8_t extraModes[MAX_EXTRA_MODES]     = { EXTRA_PAGE, EXTRA_HOME_END };
static const uint8_t arrowsModes[MAX_ARROWS_MODES]   = { ARROWS_UP_DOWN, ARROWS_LEFT_RIGHT };

const uint8_t* subModes[] = { mediaModes, youtubeModes, extraModes, arrowsModes };

uint8_t encoderMode = MEDIA;
uint8_t encoderSubModeIndex = 0;
static const uint8_t encoderKeys[][3] = {
    { KC_VOLU,  KC_VOLD,   KC_MUTE  }, // MEDIA_VOL
	{ KC_MNXT,  KC_MPRV,   KC_MPLY  }, // MEDIA_TRACK
	{ KC_L,	    KC_J,      KC_SPACE }, // YOUTUBE_1s
	{ KC_RIGHT, KC_LEFT,   KC_SPACE }, // YOUTUBE_5s
	{ KC_COMMA, KC_DOT,    KC_SPACE }, // YOUTUBE_1f
	{ KC_PGUP,  KC_PGDOWN, KC_NO    }, // EXTRA_PAG
	{ KC_END,   KC_HOME,   KC_NO    }, // EXTRA_HOME_END
	{ KC_UP,    KC_DOWN,   KC_NO    }, // ARROWS_UP_DOWN
	{ KC_RIGHT, KC_LEFT,   KC_NO    }  // ARROWS_LEFT_RIGHT
};
static const char* encoderLabels[][3] = {
    { "VolUp", "VolDn", "Mute " },
	{ "NextT", "PrevT", "Pause" },
	{ "Y+10s", "Y-10s", "Pause" },
	{ "Y+05s", "Y-05s", "Pause" },
	{ "Y+01f", "Y-01f", "Pause" },
	{ "PgUp ", "PgDn ", "     " },
	{ " End ", "Home ", "     " },
	{ " Up  ", "Down ", "     " },
	{ "Right", "Left ", "     " }
};

static const char* layerLabels[][5] = {
	{ "Wther", "TmeZn", "Audio", "PiHle", "  +  " },
	{ "17-20", "21-24", "Emo 1", "Emo 2", "  -  " },
	{ " F17 ", " F18 ", " F19 ", " F20 ", "Back " },
	{ " F21 ", " F22 ", " F23 ", " F24 ", "Back " },
	{ " :)  ", " :D  ", " |D  ", " ;)  ", "Back " },
	{ "kiss ", " ;p  ", "roll ", " :(  ", "Back " },
	{ "Media", "YouTB", "Extra", "Arrow", "SMode" }
};

enum unicode_names {
	SLIGHTLY_SMILING_FACE,
	GRINNING_FACE_WITH_BIG_EYES,
	BEAMING_FACE_WITH_SMILING_EYES,
	WINKING_FACE,
	FACE_BLOWING_A_KISS,
	WINKING_FACE_WITH_TONGUE,
	FACE_WITH_ROLLING_EYES,
	SLIGHTLY_FROWNING_FACE
};

const uint32_t PROGMEM unicode_map[] = {
	[SLIGHTLY_SMILING_FACE]  			= 0x1F642, // 🙂
	[GRINNING_FACE_WITH_BIG_EYES] 		= 0x1F603, // 😃
	[BEAMING_FACE_WITH_SMILING_EYES]	= 0x1F601, // 😁
	[WINKING_FACE]						= 0x1F609, // 😉
	[FACE_BLOWING_A_KISS] 				= 0x1F618, // 😘
	[WINKING_FACE_WITH_TONGUE] 			= 0x1F61C, // 😜
	[FACE_WITH_ROLLING_EYES] 			= 0x1F644, // 🙄
	[SLIGHTLY_FROWNING_FACE] 			= 0x1F641  // 🙁
};

enum layer_labels {
	_BASE = 0,
	_CHOOSE_LAYER,
	_LAYER_1,
	_LAYER_2,
	_LAYER_3,
	_LAYER_4,
	_ENC_MODES
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = KEYMAP(
			KC_F13,                         KC_F15,                            MO(_CHOOSE_LAYER), KC_NO,
			KC_F14,                         KC_F16,                            MO(_ENC_MODES),    KC_NO, 
			KC_NO,                          KC_NO,                             KC_NO,             ENC_BTN),

	[_CHOOSE_LAYER] = KEYMAP(
			TO(_LAYER_1),                   TO(_LAYER_3),                      KC_TRNS,           KC_NO,
			TO(_LAYER_2),                   TO(_LAYER_4),                      KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_TRNS),

	[_LAYER_1] = KEYMAP(
			KC_F17,                         KC_F19,                            TG(_LAYER_1),      KC_NO,
			KC_F18,                         KC_F20,                            KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_TRNS),

	[_LAYER_2] = KEYMAP(
			KC_F21,                         KC_F23,                            TG(_LAYER_2),      KC_NO,
			KC_F22,                         KC_F24,                            KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_TRNS),

	[_LAYER_3] = KEYMAP(
			X(SLIGHTLY_SMILING_FACE),       X(BEAMING_FACE_WITH_SMILING_EYES), TG(_LAYER_3),      KC_NO,
			X(GRINNING_FACE_WITH_BIG_EYES), X(WINKING_FACE),                   KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_TRNS),

	[_LAYER_4] = KEYMAP(
			X(FACE_BLOWING_A_KISS),         X(FACE_WITH_ROLLING_EYES),         TG(_LAYER_4),      KC_NO,
			X(WINKING_FACE_WITH_TONGUE),    X(SLIGHTLY_FROWNING_FACE),         KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_TRNS),

    [_ENC_MODES] = KEYMAP(
			SET_MEDIA_CONTROLS_ENC_MODE,    SET_EXTRA_CONTROLS_ENC_MODE,       ENC_MODE_CHANGE,   KC_NO,
			SET_YOUTUBE_CONTROLS_ENC_MODE,  SET_ARROWS_CONTROLS_ENC_MODE,      KC_TRNS,           KC_NO,
			KC_NO,                          KC_NO,                             KC_NO,             KC_NO)
};

uint8_t currentLayer = 0;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	return MACRO_NONE;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	currentLayer=get_highest_layer(state);
	return state;
}		
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint8_t newEncodeMode = encoderMode;
	uint8_t newEncoderSubModeIndex = encoderSubModeIndex;

	if(keycode < SAFE_RANGE){
		return true;
	}

	if (!record->event.pressed) {
		return false;
	}

	bool retCode = false;
	switch (keycode) {
		case SET_MEDIA_CONTROLS_ENC_MODE:
			newEncodeMode = MEDIA;
			break;
		case SET_YOUTUBE_CONTROLS_ENC_MODE:
			newEncodeMode = YOUTUBE;
			break;
		case SET_EXTRA_CONTROLS_ENC_MODE:
			newEncodeMode = EXTRA;
			break;
		case SET_ARROWS_CONTROLS_ENC_MODE:
			newEncodeMode = ARROWS;
			break;
		case ENC_MODE_CHANGE:
			newEncoderSubModeIndex++;
			if(newEncoderSubModeIndex >= maxSubModes[encoderMode]){
				newEncoderSubModeIndex = 0;
			}
			break;
		case ENC_BTN:
			tap_code(encoderKeys[subModes[encoderMode][encoderSubModeIndex]][2]); // Fall through
		default:
			retCode = true;
	}
	if(newEncodeMode - encoderMode != 0){
		encoderMode = newEncodeMode;
		encoderSubModeIndex = 0;
	}else{
		encoderSubModeIndex = newEncoderSubModeIndex;
	}
	return retCode;
}

void encoder_update_user(uint8_t index, bool clockwise) {
	tap_code((clockwise?encoderKeys[subModes[encoderMode][encoderSubModeIndex]][0]:encoderKeys[subModes[encoderMode][encoderSubModeIndex]][1]));
}

void oled_task_user(void) {
    char buff[30];
	uint8_t index = subModes[encoderMode][encoderSubModeIndex];
	sprintf(buff, "%s  %s   %s\n", layerLabels[currentLayer][0], layerLabels[currentLayer][1], encoderLabels[index][0]);
	oled_write(buff, false);
	
	sprintf(buff, "%s  %s   %s\n", layerLabels[currentLayer][2], layerLabels[currentLayer][3], encoderLabels[index][1]);
	oled_write(buff, false);
	oled_write_P(PSTR("--------------------\n"), false);

	sprintf(buff, "%s Layer:%d %s\n", layerLabels[currentLayer][4], currentLayer, encoderLabels[index][2]);
	oled_write(buff, false);
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