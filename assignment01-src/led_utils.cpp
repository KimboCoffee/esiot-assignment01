#include <Arduino.h>
#include "led_utils.h"

#define OFFSET 6

int state[4];

int fade_amount = 5;
int brightness;

void led_init() {
  for (int i = 0; i < 4; i++) {
    pinMode(i + OFFSET, OUTPUT);
    state[i] = LOW;
  }
  fade_amount = 5;
  brightness = 0;

  Serial.println("LEDs initialised");
  Serial.print("LS fade: ");
  Serial.println(fade_amount);
  Serial.print("LS brightness: ");
  Serial.println(brightness);
}

void turn_led(int pin) {
  state[pin - OFFSET] = !state[pin - OFFSET];
  digitalWrite(pin, state[pin - OFFSET]);

  Serial.print("Turned led ");
  Serial.print(pin - OFFSET + 1);
  Serial.print(": state ");
  Serial.println(state[pin - OFFSET]);
}

void sweep_leds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(i + OFFSET, LOW);
    state[i] = LOW;
  }

  brightness = 0;
  fade_amount = 5;
  analogWrite(LS, brightness);

  Serial.println("LEDs swept");
  Serial.print("LS fade: ");
  Serial.println(fade_amount);
  Serial.print("LS brightness: ");
  Serial.println(brightness);
}

int get_led_state(int pin) {
  return state[pin - OFFSET];
}

void fade_led() {
  brightness += fade_amount;

  if (brightness == 0 || brightness == 255) {
    fade_amount = -fade_amount;
  }

  analogWrite(LS, brightness);
  /*Serial.print("LS fade: ");
  Serial.println(fade_amount);
  Serial.print("LS brightness: ");
  Serial.println(brightness);*/
}