/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: cars.h
 *
 * PROJECT....: Traffic light
 *
 * DESCRIPTION: Class for each car
 *
 * Change Log:
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

/***************** End of module **************/

#endif