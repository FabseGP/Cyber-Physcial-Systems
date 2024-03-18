/**********************************************
* Univeristy of Southern Denmark
* Project in Cyber Physical Systems (CPS)
*
* MODULENAME: main.c
* PROJECT: Trafic light
* DESCRIPTION: Main file
* Change log:
**********************************************
* Date of Change
* 240219 - DDMMYY
* ----------------
* 170324 Module created
*
***********************************************/

/***************** Include files **************/

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "include/registers.h"

/***************** Defines ********************/

#define LED                 5

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void app_main() {

    GPIO_ENABLE_REG_R = (1 << LED); // sets LED as output

    while(1) {
        GPIO_OUT_W1TS_REG_R = (1 << LED);
    }
    
}

/***************** End of module **************/
