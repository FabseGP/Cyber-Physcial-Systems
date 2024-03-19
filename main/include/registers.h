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

// Header-files found within the folder of this git-link
// https://github.com/espressif/esp-idf/tree/6b9c2fca79a7b77a42242d48b0cfa82d612e9b85/components/soc/esp32s2

#include "soc/gpio_reg.h"
#include "soc/interrupt_reg.h"
#include "soc/systimer_reg.h"
#include "soc/timer_group_reg.h"

/*****************************    Defines    *******************************/

//***************************************************************
//
// GPIO0 ~ 31 output register (PDF-page 174)
//
//***************************************************************

#define GPIO_OUT_W1TS_REG_R (*((volatile uint32_t *)GPIO_OUT_W1TS_REG))
#define GPIO_OUT_W1TC_REG_R (*((volatile uint32_t *)GPIO_OUT_W1TC_REG))

#define GPIO_IN_REG_R (*((volatile uint32_t *)GPIO_IN_REG))

#define GPIO_ENABLE_REG_R (*((volatile uint32_t *)GPIO_ENABLE_REG))
#define GPIO_ENABLE_W1TS_REG_R (*((volatile uint32_t *)GPIO_ENABLE_W1TS_REG))
#define GPIO_ENABLE_W1TC_REG_R (*((volatile uint32_t *)GPIO_ENABLE_W1TC_REG))

//***************************************************************
//
// UART-registers (PDF-page 508)
//
//***************************************************************

#define UART_CLKDIV_REG_R (*((volatile uint32_t *)UART_CLKDIV_REG))
#define UART_CONF0_REG_R (*((volatile uint32_t *)UART_CONF0_REG))

/***************** End of module **************/

#endif