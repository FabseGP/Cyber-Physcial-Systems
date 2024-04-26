/*****************************************************************************
 * Univeristy of Southern Denmark
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
 * 240424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "driver/pcnt.h"
#include "Arduino.h"
#include "pcnt.h"
#include "soc/pcnt_struct.h"

/*****************************    Defines    *******************************/

#define PCNT_FREQ_UNIT  PCNT_UNIT_0
#define PCNT_H_LIM_VAL  3780
#define PCNT_FILTER_VAL 1000
#define RESET           0
#define OVERFLOW        0
#define TASK_DELAY      100
#define NO_CAR          1
#define CAR             2

/*****************************   Constants   *******************************/

pcnt_isr_handle_t user_isr_handle = NULL;

/*****************************   Variables   *******************************/

int16_t pulse_counter    = RESET;
uint8_t overflow_counter = RESET;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void IRAM_ATTR counter_overflow(void *arg) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  overflow_counter++;
  PCNT.int_clr.val = BIT(PCNT_FREQ_UNIT);
  pcnt_counter_clear(PCNT_FREQ_UNIT);
}

void setup_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  initialize_pcnt(PCNT_UNIT_0, PCNT_CHANNEL_0, INPUT_PIN0);
  initialize_pcnt(PCNT_UNIT_1, PCNT_CHANNEL_0, INPUT_PIN1);
  initialize_pcnt(PCNT_UNIT_2, PCNT_CHANNEL_0, INPUT_PIN2);
  initialize_pcnt(PCNT_UNIT_3, PCNT_CHANNEL_0, INPUT_PIN3);
};

void initialize_pcnt(pcnt_unit_t pcnt_unit, pcnt_channel_t pcnt_channel,
                     uint8_t input_pin) {
  pcnt_config_t pcntFreqConfig;
  pcntFreqConfig.pulse_gpio_num = input_pin;
  pcntFreqConfig.pos_mode       = PCNT_COUNT_INC;
  pcntFreqConfig.counter_h_lim  = PCNT_H_LIM_VAL;
  pcntFreqConfig.unit           = pcnt_unit;
  pcntFreqConfig.channel        = pcnt_channel;

  pcnt_unit_config(&pcntFreqConfig);
  pcnt_event_enable(pcnt_unit, PCNT_EVT_H_LIM);
  pcnt_intr_enable(pcnt_unit);
  pcnt_isr_register(counter_overflow, NULL, 0, &user_isr_handle);
  pcnt_set_filter_value(pcnt_unit, PCNT_FILTER_VAL);
  pcnt_filter_enable(pcnt_unit);
  pcnt_counter_resume(pcnt_unit);

  pinMode(input_pin, INPUT);
}

void read_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  pcnt_get_counter_value(PCNT_FREQ_UNIT, &pulse_counter);
}

void print_pcnt(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {

    static uint8_t range = 1;

    switch (range) {
      case NO_CAR:
        pcnt_counter_pause(PCNT_UNIT_0); // pauser vores pcnt
        pcnt_counter_clear(
            PCNT_UNIT_0); // sletter den optalte værdi på vores pcnt
        pcnt_counter_resume(PCNT_UNIT_0); // starter vores pcnt
        vTaskDelay(TASK_DELAY / portTICK_PERIOD_MS);

        if (overflow_counter > OVERFLOW) {
          range            = CAR;
          overflow_counter = RESET;
        } // hvis den når den høje grænse skifter vi til case 2
        else {
          Serial.println("Not changed");
          overflow_counter = RESET;
        }

        break;
      case CAR:
        pcnt_counter_pause(PCNT_UNIT_0); // pauser vores pcnt
        pcnt_counter_clear(
            PCNT_UNIT_0); // sletter den optalte værdi på vores pcnt
        pcnt_counter_resume(PCNT_UNIT_0); // starter vores pcnt
        vTaskDelay(TASK_DELAY / portTICK_PERIOD_MS);
        if (overflow_counter > OVERFLOW) {
          range            = CAR;
          overflow_counter = RESET;
        } // hvis pcnt når den høje grænse bliver den i case 2 ellers går den
          // til case 1
        else {
          range            = NO_CAR;
          overflow_counter = RESET;
        }
        read_pcnt();
        Serial.print(pulse_counter);
        Serial.print("\t");
        Serial.println(overflow_counter);

        break;
    }
  }
}

void start_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  xTaskCreate(print_pcnt,   // function to be executed
              "Print_PCNT", // name of the task
              1024,         // stack size
              NULL,         // parameter passed to the function
              1,            // priority
              NULL          // task handle
  );
}

/****************************** End Of Module *******************************/
