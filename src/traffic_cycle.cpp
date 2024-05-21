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
#include "global_def.h"

/*****************************    Defines    *******************************/

#define TL_IDLE       0
#define NS_READY      1
#define NS_GO         2
#define NS_WAIT       3
#define WE_READY      4
#define WE_GO         5
#define WE_WAIT       6

#define IDLE_TIME     10
#define NS_READY_TIME 2
#define NS_GO_TIME    18
#define NS_WAIT_TIME  3
#define WE_READY_TIME 2
#define WE_GO_TIME    18
#define WE_WAIT_TIME  3

#define QUEUE_LIMIT   4
#define MINIMUM_QUEUE 1

#define RESET         0
#define EMPTY         0
#define SECOND_PASSED 1
#define ONE_SECOND    1

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************    Objects    *******************************/

/*****************************   Functions   *******************************/

void traffic_timer_decrement() {
  traffic_light0.decrement_timer(ONE_SECOND);
  traffic_light2.decrement_timer(ONE_SECOND);
}

void update_queue(String &we_state, String &ns_state) {
  if (we_state == "Green") {
    traffic_light0.decrement_queue();
    traffic_light1.decrement_queue();
  } else if (ns_state == "Green") {
    traffic_light2.decrement_queue();
  }
}

void update_timer(String &we_state, String &ns_state) {
  uint8_t we_queue_size_1 = traffic_light0.get_queue_size(),
          we_queue_size_2 = traffic_light1.get_queue_size(),
          ns_queue_size   = traffic_light2.get_queue_size();

  if (((we_queue_size_1 > QUEUE_LIMIT || we_queue_size_2 > QUEUE_LIMIT) &&
       we_state == "Green") ||
      (ns_queue_size > QUEUE_LIMIT && ns_state == "Green")) {
    traffic_light0.increment_timer(ONE_SECOND);
    traffic_light2.increment_timer(ONE_SECOND);
  } else if (((we_queue_size_1 > QUEUE_LIMIT ||
               we_queue_size_2 > QUEUE_LIMIT) &&
              we_state == "Red") ||
             (ns_queue_size > QUEUE_LIMIT && ns_state == "Red")) {
    traffic_light0.decrement_timer(ONE_SECOND);
    traffic_light2.decrement_timer(ONE_SECOND);
  }

  if ((we_queue_size_1 >= MINIMUM_QUEUE || we_queue_size_2 >= MINIMUM_QUEUE) &&
      we_state != "Green" && ns_queue_size == EMPTY &&
      (ns_state == "Green" || ns_state == "RedYellow")) {
    traffic_light0.set_timer(RESET);
    traffic_light2.set_timer(RESET);
  } else if (ns_queue_size >= MINIMUM_QUEUE && ns_state != "Green" &&
             (we_queue_size_1 == EMPTY && we_queue_size_2 == EMPTY) &&
             (we_state == "Green" || we_state == "RedYellow")) {
    traffic_light0.set_timer(RESET);
    traffic_light2.set_timer(RESET);
  }
}

void traffic_algorithm() {
  if (timer_change == SECOND_PASSED) {

    timer_change = RESET;

    traffic_timer_decrement();

    String we_state = traffic_light0.get_state(),
           ns_state = traffic_light2.get_state();

    update_queue(we_state, ns_state);
    update_timer(we_state, ns_state);

    uint8_t traffic_light0_id = traffic_light0.get_id();

    xQueueSend(xTrafficLightQueue, &traffic_light0_id, (TickType_t)TICKS_WAIT);
    xSemaphoreGive(xTrafficLightSemaphore);
  }
}

void traffic_cycle(void *pvParameters) {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  while (1) {

    traffic_algorithm();

    static uint8_t traffic_state = TL_IDLE;
    uint8_t        timer         = traffic_light0.get_timer();

    if (timer == RESET) {

      switch (traffic_state) {
        case TL_IDLE:

          traffic_light0.set_red();
          traffic_light1.set_red();
          traffic_light2.set_red();
          traffic_light0.set_timer(IDLE_TIME);
          traffic_light1.set_timer(IDLE_TIME);
          traffic_light2.set_timer(IDLE_TIME);
          traffic_state = WE_READY;
          break;

        case WE_READY:
          traffic_light0.set_red_yellow();
          traffic_light1.set_red_yellow();
          traffic_light2.set_red();
          traffic_light0.set_timer(WE_READY_TIME);
          traffic_light1.set_timer(WE_READY_TIME);
          traffic_light2.set_timer(WE_READY_TIME);
          traffic_state = WE_GO;
          break;

        case WE_GO:
          traffic_light0.set_green();
          traffic_light1.set_green();
          traffic_light2.set_red();
          traffic_light0.set_timer(WE_GO_TIME);
          traffic_light1.set_timer(WE_GO_TIME);
          traffic_light2.set_timer(WE_GO_TIME);
          traffic_state = WE_WAIT;
          break;

        case WE_WAIT:
          traffic_light0.set_yellow();
          traffic_light1.set_yellow();
          traffic_light2.set_red();
          traffic_light0.set_timer(WE_WAIT_TIME);
          traffic_light1.set_timer(WE_WAIT_TIME);
          traffic_light2.set_timer(WE_WAIT_TIME);
          traffic_state = NS_READY;
          break;

        case NS_READY:
          traffic_light0.set_red();
          traffic_light1.set_red();
          traffic_light2.set_red_yellow();
          traffic_light0.set_timer(NS_READY_TIME);
          traffic_light1.set_timer(NS_READY_TIME);
          traffic_light2.set_timer(NS_READY_TIME);
          traffic_state = NS_GO;
          break;

        case NS_GO:
          traffic_light0.set_red();
          traffic_light1.set_red();
          traffic_light2.set_green();
          traffic_light0.set_timer(NS_GO_TIME);
          traffic_light1.set_timer(NS_GO_TIME);
          traffic_light2.set_timer(NS_GO_TIME);
          traffic_state = NS_WAIT;
          break;

        case NS_WAIT:
          traffic_light0.set_red();
          traffic_light1.set_red();
          traffic_light2.set_yellow();
          traffic_light0.set_timer(NS_WAIT_TIME);
          traffic_light1.set_timer(NS_WAIT_TIME);
          traffic_light2.set_timer(NS_WAIT_TIME);
          traffic_state = WE_READY;
          break;

        default:
          break;
      }
    }
  }
}

/****************************** End Of Module *******************************/
