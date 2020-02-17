 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Source file for the PWM AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

#ifndef _PWM_H_
#define _PWM_H_

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "../../micro_config.h"
#include "../../std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void PWM_init();
void PWM0_setDuty(uint8_t duty_cycle);
void PWM1_setDuty(uint8_t duty_cycle);


#endif /* _PWM_H_ */
