/**********************************************
 * Univeristy of Southern Denmark
 * Project in Cyber Physical Systems (CPS)
 *
 * MODULENAME: systick.c
 * PROJECT: Trafic light
 * DESCRIPTION: See module specification file (.h-file)
 * Change log:
 **********************************************
 * Date of Change
 * 240219 - DDMMYY
 * ----------------
 * 180223 Module created
 *
 ***********************************************/

/***************** Include files **************/

#include "../include/systick.h"
#include "../include/registers.h"

/***************** Defines ********************/

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void enable_clocks() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  SYSTEM_PERIP_CLK_EN0_REG_R =
      0x20000405; // Enable peripheral clock for system timer, uart, pcnt
                  // & timers (pdf-page 410)
}

void init_systick() {
  /*****************************************************************************
   *   Function : See module specification (.h-file)
   *****************************************************************************/

  SYSTIMER_INT_CLR_REG_R =
      0x00000000; // clear interrupt on system timers 0, 1 & 2
  SYSTIMER_UPDATE_REG_R =
      0x80000000; // enable updating timer values into registers
  SYSTIMER_INT_ENA_REG_R = 0x00000001; // enable interrupt on system timer 1
}
