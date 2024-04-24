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

#define PCNT_FREQ_UNIT  PCNT_UNIT_3
#define PCNT_H_LIM_VAL  10000
#define PCNT_FILTER_VAL 10000

/*****************************   Constants   *******************************/

pcnt_isr_handle_t user_isr_handle = NULL;

/*****************************   Variables   *******************************/

int16_t PulseCounter    = 0;
int     OverflowCounter = 0;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void IRAM_ATTR counter_overflow(void *arg) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  OverflowCounter++;
  PCNT.int_clr.val = BIT(PCNT_FREQ_UNIT);
  pcnt_counter_clear(PCNT_FREQ_UNIT);
}

void setup_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  pcnt_config_t pcntFreqConfig;
  pcntFreqConfig.pulse_gpio_num = INPUT_PIN;
  pcntFreqConfig.pos_mode       = PCNT_COUNT_INC;
  pcntFreqConfig.counter_h_lim  = PCNT_H_LIM_VAL;
  pcntFreqConfig.unit           = PCNT_FREQ_UNIT;
  pcntFreqConfig.channel        = PCNT_CHANNEL_0;

  pcnt_unit_config(&pcntFreqConfig);
  pcnt_event_enable(PCNT_FREQ_UNIT, PCNT_EVT_H_LIM);
  pcnt_intr_enable(PCNT_FREQ_UNIT);
  pcnt_isr_register(counter_overflow, NULL, 0, &user_isr_handle);
  pcnt_set_filter_value(PCNT_FREQ_UNIT, PCNT_FILTER_VAL);
  pcnt_filter_enable(PCNT_FREQ_UNIT);
  pcnt_counter_resume(PCNT_FREQ_UNIT);
};

void read_reset_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  pcnt_get_counter_value(PCNT_FREQ_UNIT, &PulseCounter);

  OverflowCounter = 0;
  pcnt_counter_clear(PCNT_FREQ_UNIT);
}

void read_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/
  pcnt_get_counter_value(PCNT_FREQ_UNIT, &PulseCounter);
}

void print_pcnt(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {

    static int range = 1;

    switch (range) {
      case 1:
        pcnt_counter_pause(PCNT_UNIT_0); // pauser vores pcnt
        pcnt_counter_clear(
            PCNT_UNIT_0); // sletter den optalte værdi på vores pcnt
        pcnt_counter_resume(PCNT_UNIT_0); // starter vores pcnt
        vTaskDelay(233 / portTICK_PERIOD_MS);

        if (OverflowCounter > 2) {
          range           = 2;
          OverflowCounter = 0;
        } // hvis den når den høje grænse skifter vi til case 2
        else {
          Serial.println("ikke skiftet");
          OverflowCounter = 0;
        }

        break;
      case 2:
        pcnt_counter_pause(PCNT_UNIT_0); // pauser vores pcnt
        pcnt_counter_clear(
            PCNT_UNIT_0); // sletter den optalte værdi på vores pcnt
        pcnt_counter_resume(PCNT_UNIT_0); // starter vores pcnt
        vTaskDelay(233 / portTICK_PERIOD_MS);
        if (OverflowCounter > 2) {
          range           = 2;
          OverflowCounter = 0;
        } // hvis pcnt når den høje grænse bliver den i case 2 ellers går den
          // til case 1
        else {
          range           = 1;
          OverflowCounter = 0;
        }
        read_pcnt();
        Serial.print(PulseCounter);
        Serial.print("\t");
        Serial.print(OverflowCounter);
        Serial.print("\n");

        break;
    }
  }
}

void start_pcnt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  xTaskCreatePinnedToCore( //
      print_pcnt,          // function to be executed
      "Print_PCNT",        // name of the task
      2048,                // stack size
      NULL,                // parameter passed to the function
      1,                   // priority
      NULL,                // task handle
      0);                  // core where task should run
  pinMode(INPUT_PIN, INPUT);
}

/****************************** End Of Module *******************************/
