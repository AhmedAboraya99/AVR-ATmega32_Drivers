/*
 * BTH_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  BTH_Program.c
 *        \brief  BTH Driver
 *
 *      \details  API functions for BTH control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BTH_Interface.h"
#include "../LCD/LCD_Interface.h"
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
void BTH_vInit()
{
	UART_voidInit(get_myubrr());
}

/******************************************************************************
 * @Fn          -BTH_vTurnOn
 * @brief       -Turn ON Bluetooth
 * @param [in]  -
 * @param [in]  -
 * @return      -none
 *******************************************************************************/

void BTH_vTurnOn()
{
	/* Set USART DIO Pins */
	DIO_voidSetPinDirection(PORTD, PIN0, INPUT);
	DIO_voidSetPinDirection(PORTD, PIN1, OUTPUT);
}


/******************************************************************************
 * @Fn          -BTH_vTurnOff
 * @brief       -Turn Off Bluetooth
 * @param [in]  -None
 * @return      -none
 *******************************************************************************/

void BTH_vTurnOff(void)
{
	/* Disable USART DIO Pins */
	DIO_voidSetPinDirection(PORTD, PIN0, OUTPUT);
	DIO_voidSetPinDirection(PORTD, PIN1, INPUT);
}

/******************************************************************************
 * @Fn          -BTH_vReceiveText
 * @brief       -
 * @param [in]  -Copy_pu8RxData
 * @return      -

 *******************************************************************************/

void BTH_vReceiveText(u8* Copy_pu8RxData)
{

	u8 Local_u8Received;

	LCD_voidGotoXY(LCD_LINE4,LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"             ");
	LCD_voidGotoXY(LCD_LINE4,LCD_POSITION_FIRST);
	 while(1)
	 {

		 Local_u8Received = UART_voidReceiveData();


			if(Local_u8Received == '\r' || Local_u8Received == '\n')
			{
				*(Copy_pu8RxData) = '\0';
				break;
			}
			else if( Local_u8Received == '\b')
			{

					Copy_pu8RxData--;

			}
			else if( Local_u8Received == 0){/* Do Nothing */}
			else
			{
				* (Copy_pu8RxData++) = Local_u8Received;
				LCD_voidSendData(Local_u8Received);

			}
		}

}

void BTH_vReceivePass(u8* Copy_pu8Pass)
{
	u8 Local_u8Received;

	LCD_voidGotoXY(LCD_LINE4,LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"             ");
	LCD_voidGotoXY(LCD_LINE4,LCD_POSITION_FIRST);
	 while(1)
	 {

		 Local_u8Received = UART_voidReceiveData();


			if(Local_u8Received == '\r' || Local_u8Received == '\n')
			{
				*(Copy_pu8Pass) = '\0';
				break;
			}
			else if( Local_u8Received == '\b')
			{

				Copy_pu8Pass--;

			}
			else if( Local_u8Received == 0){/* Do Nothing */}
			else
			{
				* (Copy_pu8Pass++) = Local_u8Received;
				LCD_voidSendData('*');

			}
		}
}



/******************************************************************************
 * @Fn          -BTH_vSendText
 * @brief       -
 * @param [in]  -Copy_pu8TxData
 * @return      -none

 *******************************************************************************/

void BTH_vSendText( u8* Copy_pu8TxData)
{

	UART_voidSendString(Copy_pu8TxData);
	UART_voidSendString((u8*)" \n");
}




/**********************************************************************************************************************
 *  END OF FILE: BTH_Program.c
 *********************************************************************************************************************/


