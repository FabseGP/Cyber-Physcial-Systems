/*****************************************************************************
 * Univeristy of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: main.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: Main file
 * Change log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 130424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "cars.h"
#include "gpio.h"
#include "pcnt.h"
#include "timer.h"
#include "traffic_cycle.h"
#include "traffic_lights.h"
#include "wifi.h"
#include <Arduino.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void setup() {
  Serial.begin(921600);
  setup_gpio();
  setup_timer0();
  setup_pcnt();
  wifi_setup("WIFI_SSID_CHANGE_ME", "WIFI_PASSWORD_CHANGE_ME");
}

void loop() {
  start_pcnt();
  test_connection();
}

/****************************** End Of Module *******************************/
