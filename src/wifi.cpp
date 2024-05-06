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

void connect_eduroam(String ssid, String password, String identity) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  WiFi.begin(ssid, WPA2_AUTH_PEAP, "anonymous@student.sdu.dk", identity,
             password);

  while (WiFi.status() != WL_CONNECTED) {
  }
}

void api_task(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      uint8_t traffic_light_id = 1;

      if (xQueueReceive(xCarQueue, &traffic_light_id, (TickType_t)TICKS_WAIT) ==
          pdPASS) {
        xSemaphoreTake(xCarSemaphore, (TickType_t)TICKS_WAIT);

        HTTPClient   http;

        const String server  = "http://192.168.171.208:3000";

        const String car_url = server + "/vehicles/insert" +
                               "?car_id=" + car_counter + "&velocity=" + 2 +
                               "&date_id=" + 1 + "&car_type_id=" + 2 +
                               "&traffic_light_id=" + traffic_light_id;

        http.begin(car_url);
        http.POST("");

        car_counter++;

        http.end();

        xSemaphoreGive(xCarSemaphore);
        Serial.println("sent");

        if (xQueueReceive(xTrafficLightQueue, &traffic_light_id,
                          (TickType_t)TICKS_WAIT) == pdPASS) {
          xSemaphoreTake(xTrafficLightSemaphore, (TickType_t)TICKS_WAIT);

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
}

/****************************** End Of Module *******************************/
