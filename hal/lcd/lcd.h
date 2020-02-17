 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Ventor
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/

#include "../../std_types.h"
#include "../../micro_config.h"
#include "../../mcal/dio/dio.h"

/*******************************************************************************
 *                              CONSTANTS                                       *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define RS PA1
#define RW PA2
#define E  PA3
#define LCD_CTRL_PORT PORTA
#define LCD_CTRL_PORT_DIR DDRA

#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80 

/*******************************************************************************
 *                      FUNCTIONS DECLARATIONS                                 *
 *******************************************************************************/
void LCD_sendCommand(uint8 a_command);
void LCD_displayCharacter(uint8 a_data);
void LCD_displayString(const char *Str_ptr);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const char *Str_ptr);
void LCD_goToRowColumn(uint8 a_row,uint8 a_col);
void LCD_intgerToString(uint32 a_data);

#endif /* LCD_H_ */
