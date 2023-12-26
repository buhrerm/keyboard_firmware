/*Copyright 2019 Lyso1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

#define ENCODER_RESOLUTION 4 //default/suggested

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

// OLED Config
// configure oled driver for the 128x32 oled
#define OLED_UPDATE_INTERVAL 66 // ~15fps
// OLED_TIMEOUT is incompatible with the OLED_OFF mode
#define OLED_TIMEOUT 0
// OLED timeout reimplemented in the keyboard-specific code
#define CUSTOM_OLED_TIMEOUT 60000

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_MACOS, UNICODE_MODE_LINUX

#define UNICODE_CYCLE_PERSIST false

/* #define AUTO_SHIFT_MODIFIERS */
/* #define AUTO_SHIFT_TIMEOUT 170 */
/* #define NO_AUTO_SHIFT_SPECIAL */
/* #define NO_AUTO_SHIFT_NUMERIC */

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_TERM 200

#define NO_ACTION_ONESHOT
