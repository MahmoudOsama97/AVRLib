 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the timer AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "timer.h"

/*******************************************************************************
 *                         STATIC GLOBAL VARIABLES                              *
 *******************************************************************************/
static uint32_t g_maxOverflows;
static func_ptr TIMER0_callback_ptr = NULL; //initiate null pointer
static volatile g_nbOfOverflows0=0;

/*******************************************************************************
 *                    LOCAL FUNCTIONS IMPLEMENTATIONS                          *
 *******************************************************************************/
ISR(TIMER0_COMP_vect)
{
	g_nbOfOverflows0++;
	if(g_nbOfOverflows0 == g_maxOverflows){
		if(TIMER0_callback_ptr != NULL) TIMER0_callback_ptr();
		g_nbOfOverflows0 = 0;

	}
}

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/

void TIMER0_init(uint16_t a_period ,func_ptr callback_ptr){
	TIMER0_callback_ptr = callback_ptr;
	g_maxOverflows = (a_period*0.001)*16000000/255;
	TCNT0 = 0; //timer initial value
	OCR0  = 255; //compare value
	TIMSK |= (1<<OCIE0); //enable compare interrupt
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS00);
	SREG  |= (1<<7);           // enable global interrupts in MC.

}
