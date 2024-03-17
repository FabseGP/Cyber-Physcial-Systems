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
#include "freertos/task.h"
#include "include/registers.h"

/***************** Defines ********************/

#define RGB_LED             18
#define DELAY_TIME_MS       500

/***************** Constants ******************/

/***************** Variables ******************/

/***************** Functions ******************/

void app_main() {
    // Set the mode for GPIO5 to output
    GPIO_ENABLE_REG_R |= (1 << RGB_LED);

    while(1) {
        // Set the level for GPIO5 to HIGH
        GPIO_ENABLE_W1TS_REG_R = (1 << RGB_LED);

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));

        // Set the level for GPIO5 to LOW
        GPIO_ENABLE_W1TC_REG_R |= (1 << RGB_LED);

        // Delay
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
    
}

/***************** End of module **************/