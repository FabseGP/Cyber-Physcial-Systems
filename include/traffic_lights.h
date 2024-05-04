/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: traffic_lights.h
 *
 * PROJECT....: Cyber Physical Systems
 *
 * DESCRIPTION: Class for each traffic light
 *
 * Change Log.:
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

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

class TrafficLights {
  private:
    static uint8_t object_count;
    uint8_t        traffic_light_id, queue_size = 0, timer = 0;
    String         state, direction, location;

  public:
    TrafficLights();
    void           init(uint8_t id, String mode, String placement, String area,
                        uint8_t queue);
    uint8_t        get_id();
    String         get_state();
    String         get_direction();
    String         get_location();
    uint8_t        get_queue_size();
    void           update_timer(uint8_t subtract);
    uint8_t        get_timer();
    void           mode_cycling();
    void           set_timer(uint8_t seconds);
    static uint8_t get_count();
    String         get_parameters();
};

extern TrafficLights traffic_light0, traffic_light1, traffic_light2,
    traffic_light3;

/*****************************   Functions   *******************************/

void setup_traffic_lights();
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Initialize all traffic lights
 ******************************************************************************/

/****************************** End Of Module *******************************/

#endif