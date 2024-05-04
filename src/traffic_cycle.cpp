/*****************************************************************************
 * University of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME.: traffic_cycle.cpp
 * PROJECT....: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log.:
 ******************************************************************************
 * Date    Id    Change
 * DDMMYY
 * --------------------
 * 230424  MoH    Module created
 *
 *****************************************************************************/

/***************************** Include files *******************************/

#include "Arduino.h"
#include "traffic_lights.h"

/*****************************    Defines    *******************************/

#define TL_IDLE  0
#define NS_READY 1
#define NS_GO    2
#define NS_WAIT  3
#define WE_READY 4
#define WE_GO    5
#define WE_WAIT  6

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void traffic_cycle(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {

    static uint8_t traffic_state = NS_READY;

    uint8_t        timer         = traffic_light0.get_timer();

    if (timer == 0) {

      switch (traffic_state) {
        case TL_IDLE:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_3, HIGH);
          digitalWrite(GPIO_NUM_6, HIGH);
          //  delay(30000);
          traffic_light0.set_timer(10);
          break;

        case NS_READY:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_6, HIGH);
          digitalWrite(GPIO_NUM_3, HIGH);
          digitalWrite(GPIO_NUM_2, HIGH);
          //   delay(2000);
          traffic_light0.set_timer(2);
          traffic_state = NS_GO;
          break;

        case NS_GO:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_6, HIGH);
          digitalWrite(GPIO_NUM_1, HIGH);
          //  delay(18000);
          traffic_light0.set_timer(7);
          traffic_state = NS_WAIT;
          break;

        case NS_WAIT:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_6, HIGH);
          digitalWrite(GPIO_NUM_2, HIGH);
          //  delay(5000);
          traffic_light0.set_timer(5);
          traffic_state = WE_READY;
          break;

        case WE_READY:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_3, HIGH);
          digitalWrite(GPIO_NUM_6, HIGH);
          digitalWrite(GPIO_NUM_5, HIGH);
          //  delay(2000);
          traffic_light0.set_timer(2);
          traffic_state = WE_GO;
          break;

        case WE_GO:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_3, HIGH);
          digitalWrite(GPIO_NUM_4, HIGH);
          // delay(18000);
          traffic_light0.set_timer(7);
          traffic_state = WE_WAIT;
          break;

        case WE_WAIT:
          digitalWrite(GPIO_NUM_1, LOW);
          digitalWrite(GPIO_NUM_2, LOW);
          digitalWrite(GPIO_NUM_3, LOW);
          digitalWrite(GPIO_NUM_4, LOW);
          digitalWrite(GPIO_NUM_5, LOW);
          digitalWrite(GPIO_NUM_6, LOW);
          digitalWrite(GPIO_NUM_3, HIGH);
          digitalWrite(GPIO_NUM_5, HIGH);
          // delay(5000);
          traffic_light0.set_timer(5);
          traffic_state = NS_READY;
          break;

        default:
          break;
      }
    }
  }
}

/****************************** End Of Module *******************************/
