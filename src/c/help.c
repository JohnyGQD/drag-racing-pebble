#include "help.h"
#include <pebble.h>
#include <main.h>
  
static ScrollLayer *scroll_layer;
static TextLayer *text_layer;
static char scroll_text[] = "Choosing starting car? Muscle cars are easier to start and reach maximum speed. But these are lacking speed. If you handle the wild racing car, you can reach better times with it. However, you can always upgrade and match the other one. Just pick the style you prefer and let the car improve as you play.\n\nWatch your RPM on start. Match the arrow to minimize wheel spin. Wheel spin can be optimized via tires upgrade.\n\nFind a gearing point that works best for your car setup. Gearing up at max RPM is very efficient, but gearing up a little sooner might give you better times. Use gearbox upgrades to increase acceleration.\n\nAfter you gear all the way up, you are only limited by your max speed. Upgrade the engine if your opponents pass you in the final seconds.\n\nIt's not always good to use nitro in the very end. If acceleration is a weak point of your car, try to boost earlier. Upgrade nitro to get longer boost.\n\nDon't rush your upgrade choices. Try to resolve the weakest point of your car or driving skills. The opponents upgrade cars as well, and they might distribute the car score more efficiently.";

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static void initialise_ui(void) {
  s_window = window_create();
  #ifdef PBL_SDK_2
    window_set_fullscreen(s_window, true);
  #endif
}

static void destroy_ui(void) {
  window_destroy(s_window);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
  
  text_layer_destroy(text_layer);
  scroll_layer_destroy(scroll_layer);
}

void show_help(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  #ifdef PBL_COLOR
    window_set_background_color(s_window, GColorPastelYellow);
  #endif

  window_stack_push(s_window, true);
  
  GRect bounds = layer_get_frame(window_get_root_layer(s_window));
  GRect max_text_bounds = GRect(0, 0, bounds.size.w, 10000);
  
  scroll_layer = scroll_layer_create(bounds);
  scroll_layer_set_click_config_onto_window(scroll_layer, s_window);
  
  text_layer = text_layer_create(max_text_bounds);
  text_layer_set_text(text_layer, scroll_text);
    
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));

  GSize max_size = text_layer_get_content_size(text_layer);
  max_size = GSize(max_size.w, max_size.h + 10);
  text_layer_set_size(text_layer, max_size);
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, max_size.h));

  scroll_layer_add_child(scroll_layer, text_layer_get_layer(text_layer));
  layer_add_child(window_get_root_layer(s_window), scroll_layer_get_layer(scroll_layer));
  
  #ifdef PBL_COLOR
    text_layer_set_background_color(text_layer, GColorPastelYellow);
  #endif
    
  text_layer_set_text_color(text_layer, GColorBlack);
  layer_mark_dirty(text_layer_get_layer(text_layer));
  
  text_layer_enable_screen_text_flow_and_paging(text_layer, 8);
  scroll_layer_set_paging(scroll_layer, true);
}

void hide_help(void) {
  window_stack_remove(s_window, true);
}
