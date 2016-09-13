#include "garage.h"
#include <pebble.h>
#include <main.h>
#include <upgrades.h>
  
static GBitmap *car_bitmap;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GRect bounds;
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
  #ifdef PBL_SDK_2
    window_set_fullscreen(s_window, true);
  #endif
  
  bounds = layer_get_bounds(window_get_root_layer(s_window));
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_up = gbitmap_create_with_resource(RESOURCE_ID_UP);
  // car
  car = bitmap_layer_create(GRect((bounds.size.w-100)/2, ((bounds.size.h-144)/2)+8, 100, 30));
  bitmap_layer_set_background_color(car, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)car);
  
  // score
  score = text_layer_create(GRect(5, ((bounds.size.h-144)/2)+42, bounds.size.w-10, 24));
  text_layer_set_text(score, "Text layer");
  text_layer_set_text_alignment(score, GTextAlignmentCenter);
  text_layer_set_font(score, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)score);
  
  // speed
  speed = text_layer_create(GRect(5, ((bounds.size.h-144)/2)+64, bounds.size.w-10, 20));
  text_layer_set_text(speed, "Text layer");
  text_layer_set_text_alignment(speed, GTextAlignmentCenter);
  text_layer_set_font(speed, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)speed);
  
  // acceleration
  acceleration = text_layer_create(GRect(5, ((bounds.size.h-144)/2)+84, bounds.size.w-10, 20));
  text_layer_set_text(acceleration, "Text layer");
  text_layer_set_text_alignment(acceleration, GTextAlignmentCenter);
  text_layer_set_font(acceleration, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)acceleration);
  
  // grip
  grip = text_layer_create(GRect(5, ((bounds.size.h-144)/2)+104, bounds.size.w-10, 20));
  text_layer_set_text(grip, "Text layer");
  text_layer_set_text_alignment(grip, GTextAlignmentCenter);
  text_layer_set_font(grip, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)grip);
  
  // nitro
  nitro = text_layer_create(GRect(5, ((bounds.size.h-144)/2)+124, bounds.size.w-10, 20));
  text_layer_set_text(nitro, "Text layer");
  text_layer_set_text_alignment(nitro, GTextAlignmentCenter);
  text_layer_set_font(nitro, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)nitro);
  
  // buttons_background
  buttons_background = bitmap_layer_create(GRect(bounds.size.w-17, bounds.size.h/2-8, 17, 17));
  bitmap_layer_set_background_color(buttons_background, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)buttons_background);
  
  // upgrade
  upgrade = bitmap_layer_create(GRect(bounds.size.w-14, bounds.size.h/2-5, 11, 11));
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
  
  #ifdef PBL_COLOR
    window_set_background_color(s_window, GColorPastelYellow);
  #endif

  window_stack_push(s_window, true);
  window_set_click_config_provider(s_window, click_config_provider);
  
  if (get_car_type()==CAR_TYPE_MUSCLE) {
    car_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MUSCLE);    
  } else {
    car_bitmap = gbitmap_create_with_resource(RESOURCE_ID_RACING);    
  }

  bitmap_layer_set_compositing_mode(car, GCompOpSet);
  
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
  
  #ifdef PBL_COLOR
    bitmap_layer_set_background_color(car, GColorPastelYellow);
    text_layer_set_background_color(score, GColorPastelYellow);
    text_layer_set_background_color(speed, GColorPastelYellow);
    text_layer_set_background_color(acceleration, GColorPastelYellow);
    text_layer_set_background_color(grip, GColorPastelYellow);
    text_layer_set_background_color(nitro, GColorPastelYellow);
  #endif
}

void hide_garage(void) {
  gbitmap_destroy(car_bitmap);
  
  window_stack_remove(s_window, true);
}
