#include "dk_proto.h"

enum custom_keycodes {
  TENS = SAFE_RANGE,
  FIVES,
  ONES
};

enum layer_labels {
	_BASE = 0,
	_ROT_MODES
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP(
		TENS, FIVES, ONES, MO(1)),
    [1] = KEYMAP(
		KC_4, KC_5, RESET, KC_TRNS)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	// keyevent_t event = record->event;

	// switch (id) {

	// }
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

int lastPressed = TENS;
int currentLayer = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
	currentLayer=get_highest_layer(state);
	return state;
}		

void encoder_update_user(uint8_t index, bool clockwise) {
    // if (index == 0) { /* First encoder */
        if (clockwise) {
			switch (lastPressed) {
				case TENS:
		            tap_code(KC_L);
					break;
				case FIVES:
		            tap_code(KC_RIGHT);
					break;
				case ONES:
		            tap_code(KC_COMMA);
					break;
			}
        } else {
			switch (lastPressed) {
				case TENS:
		            tap_code(KC_J);
					break;
				case FIVES:
		            tap_code(KC_LEFT);
					break;
				case ONES:
		            tap_code(KC_DOT);
					break;
			}
        }
    // }
}

#ifdef OLED_DRIVER_ENABLE
// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//     };

//     oled_write_P(qmk_logo, false);
// }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

void printStatus(void){
	// if(!is_oled_on()){
	// 	oled_on();
	// }

	switch (lastPressed) {
		case TENS:
			oled_write_P(PSTR("10 seconds\n"), false);
			break;
		case FIVES:
			oled_write_P(PSTR("5 seconds\n"), false);
			break;
		case ONES:
			oled_write_P(PSTR("1 frame\n"), false);
			break;
	}
	switch(currentLayer){
		case 0:
			oled_write_P(PSTR("Layer 0\n"), false);
			break;
		case 1:
			oled_write_P(PSTR("Layer 1\n"), false);
			break;
	}
	char buff[50];
	sprintf(buff, "abc4567890.1234567890\n");
	oled_write(buff, false);
	//                 [     ][     ][     ]
	/*
		[VolUp]
		[Mute ]
		[VOlDn]

		[Next ]
		[Pause]
		[Prev ]



		[+10s ]
		[Pause]
		[-10s ]

		[ +5s ]
		[Pause]
		[ -5s ]

		[+1frm]
		[Pause]
		[-1frm]



		[PgUp ]
		[ nop ]
		[PgDn ]

		[Home ]
		[ nop ]
		[End  ]

		[ Up  ]
		[ nop ]
		[ Dn  ]

		[right]
		[ nop ]
		[left ]


	*/
}

void oled_task_user(void) {
	printStatus();
    // Host Keyboard Layer Status
    // oled_write_P(PSTR("Layer: "), false);

    // switch (get_highest_layer(layer_state)) {
    //     case _QWERTY:
    //         oled_write_P(PSTR("Default\n"), false);
    //         break;
    //     case _FN:
    //         oled_write_P(PSTR("FN\n"), false);
    //         break;
    //     case _ADJ:
    //         oled_write_P(PSTR("ADJ\n"), false);
    //         break;
    //     default:
    //         // Or use the write_ln shortcut over adding '\n' to the end of your string
    //         oled_write_ln_P(PSTR("Undefined"), false);
    // }

    // Host Keyboard LED Status
    // led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	// render_logo();
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case TENS:
		case FIVES:
		case ONES:
			if (record->event.pressed) {
				lastPressed = keycode;
// #ifdef OLED_DRIVER_ENABLE
// 				printStatus();
// #endif
			}
			return false;
		default:
			return true;
	}
	return true;
}

void led_set_user(uint8_t usb_led) {

#ifdef OLED_DRIVER_ENABLE
	if(!is_oled_on()){
		oled_on();
	}
#endif

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