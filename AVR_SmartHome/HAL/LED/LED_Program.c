/*
 * LED_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  LED_Program.c
 *        \brief  LED Driver
 *
 *      \details  API functions for LED control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "LED_Config.h"
#include "LED_Interface.h"
#include "LED_Private.h"
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
void LED_voidInit(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{
	DIO_voidSetPinDirection(Copy_u8PortId, Copy_u8PinId, OUTPUT);
}

/******************************************************************************
 * @Fn          -LED_voidTurnOn
 * @brief       -Turn ON Led on specific PIN
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void LED_voidTurnOn(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, HIGH);
}


/******************************************************************************
 * @Fn          -LED_voidTurnOff
 * @brief       -Turn OFF Led on specific PIN
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void LED_voidTurnOff(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, LOW);
}

/******************************************************************************
 * @Fn          -LED_voidTurnOff_ms
 * @brief       -Turn OFF Led on specific PIN for duration in ms
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void LED_voidTurnOff_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u16 Copy_u16Duration)
{
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, LOW);
	delay_ms(Copy_u16Duration);
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, HIGH);

}
/******************************************************************************
 * @Fn          -LED_voidTurnOn_ms
 * @brief       -Turn ON Led on specific PIN for duration in ms
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void LED_voidTurnOn_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u16 Copy_u16Duration)
{
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, HIGH);
	delay_ms(Copy_u16Duration);
	DIO_voidSetPinLevel(Copy_u8PortId, Copy_u8PinId, LOW);

}
/******************************************************************************
 * @Fn          -LED_voidToggle
 * @brief       -Toggle value on specific Pin
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void LED_voidToggle(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId)
{

	DIO_voidTogglePin(Copy_u8PortId, Copy_u8PinId);

}
/******************************************************************
 * @Fn          -LED_voidTogglePort
 * @brief       -Toggle value on PORT
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select LED peripheral
 * @return      -none

 *******************************************************************************/

void LED_voidTogglePort(DIO_Port_t Copy_u8PortId)
{

	DIO_voidTogglePort(Copy_u8PortId);

}



/**********************************************************************************************************************
 *  END OF FILE: LED_Program.c
 *********************************************************************************************************************/


