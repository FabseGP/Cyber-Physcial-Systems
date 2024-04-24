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
#include "traffic_cycle.h"

/*****************************    Defines    *******************************/

#define PRESCALER_1MHz 80
#define TIMER_0        0

/*****************************   Constants   *******************************/

hw_timer_t *timer = NULL;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; // only needed when
// writing to shared memory/variables

/*****************************   Variables   *******************************/

// volatile int interrupts;
// int          totalInterrupts;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void IRAM_ATTR onTime() { // IRAM_ATTR forces the code into RAM instead of flash
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // portENTER_CRITICAL_ISR(&timerMux); // only needed when writing to shared
  // memory/variables
  traffic_cycle();
  // portEXIT_CRITICAL_ISR(&timerMux);
}

void setup_timer0() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  timer = timerBegin(TIMER_0, PRESCALER_1MHz,
                     true); // prescaler = 80 for 1 MHz clock-signal
  timerAttachInterrupt(timer, &onTime,
                       true); // attachs onTime-interrupt to timer0
  // Fire Interrupt every 1m ticks, so 1s
  timerAlarmWrite(timer, 1000000,
                  true); // Fire Interrupt every 1m ticks, so 1s

  timerAlarmEnable(timer);
  Serial.println("Timer has been set up");
}

/****************************** End Of Module *******************************/
