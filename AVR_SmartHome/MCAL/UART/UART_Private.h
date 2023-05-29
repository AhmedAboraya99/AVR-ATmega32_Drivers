/*
 * UART_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_UART_PRIVATE_H_
#define MCAL_UART_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//=======Private-Functions=======


/*UDR - USART I/O Data Register*/
/*USART Transmit / Receive Data Buffer*/
#define UDR_REG 			*((volatile u8*)0x2C)
/* UCSRA - USART Control and Status Register A*/
#define UCSRA_REG 			*((volatile u8*)0x2B)

/* UCSRA */

#define UCSRA_UDRE		5		//USART Data Register Empty
#define UCSRA_TXC		6		//USART Transmit Complete
#define UCSRA_RXC		7		//USART Receive Complete
#define UCSRA_U2X    	1
#define UCSRA_MPCM    	0

/*UCSRB - USART Control and Status Register B*/
#define UCSRB_REG 			*((volatile u8*)0x2A)

/* UCSRB */
#define UCSRB_RXCIE		7
#define UCSRB_TXCIE		6
#define UCSRB_UDRIE		5
#define UCSRB_RXEN		4		//USART Receive Enable
#define UCSRB_TXEN		3		//USART Transmit Enable
#define UCSRB_UCSZ2   	2
#define UCSRB_RXB8    	1
#define UCSRB_TXB8    	0
/*UCSRC - USART Control and Status Register C*/
#define UCSRC_REG 			*((volatile u8*)0x40)
/* UCSRC */
//Bits 2:1 - UCSZn: Character Size [n = 1:0]
#define UCSRC_UCSZ0   1
#define UCSRC_UCSZ1   2

#define UCSRC_USBS    3
#define UCSRC_UPM0    4
#define UCSRC_UPM1    5
#define UCSRC_UMSEL   6
#define UCSRC_URSEL   7
/*UBBRH - USART Baud Rate Register High*/
#define UBRRH_REG 			*((volatile u8*)0x40)

/*UBRRL - USART Baud Rate Register Low*/
#define UBRRL_REG 			*((volatile u8*)0x29)






#endif /* MCAL_UART_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: UART.h
 *********************************************************************************************************************/


