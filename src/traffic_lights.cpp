/**********************************************
 * Univeristy of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME: traffic_lights.cpp
 * PROJECT: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log:
 **********************************************
 * Date of Change
 * 240219 - DDMMYY
 * ----------------
 * 130424 Module created
 *
 ***********************************************/

/***************** Include files **************/

#include "traffic_lights.h"
#include <Arduino.h>

/***************** Defines ********************/

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void TrafficLights::init(int id, String mode, String placement, String area,
                         int queue) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  traffic_light_id = id;
  state            = mode;
  direction        = placement;
  location         = area;
  queue_size       = queue;
}

int    TrafficLights::return_id() { return traffic_light_id; }

String TrafficLights::return_state() { return state; }

String TrafficLights::return_direction() { return direction; }

String TrafficLights::return_location() { return location; }

int    TrafficLights::return_queue_size() { return queue_size; }

/***************** End of module **************/
