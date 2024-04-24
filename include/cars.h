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

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

class Cars {
  private:
    int car_id, velocity, date_id, car_type_id, traffic_light_id;

  public:
    void init(int id, int speed, int date, int type, int traffic_light);
    int  return_id();
    int  return_velocity();
    int  return_date();
    int  return_type();
    int  return_traffic_id();
};

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/

#endif