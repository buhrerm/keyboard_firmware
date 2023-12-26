/* Copyright 2021 Lyso1/ItsWaffle(oled code)
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
 #include "kl90.h"

/* Artificial delay added to get media keys to work in the encoder*/
#define MEDIA_KEY_DELAY 10

volatile uint8_t led_numlock = false;
volatile uint8_t led_capslock = false;
volatile uint8_t led_scrolllock = false;

uint8_t layer;

bool clock_set_mode = false;
uint8_t oled_mode = OLED_DEFAULT;
bool oled_repaint_requested = false;
bool oled_wakeup_requested = false;
uint32_t oled_sleep_timer;

uint8_t encoder_value = 0;
uint8_t encoder_mode = ENC_MODE_VOLUME;
uint8_t enabled_encoder_modes = 5;

uint8_t previous_encoder_mode = 0;

uint8_t animation_select = 0;
bool animation_invert = false;
bool force_rewrite = false;
uint8_t current_tap_frame = 0;
uint8_t current_prep_frame = 0;
uint8_t current_idle_frame = 0;

bool encoder_update_kb(uint8_t index, bool clockwise) {
  if (!encoder_update_user(index, clockwise)) return false;
  oled_request_wakeup();
  encoder_value = (encoder_value + (clockwise ? 1 : -1)) % 64;
  if (index == 0) {
    if (layer == 0){
      uint16_t mapped_code = 0;
      if (clockwise) {
        mapped_code = handle_encoder_clockwise();
      } else {
        mapped_code = handle_encoder_ccw();
      }
      uint16_t held_keycode_timer = timer_read();
      if(mapped_code != 0){
        register_code16(mapped_code);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
        unregister_code16(mapped_code);
      }
    } else {
      if(clockwise){
        change_encoder_mode(false);
      } else {
        change_encoder_mode(true);
      }
    }
  }
  return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  state = layer_state_set_user(state);
  layer = get_highest_layer(state);
  oled_request_wakeup();
  return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  oled_request_wakeup();
  switch (keycode) {
    case OLED_TOGG:
      if (record->event.pressed) {
        oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
      }
      return false;
    case ENC_PRESS:
      if (record->event.pressed) {
        uint16_t mapped_code = handle_encoder_press();
        uint16_t held_keycode_timer = timer_read();
        if(mapped_code != 0){
          register_code16(mapped_code);
          while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
          unregister_code16(mapped_code);
        }
      } else {
        // Do something else when release
      }
      return false;
    default:
      break;
  }

  return process_record_user(keycode, record);
}
