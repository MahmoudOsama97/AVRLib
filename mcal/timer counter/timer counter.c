 /******************************************************************************
 *
 * Module: GLOBAL TIMER
 *
 * File Name: timer counter.c
 *
 * Description: Source file for the timer2 AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "timer counter.h"

/*******************************************************************************
 *                          FUNCTIONS DECLARATIONS                              *
 *******************************************************************************/
void TIMER2_init(uint8_t prescaler);
void TIMER2_reset();
uint32_t TIMER2_read();

/*******************************************************************************
 *                           GLOBAL VARIABLES                                   *
 *******************************************************************************/
volatile uint32_t g_nbOfOverflows=0;

/*******************************************************************************
 *                    LOCAL FUNCTIONS IMPLEMENTATIONS                          *
 *******************************************************************************/
ISR(TIMER2_COMP_vect){
	g_nbOfOverflows++;
}

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void TIMER2_init(uint8_t a_prescaler)
{
	SREG  |= (1<<7);// enable global interrupts in MC.
	TCNT2 = 0; //timer initial value
	OCR2  = 255; //compare value
	TIMSK |= (1<<OCIE2); //enable compare interrupt
	TCCR2 = (1<<FOC2) | (1<<WGM21);
	TCCR2 &= 0b11111000;
	TCCR2 |= (MASK | a_prescaler);
}

void TIMER2_reset()
{
	g_nbOfOverflows = 0;
}

uint32_t TIMER2_read()
{
	return g_nbOfOverflows*0.16;
}

