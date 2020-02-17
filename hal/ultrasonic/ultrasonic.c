 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ultrasonic AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "ultrasonic.h"

/*******************************************************************************
 *                     LOCAL FUNCTIONS PROTOTYPES                              *
 *******************************************************************************/
void ULTRASONIC_timer0CallbackFunction();
void ULTRASONIC_interrupt2CallbackFunction();
void ULTRASONIC_initPolling();
uint16_t ULTRASONIC_readRight();
void ULTRASONIC_initInterrupt();
uint16_t ULTRASONIC_readFront();

/*******************************************************************************
 *                       GLOBAL STATIC VARIABLES                               *
 *******************************************************************************/
static uint32_t g_ultraBeg1 ;
static uint32_t g_ultraEnd1 ;
static uint32_t g_ultraBeg2 ;
static uint32_t g_ultraEnd2 ;
static uint16_t g_ultraDistance;

/*******************************************************************************
 *                       GLOBAL EXTERN VARIABLES                               *
 *******************************************************************************/
extern volatile uint32_t g_nbOfOverflows;

/*******************************************************************************
 *                    LOCAL FUNCTIONS IMPLEMENTATIONS                          *
 *******************************************************************************/
void ULTRASONIC_timer0CallbackFunction(){
	DIO_setPinValue(PORT_TRIG1, TRIG1,0);
	_delay_us(10);
	DIO_setPinValue(PORT_TRIG1, TRIG1,1);
	_delay_us(10);
	DIO_setPinValue(PORT_TRIG1, TRIG1,0);
}

void ULTRASONIC_interrupt2CallbackFunction(){
	if(((MCUCSR) >> (ISC2)) & 0x01){
		g_ultraBeg1 = g_nbOfOverflows;
	}
	else {
		g_ultraEnd1 = g_nbOfOverflows;
		g_ultraDistance = (g_ultraEnd1 - g_ultraBeg1)*0.16;
	}
}

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void ULTRASONIC_initPolling(){
	DIO_setPinDirection(PC, TRIG2,1);
	DIO_setPinDirection(PC, ECHO2,0);
	TIMER2_init(PRE_1);
}

void ULTRASONIC_initInterrupt()
{
	TIMER0_init(ULTRASONIC_PERIOD ,ULTRASONIC_timer0CallbackFunction);
	TIMER2_init(PRE_1);
	INTERRUPT2_init(BOTH,ULTRASONIC_interrupt2CallbackFunction);
	DIO_setPinDirection(PORT_TRIG1,TRIG1,1);
	DIO_setPinDirection(PORT_TRIG1,TRIG1,1);
	DIO_setPinValue(PORT_TRIG1,TRIG1,0);
}

uint16_t ULTRASONIC_readFront()
{
	return g_ultraDistance ;
}

uint16_t ULTRASONIC_readRight(){
	DIO_setPinValue(PC, TRIG2,0);
	_delay_us(10);
	DIO_setPinValue(PC, TRIG2,1);
	_delay_us(10);
	DIO_setPinValue(PORT2u, TRIG2,0);
	g_ultraBeg2 = g_nbOfOverflows;
	while(!DIO_getPinValue(PIN2u,ECHO2));
	while(PIN2u & (1 << ECHO2));
	g_ultraEnd2 = g_nbOfOverflows;
	return ((g_ultraBeg2 - g_ultraEnd2) * 0.16 - 5);
}
