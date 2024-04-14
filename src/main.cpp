/**********************************************
 * Univeristy of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME: main.cpp
 * PROJECT: Trafic light
 * DESCRIPTION: Main file
 * Change log:
 **********************************************
 * Date of Change
 * 240219 - DDMMYY
 * ----------------
 * 130424 Module created
 *
 ***********************************************/

/***************** Include files **************/

#include "cars.h"
#include "wifi.h"
#include <Arduino.h>
#include <HTTPClient.h>

/***************** Defines ********************/

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void setup() {
  Serial.begin(921600);
  wifi_setup("WiFimodem-0CCC-2GHz", "VAM21K48");
}

void loop() {
  Cars car1;
  car1.init(20, 30, 2, 1, 2);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient   http;

    const String serverAddress = "http://192.168.0.200:3000/vehicles/insert";

    String       url           = serverAddress + "?car_id=" + car1.return_id() +
                 "&velocity=" + car1.return_velocity() +
                 "&date_id=" + car1.return_date() +
                 "&car_type_id=" + car1.return_type() +
                 "&traffic_light_id=" + car1.return_traffic_id();

    http.begin(url);

    int httpResponseCode = http.POST("");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.println("Error in HTTP POST request");
    }

    http.end();

  } else {
    Serial.println("get a better internet connection!");
  }

  delay(5000);
}

/***************** End of module **************/
