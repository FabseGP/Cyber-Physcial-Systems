/*****************************************************************************
 * University of Southern Denmark
 * Project 4. semester
 *
 * MODULENAME.: global_def.h
 *
 * PROJECT....: Cyber Physical Systems
 *
 * DESCRIPTION: Global definitions
 *
 * Change Log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 230424  MoH    Module created
 *
 *****************************************************************************/

#ifndef GLOBAL_DEF_H_
#define GLOBAL_DEF_H_

/***************************** Include files *******************************/

#include "pcnt.h"
#include "traffic_lights.h"
#include <Arduino.h>

/*****************************    Defines    *******************************/

#define TICKS_WAIT 10

extern QueueHandle_t     xCarQueue, xTrafficLightQueue;
extern SemaphoreHandle_t xCarSemaphore, xTrafficLightSemaphore;

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

extern uint16_t car_counter;
extern uint8_t  timer_change, traffic_state;

/*****************************    Objects    *******************************/

extern PCNTModule    pcnt0, pcnt1, pcnt2, pcnt3;
extern TrafficLights traffic_light0, traffic_light1, traffic_light2;

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/

#endif
