#ifndef HAL_WIFI_WIFI_H_
#define HAL_WIFI_WIFI_H_

#include "../../mcal/uart/uart.h"
#include "../../micro_config.h"

#define WIFI_Connect(ssid, password) 			UART_sendString("AT+CWJAP=\""#ssid"\",\""#password"\"\r\n")

#define WIFI_EnableMultipleTCPConnections() 	UART_sendString("AT+CIPMUX=1\r\n")

#define WIFI_CreateServer(port)					 WIFI_EnableMultipleTCPConnections();\
												 _delay_ms(500);\
												 UART_sendString("AT+CIPSERVER=1,"#port"\r\n")

#define WIFI_init() 							UART_init();\
												_delay_ms(3000);\
												UART_sendString("AT\r\n")

#define WIFI_Read() 							UART_getChar()

#define WIFI_PrintIP()                          UART_sendString("AT+CIFSR\r\n")

#define WIFI_ConnectToTCPServer(IP,PORT)		UART_sendString("AT+CIPSTART=\"TCP\",\"192.168.43.43\",8080\r\n")

#define WIFI_SendTcpMessage(LENGTH, MESSAGE)	UART_sendString("AT+CIPSEND="#LENGTH"\r\n");\
												_delay_ms(500);\
												UART_sendString(#MESSAGE"\r\n")

#endif /* HAL_WIFI_WIFI_H_ */
