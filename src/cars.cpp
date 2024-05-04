/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: cars.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 130424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "cars.h"
#include "Arduino.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

uint8_t Cars::object_count = 0;

Cars    car0;

/*****************************   Functions   *******************************/

Cars::Cars() { ++object_count; }

void Cars::init(uint8_t id, uint8_t speed, uint8_t date, uint8_t type,
                uint8_t traffic_light) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  car_id           = id;
  velocity         = speed;
  date_id          = date;
  car_type_id      = type;
  traffic_light_id = traffic_light;
}

uint8_t Cars::get_id() { return car_id; }

uint8_t Cars::get_velocity() { return velocity; }

uint8_t Cars::get_date() { return date_id; }

uint8_t Cars::get_type() { return car_type_id; }

uint8_t Cars::get_traffic_id() { return traffic_light_id; }

String  Cars::get_parameters() {
  return String("?car_id=") + car_id + "&velocity=" + velocity +
         "&date_id=" + date_id + "&car_type_id=" + car_type_id +
         "&traffic_light_id=" + traffic_light_id;
}

void setup_cars() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  car0.init(20, 30, 2, 2, 2);
}

/****************************** End Of Module *******************************/
