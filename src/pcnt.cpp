/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: pcnt.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 230424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "driver/pcnt.h"
#include "Arduino.h"
#include "pcnt.h"
#include "soc/pcnt_struct.h"

/*****************************    Defines    *******************************/

#define PCNT_FREQ_UNIT_0 PCNT_UNIT_0
#define PCNT_FREQ_UNIT_1 PCNT_UNIT_1
#define PCNT_FREQ_UNIT_2 PCNT_UNIT_2
#define PCNT_FREQ_UNIT_3 PCNT_UNIT_3

#define INPUT_PIN_0      7
#define INPUT_PIN_1      8
#define INPUT_PIN_2      9
#define INPUT_PIN_3      21

#define NO_CAR           0
#define RESET            0
#define CAR              1

#define PCNT_H_LIM_VAL   10
#define PCNT_FILTER_VAL  100
#define TASK_DELAY       100
#define OVERFLOW_LIMIT   1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

uint8_t     PCNT_module::object_count = RESET;

PCNT_module pcnt0, pcnt1, pcnt2, pcnt3;

/*****************************   Functions *******************************/

PCNT_module::PCNT_module() { ++object_count; }

void PCNT_module::static_counter_overflow(void *arg) {
  PCNT_module *pcnt_module = static_cast<PCNT_module *>(arg);
  pcnt_module->counter_overflow();
}

void PCNT_module::init(pcnt_unit_t unit, uint8_t pin, int16_t limit,
                       uint16_t filter, uint8_t delay, uint8_t overflow) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  pcnt_unit        = unit;
  input_pin        = pin;
  high_limit       = limit;
  filter_value     = filter;
  delay_timer      = delay;
  overflow_limit   = overflow;
  overflow_counter = RESET;
  pulse_counter    = RESET;
  state            = NO_CAR;
  user_isr_handle  = NULL;
  pcnt_config      = {};
}

void PCNT_module::init_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  pcnt_config.pulse_gpio_num = input_pin;
  pcnt_config.pos_mode       = PCNT_COUNT_INC;
  pcnt_config.counter_h_lim  = PCNT_H_LIM_VAL;
  pcnt_config.unit           = pcnt_unit;
  pcnt_config.channel        = PCNT_CHANNEL_0;
  pcnt_unit_config(&pcnt_config);

  // pcnt_isr_register(&PCNT_module::static_counter_overflow, this, 0,
  //                  &user_isr_handle);
  pcnt_isr_service_install(0);
  pcnt_isr_handler_add(pcnt_unit, &PCNT_module::static_counter_overflow, this);
  pcnt_intr_enable(pcnt_unit);

  pcnt_set_filter_value(pcnt_unit, PCNT_FILTER_VAL);
  pcnt_filter_enable(pcnt_unit);

  pcnt_counter_pause(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
  pcnt_event_enable(pcnt_unit, PCNT_EVT_H_LIM);
  pcnt_counter_resume(pcnt_unit);
};

void IRAM_ATTR PCNT_module::counter_overflow() {
  overflow_counter++;
  PCNT.int_clr.val = BIT(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
}

void PCNT_module::read_pcnt() {
  pcnt_get_counter_value(pcnt_unit, &pulse_counter);
}

void PCNT_module::print_pcnt() {
  while (1) {

    switch (state) {
      case NO_CAR:
        pcnt_counter_pause(pcnt_unit);
        pcnt_counter_clear(pcnt_unit);
        pcnt_counter_resume(pcnt_unit);
        vTaskDelay(delay_timer / portTICK_PERIOD_MS);

        // if the frequency is higher than the targeted high_limit
        // an overflow occurs; if the amount of overflows is higehr
        // than the sat limit, a car has arrived
        if (overflow_counter > overflow_limit) {
          state = CAR;
        } else {
          overflow_counter = RESET;
        }
        break;

      case CAR:
        pcnt_counter_pause(pcnt_unit);
        pcnt_counter_clear(pcnt_unit);
        pcnt_counter_resume(pcnt_unit);
        vTaskDelay(delay_timer / portTICK_PERIOD_MS);

        // if the overflow_count is less than the limit, the frequency of the
        // signal is not what is expected for a car passing by
        if (overflow_counter < overflow_limit) {
          state = NO_CAR;
        }
        overflow_counter = RESET;
        read_pcnt();
        Serial.print(pulse_counter);
        Serial.print("\t");
        Serial.print(overflow_counter);
        Serial.print("\n");
        break;
    }
  }
}

void setup_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  pcnt0.init(PCNT_UNIT_0, INPUT_PIN_0, PCNT_H_LIM_VAL, PCNT_FILTER_VAL,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt1.init(PCNT_UNIT_1, INPUT_PIN_1, PCNT_H_LIM_VAL, PCNT_FILTER_VAL,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt2.init(PCNT_UNIT_2, INPUT_PIN_2, PCNT_H_LIM_VAL, PCNT_FILTER_VAL,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt3.init(PCNT_UNIT_3, INPUT_PIN_3, PCNT_H_LIM_VAL, PCNT_FILTER_VAL,
             TASK_DELAY, OVERFLOW_LIMIT);

  pcnt0.init_pcnt();
  pcnt1.init_pcnt();
  pcnt2.init_pcnt();
  pcnt3.init_pcnt();
}

void pcnt0_task(void *pvParameters) {
  PCNT_module *pcnt_module = static_cast<PCNT_module *>(pvParameters);
  while (1) {
    pcnt_module->print_pcnt();
  }
}

void pcnt1_task(void *pvParameters) {
  PCNT_module *pcnt_module = static_cast<PCNT_module *>(pvParameters);
  while (1) {
    pcnt_module->print_pcnt();
  }
}

void pcnt2_task(void *pvParameters) {
  PCNT_module *pcnt_module = static_cast<PCNT_module *>(pvParameters);
  while (1) {
    pcnt_module->print_pcnt();
  }
}

void pcnt3_task(void *pvParameters) {
  PCNT_module *pcnt_module = static_cast<PCNT_module *>(pvParameters);
  while (1) {
    pcnt_module->print_pcnt();
  }
}

/****************************** End Of Module *******************************/
