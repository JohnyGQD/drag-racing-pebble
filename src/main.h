#include <pebble.h>

static const uint8_t SETTING_ID_CAR_TYPE = 10;
static const uint8_t SETTING_ID_CAR_SPEED = 11;
static const uint8_t SETTING_ID_CAR_ACCELERATION = 12;
static const uint8_t SETTING_ID_CAR_GRIP = 13;
static const uint8_t SETTING_ID_CAR_NITRO = 14;

static const uint8_t SETTING_ID_DIFFICULTY = 20;

static const uint8_t SETTING_ID_BEST_TIME_DURATION = 30;
static const uint8_t SETTING_ID_BEST_TIME_SCORE = 31;

static const uint8_t SETTING_ID_BUDGET = 40;

static const int DIFFICULTY_COEFFICIENT_EASY = 9;
static const int DIFFICULTY_COEFFICIENT_MEDIUM = 11;
static const int DIFFICULTY_COEFFICIENT_HARD = 14;

static const int REWARD_COEFFICIENT_EASY = 8;
static const int REWARD_COEFFICIENT_MEDIUM = 11;
static const int REWARD_COEFFICIENT_HARD = 17;

static const int PRICE_COEFFICIENT = 500;

static const long RACE_LENGTH = 165000;

enum {
	CAR_TYPE_NONE = 0,
	CAR_TYPE_MUSCLE = 1,
	CAR_TYPE_RACING = 2
};

enum {
	DIFFICULTY_EASY = 0,
	DIFFICULTY_MEDIUM = 1,
	DIFFICULTY_HARD = 2
};
  
long race_reward;
long race_duration;
bool race_win;

int get_car_type(void);
int32_t get_car_speed(void);
int32_t get_car_acceleration(void);
int32_t get_car_grip(void);
int32_t get_car_nitro(void);
int32_t get_car_score(void);
int32_t get_difficulty(void);
int32_t get_best_time_duration(void);
int32_t get_best_time_score(void);
int32_t get_budget(void);

void set_car_type(int value);
void set_car_speed(int32_t value);
void set_car_acceleration(int32_t value);
void set_car_grip(int32_t value);
void set_car_nitro(int32_t value);
void set_difficulty(int32_t value);
void set_best_time_duration(int32_t value);
void set_best_time_score(int32_t value);
void set_budget(int32_t value);