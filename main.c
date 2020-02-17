#include "micro_config.h"
#include "std_types.h"
#include "mcal/pwm/pwm.h"
#include "hal/motor/motor.h"
#include "mcal/interrupt/interrupt.h"
#include "mcal/timer/timer.h"
#include "mcal/timer counter/timer counter.h"
#include "hal/lcd/lcd.h"
#include <stdio.h>
#include "hal/ultrasonic/ultrasonic.h"
#include "mcal/uart/uart.h"
#include "hal/wifi/wifi.h"
#include "application/phase0.h"
#include "application/phase2.h"
#include "application/phase3.h"
#include "application/phase4.h"
#include "application/phase5.h"
char p;

//Phase X
void main(){
	MOTOR_init();
	LCD_init();
	WIFI_init();
	_delay_ms(2000);
	WIFI_Connect(MGTMM,8111998alia);
	_delay_ms(20000);
	WIFI_CreateServer(80);
	_delay_ms(20000);
	WIFI_PrintIP();
	char phase =0;
	while(1){
		p= WIFI_Read();
if(p=='0') MOTOR_stop();
else if(p=='2')phase=2;
else if(p=='3')phase=3;
else if(p=='4')phase=4;
else if(p=='5')phase=5;

if(phase=='0') MOTOR_stop();
else if(phase=='2')phase2();
else if(phase=='3')phase3();
else if(phase=='4')phase4();

	}
}

