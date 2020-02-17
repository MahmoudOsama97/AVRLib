 /******************************************************************************
 *
 * Module: DIO
 *
 * File Name: dio.c
 *
 * Description: Source file for the dio AVR driver
 *
 * Author: Ventor
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "dio.h"

/*******************************************************************************
 *                              MACROS                                     *
 *******************************************************************************/
#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)

/*******************************************************************************
 *                       GLOBAL  VARIABLES                                     *
 *******************************************************************************/

/* Define Array of pointers to hold all registers */
volatile  uint8_t * g_DIO_OutRegisters [4] = {PORTA_Register, PORTB_Register, PORTC_Register, PORTD_Register};
volatile  uint8_t * g_DIO_InRegisters  [4] = {PINA_Register , PINB_Register , PINC_Register , PIND_Register };
volatile  uint8_t * g_DIO_DirRegisters [4] = {DDRA_Register , DDRB_Register , DDRC_Register , DDRD_Register };


/*******************************************************************************
 *                     APIs IMPLEMENTATIONS                          *
 *******************************************************************************/

/* IO Pins */
void DIO_setPinValue(uint8_t a_u8PortIdCopy , uint8_t a_u8PIdCopy, uint8_t a_u8PinValCopy)
{
	/* Make sure that the P ID and Pin ID are in the valid range */
	if ((a_u8PortIdCopy <= PD) && (a_u8PIdCopy <= PIN7))
	{
		if (a_u8PinValCopy == HIGH)
		{
			SET_BIT(*g_DIO_OutRegisters[a_u8PortIdCopy],a_u8PIdCopy);
		}
		
		else if (a_u8PinValCopy == LOW)
		{
			CLR_BIT(*g_DIO_OutRegisters[a_u8PortIdCopy],a_u8PIdCopy);
		}
	
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

uint8_t DIO_getPinValue(uint8_t u8PortIdCopy, uint8_t a_u8PIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	uint8_t u8ResultLocal;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PD) && (a_u8PIdCopy <= PIN7))
	{
		u8ResultLocal= GET_BIT(*g_DIO_InRegisters[u8PortIdCopy],a_u8PIdCopy);
	}
	
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF;
	}
	
	return u8ResultLocal;
}

void DIO_setPinDirection (uint8_t u8PortIdCopy, uint8_t a_u8PIdCopy, uint8_t u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PD) && (a_u8PIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			SET_BIT(*g_DIO_DirRegisters[u8PortIdCopy],a_u8PIdCopy);		
		}
		
		else if ( u8PinDirCopy == INPUT )
		{
			CLR_BIT(*g_DIO_DirRegisters[u8PortIdCopy],a_u8PIdCopy);
		}
		
		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}
	
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}


/* IO Ports */
void DIO_setPortDirection (uint8_t u8PortId, uint8_t u8PortDir)
{
	/* Check on the Required PORT Number */
	if (u8PortId <= PD)
	{
		*g_DIO_DirRegisters[u8PortId] = u8PortDir;
	}
	
	else
	{
		/* Wrong Port ID */
	}
}

void DIO_setPortValue (uint8_t u8PortId, uint8_t u8PortVal)
{
	/* Check on the Required PORT Number */
	if (u8PortId <= PD)
	{
		*g_DIO_OutRegisters[u8PortId] = u8PortVal;
	}
	
	else
	{
		/* Wrong Port ID */
	}
}
