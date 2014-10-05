#include "main.h"
#include <pebble.h>
#include <main_menu.h>
  
int main() {  
    show_main_menu();
    app_event_loop();
    return 0;
}

int get_car_type() {
  return persist_read_int(SETTING_ID_CAR_TYPE);
}

int32_t get_car_speed() {
  return persist_read_int(SETTING_ID_CAR_SPEED);
}

int32_t get_car_acceleration() {
  return persist_read_int(SETTING_ID_CAR_ACCELERATION);  
}

int32_t get_car_grip() {
  return persist_read_int(SETTING_ID_CAR_GRIP);  
}

int32_t get_car_nitro() {
  return persist_read_int(SETTING_ID_CAR_NITRO);  
}

int32_t get_car_score() {
  return get_car_speed() + get_car_acceleration() + get_car_grip() + get_car_nitro();
}

int32_t get_difficulty() {
  return persist_read_int(SETTING_ID_DIFFICULTY);  
}

int32_t get_best_time_duration() {
  return persist_read_int(SETTING_ID_BEST_TIME_DURATION);  
}

int32_t get_best_time_score() {
  return persist_read_int(SETTING_ID_BEST_TIME_SCORE);  
}

int32_t get_budget() {
  return persist_read_int(SETTING_ID_BUDGET);  
}

bool get_backlight_on() {
  return persist_read_bool(SETTING_ID_BACKLIGHT_ON);  
}

bool get_low_power() {
  return persist_read_bool(SETTING_ID_LOW_POWER);  
}

void set_car_type(int value) {
  persist_write_int(SETTING_ID_CAR_TYPE, value);
}

void set_car_speed(int32_t value) {
  persist_write_int(SETTING_ID_CAR_SPEED, value);
}

void set_car_acceleration(int32_t value) {
  persist_write_int(SETTING_ID_CAR_ACCELERATION, value);  
}

void set_car_grip(int32_t value) {
  persist_write_int(SETTING_ID_CAR_GRIP, value);  
}

void set_car_nitro(int32_t value) {
  persist_write_int(SETTING_ID_CAR_NITRO, value);  
}

void set_difficulty(int32_t value) {
  persist_write_int(SETTING_ID_DIFFICULTY, value);  
}

void set_best_time_duration(int32_t value) {
  persist_write_int(SETTING_ID_BEST_TIME_DURATION, value);  
}

void set_best_time_score(int32_t value) {
  persist_write_int(SETTING_ID_BEST_TIME_SCORE, value);  
}

void set_budget(int32_t value) {
  persist_write_int(SETTING_ID_BUDGET, value);  
}

void set_backlight_on(bool value) {
  persist_write_bool(SETTING_ID_BACKLIGHT_ON, value);  
}

void set_low_power(bool value) {
  persist_write_bool(SETTING_ID_LOW_POWER, value);  
}