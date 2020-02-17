 /******************************************************************************
 *
 * Module: motor
 *
 * File Name: motor.c
 *
 * Description: Source file for the PWM AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/

#include "motor.h"

/*******************************************************************************
 *                     LOCAL FUNCTIONS PROTOTYPES                              *
 *******************************************************************************/
void MOTOR_init();
void MOTOR_forward(uint8_t a_spd);
void MOTOR_backward(uint8_t a_spd);
void MOTOR_left(uint8_t a_spd);
void MOTOR_right(uint8_t a_spd);
void MOTOR_stop();
static void MOTOR_A(uint8_t a_direction ,uint8_t a_speed);
static void MOTOR_B(uint8_t a_direction ,uint8_t a_speed);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
static void MOTOR_A(uint8_t a_direction,uint8_t a_speed)
{
	 PWM0_set_duty(a_speed);
	if(a_speed<=255)
	{
		if(a_direction) //clkwise
		{
			DIO_setPinValue(PD,2,1);
			DIO_setPinValue(PD,3,0);
		}
		else if(!a_direction) //aclkwise
		{
			DIO_setPinValue(PD,2,0);
			DIO_setPinValue(PD,3,1);
		}
	}

}

static void MOTOR_B(uint8_t a_direction ,uint8_t a_speed)
{
	 PWM1_set_duty(a_speed);
	if(a_speed<=255)
	{
		if(a_direction) //clkwise
		{
			DIO_setPinValue(PD,6,1);
			DIO_setPinValue(PD,7,0);

		}
		else if(!a_direction) //aclkwise
		{
			DIO_setPinValue(PD,6,0);
		    DIO_setPinValue(PD,7,1);
		}
	}

}
/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void MOTOR_init(){
	 PWM_init();
	DIO_setPinDirection(PD, 3,1);
	DIO_setPinDirection(PD, 2,1);
	DIO_setPinDirection(PD, 6,1);
	DIO_setPinDirection(PD, 7,1);
}

void MOTOR_forward(uint8_t a_spd){

	MOTOR_A(clkwise,a_spd);
	MOTOR_B(clkwise,a_spd);
}

void MOTOR_backward(uint8_t a_spd){

	MOTOR_A(aclkwise,a_spd);
	MOTOR_B(aclkwise,a_spd);
}

void MOTOR_left(uint8_t a_spd){
	MOTOR_A(aclkwise,a_spd);
	MOTOR_B(clkwise,a_spd);
}

void MOTOR_right(uint8_t a_spd){
	MOTOR_A(clkwise,a_spd);
	MOTOR_B(aclkwise,a_spd);
}

void MOTOR_stop(){
	MOTOR_A(aclkwise,0);
	MOTOR_B(aclkwise,0);
}
