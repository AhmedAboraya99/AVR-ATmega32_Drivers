/*
 * UART_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_Config.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_UART_CONFIG_H_
#define MCAL_UART_CONFIG_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


//@ref UART_Mode_define
enum {
 UART_MODE_TX		=	0b01,	//TXEN = 1
 UART_MODE_RX		=	0b10,	//RXEN = 1
 UART_MODE_TX_RX	=	0b11
} UART_Mode_t;
#define UART_MODE_SELECTION		UART_MODE_TX_RX

//Bit UCSRC UMSEL: UART mode selection
enum{
 UART_ASYNCHRONOUS_OPERATION	=  0b0,
 UART_SYNCHRONOUS_OPERATION		=  0b1

}UART_eOPERATION;
#define	UART_OPERATION_SELECTION	UART_ASYNCHRONOUS_OPERATION
//@ref BaudRate_define

enum {
	UART_BAUDRATE_2400		=		2400,
	UART_BAUDRATE_4800		= 		4800,
	UART_BAUDRATE_9600		=		9600,
	UART_BAUDRATE_14400		=		14400,
	UART_BAUDRATE_19200		=		19200,
	UART_BAUDRATE_57600		=		57600,
	UART_BAUDRATE_76800		=		76800,
	UART_BAUDRATE_115200	=		115200,
	UART_BAUDRATE_230400	=		230400,
	UART_BAUDRATE_460800	=		460800,
	UART_BAUDRATE_921600	=		921600,
	UART_BAUDRATE_2250000	=		2250000,
	UART_BAUDRATE_4500000	=		4500000,
}UART_eBaudRate;

#define UART_BAUDRATE				UART_BAUDRATE_76800



// @ref USART_Speed_define

enum{

	// Bit 1 - U2X: Double the USART Transmission Speed
	UART_SPEED_NORMAL	=  0b0,
	UART_SPEED_DOUBLE	=  0b1,

}UART_Speed_t;

#define UART_SPEED_SELECTION		UART_SPEED_NORMAL

// @ref Payload_Length_define

//Bit 12 M: Word length
enum{
	UART_PAYLOAD_LENGTH_5B	=  	0b00,
	UART_PAYLOAD_LENGTH_6B	=  	0b01,
	UART_PAYLOAD_LENGTH_7B	=  	0b10,
	UART_PAYLOAD_LENGTH_8B	=  	0b11,
	UART_PAYLOAD_LENGTH_9B 	=	0b111

}UART_Payload_t;

#define UART_PAYLOAD_SELECTION		UART_PAYLOAD_LENGTH_8B

//@ref Parity_define
//Bit 10 PCE: Parity control enable
//Bit 9 PS: Parity selection
enum{
  UART_NONE_PARITY		=  0b00,
  UART_EVEN_PARITY		=  0b10,
  UART_ODD_PARITY		=  0b11

}UART_Parity_t;

#define UART_PARITY_SELECTION	UART_NONE_PARITY
//@ref StopBits_define
//Bits 3 USBS: STOP bits
enum{
  UART_1_STOPBIT		=  0b0,
  UART_2_STOPBIT		=  0b1,

}UART_StopBit_t;
#define UART_STOPBIT_SELECTION	UART_1_STOPBIT

//@ref IRQ_Enable_define
//Bit 7 - RXCIE: RX Complete Interrupt Enable
//Bit 6 - TXCIE: TX Complete Interrupt Enable
//Bit 5 - UDRIE: USART Data Register Empty Interrupt Enable

enum{
  UART_IRQ_DISABLE				=  	0b000,
  UART_IRQ_ENABLE_UDRE			=  	0b001,
  UART_IRQ_ENABLE_TXC			=  	0b010,
  UART_IRQ_ENABLE_UDRE_TXC		= 	0b011,
  UART_IRQ_ENABLE_RXC			=  	0b100,
  UART_IRQ_ENABLE_UDRE_RXC		=	0b101,
  UART_IRQ_ENABLE_UDRE_TXC_RXC	=	0b111,

}UART_IRQ_t;

#define UART_IRQ_SOURCE		UART_IRQ_DISABLE




#endif /* MCAL_UART_CONFIG_H_ */
