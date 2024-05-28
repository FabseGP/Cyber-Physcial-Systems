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

#define RESET           0
#define FALSE           0
#define TRUE            1

#define TRAFFIC_LIGHT_W 1

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

  // wait till a connection have been established
  while (WiFi.status() != WL_CONNECTED) {
  }
}

void api_task(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  uint8_t traffic_light_id, send = FALSE;

  // ip-address for web-server
  const String server = "http://192.168.255.208:3000";

  // a object of the HTTPClient-class is created
  HTTPClient http;

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      // the semaphore can only be taken when a car is being registered
      if (xSemaphoreTake(xCarSemaphore, (TickType_t)10) == pdTRUE) {
        // as long as there's a id in the queue
        while (xQueueReceive(xCarQueue, &traffic_light_id,
                             (TickType_t)TICKS_WAIT) == pdPASS) {

          // if a car is registered at the W-traffic light and a velocity
          // have been calculated, the registered car can be sent to the server
          // and the velocity_measured-flag is being reset
          if (traffic_light_id == TRAFFIC_LIGHT_W)
            if (velocity_measured == TRUE) {
              send              = TRUE;
              velocity_measured = RESET;
            } else {
              velocity = RESET;
            }
          else {
            send = TRUE;
          }

          // if the traffic light is TRAFFIC_LIGHT_W and has a velocity
          // calculated or any other traffic light
          if (send == TRUE) {
            // the server-address is stored as a String to make sure that
            // String is being the highest type in the addition
            const String car_url = server + "/vehicles/insert" +
                                   "?car_id=" + car_counter +
                                   "&velocity=" + velocity + "&date_id=" + 1 +
                                   "&traffic_light_id=" + traffic_light_id;

            // a POST-request is being sent to the web-server
            http.begin(car_url);
            http.POST("");
            http.end();

            // the car_counter-variable is incremented so the next car has
            // a higher id, while the send-variable is being set to FALSE
            car_counter++;
            send = FALSE;
          }
        }
      }

      // the semaphore can only be taken when a car is being registered
      if (xSemaphoreTake(xTrafficLightSemaphore, (TickType_t)10) == pdTRUE) {
        // as long as there's a id in the queue
        while (xQueueReceive(xTrafficLightQueue, &traffic_light_id,
                             (TickType_t)TICKS_WAIT) == pdPASS) {

          // every traffic_light has their own get_url-function that returns
          // the parameter from each traffic light, including their state and
          // queue-size
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
