 /******************************************************************************
 *
 * Module: DIO
 *
 * File Name: dio.h
 *
 * Description: Source file for the DIO AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

#ifndef _DIO_INT_H
#define _DIO_INT_H

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "../../std_types.h"
#include "../../micro_config.h"


/*******************************************************************************
 *                              CONSTANTS                                       *
 *******************************************************************************/

/* Group A Registers */
#define PORTA_Register  ((volatile uint8_t*)0x3B)
#define DDRA_Register   ((volatile uint8_t*)0x3A)
#define PINA_Register   ((volatile uint8_t*)0x39)

/* Group B Registers */
#define PORTB_Register  ((volatile uint8_t*)0x38)
#define DDRB_Register   ((volatile uint8_t*)0x37)
#define PINB_Register   ((volatile uint8_t*)0x36)

/* Group C Registers */
#define PORTC_Register  ((volatile uint8_t*)0x35)
#define DDRC_Register   ((volatile uint8_t*)0x34)
#define PINC_Register   ((volatile uint8_t*)0x33)

/* Group D Registers */
#define PORTD_Register  ((volatile uint8_t*)0x32)
#define DDRD_Register   ((volatile uint8_t*)0x31)
#define PIND_Register   ((volatile uint8_t*)0x30)

/* Port Defines */
#define PA    0  //portA
#define PB    1  //portB
#define PC    2  //portC
#define PD    3  //portD

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1


/*******************************************************************************
 *                     LOCAL FUNCTIONS PROTOTYPES                              *
 *******************************************************************************/
/* IO Pins */
void DIO_setPinValue(uint8_t u8PortIdCopy , uint8_t u8PinIdCopy, uint8_t u8PinValCopy);

uint8_t DIO_getPinValue(uint8_t u8PortIdCopy, uint8_t u8PinIdCopy);

void DIO_setPinDirection (uint8_t u8PortIdCopy, uint8_t u8PinIdCopy, uint8_t u8PinDirCopy);

/* IO Ports */
void DIO_SetPortDirection (uint8_t u8PortId, uint8_t u8PortDir);

void DIO_SetPortValue     (uint8_t u8PortId, uint8_t u8PortVal);

#endif
