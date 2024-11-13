#include <EnableInterrupt.h>
#include <Arduino.h>
#include "but_utils.h"
#include "event_utils.h"

#define DEBOUNCE_TIME 50

long last_interrupt_ts;

void b1_pressed() {
  if (millis() - last_interrupt_ts > DEBOUNCE_TIME) {
    add_event(B1_PRESSED);
    Serial.println("B1 was pressed");

    last_interrupt_ts = millis();
  } 
}

void b2_pressed() {
  if (millis() - last_interrupt_ts > DEBOUNCE_TIME) {
    add_event(B2_PRESSED);
    Serial.println("B2 was pressed");

    last_interrupt_ts = millis();
  } 
}

void b3_pressed() {
  if (millis() - last_interrupt_ts > DEBOUNCE_TIME) {
    add_event(B3_PRESSED);
    Serial.println("B3 was pressed");

    last_interrupt_ts = millis();
  } 
}

void b4_pressed() {
  if (millis() - last_interrupt_ts > DEBOUNCE_TIME) {
    add_event(B4_PRESSED);
    Serial.println("B4 was pressed");

    last_interrupt_ts = millis();
  } 
}

void but_init() {
  enableInterrupt(B1, b1_pressed, FALLING);
  enableInterrupt(B2, b2_pressed, FALLING);
  enableInterrupt(B3, b3_pressed, FALLING);
  enableInterrupt(B4, b4_pressed, FALLING);

  Serial.println("Buttons initialised");
}