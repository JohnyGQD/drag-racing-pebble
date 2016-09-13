#include "main_menu.h"
#include <pebble.h>
#include <main.h>
#include <race_selection.h>
#include <car_selection.h>
#include <garage.h>
#include <hiscore.h>
#include <help.h>
#include <settings.h>

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
}

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 5;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 48;
}

static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    return 34;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  #ifdef PBL_COLOR    
    graphics_context_set_fill_color(ctx, GColorPastelYellow);
    graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w, 48), 0, GCornerNone);
    
    graphics_context_set_fill_color(ctx, GColorDarkCandyAppleRed);
  #else
    graphics_context_set_fill_color(ctx, GColorBlack);
  #endif  
  
  #ifdef PBL_ROUND
    graphics_fill_rect(ctx, GRect(20, 6, bounds.size.w-40, 37), 20, GCornersAll);
  #else
    graphics_fill_rect(ctx, GRect(6, 6, bounds.size.w-12, 37), 20, GCornersAll);  
  #endif
  
  graphics_context_set_text_color(ctx, GColorWhite);
  graphics_draw_text(ctx, "Drag Racing", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(5, 5, bounds.size.w-10, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {  
  /*#ifdef PBL_COLOR    
    graphics_context_set_fill_color(ctx, GColorPastelYellow);
    graphics_fill_rect(ctx, GRect(0, 0, 144, 54), 0, GCornerNone);
  #endif*/
    
  #ifdef PBL_SDK_2
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
  
  GRect row_rect = GRect(5, -2, bounds.size.w-10, 34);
  
  switch (cell_index->row) {
    case 0:
      graphics_draw_text(ctx, "Race", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
    case 1:
      graphics_draw_text(ctx, "Garage", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
    case 2:
      graphics_draw_text(ctx, "High score", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
    case 3:
      graphics_draw_text(ctx, "How to play", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
    case 4:
      graphics_draw_text(ctx, "Settings", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {  
  switch (cell_index->row) {
    case 0:      
      if (get_car_type()==CAR_TYPE_NONE)
        show_car_selection();
      else
        show_race_selection();
      break;
    case 1:
      if (get_car_type()==CAR_TYPE_NONE)
        show_car_selection();
      else
        show_garage();
      break;
    case 2:
        show_hiscore();
      break;
    case 3:
        show_help();
      break;
    case 4:
        show_settings();
      break;
  }
}

void show_main_menu(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
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

void hide_main_menu(void) {
  window_stack_remove(s_window, true);
}