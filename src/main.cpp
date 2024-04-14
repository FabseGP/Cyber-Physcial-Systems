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
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient   http;

    const String serverAddress =
        "http://192.168.0.200:3000/trafficlights/insert";

    String traffic_light[] = {"210", "Yellow", "South", "Odensevej", "30"};

    String url =
        serverAddress + "?traffic_light_id=" + traffic_light[0] +
        "&state=" + traffic_light[1] + "&direction=" + traffic_light[2] +
        "&location=" + traffic_light[3] + "&queue_size=" + traffic_light[4];

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
