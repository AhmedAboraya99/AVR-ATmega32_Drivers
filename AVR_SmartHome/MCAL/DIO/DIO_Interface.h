/*
 * DIO_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/STD_API.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO_Private.h"
#include "DIO_Config.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//@ pin_id_options
typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}DIO_Pin_t;

//@ port_id_options
typedef enum {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
}DIO_Port_t;

typedef enum {
	LOW,
	HIGH
}DIO_Level_t;

typedef enum {

    INPUT,
    OUTPUT

}DIO_PinDir_t;

typedef enum {

    INPUT_PORT = 0x00 ,
    OUTPUT_PORT = 0xFF

}DIO_PortDir_t;


typedef enum {
	LOW_PORT = 0x00,
	HIGH_PORT = 0xFF
}DIO_PortLevel_t;

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
//void DIO_voidInit(void);
void DIO_voidSetPinLevel(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, DIO_Level_t Copy_u8Level);
void DIO_voidSetPinDirection(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, DIO_Level_t Copy_u8Direction);
DIO_Level_t DIO_u8GetPinLevel(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void DIO_voidTogglePin(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);

void DIO_voidWritePins(DIO_Port_t Copy_u8PortId, DIO_Pin_t Copy_u8StPin,u8 Copy_u8Length, u8 Copy_u8Value);
void DIO_voidSetPortDirection(DIO_Port_t Copy_u8PortId, u8 Copy_u8Direction);
u8 DIO_u8ReadPort(DIO_Port_t Copy_u8PortId);
void DIO_voidWritePort(DIO_Port_t Copy_u8PortId, u8 Copy_u8Value);
void DIO_voidTogglePort(DIO_Port_t Copy_u8PortId);



//API-Types


#endif /* MCAL_DIO_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: DIO_Interface.h
 *********************************************************************************************************************/








