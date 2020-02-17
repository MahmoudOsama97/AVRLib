 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the uart AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "uart.h"

/*******************************************************************************
 *                       LOCAL FUNCTION PROTOTYPES                             *
 *******************************************************************************/
void UART_init(void);
void UART_sendChar(uint8_t a_data);
uint8_t UART_getChar(void);
void UART_sendString(uint8_t a_data[]);
uint8_t UART_getLastChar(uint8_t a_beforeLast);

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/

void UART_init(void)
//#define FREQ 160000
{
  // Set BaudRate -> 9600/16MhZ
  UBRRL = (160000 / (96*16))-1 ;
  UBRRH = 0;
  // Set Frame Format -> 8 data, 1 stop, No Parity
  UCSRC = 0x86;
   
  // Enable RX and TX
  UCSRB = 0x18;
}

void UART_sendChar(uint8_t a_data)
{
  // Wait until transmission Register Empty
  while((UCSRA&0x20) == 0x00);
  UDR = a_data;
}

uint8_t UART_getChar(void)
{
  uint8_t a_Result;
  // Wait until Reception Complete
  while((UCSRA &0x80) == 0x00);
  a_Result = UDR;
  
  /* Clear Flag */
  UCSRA |= 1<<7;
  return a_Result;
  
}

void UART_sendString(uint8_t a_data[])
 {
		int j = 0;
		while(a_data[j] != '\0'){
			UART_sendChar(a_data[j]);
			j++;
		}
		UART_sendChar(0);
 }
 
 
uint8_t UART_getLastChar(uint8_t a_beforeLast)
{
	while(UART_getChar() != a_beforeLast)
		{_delay_ms(10);}
	return UART_getChar();
}
 
