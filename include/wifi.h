/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: wifi.h
 *
 * PROJECT....: Traffic light
 *
 * DESCRIPTION: Initializing a WiFi-connection and communicate with the
 *API-server
 *
 * Change Log:
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

/*****************************    Functions    *******************************/

void wifi_setup(String ssid, String password);
/*****************************************************************************
 *   Input    : SSID and password for WiFi-network
 *   Output   : -
 *   Function : Initialize a WiFi-connection
 ******************************************************************************/

/***************** End of module **************/

#endif