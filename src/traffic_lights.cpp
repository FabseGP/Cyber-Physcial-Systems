/**********************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: traffic_lights.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log.:
 **********************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 130424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "traffic_lights.h"
#include "global_def.h"
#include <Arduino.h>
#include <UrlEncode.h>

/*****************************    Defines    *******************************/

#define TRAFFIC_LIGHT_E 0
#define TRAFFIC_LIGHT_W 1
#define TRAFFIC_LIGHT_N 2

#define RED_NS          GPIO_NUM_6
#define YELLOW_NS       GPIO_NUM_5
#define GREEN_NS        GPIO_NUM_4

#define RED_WE          GPIO_NUM_3
#define YELLOW_WE       GPIO_NUM_2
#define GREEN_WE        GPIO_NUM_1

#define EMPTY_QUEUE     0
#define RESET           0
#define SECONDS_PER_CAR 1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

uint8_t TrafficLights::object_count = RESET;

/*****************************    Objects    *******************************/

TrafficLights traffic_light0, traffic_light1, traffic_light2;

/*****************************   Functions   *******************************/

TrafficLights::TrafficLights() { ++object_count; }

void TrafficLights::init(uint8_t id, String mode, String placement, String area,
                         uint8_t queue, uint8_t car_rate, gpio_num_t red_pin,
                         gpio_num_t yellow_pin, gpio_num_t green_pin) {
  traffic_light_id        = id;
  state                   = mode;
  direction               = placement;
  location                = area;
  queue_size              = queue;
  red_led                 = red_pin;
  yellow_led              = yellow_pin;
  green_led               = green_pin;
  rate                    = car_rate;
  timer                   = RESET;
  timer_increment_counter = RESET;
  duration                = rate;
}

uint8_t TrafficLights::get_id() { return traffic_light_id; }

uint8_t TrafficLights::get_queue_size() { return queue_size; }

uint8_t TrafficLights::get_timer() { return timer; }

uint8_t TrafficLights::get_count() { return object_count; }

String  TrafficLights::get_state() { return state; }

String  TrafficLights::get_url() {
  return String("/trafficlights/insert") +
         "?traffic_light_id=" + traffic_light_id +
         "&state=" + urlEncode(state) + "&direction=" + urlEncode(direction) +
         "&location=" + urlEncode(location) + "&queue_size=" + queue_size;
  ;
}

void TrafficLights::increment_timer(uint8_t addition) {
  if (timer_increment_counter <= 5) {
    timer += addition;
  }
  ++timer_increment_counter;
}

void TrafficLights::decrement_timer(uint8_t subtract) {
  if (timer <= subtract) {
    if (timer >= 1) {
      --timer;
    } else {
      timer = RESET;
    }
  } else {
    timer -= subtract;
  }
}

void TrafficLights::increment_queue() { ++queue_size; }

void TrafficLights::decrement_queue() {
  if (duration == 0) {
    if (queue_size >= 1) {
      --queue_size;
    } else {
      queue_size = RESET;
    }
    duration = rate;
  } else {
    --duration;
  }
}

void TrafficLights::set_timer(uint8_t seconds) {
  timer                   = seconds;
  timer_increment_counter = RESET;
}

void TrafficLights::set_red() {
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  state = "Red";
}
void TrafficLights::set_yellow() {
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, HIGH);
  digitalWrite(green_led, LOW);
  state = "Yellow";
}
void TrafficLights::set_green() {
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, HIGH);
  state = "Green";
}
void TrafficLights::set_red_yellow() {
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, HIGH);
  digitalWrite(green_led, LOW);
  state = "RedYellow";
}

void setup_traffic_lights() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  traffic_light0.init(TRAFFIC_LIGHT_E, "Red", "East", "Faaborgvej, 5610 Assens",
                      EMPTY_QUEUE, SECONDS_PER_CAR, RED_WE, YELLOW_WE,
                      GREEN_WE);
  traffic_light1.init(TRAFFIC_LIGHT_W, "Red", "West", "Faaborgvej, 5610 Assens",
                      EMPTY_QUEUE, SECONDS_PER_CAR, RED_WE, YELLOW_WE,
                      GREEN_WE);
  traffic_light2.init(TRAFFIC_LIGHT_N, "Red", "North", "Damgade, 5610 Assens",
                      EMPTY_QUEUE, SECONDS_PER_CAR, RED_NS, YELLOW_NS,
                      GREEN_NS);
}

/****************************** End Of Module *******************************/
