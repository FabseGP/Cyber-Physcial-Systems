/*****************************************************************************
 * University of Southern Denmark
 * Project 4. semester
 *
 * MODULENAME.: pcnt.h
 *
 * PROJECT....: Cyber Physical Systems
 *
 * DESCRIPTION: Initializing the PCNT-modules
 *
 * Change Log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 240424  MoH    Module created
 *
 *****************************************************************************/

#ifndef PCNT_H_
#define PCNT_H_

/***************************** Include files *******************************/

#include "Arduino.h"
#include "driver/pcnt.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

class PCNTModule {
  private:
    static uint8_t object_count;
    uint8_t     input_pin, overflow_counter, overflow_limit, state, delay_timer;
    uint16_t    filter_value;
    int16_t     high_limit, pulse_counter;
    pcnt_unit_t pcnt_unit;
    pcnt_isr_handle_t user_isr_handle;
    pcnt_config_t     pcnt_config;
    static void       static_counter_overflow(void *arg);

  public:
    PCNTModule();
    void           init(pcnt_unit_t pcnt_unit, uint8_t input_pin, int16_t limit,
                        uint16_t filter, uint8_t delay, uint8_t overflow);
    void           init_pcnt();
    void           read_pcnt();
    void           pcnt_task();
    void IRAM_ATTR counter_overflow();
};

/*****************************   Functions   *******************************/

void setup_pcnt();
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Initialize all 4 PCNT-modules
 ******************************************************************************/

void pcnt0_task(void *pvParameters);
void pcnt1_task(void *pvParameters);
void pcnt2_task(void *pvParameters);
void pcnt3_task(void *pvParameters);

/****************************** End Of Module *******************************/

#endif
