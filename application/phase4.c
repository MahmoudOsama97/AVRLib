/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "phase4.h"

/*******************************************************************************
 *                       GLOBAL EXTERN VARIABLES                               *
 *******************************************************************************/
extern char p;


/*******************************************************************************
 *                           APIs IMPLEMENTATIONS                              *
 *******************************************************************************/
void phase4(void){


	LCD_clearScreen();
	LCD_displayString("Phase 4");

		p= WIFI_Read();

		if(p=='w'){
			MOTOR_forward(40);
			LCD_clearScreen();
			LCD_displayCharacter(p);
		}else if(p=='a'){
			MOTOR_left(40);
			LCD_clearScreen();
			LCD_displayCharacter(p);
		}else if(p=='d'){
			MOTOR_right(40);
			LCD_clearScreen();
			LCD_displayCharacter(p);
		}else if(p=='s'){
			MOTOR_backward(40);
			LCD_clearScreen();
			LCD_displayCharacter(p);
		}else if(p=='b'){
			MOTOR_stop();
			LCD_clearScreen();
			LCD_displayCharacter(p);
		}


	}

