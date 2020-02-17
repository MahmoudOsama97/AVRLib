 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "pwm.h"
#include "../dio/dio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_init()//TIMER
{
	TCNT1 = 0; // Timer initial value

//	DDRD  = DDRD | (1<<PD5); //set OC4 as output pin --> pin where the PWM signal is generated from MC
//DDRD  = DDRD | (1<<PD4); //set OC5 as output pin --> pin where the PWM signal is generated from MC
		DIO_setPinDirection (PD, 5, OUTPUT );
		DIO_setPinDirection (PD, 4, OUTPUT );
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR1A = 0b10100001;
	TCCR1B = 0b00001101;
}

void PWM0_set_duty(uint8_t a_duty_cycle)
{
	OCR1A  = (a_duty_cycle*255)*0.01; //compare value
}

void PWM1_set_duty(uint8_t a_duty_cycle)
{
	OCR1B  = (a_duty_cycle*255)*0.01; //compare value
}
