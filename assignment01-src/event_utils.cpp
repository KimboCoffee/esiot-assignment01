#include <stdlib.h>
#include <Arduino.h>
#include "event_utils.h"

#define MAX_OCCUPATION 10

queue_node* head;
int occupation;

void queue_init() {
  head = (queue_node*)malloc(sizeof(queue_node));
  head->next = NULL;
  head->elem = NONE;
  occupation = 0;
  Serial.println("Initialised queue");
}

void add_event(events event) {
  if (occupation <= MAX_OCCUPATION) {
    queue_node *temp = (queue_node*)malloc(sizeof(queue_node));

    if (temp != NULL) {
      temp->next = head->next;
      temp->elem = event;
      head->next = temp;
    }

    occupation++;

    Serial.print("Added event ");
    Serial.println(event);
    Serial.print("Occupation: ");
    Serial.println(occupation);
  } else {
    Serial.print("Reached max occupation of ");
    Serial.println(occupation);
  }
}

events get_event() {
  queue_node *temp = head;
  queue_node *prev;

  while(temp->next != NULL) {
    prev = temp;
    temp = temp->next;
  }

  events event = temp->elem;

  if (event != NONE) {
    free(temp);
    prev->next = NULL;
    occupation--;
    Serial.print("Fetched event ");
    Serial.println(event);
    Serial.print("Occupation: ");
    Serial.println(occupation);
  } /*else {
    Serial.println("No event fetched");
  }*/

  return event;
}

void clear_queue() {
  queue_node *temp = head;
  queue_node *next = head->next;

  while (next != NULL) {
    temp = next;
    next = temp->next;
    free(temp);
  }

  head->next = NULL;

  occupation = 0;

  Serial.println("Cleared event queue");
  Serial.print("Occupation: ");
  Serial.println(occupation);
}