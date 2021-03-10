/* Copyright 2020 Jay Greco
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

enum layer_names {
  _MA,
  _FN
};

enum custom_keycodes {
  KC_CUST = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MA] = LAYOUT_ansi(
             KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,
    KC_MUTE, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    _______, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
    KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_F7,   MO(_FN), KC_RCTL, KC_LEFT,          KC_DOWN, KC_RGHT
  ),
  [_FN] = LAYOUT_ansi(
             KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, KC_MPLY,
    _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE,
    RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP, KC_VOLD,
    _______, _______, _______, _______,                   _______,                   _______, _______, _______, KC_HOME,          KC_PGDN, KC_END
  ),

};

// RGB config, for changing RGB settings on non-VIA firmwares
void change_RGB(bool clockwise) {
    bool shift = get_mods() & MOD_MASK_SHIFT;
    bool alt = get_mods() & MOD_MASK_ALT;
    bool ctrl = get_mods() & MOD_MASK_CTRL;

    if (clockwise) {
        if (alt) {
            rgblight_increase_hue();
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (shift) {
            rgblight_increase_sat();
        } else {
            rgblight_step();
        }

  } else {
      if (alt) {
            rgblight_decrease_hue();
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (shift) {
            rgblight_decrease_sat();
        } else {
            rgblight_step_reverse();
        }
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (layer_state_is(_FN)) {
    //change RGB settings
    change_RGB(clockwise);
  }
  else {
    if (clockwise) {
      tap_code(KC_VOLU);
  } else {
      tap_code(KC_VOLD);
    }
  }
}

void matrix_init_user(void) {
  // Initialize remote keyboard, if connected (see readme)
  matrix_init_remote_kb();
}

void matrix_scan_user(void) {
  // Scan and parse keystrokes from remote keyboard, if connected (see readme)
  matrix_scan_remote_kb();
}

// Keyboard animation start 
static char keyboard_buffer[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void paint_xy(int x, int y, bool on){
    if(x < 0){
      x = 0;
    }else if (x > 127){
      x = 127;
    }
    if(y < 0){
      y = 0;
    }else if(y > 31){
      y = 31;
    }

  int i = 128*(y/8) + x;
  int s = y%8;
  uint8_t val = 1;
  val <<= s;
  if(on){
    keyboard_buffer[i] |= val;
  }else{
    keyboard_buffer[i] &= (~val);
  }
}

static void paint_border(int x0, int y0, int w, int h, bool on){
  int maxX = x0+w;
  int maxY = y0+h;
  for(int x = x0; x < maxX ; x++){
    paint_xy(x,y0,on);
    paint_xy(x,maxY-1,on);
  }
  for(int y = y0; y < maxY ; y++){
    paint_xy(x0,y,on);
    paint_xy(maxX-1,y,on);
  }
}

static void paint_inside(int x0, int y0, int w, int h, bool on){
  int maxX = x0+w;
  int maxY = y0+h;
  for(int x = x0+1; x < maxX-1 ; x++){
    for(int y = y0+1; y < maxY-1 ; y++){
      paint_xy(x,y,on);
    }
  }
}

struct key_info
{
    int8_t key_x_offset;
    uint8_t key_width; 
};

#define V_KEYB_X_OFF 20
#define V_KEYB_Y_OFF 5
#define U1_00_W 4
#define U1_25_W 5
#define U1_50_W 6
#define U1_75_W 7
#define U2_00_W 8
#define U2_25_W 10
#define U6_25_W 30
#define KEY_H 4

struct key_info key_infos[5][16] = 
{
  //     Special      mod left         1             2             3             4             5              6              7              8              9         0              -              =            Bskpc           Ins
    {{0,0},        {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W},  {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U1_00_W}, {0, U2_00_W},  {4, U1_00_W} },
    {{0, U1_00_W}, {0, U1_50_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W},  {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_00_W}, {2, U1_50_W},  {4, U1_00_W} },
    {{0, U1_00_W}, {0, U1_75_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W},  {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {3, U1_00_W}, {-2, U2_25_W}, {4, U1_00_W} },
    {{0, U1_00_W}, {0, U2_25_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W},  {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_00_W}, {6, U1_75_W}, {0, 0},       {4, U1_00_W},  {4, U1_00_W} },
    {{0, U1_00_W}, {0, U1_25_W}, {1, U1_25_W}, {2, U1_25_W}, {0,0},        {0,0},        {-7, U6_25_W}, {9, U1_00_W}, {9, U1_00_W}, {9, U1_00_W}, {9, U1_00_W}, {9, U1_00_W}, {9, U1_00_W}, {9, U1_00_W}, {4, U1_00_W},  {4, U1_00_W} },
};

static void paint_keyboard(void){
  paint_border(V_KEYB_X_OFF-2, V_KEYB_Y_OFF-2, 87, 28, true);
  for(uint8_t r = 0 ; r < 5 ; r++){
    for(uint8_t c = 0 ; c < 16 ; c++){
      if((key_infos[r][c]).key_width > 0){
        int x = V_KEYB_X_OFF+(key_infos[r][c]).key_x_offset+((U1_00_W+1)*c);
        int y = V_KEYB_Y_OFF+(KEY_H+1)*r;
        paint_inside(x, y, (key_infos[r][c]).key_width, KEY_H, true);
      }
    }
  }
}

static void paint_key(uint16_t keycode, keyrecord_t *record){
  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  int x = V_KEYB_X_OFF+(key_infos[r][c]).key_x_offset+((U1_00_W+1)*c);
  int y = V_KEYB_Y_OFF+(KEY_H+1)*r;
  paint_border(x, y, (key_infos[r][c]).key_width, KEY_H, record->event.pressed);
}
// Keyboard animation end

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Send keystrokes to host keyboard, if connected (see readme)
  process_record_remote_kb(keycode, record);
  paint_keyboard();
  paint_key(keycode, record);
  switch(keycode) {
    case KC_CUST:
      if (record->event.pressed) {
      }
    break;
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }

static void render_keyboard(void) {
    oled_write_raw(keyboard_buffer, sizeof(keyboard_buffer));
}

void oled_task_user(void) {
  render_keyboard();
}
#endif
