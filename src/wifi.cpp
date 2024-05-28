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

double velocity;

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

  uint8_t      traffic_light_id, send = FALSE;
  const String server = "http://192.168.255.208:3000";

  HTTPClient   http;

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      if (xSemaphoreTake(xCarSemaphore, (TickType_t)10) == pdTRUE) {
        while (xQueueReceive(xCarQueue, &traffic_light_id,
                             (TickType_t)TICKS_WAIT) == pdPASS) {

          if (traffic_light_id == 1 && velocity_measured == TRUE) {
            send              = TRUE;
            velocity_measured = RESET;
          } else {
            velocity = RESET;
          }

          if (send == TRUE) {
            // server-adressen lagres som en String for at sikre, at String
            // forbliver den største type i additionen
            const String car_url = server + "/vehicles/insert" +
                                   "?car_id=" + car_counter +
                                   "&velocity=" + velocity + "&date_id=" + 1 +
                                   "&traffic_light_id=" + traffic_light_id;

            http.begin(car_url);
            http.POST("");
            http.end();

            car_counter++;
            send = FALSE;
          }
        }
      }

      if (xSemaphoreTake(xTrafficLightSemaphore, (TickType_t)10) == pdTRUE) {
        while (xQueueReceive(xTrafficLightQueue, &traffic_light_id,
                             (TickType_t)TICKS_WAIT) == pdPASS) {

          const String traffic_light0_url = server + traffic_light0.get_url();

          http.begin(traffic_light0_url);
          http.POST("");

          const String traffic_light1_url = server + traffic_light1.get_url();

          http.begin(traffic_light1_url);
          http.POST("");

          const String traffic_light2_url = server + traffic_light2.get_url();

          http.begin(traffic_light2_url);
          http.POST("");

          http.end();
        }
      }
    }
  }
}

/****************************** End Of Module *******************************/
