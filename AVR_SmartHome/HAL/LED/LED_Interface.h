/*
 * LED_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LED_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void LED_voidInit(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void LED_voidTurnOn(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void LED_voidTurnOff(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void LED_voidToggle(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);

void LED_voidTurnOn_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u16 Copy_u16Duration);
void LED_voidTurnOff_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u16 Copy_u16Duration);
void LED_voidToggle_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u16 Copy_u16Duration);
void LED_voidTogglePort(DIO_Port_t Copy_u8PortId);


//API-Types


#endif /* HAL_LED_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: LED_Interface.h
 *********************************************************************************************************************/








