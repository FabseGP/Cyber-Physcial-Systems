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
#include <Arduino.h>
#include <UrlEncode.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

uint8_t       TrafficLights::object_count = 0;

TrafficLights traffic_light0, traffic_light1, traffic_light2, traffic_light3;

/*****************************   Functions   *******************************/

TrafficLights::TrafficLights() { ++object_count; }

void TrafficLights::init(uint8_t id, String mode, String placement, String area,
                         uint8_t queue) {
  traffic_light_id = id;
  state            = mode;
  direction        = placement;
  location         = area;
  queue_size       = queue;
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

String  TrafficLights::get_parameters() {
  return String("?traffic_light_id=") + traffic_light_id +
         "&state=" + urlEncode(state) + "&direction=" + urlEncode(direction) +
         "&location=" + urlEncode(location) + "&queue_size=" + queue_size;
  ;
}

void setup_traffic_lights() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  traffic_light0.init(0, "Green", "South", "Faaborgvej 23, 5610 Assens", 20);
  traffic_light1.init(1, "Green", "South", "Faaborgvej 24, 5610 Assens", 20);
  traffic_light2.init(2, "Green", "South", "Faaborgvej 23, 5610 Assens", 20);
  traffic_light3.init(3, "Green", "South", "Faaborgvej 23, 5610 Assens", 20);
}

/****************************** End Of Module *******************************/
