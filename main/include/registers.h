/*****************************************************************************
* University of Southern Denmark
* Project in Cyber Physical Systems (CPS)
*
* MODULENAME.: registers.h
*
* PROJECT....: Traffic light
*
* DESCRIPTION: Mapping registers to human-readable names
*
* Change Log:
******************************************************************************
* Date    Id    Change
* DDMMYY
* --------------------
* 170324  MoH    Module created
*
*****************************************************************************/

#ifndef _REGISTERS_H_ 
#define _REGISTERS_H_ 

/***************************** Include files *******************************/

#include "soc/gpio_reg.h"

/*****************************    Defines    *******************************/

//***************************************************************
//
// GPIO0 ~ 31 output register (PDF-page 174)
//
//***************************************************************

#define GPIO_OUT_W1TS_REG_R       (*((volatile uint32_t *)GPIO_OUT_W1TS_REG))
#define GPIO_OUT_W1TC_REG_R       (*((volatile uint32_t *)GPIO_OUT_W1TC_REG)) 

#define GPIO_ENABLE_REG_R         (*((volatile uint32_t *)GPIO_ENABLE_REG)) 
#define GPIO_ENABLE_W1TS_REG_R    (*((volatile uint32_t *)GPIO_ENABLE_W1TS_REG)) 
#define GPIO_ENABLE_W1TC_REG_R    (*((volatile uint32_t *)GPIO_ENABLE_W1TC_REG)) 

/***************** End of module **************/

#endif