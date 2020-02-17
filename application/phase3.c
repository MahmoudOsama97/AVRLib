/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "phase3.h"

/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void phase3(){
	int fd,rd;

	LCD_clearScreen();
	LCD_displayString("Phase 3");

		fd=ULTRASONIC_readFront();
		rd=ULTRASONIC_readRight();

		if((fd>0)&&(fd<30)){
			if(rd<10) {
				MOTOR_stop();
				_delay_ms(200);
				MOTOR_left(30);
				_delay_ms(200);
			}else if(rd>40){
				MOTOR_stop();
				_delay_ms(200);
				MOTOR_right (30);
				_delay_ms(200);
			}else {
				MOTOR_stop();
				_delay_ms(100);
			}
		}else{
			MOTOR_forward(30);
			_delay_ms(100);
	}
}
