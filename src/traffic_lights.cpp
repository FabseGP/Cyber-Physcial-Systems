/**********************************************
 * Univeristy of Southern Denmark
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

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void TrafficLights::init(uint8_t id, String mode, String placement, String area,
                         uint8_t queue) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  traffic_light_id = id;
  state            = mode;
  direction        = placement;
  location         = area;
  queue_size       = queue;
}

uint8_t TrafficLights::return_id() { return traffic_light_id; }

String  TrafficLights::return_state() { return state; }

String  TrafficLights::return_direction() { return direction; }

String  TrafficLights::return_location() { return location; }

uint8_t TrafficLights::return_queue_size() { return queue_size; }

/****************************** End Of Module *******************************/
