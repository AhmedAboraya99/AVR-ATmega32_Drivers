/*
 * UART_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define RXC_UART_INDEX 0 // Rx Complete
#define UDRE_UART_INDEX 1//Data Register Empty
#define TXC_UART_INDEX 2//Tx Complete

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (* GP_UART_IRQ_CallBack[3]) (void) ;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void UART_voidInit(u16 Copy_u16Ubrr)
{
	/* Set USART DIO Pins */
	DIO_voidSetPinDirection(PORTD, PIN0, INPUT);
	DIO_voidSetPinDirection(PORTD, PIN1, OUTPUT);


	//Define USART Baud Rate Register



	UBRRH_REG = (u8) ((Copy_u16Ubrr) >>8);
	UBRRL_REG = (u8) Copy_u16Ubrr;

	//Enable TX, RX
	ASSIGN_BITS(UCSRB_REG,UCSRB_TXEN,TWO_BITS,UART_MODE_SELECTION);

	/* Set frame format: 8data, 1stop bit */

    /* Set baud rate */
//    UBRRH_REG = (unsigned char)(Copy_u16Ubrr>>8);
//    UBRRL_REG = (unsigned char)Copy_u16Ubrr;
//    /* Enable receiver and transmitter */
//    UCSRB_REG = (1<<UCSRB_RXEN)|(1<<UCSRB_TXEN);
    /* Set frame format: 8data, 1stop bit */
    UCSRC_REG = (1<<UCSRC_URSEL)|(3<<UCSRC_UCSZ0);
	/* define parity mode */
//    u8 Local_u8TempUCSRC = 0;
//	ASSIGN_BITS(Local_u8TempUCSRC, UCSRC_UPM0,TWO_BITS,UART_PARITY_SELECTION);
//
//
//	/* Mode select between Asynchronous and Synchronous */
//	ASSIGN_BIT(Local_u8TempUCSRC, UCSRC_UMSEL, UART_OPERATION_SELECTION);
//
//	/* define character size */
//	ASSIGN_BITS(Local_u8TempUCSRC, UCSRC_UCSZ0, TWO_BITS, UART_PAYLOAD_SELECTION);
//
//
//	/* define number of Stop Bits */
//	ASSIGN_BIT(Local_u8TempUCSRC, UCSRC_USBS, UART_STOPBIT_SELECTION);
//
//	UCSRC_REG = Local_u8TempUCSRC;
	/* define UART speed */
	if(UART_OPERATION_SELECTION == UART_ASYNCHRONOUS_OPERATION)
		ASSIGN_BIT(UCSRA_REG,UCSRA_U2X, UART_SPEED_SELECTION);



	if(UART_PAYLOAD_SELECTION == UART_PAYLOAD_LENGTH_9B)
		SET_BIT(UCSRB_REG ,UCSRB_UCSZ2);

	//Enable or disable UART interrupt
	ASSIGN_BITS(UCSRB_REG,UCSRB_UDRIE, THREE_BITS,UART_IRQ_SOURCE);
	if(UART_IRQ_SOURCE != UART_IRQ_DISABLE)
	{

		GINT_voidEnable();
	}



}
void UART_voidSendData(u8 Copy_u8Data)
{
	/* Wait for empty transmit buffer */
	while(!GET_BIT(UCSRA_REG,UCSRA_UDRE) );
	/* Put data into buffer, sends the data */
	UDR_REG = Copy_u8Data;


}
void UART_voidSendString(u8* Copy_pu8Data)
{

	while (*Copy_pu8Data != '\0')
	{
		UART_voidSendData(*Copy_pu8Data++);
		_delay_ms(10);
	}
	// Wait for all data to be transmitted
	  while (!(UCSRA_REG & (1 << UCSRA_TXC)));


	_delay_ms(100);


}
u8 UART_voidReceiveData(void)
{


	if(UART_IRQ_SOURCE == UART_IRQ_DISABLE)
	{
		/* Wait for data to be received */
		while(!GET_BIT(UCSRA_REG,UCSRA_RXC));
	}


	/* Get and return received data from buffer */
	return UDR_REG;


}

//void UART_voidReceiveString(u8* Copy_pu8Data)
//{
//	u8 ReceivedData, DataIndex = 0;
//	do{
//		UART_voidReceiveData(&ReceivedData);
//		Copy_pu8Data[DataIndex++] = ReceivedData;
//	}while (ReceivedData != '\n');
//	*Copy_pu8Data = '\0';
//	_delay_ms(100);
//}

void UART_voidReceiveString(u8* Copy_pu8Data)
{
	u8 ReceivedData;
	u16 Index = 0;
	do
	{
		ReceivedData = UART_voidReceiveData();

			Copy_pu8Data[Index++] = ReceivedData;

		_delay_ms(10);
	} while (ReceivedData != '\n');

		Copy_pu8Data[Index] = '\0'; // Add null terminator to the end of the string


}

void UART_voidClear(void)
{
	u8 Local_u8Dummy;
	/* Wait for empty transmit buffer */
	while(GET_BIT( UCSRA_REG , UCSRA_RXC)) Local_u8Dummy = UDR_REG;



}

void UART_voidSetRXC_CallBack(void (*UART_pRXC_CallBack)(void))
{
	GP_UART_IRQ_CallBack[RXC_UART_INDEX] = UART_pRXC_CallBack;
}


// Define the RXC ISR function
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{

	GP_UART_IRQ_CallBack[RXC_UART_INDEX]();
}

/**********************************************************************************************************************
 *  END OF FILE: UART_Program.c
 *********************************************************************************************************************/


