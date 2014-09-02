#include "hiscore.h"
#include <pebble.h>
#include <main.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_28;
static TextLayer *duration_label;
static TextLayer *duration_value;
static TextLayer *score_label;
static TextLayer *score_value;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_28 = fonts_get_system_font(FONT_KEY_GOTHIC_28);
  // duration_label
  duration_label = text_layer_create(GRect(4, 0, 138, 24));
  text_layer_set_text(duration_label, "Best time:");
  text_layer_set_font(duration_label, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)duration_label);
  
  // duration_value
  duration_value = text_layer_create(GRect(4, 24, 138, 28));
  text_layer_set_text(duration_value, "N/A");
  text_layer_set_font(duration_value, s_res_gothic_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)duration_value);
  
  // score_label
  score_label = text_layer_create(GRect(4, 60, 138, 24));
  text_layer_set_text(score_label, "With car score of:");
  text_layer_set_font(score_label, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)score_label);
  
  // score_value
  score_value = text_layer_create(GRect(4, 84, 138, 28));
  text_layer_set_text(score_value, "N/A");
  text_layer_set_font(score_value, s_res_gothic_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)score_value);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(duration_label);
  text_layer_destroy(duration_value);
  text_layer_destroy(score_label);
  text_layer_destroy(score_value);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_hiscore(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  int best_time = get_best_time_duration();
  
  if (best_time>0) {    
    char *duration_text = "dddddddddddddddd";
    int seconds = best_time/100;
    int decimals = best_time%100;
    
    snprintf(duration_text, 16, "%d.%02d s", seconds, decimals);
    text_layer_set_text(duration_value, duration_text);
    layer_mark_dirty(text_layer_get_layer(duration_value));
    
    
    char *score_text = "ssssssssssssssss";
    snprintf(score_text, 16, "%ld", (long)get_best_time_score());
    text_layer_set_text(score_value, score_text);
    layer_mark_dirty(text_layer_get_layer(score_value));
  }
}

void hide_hiscore(void) {
  window_stack_remove(s_window, true);
}
