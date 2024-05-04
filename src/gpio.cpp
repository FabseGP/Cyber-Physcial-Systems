/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: gpio.cpp
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

#include "Arduino.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void setup_gpio() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  // LEDS

  // NS, green -> yellow -> red
  pinMode(GPIO_NUM_1, OUTPUT);
  pinMode(GPIO_NUM_2, OUTPUT);
  pinMode(GPIO_NUM_3, OUTPUT);

  // WE, green -> yellow -> red
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);
  pinMode(GPIO_NUM_6, OUTPUT);

  // Sensors
  pinMode(GPIO_NUM_7, INPUT);  // SEN1
  pinMode(GPIO_NUM_8, INPUT);  // SEN2
  pinMode(GPIO_NUM_9, INPUT);  // SEN3
  pinMode(GPIO_NUM_21, INPUT); // SEN4
}

/****************************** End Of Module *******************************/
