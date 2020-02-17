 /******************************************************************************
 *
 * Module: INTERRUPTS
 *
 * File Name: interrupts.c
 *
 * Description: Source file for the interrupts AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "interrupt.h"

/*******************************************************************************
 *                     LOCAL FUNCTIONS PROTOTYPES                              *
 *******************************************************************************/
void INTERRUPT0_init(uint8_t a_type, func_ptr callback_ptr);
//void INTERRUPT1_init(uint8_t a_type, func_ptr callback_ptr);
void INTERRUPT2_init(uint8_t a_type, func_ptr callback_ptr);

/*******************************************************************************
 *                       GLOBAL STATIC VARIABLES                               *
 *******************************************************************************/
static func_ptr int0Callback_ptr=NULL;
static func_ptr int1Callback_ptr=NULL;
static func_ptr int2Callback_ptr=NULL;

static uint8_t g_typeFlag=0;

/*******************************************************************************
 *                    LOCAL FUNCTIONS IMPLEMENTATIONS                          *
 *******************************************************************************/
ISR(INT0_vect)
{
	if(int0Callback_ptr!= NULL)int0Callback_ptr();
}

ISR(INT1_vect)
{
	if(int1Callback_ptr!= NULL)int1Callback_ptr();
}

ISR(INT2_vect)
{
	if(int2Callback_ptr!= NULL)int2Callback_ptr();
	if(g_typeFlag==1)
	GICR &= ~(1<<INT2);
	(MCUCSR) ^=  (1 << (ISC2));
	GICR |= (1<<INT2);
	GIFR &= ~(1<<INTF2);
}

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void INTERRUPT0_init(uint8_t a_type, func_ptr callback_ptr){
	int0Callback_ptr = callback_ptr;
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DIO_setPinDirection (PD, 2, INPUT );										// Configure INT0/PD2 as input pin
	GICR  |= (1<<INT0);											// Enable external interrupt pin INT0
	if(a_type != BOTH) {MCUCR |= (a_type<<ISC00) | (1<<ISC01);}     // Trigger INT0 with the rising/falling edge
	else {MCUCR |= (1<<ISC00);									// Trigger INT0 with the both edges
	SREG = SREG | (1<<7);										// Enable interrupts by setting I-bit
}

void INTERRUPT1_init(uint8_t a_type, func_ptr callback_ptr){
	int1Callback_ptr = callback_ptr;
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DIO_setPinDirection (PD, 3, INPUT );										// Configure INT0/PD2 as input pin
	GICR  |= (1<<INT1);											// Enable external interrupt pin INT0
	if(a_type != BOTH) {MCUCR |= (a_type<<ISC10) | (1<<ISC11);}     // Trigger INT0 with the rising/falling edge
	else {MCUCR |= (1<<ISC10);	}								// Trigger INT0 with the both edges
	}
	SREG = SREG | (1<<7);										// Enable interrupts by setting I-bit
}

void INTERRUPT2_init(uint8_t a_type, func_ptr callback_ptr){
	int2Callback_ptr = callback_ptr;
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DIO_setPinDirection (PB, 2, INPUT );										// Configure INT0/PD2 as input pin
	GICR  |= (1<<INT2);											// Enable external interrupt pin INT0
	if(a_type != BOTH) {MCUCSR |= (a_type<<ISC2);}				     // Trigger INT0 with the rising/falling edge
	else {
		g_typeFlag=1;
	}															// Trigger INT0 with the both edges
	sei();														// Enable interrupts by setting I-bit
}

