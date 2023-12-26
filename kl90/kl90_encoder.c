#include "kl90.h"

void change_encoder_mode(bool negative){
  if(enabled_encoder_modes == 0){
    enabled_encoder_modes = 5;
  }
  if(negative){
    if (encoder_mode == 0){
      encoder_mode = _NUM_ENCODER_MODES - 1;
    } else{
      encoder_mode = encoder_mode - 1;
    }
  } else {
      encoder_mode = (encoder_mode + 1) % (_NUM_ENCODER_MODES);
  }
}

uint16_t handle_encoder_clockwise(void){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLU;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_NEXT_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_D;
      break;
    case ENC_MODE_ANIMATION:
      if (animation_select == NUM_ANIMATIONS - 1){
        animation_select = 0;
      }else {
        animation_select ++;
      }
      current_idle_frame = 0;
      current_prep_frame = 0;
      current_tap_frame = 0;
      force_rewrite = true;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_UP;
      break;
  }
  return mapped_code;
}

uint16_t handle_encoder_ccw(void){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLD;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PREV_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_U;
      break;
    case ENC_MODE_ANIMATION:
      if (animation_select == 0){
        animation_select = NUM_ANIMATIONS - 1;
      } else {
        animation_select = animation_select - 1;
      }
      current_idle_frame = 0;
      current_prep_frame = 0;
      current_tap_frame = 0;
      force_rewrite = true;
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_DOWN;
      break;
  }
  return mapped_code;
}

uint16_t handle_encoder_press(void){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    case ENC_MODE_VOLUME:
      mapped_code = KC_MUTE;
      break;
    default:
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PLAY_PAUSE;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_BTN3;
      break;
    case ENC_MODE_ANIMATION:
      animation_invert = !animation_invert;
      current_idle_frame = 0;
      current_prep_frame = 0;
      current_tap_frame = 0;
      force_rewrite = true;
      break;
    case ENC_MODE_BRIGHTNESS:
      break;
  }
  return mapped_code;
}
