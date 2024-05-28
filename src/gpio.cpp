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

  // NS
  pinMode(GPIO_NUM_1, OUTPUT); // green
  pinMode(GPIO_NUM_2, OUTPUT); // yellow
  pinMode(GPIO_NUM_3, OUTPUT); // red

  // WE
  pinMode(GPIO_NUM_4, OUTPUT); // green
  pinMode(GPIO_NUM_5, OUTPUT); // yellow
  pinMode(GPIO_NUM_6, OUTPUT); // red

  // Sensors
  pinMode(GPIO_NUM_7, INPUT);  // SEN1
  pinMode(GPIO_NUM_8, INPUT);  // SEN2
  pinMode(GPIO_NUM_9, INPUT);  // SEN3
  pinMode(GPIO_NUM_21, INPUT); // SEN4
}

/****************************** End Of Module *******************************/
