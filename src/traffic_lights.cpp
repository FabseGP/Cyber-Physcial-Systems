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

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

uint8_t TrafficLights::object_count = 0;

/*****************************    Objects    *******************************/

TrafficLights traffic_light0, traffic_light1, traffic_light2;

/*****************************   Functions   *******************************/

TrafficLights::TrafficLights() { ++object_count; }

void TrafficLights::init(uint8_t id, String mode, String placement, String area,
                         uint8_t queue, gpio_num_t red_pin,
                         gpio_num_t yellow_pin, gpio_num_t green_pin) {
  traffic_light_id = id;
  state            = mode;
  direction        = placement;
  location         = area;
  queue_size       = queue;
  red_led          = red_pin;
  yellow_led       = yellow_pin;
  green_led        = green_pin;
}

uint8_t TrafficLights::get_id() { return traffic_light_id; }

String  TrafficLights::get_state() { return state; }

String  TrafficLights::get_direction() { return direction; }

String  TrafficLights::get_location() { return location; }

uint8_t TrafficLights::get_queue_size() { return queue_size; }

void    TrafficLights::update_timer(uint8_t subtract) {
  if (timer < subtract) {
    if (timer >= 1) {
      --timer;
    } else {
      timer = 0;
    }
  } else {
    timer -= subtract;
  }
}

uint8_t TrafficLights::get_timer() { return timer; }

void    TrafficLights::set_timer(uint8_t seconds) { timer = seconds; }

void    TrafficLights::mode_cycling() {}

uint8_t TrafficLights::get_count() { return object_count; }

String  TrafficLights::get_url() {
  return String("http://192.168.0.200:3000/trafficlights/insert") +
         "?traffic_light_id=" + traffic_light_id +
         "&state=" + urlEncode(state) + "&direction=" + urlEncode(direction) +
         "&location=" + urlEncode(location) + "&queue_size=" + queue_size;
  ;
}

void TrafficLights::set_red() {
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
}
void TrafficLights::set_yellow() {
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, HIGH);
  digitalWrite(green_led, LOW);
}
void TrafficLights::set_green() {
  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, HIGH);
}
void TrafficLights::set_red_yellow() {
  digitalWrite(red_led, HIGH);
  digitalWrite(yellow_led, HIGH);
  digitalWrite(green_led, LOW);
}

void setup_traffic_lights() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  traffic_light0.init(TRAFFIC_LIGHT_E, "Green", "East",
                      "Faaborgvej 23, 5610 Assens", EMPTY_QUEUE, RED_WE,
                      YELLOW_WE, GREEN_WE);
  traffic_light1.init(TRAFFIC_LIGHT_W, "Green", "West",
                      "Faaborgvej 24, 5610 Assens", EMPTY_QUEUE, RED_WE,
                      YELLOW_WE, GREEN_WE);
  traffic_light2.init(TRAFFIC_LIGHT_N, "Green", "North",
                      "Faaborgvej 25, 5610 Assens", EMPTY_QUEUE, RED_NS,
                      YELLOW_NS, GREEN_NS);
}

/****************************** End Of Module *******************************/
