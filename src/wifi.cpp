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

#define RESET 0
#define FALSE 0
#define TRUE  1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

float velocity;

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
    Serial.println("wait");
  }
}

void api_task(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  HTTPClient http;

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      uint8_t traffic_light_id, send = FALSE;

      if (xSemaphoreTake(xCarSemaphore, (TickType_t)10) == pdTRUE) {
        if (xQueueReceive(xCarQueue, &traffic_light_id,
                          (TickType_t)TICKS_WAIT) == pdPASS) {

          if (traffic_light_id == 1) {
            if (second == 1) {
              send   = TRUE;
              second = RESET;
            }
          } else {
            send     = TRUE;
            velocity = RESET;
          }

          if (send == TRUE) {

            const String server = "http://192.168.171.208:3000";

            const String car_url =
                server + "/vehicles/insert" + "?car_id=" + car_counter +
                "&velocity=" + velocity + "&date_id=" + 1 +
                "&car_type_id=" + 2 + "&traffic_light_id=" + traffic_light_id;

            http.begin(car_url);
            http.POST("");

            car_counter++;

            http.end();
          }
        }
      }

      if (xSemaphoreTake(xTrafficLightSemaphore, (TickType_t)10) == pdTRUE) {
        if (xQueueReceive(xTrafficLightQueue, &traffic_light_id,
                          (TickType_t)TICKS_WAIT) == pdPASS) {

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
        }
      }
    }
  }
}

/****************************** End Of Module *******************************/
