/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: timer.cpp
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

#include "Arduino.h"
#include "global_def.h"

/*****************************    Defines    *******************************/

#define PRESCALER_1MHz 80
#define TIMER_0        0
#define ALARM_1_SECOND 1000000
#define SECOND_PASSED  1

/*****************************   Constants   *******************************/

hw_timer_t *timer = NULL;

// only needed when writing to shared memory/variables
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

/*****************************   Variables   *******************************/

uint8_t timer_change = 0;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void IRAM_ATTR timer_interrupt() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // only needed when writing to shared memory/variables
  portENTER_CRITICAL_ISR(&timerMux);

  timer_change = SECOND_PASSED;

  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup_timer0() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // prescaler = 80 for 1 MHz clock-signal
  timer = timerBegin(TIMER_0, PRESCALER_1MHz, true);

  // Attach onTime-interrupt to timer0
  timerAttachInterrupt(timer, &timer_interrupt, true);

  // Fire interrupt every 1M ticks, so 1s timer
  timerAlarmWrite(timer, ALARM_1_SECOND, true);

  // Enable timer interrupt
  timerAlarmEnable(timer);
}

/****************************** End Of Module *******************************/
