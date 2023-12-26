#include "quantum.h"

#pragma once

// Start these at the USER code range in VIA
enum my_keycodes {
  ENC_PRESS = SAFE_RANGE,
  OLED_TOGG
};

enum s75_custom_value_id {
  id_encoder_modes = 1,
  id_oled_default_mode,
  id_encoder_custom,
  id_oled_mode
};

enum encoder_modes {
  ENC_MODE_VOLUME,
  ENC_MODE_MEDIA,
  ENC_MODE_ANIMATION,
  ENC_MODE_SCROLL,
  ENC_MODE_BRIGHTNESS,
  _NUM_ENCODER_MODES,
};

enum oled_modes {
  OLED_DEFAULT,
  OLED_OFF,
  _NUM_OLED_MODES
};

// Encoder Animation
#define NUM_ANIMATIONS 4
extern uint8_t animation_select;
extern bool animation_invert;
extern bool force_rewrite;
extern uint8_t current_tap_frame;
extern uint8_t current_prep_frame;
extern uint8_t current_idle_frame;

// Keyboard Information
extern volatile uint8_t led_numlock;
extern volatile uint8_t led_capslock;
extern volatile uint8_t led_scrolllock;
extern uint8_t layer;

// OLED Behavior
extern uint8_t oled_mode;
extern bool oled_repaint_requested;
extern bool oled_wakeup_requested;
extern uint32_t oled_sleep_timer;

// Encoder Behavior
extern uint8_t encoder_value;
extern uint8_t encoder_mode;
extern uint8_t enabled_encoder_modes;

// RTC Configuration
extern uint8_t previous_encoder_mode;

void change_encoder_mode(bool negative);
uint16_t handle_encoder_clockwise(void);
uint16_t handle_encoder_ccw(void);
uint16_t handle_encoder_press(void);

void oled_request_wakeup(void);
void oled_request_repaint(void);
bool oled_task_needs_to_repaint(void);
