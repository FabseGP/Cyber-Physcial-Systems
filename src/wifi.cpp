/**********************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: wifi.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log.:
 **********************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 130424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "global_def.h"
#include <HTTPClient.h>
#include <WiFi.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

QueueHandle_t     xCarQueue, xTrafficLightQueue;
SemaphoreHandle_t xCarSemaphore, xTrafficLightSemaphore;

/*****************************   Functions   *******************************/

void connect_wifi(String ssid, String password) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  }
}

void car_api(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      uint8_t traffic_light_id;
      if (xQueueReceive(xCarQueue, &traffic_light_id, (TickType_t)10) ==
          pdPASS) {
        xSemaphoreTake(xCarSemaphore, (TickType_t)10);

        HTTPClient   http;

        const String server  = "http://192.168.0.200:3000";

        const String car_url = server + "/vehicles/insert" +
                               "?car_id=" + car_counter + "&velocity=" + 2 +
                               "&date_id=" + 1 + "&car_type_id=" + 2 +
                               "&traffic_light_id=" + traffic_light_id;

        http.begin(car_url);
        http.POST("");

        car_counter++;

        http.end();

        xSemaphoreGive(xCarSemaphore);
      }
    }
  }
}

void traffic_light_api(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {

      uint8_t traffic_light_id;
      if (xQueueReceive(xTrafficLightQueue, &traffic_light_id,
                        (TickType_t)10) == pdPASS) {
        xSemaphoreTake(xTrafficLightSemaphore, (TickType_t)10);

        HTTPClient   http;

        const String traffic_light0_url = traffic_light0.get_url();

        http.begin(traffic_light0_url);
        http.POST("");

        const String traffic_light1_url = traffic_light1.get_url();

        http.begin(traffic_light1_url);
        http.POST("");

        const String traffic_light2_url = traffic_light2.get_url();

        http.begin(traffic_light2_url);
        http.POST("");

        http.end();

        xSemaphoreGive(xTrafficLightSemaphore);
      }
    }
  }
}

/****************************** End Of Module *******************************/
