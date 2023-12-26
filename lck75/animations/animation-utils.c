#pragma once

#ifndef IDLE_SPEED
  #define IDLE_SPEED 30
#endif
#ifndef TAP_SPEED
  #define TAP_SPEED40 //Switch to fast animation when over words per minute
#endif
#ifndef ANIM_FRAME_DURATION
  #define ANIM_FRAME_DURATION 200 //Invert animation color and background
#endif
#ifndef ANIM_SIZE
  #define ANIM_SIZE 512
#endif

static void render_animation(const char **tap_frames, const char **idle_frames, uint8_t tap_frames_len, uint8_t idle_frames_len) {
    static uint32_t anim_timer = 0;
    static uint32_t anim_sleep = 0;
    static uint8_t current_idle_frame = 0;
    static uint8_t current_tap_frame = 0;

    void animation_phase(void) {

        if (get_current_wpm() <=IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % idle_frames_len;
            oled_write_raw_P(idle_frames[abs((idle_frames_len-1)-current_idle_frame)], ANIM_SIZE);
        }else {
            current_tap_frame = (current_tap_frame + 1) % tap_frames_len;
            oled_write_raw_P(tap_frames[abs((tap_frames_len-1)-current_tap_frame)], ANIM_SIZE);
        }
    }

    if (get_current_wpm() > 0) {

        oled_on();

        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }

        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
    }
}
  
