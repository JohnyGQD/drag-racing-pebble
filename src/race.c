#include "race.h"
#include <pebble.h>
#include <main.h>
#include <race_result.h>
  
static const int UPDATE_INTERVAL = 10;
static const int RENDERING_INTERVAL = 33;
  
static Layer *rpm_layer;
static Layer *player_layer;
static Layer *opponent_layer;
static Layer *buildings_layer;
static Layer *gear_layer;
static Layer *duration_layer;
static Layer *info_layer;
static Layer *progress_layer;
  
static AppTimer *update_loop;
static AppTimer *rendering_loop;
static long update_counter;

static bool started;
static bool rpm_back;
static long start_loop;

static int player_gear;
static int player_rpm;
static long player_wheelspin;
static long player_speed;
static long player_distance;
static int player_remaining_nitro;
static bool player_nitro_used;

static int32_t player_car_speed;
static int32_t player_car_acceleration;
static int32_t player_car_grip;
static int32_t player_car_nitro;

static int opponent_gear;
static int opponent_rpm;
static long opponent_wheelspin;
static long opponent_speed;
static long opponent_distance;
static int opponent_remaining_nitro;
static bool opponent_nitro_used;

static int32_t opponent_car_speed;
static int32_t opponent_car_acceleration;
static int32_t opponent_car_grip;
static int32_t opponent_car_nitro;

static int current_difficulty;
static int current_difficulty_coefficient;

static int progress_width;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_racing;
static GBitmap *s_res_muscle;
static GBitmap *s_res_buildings;
static GBitmap *s_res_up;
static GBitmap *s_res_nitro;
static GBitmap *s_res_right;
static GBitmap *s_res_down;
static GBitmap *s_res_mark;
static TextLayer *info;
static TextLayer *gear;
static BitmapLayer *lane_bottom;
static BitmapLayer *progress;
static BitmapLayer *lane_top;
static BitmapLayer *opponent;
static BitmapLayer *player;
static BitmapLayer *buildings;
static BitmapLayer *buttons_background;
static BitmapLayer *up;
static BitmapLayer *nitro;
static BitmapLayer *start;
static BitmapLayer *down;
static BitmapLayer *mark;
static BitmapLayer *rpm_background;
static BitmapLayer *rpm;
static TextLayer *duration;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_racing = gbitmap_create_with_resource(RESOURCE_ID_RACING);
  s_res_muscle = gbitmap_create_with_resource(RESOURCE_ID_MUSCLE);
  s_res_buildings = gbitmap_create_with_resource(RESOURCE_ID_BUILDINGS);
  s_res_up = gbitmap_create_with_resource(RESOURCE_ID_UP);
  s_res_nitro = gbitmap_create_with_resource(RESOURCE_ID_NITRO);
  s_res_right = gbitmap_create_with_resource(RESOURCE_ID_right);
  s_res_down = gbitmap_create_with_resource(RESOURCE_ID_DOWN);
  s_res_mark = gbitmap_create_with_resource(RESOURCE_ID_MARK);
  // info
  info = text_layer_create(GRect(21, 123, 102, 17));
  text_layer_set_text(info, " ");
  text_layer_set_text_alignment(info, GTextAlignmentCenter);
  text_layer_set_font(info, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)info);
  
  // gear
  gear = text_layer_create(GRect(-3, 120, 28, 28));
  text_layer_set_text(gear, "N");
  text_layer_set_text_alignment(gear, GTextAlignmentCenter);
  text_layer_set_font(gear, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)gear);
  
  // lane_bottom
  lane_bottom = bitmap_layer_create(GRect(0, 124, 144, 2));
  bitmap_layer_set_background_color(lane_bottom, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)lane_bottom);
  
  // progress
  progress = bitmap_layer_create(GRect(0, 83, 128, 2));
  bitmap_layer_set_background_color(progress, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)progress);
  
  // lane_top
  lane_top = bitmap_layer_create(GRect(0, 42, 144, 2));
  bitmap_layer_set_background_color(lane_top, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)lane_top);
  
  // opponent
  opponent = bitmap_layer_create(GRect(14, 52, 100, 30));
  bitmap_layer_set_bitmap(opponent, s_res_racing);
  bitmap_layer_set_background_color(opponent, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)opponent);
  
  // player
  player = bitmap_layer_create(GRect(14, 93, 100, 30));
  bitmap_layer_set_bitmap(player, s_res_muscle);
  bitmap_layer_set_background_color(player, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)player);
  
  // buildings
  buildings = bitmap_layer_create(GRect(90, 14, 34, 28));
  bitmap_layer_set_bitmap(buildings, s_res_buildings);
  bitmap_layer_set_background_color(buildings, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)buildings);
  
  // buttons_background
  buttons_background = bitmap_layer_create(GRect(128, 0, 18, 152));
  bitmap_layer_set_background_color(buttons_background, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)buttons_background);
  
  // up
  up = bitmap_layer_create(GRect(130, 137, 11, 11));
  bitmap_layer_set_bitmap(up, s_res_up);
  bitmap_layer_set_background_color(up, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)up);
  
  // nitro
  nitro = bitmap_layer_create(GRect(130, 70, 11, 11));
  bitmap_layer_set_bitmap(nitro, s_res_nitro);
  bitmap_layer_set_background_color(nitro, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)nitro);
  
  // start
  start = bitmap_layer_create(GRect(130, 70, 11, 11));
  bitmap_layer_set_bitmap(start, s_res_right);
  bitmap_layer_set_background_color(start, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)start);
  
  // down
  down = bitmap_layer_create(GRect(130, 4, 11, 11));
  bitmap_layer_set_bitmap(down, s_res_down);
  bitmap_layer_set_background_color(down, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)down);
  
  // mark
  mark = bitmap_layer_create(GRect(93, 130, 11, 6));
  bitmap_layer_set_bitmap(mark, s_res_mark);
  bitmap_layer_set_background_color(mark, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)mark);
  
  // rpm_background
  rpm_background = bitmap_layer_create(GRect(22, 139, 102, 10));
  bitmap_layer_set_background_color(rpm_background, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)rpm_background);
  
  // rpm
  rpm = bitmap_layer_create(GRect(23, 140, 100, 8));
  bitmap_layer_set_background_color(rpm, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)rpm);
  
  // duration
  duration = text_layer_create(GRect(2, -1, 60, 14));
  text_layer_set_text(duration, "0.0 s");
  text_layer_set_font(duration, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)duration);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(info);
  text_layer_destroy(gear);
  bitmap_layer_destroy(lane_bottom);
  bitmap_layer_destroy(progress);
  bitmap_layer_destroy(lane_top);
  bitmap_layer_destroy(opponent);
  bitmap_layer_destroy(player);
  bitmap_layer_destroy(buildings);
  bitmap_layer_destroy(buttons_background);
  bitmap_layer_destroy(up);
  bitmap_layer_destroy(nitro);
  bitmap_layer_destroy(start);
  bitmap_layer_destroy(down);
  bitmap_layer_destroy(mark);
  bitmap_layer_destroy(rpm_background);
  bitmap_layer_destroy(rpm);
  text_layer_destroy(duration);
  gbitmap_destroy(s_res_racing);
  gbitmap_destroy(s_res_muscle);
  gbitmap_destroy(s_res_buildings);
  gbitmap_destroy(s_res_up);
  gbitmap_destroy(s_res_nitro);
  gbitmap_destroy(s_res_right);
  gbitmap_destroy(s_res_down);
  gbitmap_destroy(s_res_mark);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  app_timer_cancel(rendering_loop);
  app_timer_cancel(update_loop);  
  
  light_enable(false);
  
  destroy_ui();
}

static long get_target_speed(int32_t car_speed, long wheelspin, long rpm, int gear) {
  long coefficient = 0;
  
  switch (gear) {
    case 1:
      coefficient = ((rpm*30)/100);
      break;
    case 2:
      coefficient = ((rpm*35)/100)+5;
      break;
    case 3:
      coefficient = ((rpm*45)/100)+10;
      break;
    case 4:
      coefficient = ((rpm*60)/100)+15;
      break;
    case 5:
      coefficient = ((rpm*80)/100)+20;
      break;
  }
  
  coefficient -= wheelspin/200;
  
  return car_speed*coefficient/1000;
}

static void set_player_gear(int new_gear) {
  int old_gear = player_gear;
  player_gear = new_gear;
  
  char *gear_text = "x";
  snprintf(gear_text, sizeof(gear_text), "%d", player_gear);
  text_layer_set_text(gear, gear_text);
  layer_mark_dirty(gear_layer);
  
  if (!started) {
    start_loop = update_counter;
    started = true;
  } else {    
    if (player_wheelspin>0) {
      player_wheelspin = player_wheelspin * 15 / 10;
    }
    
    if (old_gear<player_gear && old_gear>0) player_rpm = player_rpm/2;
    else if (old_gear>player_gear) player_rpm = player_rpm*2;    
    
    layer_set_hidden(bitmap_layer_get_layer(up), player_gear>=5);
    layer_set_hidden(bitmap_layer_get_layer(down), player_gear<=1);
  }
}

static void set_opponent_gear(int new_gear) {
  int old_gear = opponent_gear;
  opponent_gear = new_gear;
  
  if (started) {
    if (opponent_wheelspin>0) {
      opponent_wheelspin = opponent_wheelspin * 15 / 10;
    }
    
    if (old_gear<opponent_gear && old_gear>0) opponent_rpm = opponent_rpm/2;
    else if (old_gear>opponent_gear) opponent_rpm = opponent_rpm*2;    
  }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (!started) {
    layer_set_hidden(bitmap_layer_get_layer(start), true);
    layer_set_hidden(bitmap_layer_get_layer(mark), true);
    layer_set_hidden(bitmap_layer_get_layer(up), false);
    
    int player_coefficient = (player_rpm - 7500)/100;
    if (player_coefficient < 0) player_coefficient = -player_coefficient;
    if (player_coefficient <= 10) player_coefficient = 10;    
    player_wheelspin = player_rpm * player_coefficient;
    
    switch (current_difficulty) {
      case DIFFICULTY_EASY:
        opponent_rpm = 7900;
        break;
      case DIFFICULTY_MEDIUM:
      default:
        opponent_rpm = 8700;
        break;
      case DIFFICULTY_HARD:
        opponent_rpm = 9500;
        break;
    }
    
    int opponent_coefficient = (opponent_rpm - 7500)/100;
    if (opponent_coefficient < 0) opponent_coefficient = -opponent_coefficient;
    if (opponent_coefficient <= 10) opponent_coefficient = 10;    
    opponent_wheelspin = opponent_rpm * opponent_coefficient;
    
    set_player_gear(1);
    set_opponent_gear(1);
  } else if (!player_nitro_used) {
    layer_set_hidden(bitmap_layer_get_layer(nitro), true);
    player_nitro_used = true;
  }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (started && player_gear>1) {
    set_player_gear(player_gear-1);
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (started && player_gear<5) {
    set_player_gear(player_gear+1);
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static long get_race_duration() {
  return (update_counter - start_loop) * 165 / 100;
}

static void update() {  
  if (!started) {
    if (player_rpm<=0) {
      rpm_back = false;
    } else if (player_rpm>=10000) {
      rpm_back = true;
    }
    
    if (rpm_back) {
      player_rpm-=300;
    } else {
      player_rpm+=300;
    }
  } else {   
    // Player RPM
    if (player_wheelspin>0) {
      player_wheelspin = player_wheelspin-(player_car_grip*50);
      if (player_wheelspin<0) player_wheelspin = 0;
      player_rpm -= 50;
    } else {
      long player_rpm_increase = (player_rpm*(player_car_acceleration+(player_car_grip/10)))/3500;      
      player_rpm += player_rpm_increase;      
      if (player_nitro_used && player_remaining_nitro>0) player_rpm += player_rpm_increase / 2;
    }
      
    if (player_rpm<=200) player_rpm=200;
    if (player_rpm>10000) player_rpm = 10000;
    
    // Computer RPM
    if (opponent_wheelspin>0) {
      opponent_wheelspin = opponent_wheelspin-(opponent_car_grip*50);
      if (opponent_wheelspin<0) opponent_wheelspin = 0;
      opponent_rpm -= 50;
    } else {
      long opponent_rpm_increase = (opponent_rpm*(opponent_car_acceleration+(opponent_car_grip/10)))/3500;      
      opponent_rpm += opponent_rpm_increase;      
      if (opponent_nitro_used && opponent_remaining_nitro>0) opponent_rpm += opponent_rpm_increase / 2;
    }
      
    if (opponent_rpm<=200) opponent_rpm=200;
    if (opponent_rpm>10000) opponent_rpm = 10000;
    
    // Player speed
    long player_target_speed = get_target_speed(player_car_speed, player_wheelspin, player_rpm, player_gear);
    if (player_target_speed<0) player_target_speed = 0;
    
    if (player_nitro_used && player_remaining_nitro>0) player_target_speed += player_target_speed / 2;
        
    if (player_speed<player_target_speed) {
      player_speed = player_speed + (player_car_acceleration/10);
    } else if (player_speed-player_target_speed>10) {
      player_speed = player_speed - 10;
    }
    
    // Computer speed
    long opponent_target_speed = get_target_speed(opponent_car_speed, opponent_wheelspin, opponent_rpm, opponent_gear);
    if (opponent_target_speed<0) opponent_target_speed = 0;
    
    if (opponent_nitro_used && opponent_remaining_nitro>0) opponent_target_speed += opponent_target_speed / 2;
        
    if (opponent_speed<opponent_target_speed) {
      opponent_speed = opponent_speed + (opponent_car_acceleration/10);
    } else if (opponent_speed-opponent_target_speed>10) {
      opponent_speed = opponent_speed - 10;
    }
    
    // Computer gearing
    switch (current_difficulty) {
      case DIFFICULTY_EASY:
        if (opponent_rpm>=8500) {
          if (opponent_gear<5) set_opponent_gear(opponent_gear + 1);
          else if (!opponent_nitro_used) opponent_nitro_used = true;
        } 
        break;
      case DIFFICULTY_MEDIUM:
      default:
        if (opponent_rpm>=9000) {
          if (opponent_gear<5) set_opponent_gear(opponent_gear + 1);
          else if (!opponent_nitro_used) opponent_nitro_used = true;
        }
        break;
      case DIFFICULTY_HARD:
        if (opponent_rpm>=9500) {
          if (opponent_gear<5) set_opponent_gear(opponent_gear + 1);
          else if (!opponent_nitro_used) opponent_nitro_used = true;
        }
        break;
    }
    
    // Other calculations
    if (player_nitro_used && player_remaining_nitro>0) player_remaining_nitro -= 1;
    if (opponent_nitro_used && opponent_remaining_nitro>0) opponent_remaining_nitro -= 1;
    
    player_distance += player_speed;
    opponent_distance += opponent_speed;
    
    progress_width = player_distance * 128 / RACE_LENGTH;
    if (progress_width > 128) progress_width = 128;
  }
  
  update_counter++;
    
  int progress_percentage = player_distance * 100 / RACE_LENGTH;
  if (progress_percentage<100) {
    update_loop = app_timer_register(UPDATE_INTERVAL, update, NULL);
  } else {
    // Race finished
    if (opponent_distance>player_distance) {
      race_reward = get_car_score();      
      race_win = false;
    } else {
      switch (current_difficulty) {
        case DIFFICULTY_EASY:
          race_reward = get_car_score() * REWARD_COEFFICIENT_EASY;
          break;
        case DIFFICULTY_MEDIUM:
        default:
          race_reward = get_car_score() * REWARD_COEFFICIENT_MEDIUM;
          break;
        case DIFFICULTY_HARD:
          race_reward = get_car_score() * REWARD_COEFFICIENT_HARD;
          break;
      }
      
      race_win = true;
    }
    
    set_budget(get_budget() + race_reward);
    race_duration = get_race_duration();
    
    hide_race();
    show_race_result();
  }
}

static void render() {  
  layer_set_frame(rpm_layer, GRect(23, 140, player_rpm/100, 8));
  layer_mark_dirty(rpm_layer);
  
  layer_set_frame(progress_layer, GRect(0, 83, progress_width, 2));
  layer_mark_dirty(progress_layer);
  
  if (started) {
    long distance_difference = (player_distance - opponent_distance) / 500;
    //distance_difference = 10;
    
    int player_x = distance_difference + 14;
    if (player_x>28) player_x = 28;
    if (player_x<0) player_x = 0;
    
    int opponent_x = player_x - distance_difference;    
    if (opponent_x>128) opponent_x = 128;
    if (opponent_x<-100) opponent_x = -100;
    
    int buildings_x = 128 - (((player_distance+380)/10) % 162);
    
    layer_set_frame(player_layer, GRect(player_x, 93, 100, 30));
    layer_mark_dirty(player_layer);
    
    layer_set_frame(opponent_layer, GRect(opponent_x, 52, 100, 30));
    layer_mark_dirty(opponent_layer);
    
    layer_set_frame(buildings_layer, GRect(buildings_x, 14, 34, 28));
    layer_mark_dirty(buildings_layer);
    
    char *duration_text = "xxxxxxxxxx";
    long race_duration = get_race_duration();
    int seconds = race_duration/100;
    int decimals = race_duration%100;
    
    snprintf(duration_text, 10, "%d.%02d s", seconds, decimals);
    text_layer_set_text(duration, duration_text);
    layer_mark_dirty(duration_layer);
    
    char *info_text = "xxxxxxxxxxxxxxxx"; 
    if (player_wheelspin>0) {
      snprintf(info_text, 16, "Wheel spin!");
    } else if (player_nitro_used && player_remaining_nitro>0) {
      snprintf(info_text, 16, "Burning nitro");
    } else if (player_rpm >= 10000 && player_gear<5) {
      snprintf(info_text, 16, "Gear up!");
    } else if (player_rpm >= 10000 && player_gear>=5 && !player_nitro_used) {
      snprintf(info_text, 16, "Use the nitro!");
    } else {
      snprintf(info_text, 16, " ");
    }
    
    //snprintf(info_text, 16, "%ld:%ld", player_distance, opponent_distance);
    
    text_layer_set_text(info, info_text);
    layer_mark_dirty(info_layer);
  }
  
  rendering_loop = app_timer_register(RENDERING_INTERVAL, render, NULL);
}

void show_race(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  window_set_click_config_provider(s_window, click_config_provider);
  
  light_enable(true);
  
  rpm_layer = bitmap_layer_get_layer(rpm);
  player_layer = bitmap_layer_get_layer(player);
  opponent_layer = bitmap_layer_get_layer(opponent);
  buildings_layer = bitmap_layer_get_layer(buildings);
  gear_layer = text_layer_get_layer(gear);
  duration_layer = text_layer_get_layer(duration);
  info_layer = text_layer_get_layer(info);  
  progress_layer = bitmap_layer_get_layer(progress);  
  
  layer_set_hidden(bitmap_layer_get_layer(up), true);
  layer_set_hidden(bitmap_layer_get_layer(down), true);
  
  started = false;
  rpm_back = false;
  start_loop = 0;
  
  if (get_car_type() == CAR_TYPE_RACING) {
    bitmap_layer_set_bitmap(player, s_res_racing);
  } else {
    bitmap_layer_set_bitmap(player, s_res_muscle);
  }
  
  player_car_speed = get_car_speed();
  player_car_acceleration = get_car_acceleration();
  player_car_grip = get_car_grip();
  player_car_nitro = get_car_nitro();
  
  player_gear = 0;
  player_rpm = 0;  
  player_speed = 0; 
  player_wheelspin = 0;  
  player_distance = 0;
  player_nitro_used = false;
  player_remaining_nitro = player_car_nitro * 2;
  
  current_difficulty = get_difficulty();
  
  switch (current_difficulty) {
    case DIFFICULTY_EASY:
      current_difficulty_coefficient = DIFFICULTY_COEFFICIENT_EASY;
      break;
    case DIFFICULTY_MEDIUM:
    default:
      current_difficulty_coefficient = DIFFICULTY_COEFFICIENT_MEDIUM;
      break;
    case DIFFICULTY_HARD:
      current_difficulty_coefficient = DIFFICULTY_COEFFICIENT_HARD;
      break;
  }
  
  opponent_car_speed = 20;
  opponent_car_acceleration = 20;
  opponent_car_grip = 20;
  opponent_car_nitro = 20;
  
  int third_to_distribute = ((get_car_score() * current_difficulty_coefficient / 10) - 80)/3;
  
  if (third_to_distribute>0) {
    srand(time(NULL));
    
    int speed_increment = rand() % (third_to_distribute*2);
    opponent_car_speed += speed_increment;
    opponent_car_acceleration += (third_to_distribute*2) - speed_increment;
    
    int grip_increment = rand() % third_to_distribute;
    opponent_car_grip += grip_increment;
    opponent_car_nitro += third_to_distribute - grip_increment;
  }
  
  /*APP_LOG(APP_LOG_LEVEL_DEBUG, "opponent_car_speed %ld", (long)opponent_car_speed);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "opponent_car_acceleration %ld", (long)opponent_car_acceleration);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "opponent_car_grip %ld", (long)opponent_car_grip);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "opponent_car_nitro %ld", (long)opponent_car_nitro);*/
  
  if ((opponent_car_speed+opponent_car_nitro)>(opponent_car_acceleration+opponent_car_grip)) {
    bitmap_layer_set_bitmap(opponent, s_res_racing);
  } else {
    bitmap_layer_set_bitmap(opponent, s_res_muscle);
  }
  
  opponent_gear = 0;
  opponent_rpm = 0;  
  opponent_speed = 0; 
  opponent_wheelspin = 0;  
  opponent_distance = 0;
  opponent_nitro_used = false;
  opponent_remaining_nitro = opponent_car_nitro * 2;
    
  progress_width = 0;
  
  update_counter = 0; 
  update_loop = app_timer_register(UPDATE_INTERVAL, update, NULL);
  rendering_loop = app_timer_register(RENDERING_INTERVAL, render, NULL);
}

void hide_race(void) {  
  window_stack_remove(s_window, true);
}