/*
 * DIO_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "DIO_Private.h"
#include "DIO_Config.h"
#include "DIO_Interface.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/******************************************************************************
 * @Fn          -DIO_u8GetPinLevel
 * @brief       -Read specific Copy_u8PortId Pin value
 * @param [in]  -PinId : to select DIO channel Compose from Copy_u8PortId , Copy_u8PinId
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read
 * @return      -The Reading value of the input pin
 *******************************************************************************/
DIO_Level_t DIO_u8GetPinLevel(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{
	DIO_Level_t Local_u8Level = 0;
	switch(Copy_u8PortId)
	{
	case PORTA:
		Local_u8Level = GET_BIT(PORTA_REG,Copy_u8PinId);
		break;
	case PORTB:
		Local_u8Level = GET_BIT(PORTB_REG,Copy_u8PinId);
		break;
	case PORTC:
		Local_u8Level = GET_BIT(PORTC_REG,Copy_u8PinId);
		break;
	case PORTD:
		Local_u8Level = GET_BIT(PORTD_REG,Copy_u8PinId);
		break;

	}
	return Local_u8Level;
}
/******************************************************************************
 * @Fn          -DIO_voidSetPinLevel
 * @brief       -Write value on specific PIN
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @param [in]  -Copy_u8Level : Pin value
 * @return      -none
 *******************************************************************************/

void DIO_voidSetPinLevel(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, DIO_Level_t Copy_u8Level)
{
	/* input validation */
	if(Copy_u8PortId > PORTD  || Copy_u8PinId > PIN7)
	{
		/* Do nothing because input is not valid */
	}
	else
	{
		switch (Copy_u8Level)
		{
		case HIGH:
			switch(Copy_u8PortId)
			{
			case PORTA:
				SET_BIT(PORTA_REG,Copy_u8PinId);
				break;
			case PORTB:
				SET_BIT(PORTB_REG,Copy_u8PinId);
				break;
			case PORTC:
				SET_BIT(PORTC_REG,Copy_u8PinId);
				break;
			case PORTD:
				SET_BIT(PORTD_REG,Copy_u8PinId);
				break;
			default:
				break;
			}
			break;
			case LOW:
				switch(Copy_u8PortId)
				{
				case PORTA:
					CLEAR_BIT(PORTA_REG,Copy_u8PinId);
					break;
				case PORTB:
					CLEAR_BIT(PORTB_REG,Copy_u8PinId);
					break;
				case PORTC:
					CLEAR_BIT(PORTC_REG,Copy_u8PinId);
					break;
				case PORTD:
					CLEAR_BIT(PORTD_REG,Copy_u8PinId);
					break;
				default:
					break;
				}
				break;
				default:
					break;
		}
	}

}

/******************************************************************************
 * @Fn          -DIO_u8ReadPort
 * @brief       -Read PORT Value
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @return      -The input PORT value

 *******************************************************************************/

u8 DIO_u8ReadPort(DIO_Port_t Copy_u8PortId)
{

	u8 Local_u8Value = 0;
	switch(Copy_u8PortId)
	{
	case PORTA:
		Local_u8Value = PINA_REG;
		break;
	case PORTB:
		Local_u8Value = PINB_REG;
		break;
	case PORTC:
		Local_u8Value = PINC_REG;
		break;
	case PORTD:
		Local_u8Value = PIND_REG;
		break;
	default:
		break;
	}
	return Local_u8Value;
}

/******************************************************************************
 * @Fn          -DIO_voidWritePort
 * @brief       -Write value on PORT
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Value : PIN value
 * @return      -none

 *******************************************************************************/

void DIO_voidWritePort(DIO_Port_t Copy_u8PortId, u8 Copy_u8Value)
{

	/* input validation */
	if(Copy_u8PortId > PORTD)
	{
		// Do nothing input is not valid
	}
	else
	{
		switch(Copy_u8PortId)
		{
		case PORTA:
			PORTA_REG = Copy_u8Value;
			break;
		case PORTB:
			PORTB_REG = Copy_u8Value;
			break;
		case PORTC:
			PORTC_REG = Copy_u8Value;
			break;
		case PORTD:
			PORTD_REG = Copy_u8Value;
			break;
		default:
			break;
		}
	}

}

/******************************************************************************
 * @Fn          -DIO_voidWritePins
 * @brief       -Write value on specific Pins
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8PinId : set pin number to start write (0-->7)
 * @param [in]  -Copy_u8Value : Pin value
 * @return      -none
 *******************************************************************************/

void DIO_voidWritePins(DIO_Port_t Copy_u8PortId, DIO_Pin_t Copy_u8StPin,u8 Copy_u8Length, u8 Copy_u8Value)
{

	/* input validation */
	if(Copy_u8PortId > PORTD)
	{
		// Do nothing input is not valid
	}
	else
	{
		switch(Copy_u8PortId)
		{
		case PORTA:
			ASSIGN_BITS(PORTA_REG,Copy_u8StPin,Copy_u8Length,Copy_u8Value);
			break;
		case PORTB:
			ASSIGN_BITS(PORTB_REG,Copy_u8StPin,Copy_u8Length,Copy_u8Value);
			break;
		case PORTC:
			ASSIGN_BITS(PORTC_REG,Copy_u8StPin,Copy_u8Length,Copy_u8Value);
			break;
		case PORTD:
			ASSIGN_BITS(PORTD_REG,Copy_u8StPin,Copy_u8Length,Copy_u8Value);
			break;
		default:
			break;
		}
	}

}

/******************************************************************************
 * @Fn          -DIO_voidTogglePin
 * @brief       -Toggle value on specific Pin
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void DIO_voidTogglePin(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{

	/* input validation */
	if(Copy_u8PortId > PORTD  || Copy_u8PinId > PIN7)
	{
		/* Do nothing because input is not valid */
	}
	else
	{

		switch(Copy_u8PortId)
		{
		case PORTA:
			TOGGLE_BIT(PORTA_REG,Copy_u8PinId);
			break;
		case PORTB:
			TOGGLE_BIT(PORTB_REG,Copy_u8PinId);
			break;
		case PORTC:
			TOGGLE_BIT(PORTC_REG,Copy_u8PinId);
			break;
		case PORTD:
			TOGGLE_BIT(PORTD_REG,Copy_u8PinId);
			break;
		default:
			break;
		}
	}

}

/******************************************************************************
 * @Fn          -DIO_voidTogglePort
 * @brief       -Toggle value on PORT
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @return      -none

 *******************************************************************************/

void DIO_voidTogglePort(DIO_Port_t Copy_u8PortId)
{

	/* input validation */
	if(Copy_u8PortId > PORTD)
	{
		// Do nothing input is not valid
	}
	else
	{
		switch(Copy_u8PortId)
		{
		case PORTA:
			TOGGLE_PORT(PORTA_REG);
			break;
		case PORTB:
			TOGGLE_PORT(PORTB_REG);
			break;
		case PORTC:
			TOGGLE_PORT(PORTC_REG);
			break;
		case PORTD:
			TOGGLE_PORT(PORTD_REG);
			break;
		default:
			break;
		}
	}

}

/******************************************************************************
 * @Fn          -DIO_voidSetPinDirection
 * @brief       -Set Pin direction on PORT
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @param [in]  -Copy_u8Direction :  value of pin direction
 * @return      -none
 *******************************************************************************/

void DIO_voidSetPinDirection(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, DIO_Level_t Copy_u8Direction)
{
	/*input validation*/
	if(Copy_u8PortId > PORTD || Copy_u8PinId > PIN7)
	{
		//Do Nothing
	}
	else
	{
		switch(Copy_u8Direction)
		{
		case INPUT:
			switch(Copy_u8PortId)
			{
			case PORTA:
				CLEAR_BIT(DDRA_REG,Copy_u8PinId);
				break;
			case PORTB:
				CLEAR_BIT(DDRB_REG,Copy_u8PinId);
				break;
			case PORTC:
				CLEAR_BIT(DDRC_REG,Copy_u8PinId);
				break;
			case PORTD:
				CLEAR_BIT(DDRD_REG,Copy_u8PinId);
				break;
			default:
				break;
			}
			break;
			case OUTPUT:
				switch(Copy_u8PortId)
				{
				case PORTA: /*Action*/
					SET_BIT(DDRA_REG,Copy_u8PinId);
					break;
				case PORTB:
					SET_BIT(DDRB_REG,Copy_u8PinId);
					break;
				case PORTC:
					SET_BIT(DDRC_REG,Copy_u8PinId);
					break;
				case PORTD:
					SET_BIT(DDRD_REG,Copy_u8PinId);
					break;
				default:
					break;
				}
				break;
				default:
					break;
		}
	}
}


/******************************************************************************
 * @Fn          -DIO_voidSetPortDirection
 * @brief       -Set Port direction
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select DIO peripheral
 * @param [in]  -Copy_u8Direction : value of port direction
 * @return      -none
 *******************************************************************************/

void DIO_voidSetPortDirection(DIO_Port_t Copy_u8PortId, u8 Copy_u8Direction)
{
	/*input validation*/
	if(Copy_u8PortId > PORTD)
	{
		//Do Nothing
	}
	else
	{
		switch(Copy_u8PortId)
		{
		case PORTA:
			DDRA_REG = Copy_u8Direction;
			break;
		case PORTB:
			DDRB_REG = Copy_u8Direction;
			break;
		case PORTC:
			DDRC_REG = Copy_u8Direction;
			break;
		case PORTD:
			DDRD_REG = Copy_u8Direction;
			break;
		default:
			break;
		}
	}
}
/**********************************************************************************************************************
 *  END OF FILE: DIO_Program.c
 *********************************************************************************************************************/


