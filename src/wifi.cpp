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

#include "cars.h"
#include "global_def.h"
#include "traffic_lights.h"
#include <HTTPClient.h>
#include <WiFi.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

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
      HTTPClient   http;

      const String server = "http://192.168.0.200:3000";

      const String car0_url =
          server + "/vehicles/insert" + car0.get_parameters();

      http.begin(car0_url);
      http.POST("");

      http.end();
    }
  }
}

void traffic_light_api(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {
    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient   http;

      const String server = "http://192.168.0.200:3000";

      const String traffic_light0_url =
          server + "/trafficlights/insert" + traffic_light0.get_parameters();

      http.begin(traffic_light0_url);
      http.POST("");

      const String traffic_light1_url =
          server + "/trafficlights/insert" + traffic_light1.get_parameters();

      http.begin(traffic_light1_url);
      http.POST("");

      const String traffic_light2_url =
          server + "/trafficlights/insert" + traffic_light2.get_parameters();

      http.begin(traffic_light2_url);
      http.POST("");

      const String traffic_light3_url =
          server + "/trafficlights/insert" + traffic_light3.get_parameters();

      http.begin(traffic_light3_url);
      http.POST("");

      http.end();
    }
  }
}

/****************************** End Of Module *******************************/
