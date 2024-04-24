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

void wifi_setup(String ssid, String password);
/*****************************************************************************
 *   Input    : SSID and password for WiFi-network
 *   Output   : -
 *   Function : Initialize a WiFi-connection
 ******************************************************************************/

void test_connection();
/*****************************************************************************
 *   Input    : -
 *   Output   : -
 *   Function : Tests connection to web-server by sending dummy data
 ******************************************************************************/


/****************************** End Of Module *******************************/

#endif