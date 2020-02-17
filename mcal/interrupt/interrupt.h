 /******************************************************************************
 *
 * Module: INTERRUPTS
 *
 * File Name: interrupts.h
 *
 * Description: Header file for the interrupts AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../dio/dio.h"


/*******************************************************************************
 *                              CONSTANTS                                       *
 *******************************************************************************/
#define RISING 1
#define FALLING 0
#define BOTH 2

/*******************************************************************************
 *                          FUNCTIONS DECLARATIONS                              *
 *******************************************************************************/
void INTERRUPT0_init(uint8_t a_type, func_ptr callback_ptr);
void INTERRUPT0_deinit();
void INTERRUPT1_init(uint8_t a_type, func_ptr callback_ptr);
void INTERRUPT1_deinit();
void INTERRUPT2_init(uint8_t a_type, func_ptr callback_ptr);
void INTERRUPT2_deinit();

#endif /* INTERRUPT_H_ */
