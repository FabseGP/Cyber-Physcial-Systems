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
#define RESET       0
#define QUEUE_SIZE  10

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
  connect_wifi("WiFimodem-0CCC-2GHz", "VAM21K48");

  pinMode(16, OUTPUT);

  TaskHandle_t task_0, task_1, task_2, task_3, task_4, task_5, task_6;

  xCarQueue              = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));
  xCarSemaphore          = xSemaphoreCreateBinary();

  xTrafficLightQueue     = xQueueCreate(QUEUE_SIZE, sizeof(uint8_t));
  xTrafficLightSemaphore = xSemaphoreCreateBinary();

  xTaskCreate(pcnt0_task, "pcnt0_task", LARGE_STACK, &pcnt0, HIGH_PRIO,
              &task_0);
  xTaskCreate(pcnt1_task, "pcnt1_task", LARGE_STACK, &pcnt1, HIGH_PRIO,
              &task_1);
  xTaskCreate(pcnt2_task, "pcnt2_task", LARGE_STACK, &pcnt2, HIGH_PRIO,
              &task_2);
  xTaskCreate(pcnt3_task, "pcnt3_task", LARGE_STACK, &pcnt3, HIGH_PRIO,
              &task_3);
  xTaskCreate(car_api, "car_api", LARGE_STACK, NULL, MED_PRIO, &task_4);
  xTaskCreate(traffic_light_api, "traffic_light_api", LARGE_STACK, NULL,
              MED_PRIO, &task_5);

  // if not LOW_PRIO, the PCNT-counters doesn't work + no api-transfer
  xTaskCreate(traffic_cycle, "cycle_task", SMALL_STACK, NULL, LOW_PRIO,
              &task_6);
  /*
    xTaskCreatePinnedToCore(pcnt0_task, "pcnt0_task", LARGE_STACK, &pcnt0,
                            HIGH_PRIO, &task_0, 0);
    xTaskCreatePinnedToCore(pcnt1_task, "pcnt1_task", LARGE_STACK, &pcnt1,
                            HIGH_PRIO, &task_1, 0);
    xTaskCreatePinnedToCore(pcnt2_task, "pcnt2_task", LARGE_STACK, &pcnt2,
                            HIGH_PRIO, &task_2, 0);
    xTaskCreatePinnedToCore(pcnt3_task, "pcnt3_task", LARGE_STACK, &pcnt3,
                            HIGH_PRIO, &task_3, 0);
    xTaskCreatePinnedToCore(car_api, "car_api", LARGE_STACK, NULL, MED_PRIO,
                            &task_4, 1);
    xTaskCreatePinnedToCore(traffic_light_api, "traffic_light_api", LARGE_STACK,
                            NULL, MED_PRIO, &task_5, 1);
    xTaskCreatePinnedToCore(traffic_cycle, "cycle_task", SMALL_STACK, NULL,
                            LOW_PRIO, &task_6, 1);
   */
  xSemaphoreGive(xCarSemaphore);
  xSemaphoreGive(xTrafficLightSemaphore);
}

void loop() {
  digitalWrite(16, HIGH);
  delay(1);
  digitalWrite(16, LOW);
  delay(2);
}

/****************************** End Of Module *******************************/
