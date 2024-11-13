#include <Arduino.h>
#include <avr/sleep.h>
#include <time.h>
#include "event_utils.h"
#include "led_utils.h"
#include "state_utils.h"
#include "lcd_utils.h"

#define POT A0
#define TEN_SEC 10000
#define TWO_SEC 2000
#define INITIAL_ROUND_TIME 5000
#define MAX_NUM 15
#define ROUND_SCORE 15

int score;
long round_time;
int round_num;
float diff_coefficient;

float get_difficulty() {
  switch(map(analogRead(POT), 0, 1023, 0, 3)) {
    case 0:
      Serial.println("Easy difficulty");
      return 0.90;

    case 1:
      Serial.println("Medium difficulty");
      return 0.85;
      
    case 2:
      Serial.println("Hard difficulty");
      return 0.80;
    
    case 3:
      Serial.println("Brutal difficulty");
      return 0.75;
  }
}

void go_to_sleep() {
  Serial.println("Going to sleep...");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}

long switch_state(states new_state) {
  switch(new_state) {
    case NEW_GAME:
      clear_queue();
      sweep_leds();
      welcome_screen();
      return TEN_SEC;

    case DEEP_SLEEPING:
      clear_queue();
      lcd_turn_off();
      sweep_leds();
      go_to_sleep();
      return 0;

    case GAME_START:
      clear_queue();
      sweep_leds();
      go_screen();
      round_time = INITIAL_ROUND_TIME;
      diff_coefficient = get_difficulty();
      score = 0;
      return TWO_SEC;

    case ROUND:
      clear_queue();
      srand(millis());
      round_num = rand() % MAX_NUM;
      show_number(round_num);
      return round_time;

    case SHOW_SCORE:
      clear_queue();
      sweep_leds();
      round_time = round_time * diff_coefficient;
      score += ROUND_SCORE;
      score_screen(score);
      return TWO_SEC;

    case GAME_OVER:
      clear_queue();
      analogWrite(LS, 255);
      game_over_screen(score);
      return TEN_SEC;
  }
}

bool check_round() {
  Serial.print(get_led_state(L1));
  Serial.print(get_led_state(L2));
  Serial.print(get_led_state(L3));
  Serial.print(get_led_state(L4));
  Serial.print(" == ");
  Serial.print(round_num);
  Serial.println(" ?");
  return ((get_led_state(L1) * 8) + (get_led_state(L2) * 4) + (get_led_state(L3) * 2) + get_led_state(L4)) == round_num;
}