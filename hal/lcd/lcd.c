 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: VENTOR
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "lcd.h"

/*******************************************************************************
 *                         APIs IMPLEMENTATION                                 *
 *******************************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	
	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		#else
			LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
		#endif		 
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */ 
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif
	
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 a_command)
{
	DIO_setPinValue(PA,RS,0); /* Instruction Mode RS=0 */
	DIO_setPinValue(PA,RW,0); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_setPinValue(PA,E,1); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0xF0) >> 4);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_setPinValue(PA,E,1); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_command & 0x0F);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8 a_data)
{
	DIO_setPinValue(PA,RS,1); /* Data Mode RS=1 */
	DIO_setPinValue(PA,RW,0); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_setPinValue(PA,E,1); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_data & 0xF0) >> 4);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_setPinValue(PA,E,1); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_data & 0x0F);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_setPinValue(PA,E,0); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char *Str_ptr)
{
	uint8 i = 0;
	while(Str_ptr[i] != '\0')
	{
		LCD_displayCharacter(Str_ptr[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 a_row,uint8 a_col)
{
	uint8_t Address=0;
	
	/* first of all calculate the required address */
	switch(a_row)
	{
		case 0:
				Address=a_col;
				break;
		case 1:
				Address=a_col+0x40;
				break;
		case 2:
				Address=a_col+0x10;
				break;
		case 3:
				Address=a_col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const char *Str_ptr)
{
	LCD_goToRowColumn(a_row,a_col); /* go to to the required LCD position */
	LCD_displayString(Str_ptr); /* display the string */
}

void LCD_intgerToString(uint32_t a_data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(a_data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}
