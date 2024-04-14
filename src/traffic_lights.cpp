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

/***************** End of module **************/
