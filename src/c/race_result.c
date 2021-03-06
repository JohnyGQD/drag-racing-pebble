#include "race_result.h"
#include "main.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GRect bounds;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_18;
static TextLayer *big_result;
static TextLayer *hiscore;
static TextLayer *reward;
static TextLayer *duration;
static TextLayer *budget;

static void initialise_ui(void) {
  s_window = window_create();
  #ifdef PBL_SDK_2
    window_set_fullscreen(s_window, true);
  #endif
  
  bounds = layer_get_bounds(window_get_root_layer(s_window));
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // big_result
  big_result = text_layer_create(GRect(0, ((bounds.size.h-168)/2)+15, bounds.size.w, 28));
  text_layer_set_text(big_result, "You win!");
  text_layer_set_text_alignment(big_result, GTextAlignmentCenter);
  text_layer_set_font(big_result, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)big_result);
  
  // hiscore
  hiscore = text_layer_create(GRect(0, ((bounds.size.h-168)/2)+90, bounds.size.w, 28));
  text_layer_set_text(hiscore, "New record!");
  text_layer_set_text_alignment(hiscore, GTextAlignmentCenter);
  text_layer_set_font(hiscore, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)hiscore);
  
  // reward
  reward = text_layer_create(GRect(0, ((bounds.size.h-168)/2)+50, bounds.size.w, 20));
  text_layer_set_text(reward, "Reward: 0");
  text_layer_set_text_alignment(reward, GTextAlignmentCenter);
  text_layer_set_font(reward, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)reward);
  
  // duration
  duration = text_layer_create(GRect(0, ((bounds.size.h-168)/2)+70, bounds.size.w, 20));
  text_layer_set_text(duration, "Time: 0.0 s");
  text_layer_set_text_alignment(duration, GTextAlignmentCenter);
  text_layer_set_font(duration, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)duration);
  
  // budget
  budget = text_layer_create(GRect(0, ((bounds.size.h-168)/2)+125, bounds.size.w, 24));
  text_layer_set_text(budget, "Budget: 0");
  text_layer_set_text_alignment(budget, GTextAlignmentCenter);
  text_layer_set_font(budget, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)budget);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(big_result);
  text_layer_destroy(hiscore);
  text_layer_destroy(reward);
  text_layer_destroy(duration);
  text_layer_destroy(budget);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  if (get_backlight_on())
    light_enable(false);
  
  destroy_ui();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  hide_race_result();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void show_race_result(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  #ifdef PBL_COLOR
    window_set_background_color(s_window, GColorPastelYellow);
  #endif

  window_stack_push(s_window, true);
  
  window_set_click_config_provider(s_window, click_config_provider);
  
  if (get_backlight_on())
    light_enable(true);
  
  if (race_win) text_layer_set_text(big_result, "You win!");  
  else text_layer_set_text(big_result, "You lose...");  
  layer_mark_dirty(text_layer_get_layer(big_result));
  
  char *reward_text = "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr";
  snprintf(reward_text, 32, "Reward: %ld", race_reward);
  text_layer_set_text(reward, reward_text);
  layer_mark_dirty(text_layer_get_layer(reward));
  
  char *duration_text = "dddddddddddddddd";
  int seconds = race_duration/100;
  int decimals = race_duration%100;
  
  snprintf(duration_text, 16, "Time: %d.%02d s", seconds, decimals);
  text_layer_set_text(duration, duration_text);
  layer_mark_dirty(text_layer_get_layer(duration));
  
  char *budget_text = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
  snprintf(budget_text, 32, "Budget: %ld", get_budget());
  text_layer_set_text(budget, budget_text);
  layer_mark_dirty(text_layer_get_layer(budget));
  
  if (get_best_time_duration()==0 || get_best_time_duration()>race_duration) {
    layer_set_hidden(text_layer_get_layer(hiscore), false);
    
    set_best_time_duration(race_duration);
    set_best_time_score(get_car_score());
  } else {
    layer_set_hidden(text_layer_get_layer(hiscore), true);
  }
  
  #ifdef PBL_COLOR
    text_layer_set_background_color(big_result, GColorPastelYellow);
    text_layer_set_text_color(big_result, GColorDarkCandyAppleRed);
    text_layer_set_background_color(reward, GColorPastelYellow);
    text_layer_set_background_color(duration, GColorPastelYellow);
    text_layer_set_background_color(budget, GColorPastelYellow);
    text_layer_set_background_color(hiscore, GColorPastelYellow);
    text_layer_set_text_color(hiscore, GColorDarkCandyAppleRed);
  #endif
}

void hide_race_result(void) {
  window_stack_remove(s_window, true);
}
