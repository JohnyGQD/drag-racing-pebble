#include "garage.h"
#include <pebble.h>
#include <main.h>
#include <upgrades.h>
  
static GBitmap *car_bitmap;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_18;
static GBitmap *s_res_up;
static BitmapLayer *car;
static TextLayer *score;
static TextLayer *speed;
static TextLayer *acceleration;
static TextLayer *grip;
static TextLayer *nitro;
static BitmapLayer *buttons_background;
static BitmapLayer *upgrade;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_up = gbitmap_create_with_resource(RESOURCE_ID_UP);
  // car
  car = bitmap_layer_create(GRect(22, 8, 100, 30));
  bitmap_layer_set_background_color(car, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)car);
  
  // score
  score = text_layer_create(GRect(6, 42, 136, 24));
  text_layer_set_text(score, "Text layer");
  text_layer_set_text_alignment(score, GTextAlignmentCenter);
  text_layer_set_font(score, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)score);
  
  // speed
  speed = text_layer_create(GRect(4, 64, 120, 20));
  text_layer_set_text(speed, "Text layer");
  text_layer_set_font(speed, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)speed);
  
  // acceleration
  acceleration = text_layer_create(GRect(4, 84, 120, 20));
  text_layer_set_text(acceleration, "Text layer");
  text_layer_set_font(acceleration, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)acceleration);
  
  // grip
  grip = text_layer_create(GRect(4, 104, 120, 20));
  text_layer_set_text(grip, "Text layer");
  text_layer_set_font(grip, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)grip);
  
  // nitro
  nitro = text_layer_create(GRect(4, 124, 120, 20));
  text_layer_set_text(nitro, "Text layer");
  text_layer_set_font(nitro, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)nitro);
  
  // buttons_background
  buttons_background = bitmap_layer_create(GRect(127, 67, 17, 17));
  bitmap_layer_set_background_color(buttons_background, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)buttons_background);
  
  // upgrade
  upgrade = bitmap_layer_create(GRect(130, 70, 11, 11));
  bitmap_layer_set_bitmap(upgrade, s_res_up);
  bitmap_layer_set_background_color(upgrade, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)upgrade);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(car);
  text_layer_destroy(score);
  text_layer_destroy(speed);
  text_layer_destroy(acceleration);
  text_layer_destroy(grip);
  text_layer_destroy(nitro);
  bitmap_layer_destroy(buttons_background);
  bitmap_layer_destroy(upgrade);
  gbitmap_destroy(s_res_up);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  hide_garage();
  show_upgrades();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void show_garage(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  window_set_click_config_provider(s_window, click_config_provider);
  
  if (get_car_type()==CAR_TYPE_MUSCLE) {
    car_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MUSCLE);    
  } else {
    car_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RACING);    
  }
  
  bitmap_layer_set_bitmap(car, car_bitmap);
    
  char *score_text = "Car score: xxxxxxxxxx";
  snprintf(score_text, 32, "Car score: %ld", (long)get_car_score());
  text_layer_set_overflow_mode(score, GTextOverflowModeTrailingEllipsis);
  text_layer_set_text(score, score_text);
  
  char *speed_text = "Max. speed: xxxxxxxxxx";
  snprintf(speed_text, 32, "Max. speed: %ld", (long)get_car_speed());
  text_layer_set_overflow_mode(speed, GTextOverflowModeTrailingEllipsis);
  text_layer_set_text(speed, speed_text);
  
  char *acceleration_text = "Acceleration: xxxxxxxxxx";
  snprintf(acceleration_text, 32, "Acceleration: %ld", (long)get_car_acceleration());
  text_layer_set_overflow_mode(acceleration, GTextOverflowModeTrailingEllipsis);
  text_layer_set_text(acceleration, acceleration_text);
  
  char *grip_text = "Grip: xxxxxxxxxx";
  snprintf(grip_text, 32, "Grip: %ld", (long)get_car_grip());
  text_layer_set_overflow_mode(grip, GTextOverflowModeTrailingEllipsis);
  text_layer_set_text(grip, grip_text);
  
  char *nitro_text = "Nitro: xxxxxxxxxx";
  snprintf(nitro_text, 32, "Nitro: %ld", (long)get_car_nitro());
  text_layer_set_overflow_mode(nitro, GTextOverflowModeTrailingEllipsis);
  text_layer_set_text(nitro, nitro_text);
}

void hide_garage(void) {
  gbitmap_destroy(car_bitmap);
  
  window_stack_remove(s_window, true);
}
