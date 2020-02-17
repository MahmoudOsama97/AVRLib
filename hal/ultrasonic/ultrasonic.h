 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ultrasonic AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "../../micro_config.h"
#include "../../std_types.h"
#include "../../mcal/dio/dio.h"
#include "../../mcal/interrupt/interrupt.h"
#include "../../mcal/timer counter/timer counter.h"
#include "../../mcal/timer/timer.h"

/*******************************************************************************
 *                              CONSTANTS                                       *
 *******************************************************************************/
#define ULTRASONIC_PERIOD 70
#define TRIG1 0
#define PORT_TRIG1 PB
#define TRIG2 PC2
#define ECHO2 PC3
#define PORT2u PC
#define PIN2u PC
#define DDR2 PC

/*******************************************************************************
 *                          FUNCTIONS DECLARATIONS                              *
 *******************************************************************************/
void ULTRASONIC_initPolling();
uint16_t ULTRASONIC_readRight();
void ULTRASONIC_initInterrupt();
uint16_t ULTRASONIC_readFront();

#endif /* _ULTRASONIC_H_ */



