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
    gpio_num_t     red_led, yellow_led, green_led;

  public:
    TrafficLights();
    void           init(uint8_t id, String mode, String placement, String area,
                        uint8_t queue, gpio_num_t red_pin, gpio_num_t yellow_pin,
                        gpio_num_t green_pin);
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
    String         get_url();
    void           set_red();
    void           set_yellow();
    void           set_green();
    void           set_red_yellow();
};

/*****************************   Functions   *******************************/

void setup_traffic_lights();
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Initialize all traffic lights
 ******************************************************************************/

/****************************** End Of Module *******************************/

#endif