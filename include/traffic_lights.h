/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: traffic_lights.h
 *
 * PROJECT....: Traffic light
 *
 * DESCRIPTION: Class for each traffic light
 *
 * Change Log:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 140424  MoH    Module created
 *
 *****************************************************************************/

#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

/***************************** Include files *******************************/

#include <Arduino.h>

/*****************************    Objects    *******************************/

class TrafficLights {
  private:
    int    traffic_light_id, queue_size;
    String state, direction, location;

  public:
    void   init(int id, String mode, String placement, String area, int queue);
    int    return_id();
    String return_state();
    String return_direction();
    String return_location();
    int    return_queue_size();
};

/***************** End of module **************/

#endif