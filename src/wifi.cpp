/**********************************************
 * Univeristy of Southern Denmark
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
#include "traffic_lights.h"
#include <HTTPClient.h>
#include <WiFi.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void wifi_setup(const String ssid, const String password) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5);
  }

  Serial.println("Connected to WiFi");
}

void test_connection() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    Cars       car1;
    car1.init(20, 30, 2, 1, 2);

    const String server  = "http://192.168.0.200:3000";

    const String car_url = server + "/vehicles/insert" +
                           "?car_id=" + car1.return_id() +
                           "&velocity=" + car1.return_velocity() +
                           "&date_id=" + car1.return_date() +
                           "&car_type_id=" + car1.return_type() +
                           "&traffic_light_id=" + car1.return_traffic_id();

    http.begin(car_url);

    http.POST("");

    TrafficLights traffic_light1;
    traffic_light1.init(30, "Green", "South", "Faaborgvej 23, 5610 Assens", 20);

    const String traffic_light_url =
        server + "/trafficlights/insert" +
        "?traffic_light_id=" + traffic_light1.return_id() +
        "&state=" + traffic_light1.return_state() +
        "&direction=" + traffic_light1.return_direction() +
        "&location=" + traffic_light1.return_location() +
        "&queue_size=" + traffic_light1.return_queue_size();

    http.begin(traffic_light_url);

    http.POST("");

    http.end();

  } else {
    Serial.println("Get a better internet connection!");
  }
}

/****************************** End Of Module *******************************/
