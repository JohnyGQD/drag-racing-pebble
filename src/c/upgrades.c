#include "upgrades.h"
#include "main.h"
#include <pebble.h>

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
  return 4;
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return 46;
}

static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    return 44;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  #ifdef PBL_COLOR
    graphics_context_set_fill_color(ctx, GColorBulgarianRose);
    graphics_context_set_text_color(ctx, GColorWhite);
  #else
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
    
  graphics_fill_rect(ctx, GRect(0, 0, bounds.size.w, 46), 0, GCornerNone);
  
  char *budget_value = "xxxxxxxxxxxxxxxxxxxx";
  snprintf(budget_value, 32, "%ld", (long)get_budget());
  
  graphics_draw_text(ctx, "Budget:", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(0, -1, bounds.size.w, 18), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, budget_value, fonts_get_system_font(FONT_KEY_GOTHIC_28), GRect(0, 14, bounds.size.w, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  /*#ifdef PBL_COLOR    
    graphics_context_set_fill_color(ctx, GColorPastelYellow);
    graphics_fill_rect(ctx, GRect(0, 0, 144, 44), 0, GCornerNone);
  #endif*/

  #ifdef PBL_SDK_2
    graphics_context_set_text_color(ctx, GColorBlack);
  #endif
  
  GRect row_title_rect = GRect(5, -6, bounds.size.w-10, 28);
  GRect row_subtitle_rect = GRect(5, 21, bounds.size.w-10, 18);
  
  char cost_string[128];
  
  switch (cell_index->row) {
    case 0:
      graphics_draw_text(ctx, "Engine +1", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);    
      snprintf(cost_string, sizeof(cost_string), "Cost: %ld", (long)get_car_speed()*PRICE_COEFFICIENT);
      break;
    case 1:
      graphics_draw_text(ctx, "Gearbox +1", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      snprintf(cost_string, sizeof(cost_string), "Cost: %ld", (long)get_car_acceleration()*PRICE_COEFFICIENT);
      break;
    case 2:
      graphics_draw_text(ctx, "Tires +1", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      snprintf(cost_string, sizeof(cost_string), "Cost: %ld", (long)get_car_grip()*PRICE_COEFFICIENT);
      break;
    case 3:
      graphics_draw_text(ctx, "Nitro +1", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), row_title_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
      snprintf(cost_string, sizeof(cost_string), "Cost: %ld", (long)get_car_nitro()*PRICE_COEFFICIENT);
      break;
  }
  
  graphics_draw_text(ctx, cost_string, fonts_get_system_font(FONT_KEY_GOTHIC_18), row_subtitle_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {  
  int32_t budget = get_budget();
  long upgrade_price = 0;
  
  switch (cell_index->row) {
    case 0:
      upgrade_price = get_car_speed()*PRICE_COEFFICIENT;
      if (upgrade_price<=budget) {
        set_budget(budget-upgrade_price);
        set_car_speed(get_car_speed()+1);
        hide_upgrades();
      }      
      break;
    case 1:
      upgrade_price = get_car_acceleration()*PRICE_COEFFICIENT;
      if (upgrade_price<=budget) {
        set_budget(budget-upgrade_price);
        set_car_acceleration(get_car_acceleration()+1);
        hide_upgrades();
      }  
      break;
    case 2:
      upgrade_price = get_car_grip()*PRICE_COEFFICIENT;
      if (upgrade_price<=budget) {
        set_budget(budget-upgrade_price);
        set_car_grip(get_car_grip()+1);
        hide_upgrades();
      }
      break;
    case 3:
      upgrade_price = get_car_nitro()*PRICE_COEFFICIENT;
      if (upgrade_price<=budget) {
        set_budget(budget-upgrade_price);
        set_car_nitro(get_car_nitro()+1);
        hide_upgrades();
      }
      break;
  }
}

void show_upgrades(void) {
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

void hide_upgrades(void) {
  window_stack_remove(s_window, true);
}
