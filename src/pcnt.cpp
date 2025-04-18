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
#include "global_def.h"
#include "pcnt.h"
#include "soc/pcnt_struct.h"

/*****************************    Defines    *******************************/

#define PCNT_FREQ_UNIT_0    PCNT_UNIT_0
#define PCNT_FREQ_UNIT_1    PCNT_UNIT_1
#define PCNT_FREQ_UNIT_2    PCNT_UNIT_2
#define PCNT_FREQ_UNIT_3    PCNT_UNIT_3

#define INPUT_PIN_0         7
#define INPUT_PIN_1         8
#define INPUT_PIN_2         9
#define INPUT_PIN_3         21

#define PCNT_H_LIM_VAL_1    458
#define PCNT_H_LIM_VAL_2    152
#define PCNT_FILTER_VAL_1   370
#define PCNT_FILTER_VAL_2   970

#define TASK_DELAY          50
#define OVERFLOW_LIMIT      10
#define NO_FLAGS            0

#define DISTANCE_M          0.30
#define VELOCITY_CONVERSION 3.6

#define NO_CAR              0
#define CAR                 1

#define RESET               0
#define FALSE               0
#define TRUE                1

/*****************************   Constants   *******************************/

/*****************************  Variables  *******************************/

uint8_t PCNTModule::object_count = RESET, first = FALSE,
        velocity_measured = FALSE;
int64_t time_pre, time_now;

/*****************************    Objects *******************************/

PCNTModule pcnt0, pcnt1, pcnt2, pcnt3;

/*****************************   Functions *******************************/

PCNTModule::PCNTModule() { ++object_count; }

void PCNTModule::static_counter_overflow(void *arg) {
  PCNTModule *pcnt_module = static_cast<PCNTModule *>(arg);
  pcnt_module->counter_overflow();
}

void PCNTModule::init(pcnt_unit_t unit, uint8_t pin, int16_t limit,
                      uint16_t filter, uint8_t delay, uint8_t overflow) {
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

  init_pcnt();
}

void PCNTModule::init_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  pcnt_config.pulse_gpio_num = input_pin;
  pcnt_config.pos_mode       = PCNT_COUNT_INC;
  pcnt_config.counter_h_lim  = high_limit;
  pcnt_config.unit           = pcnt_unit;
  pcnt_config.channel        = PCNT_CHANNEL_0;
  pcnt_unit_config(&pcnt_config);

  // https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/peripherals/pcnt.html#_CPPv420pcnt_isr_handler_add11pcnt_unit_tPFvPvEPv
  // pcnt_isr_register(&PCNT_module::static_counter_overflow, this, 0,
  // &user_isr_handle);
  pcnt_isr_service_install(NO_FLAGS);
  pcnt_isr_handler_add(pcnt_unit, &PCNTModule::static_counter_overflow, this);
  pcnt_intr_enable(pcnt_unit);

  pcnt_set_filter_value(pcnt_unit, filter_value);
  pcnt_filter_enable(pcnt_unit);

  pcnt_counter_pause(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
  pcnt_event_enable(pcnt_unit, PCNT_EVT_H_LIM);
  pcnt_counter_resume(pcnt_unit);
};

void IRAM_ATTR PCNTModule::counter_overflow() {
  ++overflow_counter;
  PCNT.int_clr.val = BIT(pcnt_unit);
  pcnt_counter_clear(pcnt_unit);
}

void PCNTModule::read_pcnt() {
  pcnt_get_counter_value(pcnt_unit, &pulse_counter);
}

void PCNTModule::pcnt_task() {

  switch (state) {
    case NO_CAR:
      pcnt_counter_pause(pcnt_unit);
      pcnt_counter_clear(pcnt_unit);
      pcnt_counter_resume(pcnt_unit);
      vTaskDelay(delay_timer / portTICK_PERIOD_MS);

      // if the frequency is higher than the targeted high_limit
      // an overflow occurs; if the amount of overflows is higher
      // than the sat limit, a car has arrived
      if (overflow_counter > overflow_limit) {
        state = CAR;
        uint8_t traffic_light_id;

        // for every car registered, the specific traffic light id is put into
        // the queue as a signal for the api-task to know that a car is
        // registered
        switch (pcnt_unit) {
          case PCNT_UNIT_0: // SEN1
            traffic_light_id = traffic_light0.get_id();
            traffic_light0.increment_queue();
            break;
          case PCNT_UNIT_1: // SEN2
            traffic_light_id = traffic_light2.get_id();
            traffic_light2.increment_queue();
            break;
          case PCNT_UNIT_2: // SEN3
            traffic_light_id = traffic_light1.get_id();
            traffic_light1.increment_queue();
            if (first == TRUE) {
              time_now          = esp_timer_get_time();
              double time_delta = (time_now - time_pre) / 1000000.0;
              velocity = (DISTANCE_M / time_delta) * VELOCITY_CONVERSION;
              first    = RESET;
              velocity_measured = TRUE;
            }
            break;
          case PCNT_UNIT_3: // SEN4
            traffic_light_id = traffic_light1.get_id();
            traffic_light1.increment_queue();
            if (first == FALSE) {
              time_pre = esp_timer_get_time();
              first    = TRUE;
            }
            break;
          default:
            break;
        }
        xQueueSend(xCarQueue, &traffic_light_id, (TickType_t)TICKS_WAIT);
        xSemaphoreGive(xCarSemaphore);
      }
      overflow_counter = RESET;
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
      break;

    default:
      break;
  }
}

void setup_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  pcnt0.init(PCNT_UNIT_0, INPUT_PIN_0, PCNT_H_LIM_VAL_1, PCNT_FILTER_VAL_1,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt1.init(PCNT_UNIT_1, INPUT_PIN_1, PCNT_H_LIM_VAL_2, PCNT_FILTER_VAL_2,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt2.init(PCNT_UNIT_2, INPUT_PIN_2, PCNT_H_LIM_VAL_1, PCNT_FILTER_VAL_1,
             TASK_DELAY, OVERFLOW_LIMIT);
  pcnt3.init(PCNT_UNIT_3, INPUT_PIN_3, PCNT_H_LIM_VAL_2, PCNT_FILTER_VAL_2,
             TASK_DELAY, OVERFLOW_LIMIT);
}

void pcnt0_task(void *pvParameters) {
  PCNTModule *pcnt_module = static_cast<PCNTModule *>(pvParameters);
  while (1) {
    pcnt_module->pcnt_task();
  }
}

void pcnt1_task(void *pvParameters) {
  PCNTModule *pcnt_module = static_cast<PCNTModule *>(pvParameters);
  while (1) {
    pcnt_module->pcnt_task();
  }
}

void pcnt2_task(void *pvParameters) {
  PCNTModule *pcnt_module = static_cast<PCNTModule *>(pvParameters);
  while (1) {
    pcnt_module->pcnt_task();
  }
}

void pcnt3_task(void *pvParameters) {
  PCNTModule *pcnt_module = static_cast<PCNTModule *>(pvParameters);
  while (1) {
    pcnt_module->pcnt_task();
  }
}

/****************************** End Of Module *******************************/
