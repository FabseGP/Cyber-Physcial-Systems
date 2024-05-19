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

#include "global_def.h"
#include "gpio.h"
#include "pcnt.h"
#include "timer.h"
#include "traffic_cycle.h"
#include "traffic_lights.h"
#include "wifi.h"
#include <Arduino.h>

/*****************************    Defines    *******************************/

#define IDLE_PRIO   0
#define LOW_PRIO    1
#define MED_PRIO    2
#define HIGH_PRIO   3

#define SMALL_STACK 512
#define MED_STACK   1024
#define LARGE_STACK 2024

#define BAUDRATE    921600
#define QUEUE_SIZE  20

#define RESET       0

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

uint16_t car_counter = RESET;

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void setup() {
  Serial.begin(BAUDRATE);

  setup_gpio();
  setup_timer0();
  setup_pcnt();
  setup_traffic_lights();
  connect_wifi("fabsewifi", "fabseman");

  xCarQueue              = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));
  xCarSemaphore          = xSemaphoreCreateBinary();

  xTrafficLightQueue     = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));
  xTrafficLightSemaphore = xSemaphoreCreateBinary();

  xSemaphoreGive(xCarSemaphore);
  xSemaphoreGive(xTrafficLightSemaphore);

  xTaskCreate(pcnt0_task, "pcnt0_task", LARGE_STACK, &pcnt0, HIGH_PRIO, NULL);
  xTaskCreate(pcnt1_task, "pcnt1_task", LARGE_STACK, &pcnt1, HIGH_PRIO, NULL);
  xTaskCreate(pcnt2_task, "pcnt2_task", LARGE_STACK, &pcnt2, HIGH_PRIO, NULL);
  xTaskCreate(pcnt3_task, "pcnt3_task", LARGE_STACK, &pcnt3, HIGH_PRIO, NULL);
  xTaskCreate(api_task, "api_task", LARGE_STACK, NULL, MED_PRIO, NULL);

  // if not LOW_PRIO, the PCNT-counters doesn't work + no
  // api-transfer
  xTaskCreate(traffic_cycle, "cycle_task", LARGE_STACK, NULL, LOW_PRIO, NULL);
}

void loop() {}

/****************************** End Of Module *******************************/
