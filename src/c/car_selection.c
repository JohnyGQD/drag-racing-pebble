#include "car_selection.h"
#include <pebble.h>
#include <main.h>
  
static GBitmap *s_res_racing;
static GBitmap *s_res_muscle;

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
  return 2;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 18;
}

static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    return 78;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorBulgarianRose);
    graphics_context_set_text_color(ctx, GColorWhite);
  #else
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
    
  graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w, 18), 0, GCornerNone);
    
  graphics_draw_text(ctx, "Choose starting car", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(0, -3, bounds.size.w, 18), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  /*#ifdef PBL_COLOR    
    graphics_context_set_fill_color(ctx, GColorPastelYellow);
    graphics_fill_rect(ctx, GRect(0, 0, 144, 78), 0, GCornerNone);
  #endif*/

  #ifdef PBL_SDK_2
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
  
  GRect row_title_rect = GRect(4, -6, bounds.size.w-8, 28);
  GRect row_image_rect = GRect((bounds.size.w-100)/2, 28, 100, 30);
  GRect row_subtitle_rect = GRect(4, 55, bounds.size.w-8, 18);
  
  switch (cell_index->row) {
    case 0:
      graphics_draw_text(ctx, "Muscle car", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);    
      graphics_draw_bitmap_in_rect(ctx, s_res_muscle, row_image_rect);
      graphics_draw_text(ctx, "+ acceleration & grip", fonts_get_system_font(FONT_KEY_GOTHIC_18), row_subtitle_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      break;
    case 1:
      graphics_draw_text(ctx, "Racing car", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      graphics_draw_bitmap_in_rect(ctx, s_res_racing, row_image_rect);  
      graphics_draw_text(ctx, "+ speed & nitro", fonts_get_system_font(FONT_KEY_GOTHIC_18), row_subtitle_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);    
      break;
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {  
  switch (cell_index->row) {
    case 0:
      set_car_type(CAR_TYPE_MUSCLE);
      set_car_speed(20);
      set_car_acceleration(30);
      set_car_grip(30);
      set_car_nitro(20);
      hide_car_selection();
      break;
    case 1:
      set_car_type(CAR_TYPE_RACING);
      set_car_speed(30);
      set_car_acceleration(20);
      set_car_grip(20);
      set_car_nitro(30);
      hide_car_selection();
      break;
  }
}

void show_car_selection(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  s_res_racing = gbitmap_create_with_resource(RESOURCE_ID_RACING/*_BW*/);
  s_res_muscle = gbitmap_create_with_resource(RESOURCE_ID_MUSCLE/*_BW*/);
  
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

void hide_car_selection(void) {
  gbitmap_destroy(s_res_racing);
  gbitmap_destroy(s_res_muscle);
  
  window_stack_remove(s_window, true);
}
