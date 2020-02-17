
 /******************************************************************************
 *
 * Module: MOTOR
 *
 * File Name: motor.h
 *
 * Description: Header file for the motor AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

#ifndef HAL_MOTOR_MOTOR_H_
#define HAL_MOTOR_MOTOR_H_
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../../mcal/dio/dio.h"
#include "../../mcal/pwm/pwm.h"

/*******************************************************************************
 *                             CONSTANTS                                       *
 *******************************************************************************/
#define clkwise 1
#define aclkwise 0

/*******************************************************************************
 *                        FUNCTIONS DECLARATIONS                                *
 *******************************************************************************/
void MOTOR_init();
void MOTOR_forward(uint8_t a_spd);
void MOTOR_backward(uint8_t a_spd);
void MOTOR_left(uint8_t a_spd);
void MOTOR_right(uint8_t a_spd);
void MOTOR_stop();

#endif /* HAL_MOTOR_MOTOR_H_ */
