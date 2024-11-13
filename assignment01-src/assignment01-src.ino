/**
  Assignment 01 - Embedded Systems and Internet-of-Things
  Give Me the Binary!
  An interactive game with buttons, LEDs, a potentiometer and a LCD screen where you try to guess the binary conversion
  of a decimal number.

  Author: Kimi Osti
  E-mail: kimi.osti@studio.unibo.it
*/
#include <Timer.h>
#include "state_utils.h"
#include "event_utils.h"
#include "led_utils.h"
#include "but_utils.h"
#include "lcd_utils.h"

#define FADE_TIME 15

states curr_state;
events event;
long last_fade_ts;
bool game_over_swept;
long state_time;
Timer timer;

void time_out_print(int elapsed, int max) {
  Serial.print("Elapsed time: ");
  Serial.println(elapsed);
  Serial.print("Max state time: ");
  Serial.println(max);
}

void reset_timer() {
  timer.pause();
  Serial.print("Resetting at timestamp ");
  Serial.println(timer.read());
  timer.start();
  Serial.println("Restarting timer");
}

bool time_out(long max_time) {
  /*Serial.print(timer.read());
  Serial.print(" > ");
  Serial.print(max_time);
  Serial.println(" ?");*/
  return timer.read() > max_time;
}

void setup() {
  Serial.begin(9600);

  queue_init();
  led_init();
  but_init();
  lcd_init();
  curr_state = NEW_GAME;
  last_fade_ts = 0;
  state_time = switch_state(curr_state);
  timer.start();
}

void loop() {
  event = get_event();

  switch(curr_state) {
    case NEW_GAME:
      if (timer.read() - last_fade_ts > FADE_TIME) {
        fade_led();
        last_fade_ts = timer.read();
      }
      if (event == B1_PRESSED) {
        Serial.println("Going to game start state");
        curr_state = GAME_START;
        reset_timer();
        state_time = switch_state(curr_state);
      }
      if (time_out(state_time)) {
        time_out_print(timer.read(), state_time);
        Serial.println("Going to deep sleeping state");
        curr_state = DEEP_SLEEPING;
        state_time = switch_state(curr_state);
      }
      break;

    case DEEP_SLEEPING:
      Serial.println("Woke up! Going to new game state");
      last_fade_ts = 0;
      curr_state = NEW_GAME;
      reset_timer();
      state_time = switch_state(curr_state);
      break;

    case GAME_START:
      if (time_out(state_time)) {
        time_out_print(timer.read(), state_time);
        Serial.print("Going to round state");
        reset_timer();
        curr_state = ROUND;
        state_time = switch_state(curr_state);
      }
      break;

    case ROUND:
      switch(event) {
        case B1_PRESSED:
          turn_led(L1);
          break;
        
        case B2_PRESSED:
          turn_led(L2);
          break;

        case B3_PRESSED:
          turn_led(L3);
          break;

        case B4_PRESSED:
          turn_led(L4);
          break;
      }

      if (time_out(state_time)) {
        time_out_print(timer.read(), state_time);
        Serial.println("Going to round over state");
        curr_state = ROUND_OVER;
      }
      break;

    case ROUND_OVER:
      Serial.print("Round time: ");
      Serial.println(timer.read());
      if (check_round()) {
        Serial.println("Going to show score state");
        curr_state = SHOW_SCORE;
      } else {
        Serial.println("Going to game over state");
        game_over_swept = 0;
        curr_state = GAME_OVER;
      }
      reset_timer();
      state_time = switch_state(curr_state);
      break;

    case SHOW_SCORE:
      if (time_out(state_time)) {
        time_out_print(timer.read(), state_time);
        Serial.println("Going to round state");
        reset_timer();
        curr_state = ROUND;
        state_time = switch_state(curr_state);
      }
      break;

    case GAME_OVER:
      if (time_out(state_time)) {
        time_out_print(timer.read(), state_time);
        Serial.println("Going to new game state");
        reset_timer();
        last_fade_ts = 0;
        curr_state = NEW_GAME;
        state_time = switch_state(curr_state);
      }
      if (timer.read() >= 1000 && !game_over_swept) { /*passato almeno un secondo*/
        Serial.print("Elapsed time: ");
        Serial.println(timer.read());
        sweep_leds();
        game_over_swept = 1;
      }
      break;
  }
}
