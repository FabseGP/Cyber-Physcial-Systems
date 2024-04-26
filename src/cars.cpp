/*****************************************************************************
 * Univeristy of Southern Denmark
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

/*****************************   Functions   *******************************/

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

uint8_t Cars::return_id() { return car_id; }

uint8_t Cars::return_velocity() { return velocity; }

uint8_t Cars::return_date() { return date_id; }

uint8_t Cars::return_type() { return car_type_id; }

uint8_t Cars::return_traffic_id() { return traffic_light_id; }

/****************************** End Of Module *******************************/
