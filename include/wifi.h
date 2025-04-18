/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: wifi.h
 *
 * PROJECT....: Cyber Physical Systems
 *
 * DESCRIPTION: Initializing a WiFi-connection with communication
 *
 * Change Log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 130424  MoH    Module created
 *
 *****************************************************************************/

#ifndef WIFI_H
#define WIFI_H

/***************************** Include files *******************************/

#include <Arduino.h>

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void connect_wifi(String ssid, String password);
/*****************************************************************************
 *   Input    : SSID and password for WiFi-network
 *   Output   : -
 *   Function : Initialize a WiFi-connection
 ******************************************************************************/

void connect_eduroam(String ssid, String password, String identity);
/*****************************************************************************
 *   Input    : SSID and password for WiFi-network
 *   Output   : -
 *   Function : Initialize a WiFi-connection
 ******************************************************************************/

void api_task(void *pvParameters);
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Sends data to the API
 ******************************************************************************/

/****************************** End Of Module *******************************/

#endif