#include "settings.h"
#include <pebble.h>
#include <main.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GRect bounds;
static MenuLayer *menu;

static void initialise_ui(void) {
  s_window = window_create();
  #ifdef PBL_SDK_2
    window_set_fullscreen(s_window, true);
  #endif
  
  bounds = layer_get_bounds(window_get_root_layer(s_window));
  
  menu = menu_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  menu_layer_set_click_config_onto_window(menu, s_window);
  
  #ifdef PBL_COLOR
    menu_layer_set_normal_colors(menu, GColorPastelYellow, GColorBlack);
    menu_layer_set_highlight_colors(menu, GColorDarkCandyAppleRed, GColorWhite);
  #endif
  
  #ifdef PBL_ROUND
    menu_layer_set_center_focused(menu, true);
  #endif
    
  layer_add_child(window_get_root_layer(s_window), (Layer *)menu);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(menu);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 2;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 18;
}

static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    return 54;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorBulgarianRose);
    graphics_context_set_text_color(ctx, GColorWhite);
  #else
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
  
  #ifdef PBL_ROUND
    menu_layer_set_center_focused(menu, true);
  #endif
    
  graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w, 18), 0, GCornerNone);
    
  graphics_draw_text(ctx, "Settings", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(0, -3, bounds.size.w, 18), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  /*#ifdef PBL_COLOR    
    graphics_context_set_fill_color(ctx, GColorPastelYellow);
    graphics_fill_rect(ctx, GRect(0, 0, 144, 54), 0, GCornerNone);
  #endif*/
    
  #ifdef PBL_SDK_2
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
  
  GRect label_rect = GRect(8, 0, bounds.size.w-16, 34);
  GRect value_rect = GRect(bounds.size.w-46, 0, 38, 34);
  GRect description_rect = GRect(8, 29, bounds.size.w-16, 14);
  
  switch (cell_index->row) {
    case 0:
      graphics_draw_text(ctx, "Backlight", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), label_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      graphics_draw_text(ctx, get_backlight_on() ? "On" : "Auto", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), value_rect, GTextOverflowModeFill, GTextAlignmentRight, NULL);
      graphics_draw_text(ctx, "Affects battery life", fonts_get_system_font(FONT_KEY_GOTHIC_14), description_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      break;
    case 1:
      graphics_draw_text(ctx, "Power mode", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), label_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      graphics_draw_text(ctx, get_low_power() ? "Low" : "High", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), value_rect, GTextOverflowModeFill, GTextAlignmentRight, NULL);
      graphics_draw_text(ctx, "Animations and battery", fonts_get_system_font(FONT_KEY_GOTHIC_14), description_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      break;
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {  
  switch (cell_index->row) {
    case 0:
      set_backlight_on(!get_backlight_on());
      menu_layer_reload_data(menu);
      break;
    case 1:
      set_low_power(!get_low_power());
      menu_layer_reload_data(menu);
      break;
  }
}

void show_settings(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  #ifdef PBL_COLOR
    window_set_background_color(s_window, GColorPastelYellow);
  #endif
    
  window_stack_push(s_window, true);
  
  menu_layer_set_callbacks(menu, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .get_cell_height = menu_get_cell_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  menu_layer_set_click_config_onto_window(menu, s_window);
}

void hide_settings(void) {
  window_stack_remove(s_window, true);
}
