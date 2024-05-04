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

#include <Arduino.h>

/*****************************    Defines    *******************************/

extern QueueHandle_t     xCarQueue;
extern SemaphoreHandle_t xCarSemaphore;

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/

#endif
