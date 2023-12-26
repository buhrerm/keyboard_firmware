#include "../kl90.h"
#include "quantum.h"

#pragma once

#ifndef ANIM_SIZE
  #define ANIM_SIZE 512
#endif
#ifndef MAX_ANIMATION_SPEED
  #define MAX_ANIMATION_SPEED 50
#endif
#ifndef ANIM_FRAME_DURATION
  #define ANIM_FRAME_DURATION 200
#endif

#ifndef TYPING_FRAME_DURATION
  #define TYPING_FRAME_DURATION 200
#endif
#ifndef IDLE_WPM
  #define IDLE_WPM 30
#endif
#ifndef TAP_WPM
  #define TAP_WPM 50
#endif

static void render_animation(const char **tap_frames, uint8_t _tap_frames_len) {
    static uint32_t anim_timer = 0;
    uint32_t anim_speed = ANIM_FRAME_DURATION;

    void animation_phase(void) {
      if (!force_rewrite){
        current_tap_frame = (current_tap_frame + 1) % _tap_frames_len;
      }
      oled_write_raw_P(tap_frames[abs((_tap_frames_len-1)-current_tap_frame)], ANIM_SIZE);
    }

    // Calculate animation_speed from wpm
    if (get_current_wpm() > ANIM_FRAME_DURATION){
        anim_speed = MAX_ANIMATION_SPEED;
    } else {
        anim_speed = ANIM_FRAME_DURATION - get_current_wpm();
    }
    // Cycle animation
    if (force_rewrite){
        animation_phase();
        force_rewrite = false;
    } else if (timer_elapsed32(anim_timer) > anim_speed) {
        anim_timer = timer_read32();
        animation_phase();
    }
}


// static void render_animation_with_speed(const char **tap_frames, uint8_t _tap_frames_len, uint32_t start_speed, uint32_t max_speed) {
//     static uint32_t anim_timer = 0;
//     uint32_t anim_speed = start_speed;
//
//     void animation_phase(void) {
//       if (!force_rewrite){
//         current_tap_frame = (current_tap_frame + 1) % _tap_frames_len;
//       }
//       oled_write_raw_P(tap_frames[abs((_tap_frames_len-1)-current_tap_frame)], ANIM_SIZE);
//     }
//
//     // Calculate animation_speed from wpm
//     if (get_current_wpm() > start_speed){
//         anim_speed = max_speed;
//     } else {
//         anim_speed = start_speed - get_current_wpm();
//     }
//     // Cycle animation
//     if (force_rewrite){
//         animation_phase();
//         force_rewrite = false;
//     } else if (timer_elapsed32(anim_timer) > anim_speed) {
//         anim_timer = timer_read32();
//         animation_phase();
//     }
// }

static void typing_animation_with_speed(
  const char **tap_frames,
  const char **idle_frames,
  const char ** prep_frames,
  uint8_t _tap_frames_len,
  uint8_t _idle_frames_len,
  uint8_t _prep_frames_len,
  uint8_t _typing_frame_duration
) {
  static uint32_t anim_timer = 0;

  void animation_phase(void) {
      if (get_current_wpm() <=IDLE_WPM) {
        if (!force_rewrite){
          current_prep_frame = 0;
          current_tap_frame = 0;
          current_idle_frame = (current_idle_frame + 1) % _idle_frames_len;
        }
        oled_write_raw_P(idle_frames[abs((_idle_frames_len-1)-current_idle_frame)], ANIM_SIZE);
      }

      if (get_current_wpm() >IDLE_WPM && get_current_wpm() < TAP_WPM) {
        if (!force_rewrite){
          current_idle_frame = 0;
          current_tap_frame = 0;
          current_prep_frame = (current_prep_frame + 1) % _prep_frames_len;
        }
        oled_write_raw_P(prep_frames[abs((_prep_frames_len-1)-current_prep_frame)], ANIM_SIZE);
      }

      if (get_current_wpm() >=TAP_WPM) {
        if (!force_rewrite){
          current_idle_frame = 0;
          current_prep_frame = 0;
          current_tap_frame = (current_tap_frame + 1) % _tap_frames_len;
        }
        oled_write_raw_P(tap_frames[abs((_tap_frames_len-1)-current_tap_frame)], ANIM_SIZE);
      }
  }

    // Cycle animation
  if (force_rewrite){
      animation_phase();
      force_rewrite = false;
  } else if (timer_elapsed32(anim_timer) > _typing_frame_duration) {
      anim_timer = timer_read32();
      animation_phase();
  }

}

// static void typing_animation(
//   const char **tap_frames, const char **idle_frames, const char ** prep_frames,
//   uint8_t _tap_frames_len, uint8_t _idle_frames_len) {
//   static uint32_t anim_timer = 0;
//
//   void animation_phase(void) {
//       if (get_current_wpm() <=IDLE_WPM) {
//         if (!force_rewrite){
//           current_idle_frame = (current_idle_frame + 1) % _idle_frames_len;
//         }
//         oled_write_raw_P(idle_frames[abs((_idle_frames_len-1)-current_idle_frame)], ANIM_SIZE);
//       }
//
//       if (get_current_wpm() >IDLE_WPM && get_current_wpm() < TAP_WPM) {
//         oled_write_raw_P(prep_frames[0], ANIM_SIZE);
//       }
//
//       if (get_current_wpm() >=TAP_WPM) {
//         if (!force_rewrite){
//           current_tap_frame = (current_tap_frame + 1) % _tap_frames_len;
//         }
//         oled_write_raw_P(tap_frames[abs((_tap_frames_len-1)-current_tap_frame)], ANIM_SIZE);
//       }
//   }
//
//     // Cycle animation
//   if (force_rewrite){
//       animation_phase();
//       force_rewrite = false;
//   } else if (timer_elapsed32(anim_timer) > TYPING_FRAME_DURATION) {
//       anim_timer = timer_read32();
//       animation_phase();
//   }
//
// }
