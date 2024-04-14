/**********************************************
 * Univeristy of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME: cars.cpp
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

#include "cars.h"

/***************** Defines ********************/

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void Cars::init(int id, int speed, int date, int type, int traffic_light) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  car_id           = id;
  velocity         = speed;
  date_id          = date;
  car_type_id      = type;
  traffic_light_id = traffic_light;
}

int Cars::return_id() { return car_id; }

int Cars::return_velocity() { return velocity; }

int Cars::return_date() { return date_id; }

int Cars::return_type() { return car_type_id; }

int Cars::return_traffic_id() { return traffic_light_id; }

/***************** End of module **************/
