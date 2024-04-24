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

  pinMode(GPIO_NUM_1, OUTPUT);
  pinMode(GPIO_NUM_2, OUTPUT);
  pinMode(GPIO_NUM_3, OUTPUT);
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);
  pinMode(GPIO_NUM_6, OUTPUT);
  Serial.println("GPIO has been set up");
}

/****************************** End Of Module *******************************/
