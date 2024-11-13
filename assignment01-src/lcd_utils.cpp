#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "lcd_utils.h"

#define ROWS 20
#define COLS 4

LiquidCrystal_I2C lcd(LCD, COLS, ROWS);

void lcd_init() {
  lcd.init();
  lcd.noBacklight();

  Serial.println("LCD Screen initialised");
}

void welcome_screen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to GMB!");
  lcd.setCursor(0, 1);
  lcd.print("Press B1 to start");

  Serial.println("Welcome to GMB!");
  Serial.println("Press B1 to start");
}

void go_screen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Go!");

  Serial.println("Go!");
}

void show_number(int num) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(num);

  Serial.println(num);
}

void score_screen(int score) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nice Job!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.setCursor(7, 1);
  lcd.print(score);

  Serial.print("Nice job! Score: ");
  Serial.println(score);
}

void game_over_screen(int score) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Final score: ");
  lcd.setCursor(13, 1);
  lcd.print(score);

  Serial.println("Game Over!");
  Serial.print("Final Score: ");
  Serial.println(score);
}

void lcd_turn_off() {
  Serial.println("Turning off the screen");
  lcd.clear();
  lcd.noBacklight();
}