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
    uint8_t        traffic_light_id, queue_size, timer, rate, duration,
        timer_increment_counter;
    String     state, direction, location;
    gpio_num_t red_led, yellow_led, green_led;

  public:
    TrafficLights();
    // initialisering af trafiklys med initial state og kø-størrelse
    void init(uint8_t id, String mode, String placement, String area,
              uint8_t queue, uint8_t car_rate, gpio_num_t red_pin,
              gpio_num_t yellow_pin, gpio_num_t green_pin);

    // læsning af et trafiklys state, kø-størrrelse, timer, id og url
    static uint8_t get_count();
    uint8_t        get_id();
    uint8_t        get_timer();
    uint8_t        get_queue_size();
    String         get_state();
    String         get_url();

    // skrivning til et trafiklys timer og state
    void set_timer(uint8_t seconds);
    void set_red();
    void set_yellow();
    void set_green();
    void set_red_yellow();

    // ændring af et trafiklys timer og kø-størrelse
    void increment_timer(uint8_t subtract);
    void decrement_timer(uint8_t subtract);
    void increment_queue();
    void decrement_queue();
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