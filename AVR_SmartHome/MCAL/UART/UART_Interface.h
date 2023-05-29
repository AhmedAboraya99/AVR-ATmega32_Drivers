/*
 * UART_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  UART_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_UART_INTERFACE_H_
#define MCAL_UART_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "UART_Private.h"
#include "UART_Config.h"
#include "../GINT/GINT_Interface.h"
#include"../DIO/DIO_Interface.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
static inline u16 get_myubrr() {
    return ((u16)((((u32)F_CPU * (GET_BIT(UCSRA_REG, UCSRA_U2X) + 1)) / (16UL * (u32)UART_BAUDRATE)) - 1));
}
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void UART_voidInit(u16 Copy_u16Ubrr);
void UART_voidSendData(u8 Copy_u8Data);
void UART_voidSendString(u8* Copy_pu8Data);
u8 UART_voidReceiveData(void);
void UART_voidReceiveString(u8* Copy_pu8Data);
void UART_voidClear(void);
void UART_voidSetRXC_CallBack(void (*UART_pRXC_CallBack)(void));


//API-Types


#define MYUBRR  (u16)(UART_OPERATION_SELECTION == UART_ASYNCHRONOUS_OPERATION ?\
		((((u32) F_CPU* (GET_BIT(UCSRA_REG,UCSRA_U2X)+1) ) /(16UL  * UART_BAUDRATE ))-1)\
		:((((u32) F_CPU* ) /(2UL  * UART_BAUDRATE ))-1))


#endif /* MCAL_UART_UARTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: UART_Interface.h
 *********************************************************************************************************************/








