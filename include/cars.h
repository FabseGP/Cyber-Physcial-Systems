/*****************************************************************************
 * University of Southern Denmark
 * Project 4. semester
 *
 * MODULENAME.: cars.h
 *
 * PROJECT....: Cyber Physical Systems
 *
 * DESCRIPTION: Class for each car
 *
 * Change Log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 140424  MoH    Module created
 *
 *****************************************************************************/

#ifndef CARS_H
#define CARS_H

/***************************** Include files *******************************/

#include "Arduino.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

class Cars {
  private:
    uint8_t car_id, velocity, date_id, car_type_id, traffic_light_id;

  public:
    void    init(uint8_t id, uint8_t speed, uint8_t date, uint8_t type,
                 uint8_t traffic_light);
    uint8_t return_id();
    uint8_t return_velocity();
    uint8_t return_date();
    uint8_t return_type();
    uint8_t return_traffic_id();
};

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/

#endif