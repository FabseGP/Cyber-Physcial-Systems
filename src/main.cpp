/*****************************************************************************
 * University of Southern Denmark
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

enum Priorities { IDLE_PRIO, LOW_PRIO, MED_PRIO, HIGH_PRIO };

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void setup() {
  Serial.begin(921600);

  setup_gpio();
  setup_timer0();
  setup_pcnt();
  setup_traffic_lights();
  setup_cars();
  connect_wifi("WiFimodem-0CCC-2GHz", "VAM21K48");
  pinMode(16, OUTPUT);

  xTaskCreate(pcnt0_task, "pcnt0_task", 2048, &pcnt0, HIGH_PRIO, NULL);
  xTaskCreate(pcnt1_task, "pcnt1_task", 2048, &pcnt1, HIGH_PRIO, NULL);
  xTaskCreate(pcnt2_task, "pcnt2_task", 2048, &pcnt2, HIGH_PRIO, NULL);
  xTaskCreate(pcnt3_task, "pcnt3_task", 2048, &pcnt3, HIGH_PRIO, NULL);
  xTaskCreate(traffic_light_api, "wifi_task", 2048, NULL, LOW_PRIO, NULL);
  xTaskCreate(traffic_cycle, "cycle_task", 512, NULL, LOW_PRIO, NULL);
}

void loop() {
  digitalWrite(16, HIGH);
  delay(1);
  digitalWrite(16, LOW);
  delay(2);
}

/****************************** End Of Module *******************************/
