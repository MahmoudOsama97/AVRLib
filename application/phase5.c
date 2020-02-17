/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "phase5.h"

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void phase5(void){
	ULTRASONIC_initInterrupt();
	WIFI_init();
	_delay_ms(20000);
	WIFI_ConnectToTCPServer(192.168.43.43,8080);
	_delay_ms(10000);

	int fd;

	MOTOR_forward(30);
	while(ULTRASONIC_readFront() > 10);
	MOTOR_forward(0);
	MOTOR_stop();
	WIFI_SendTcpMessage(13,PHASE 5 ENDED);
	_delay_ms(10000);
	WIFI_SendTcpMessage(1,S);
}

