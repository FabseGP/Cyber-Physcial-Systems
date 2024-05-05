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
#define TIMER_SUBTRACT 1

/*****************************   Constants   *******************************/

hw_timer_t *timer = NULL;

// only needed when writing to shared memory/variables
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

/*****************************   Variables   *******************************/

// volatile int interrupts;
// int          totalInterrupts;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void IRAM_ATTR onTime() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // only needed when writing to shared memory/variables
  portENTER_CRITICAL_ISR(&timerMux);

  traffic_light0.update_timer(TIMER_SUBTRACT);
  traffic_light1.update_timer(TIMER_SUBTRACT);
  traffic_light2.update_timer(TIMER_SUBTRACT);

  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup_timer0() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // prescaler = 80 for 1 MHz clock-signal
  timer = timerBegin(TIMER_0, PRESCALER_1MHz, true);

  // Attach onTime-interrupt to timer0
  timerAttachInterrupt(timer, &onTime, true);

  // Fire Interrupt every 1M ticks, so 1s
  timerAlarmWrite(timer, ALARM_1_SECOND, true);

  // Enable timer interrupt
  timerAlarmEnable(timer);
}

/****************************** End Of Module *******************************/
