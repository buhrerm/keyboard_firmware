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
#include "quantum.h"

#include "./animations/killua.c"
#include "./animations/ship.c"

_Bool encoder_update_kb(uint8_t index, _Bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        tap_code_delay(KC_VOLU, 10);
    } else {
        tap_code_delay(KC_VOLD, 10);
    }
    return false;
}

int animation_select = 0;
#define MAX_ANIMATIONS 2


oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}


_Bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (animation_select == 0){
        return killua();
    }
     else if (animation_select == 1){
        return ship();
    }
    return false;
}

_Bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAIL:
      if (record->event.pressed) {
        animation_select = (animation_select + 1) % MAX_ANIMATIONS;
      }
      return false; // Skip all further processing of this key
    case KC_CALCULATOR:
      if (record->event.pressed) {
        animation_select = animation_select - 1;
        if (animation_select < 0){
            animation_select = MAX_ANIMATIONS - 1;
        }
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

