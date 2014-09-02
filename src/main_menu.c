#include "main_menu.h"
#include <pebble.h>
#include <main.h>
#include <race_selection.h>
#include <car_selection.h>
#include <garage.h>
#include <hiscore.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *menu;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // menu
  menu = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(menu, s_window);
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
  return 3;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 48;
}

static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    return 34;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(6, 6, 132, 37), 20, GCornersAll);
  
  graphics_context_set_text_color(ctx, GColorWhite);
  graphics_draw_text(ctx, "Drag Racing", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(5, 5, 134, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  graphics_context_set_text_color(ctx, GColorBlack);
  
  GRect row_rect = GRect(5, -2, 134, 34);
  
  switch (cell_index->row) {
    case 0:
      graphics_draw_text(ctx, "Race", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      break;
    case 1:
      graphics_draw_text(ctx, "Garage", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
      break;
    case 2:
      graphics_draw_text(ctx, "High score", fonts_get_system_font(FONT_KEY_GOTHIC_28), row_rect, GTextOverflowModeFill, GTextAlignmentLeft, NULL);
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