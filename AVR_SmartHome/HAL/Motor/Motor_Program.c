/*
 * Motor_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Motor_Program.c
 *        \brief  Motor Driver
 *
 *      \details  API functions for Motor control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Motor_Private.h"
#include "Motor_Config.h"
#include "Motor_Interface.h"
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

void Motor_vInit(DIO_Port_t Copy_u8MotorPort)
{
	DIO_voidSetPinDirection(Copy_u8MotorPort, MOTOR_FORWARD_PIN, OUTPUT);
	DIO_voidSetPinDirection(Copy_u8MotorPort, MOTOR_BACKWARD_PIN, OUTPUT);


}

/******************************************************************************
 * @Fn          -Motor_vTurnOn
 * @brief       -Turn ON Led on specific PIN
 * @param [in]  -Copy_u8MotorPort : PORTx where x can be (A-->D) to select Motor peripheral
 * @param [in]  -Copy_u8MotorPin : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Motor_vTurnOnRight(DIO_Port_t Copy_u8MotorPort,DIO_Pin_t Copy_u8MotorPin)
{
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, HIGH);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);
}

void Motor_vTurnOnLeft(DIO_Port_t Copy_u8MotorPort,DIO_Pin_t Copy_u8MotorPin)
{
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, HIGH);
}

/******************************************************************************
 * @Fn          -Motor_vTurnOff
 * @brief       -Turn OFF Led on specific PIN
 * @param [in]  -Copy_u8MotorPort : PORTx where x can be (A-->D) to select Motor peripheral
 * @param [in]  -Copy_u8MotorPin : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Motor_vTurnOff(DIO_Port_t Copy_u8MotorPort,DIO_Pin_t Copy_u8MotorPin)
{
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);
}

/******************************************************************************
 * @Fn          -Motor_vTurnOff_ms
 * @brief       -Turn OFF Led on specific PIN for duration in ms
 * @param [in]  -Copy_u8MotorPort : PORTx where x can be (A-->D) to select Motor peripheral
 * @param [in]  -Copy_u8MotorPin : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Motor_vTurnOff_ms(DIO_Port_t Copy_u8MotorPort,DIO_Pin_t Copy_u8MotorPin, u16 Copy_u16Duration)
{
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);

	delay_ms(Copy_u16Duration);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, HIGH);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);

}
/******************************************************************************
 * @Fn          -Motor_vTurnOn_ms
 * @brief       -Turn ON Led on specific PIN for duration in ms
 * @param [in]  -Copy_u8MotorPort : PORTx where x can be (A-->D) to select Motor peripheral
 * @param [in]  -Copy_u8MotorPin : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Motor_vTurnOnRight_ms(DIO_Port_t Copy_u8MotorPort, DIO_Pin_t Copy_u8MotorPin, u16 Copy_u16Duration)
{

	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, HIGH);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);
	delay_ms(Copy_u16Duration);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);

}

void Motor_vTurnOnLeft_ms(DIO_Port_t Copy_u8MotorPort, DIO_Pin_t Copy_u8MotorPin, u16 Copy_u16Duration)
{

	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, HIGH);
	delay_ms(Copy_u16Duration);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin, LOW);
	DIO_voidSetPinLevel(Copy_u8MotorPort, Copy_u8MotorPin+1, LOW);

}

/******************************************************************************
 * @Fn          -Motor_u8ReadPort
 * @brief       -Read PORT Value
 * @param [in]  -Copy_u8MotorPort : PORTx where x can be (A-->D) to select Motor peripheral
 * @return      -The input PORT value

 *******************************************************************************/

void Motor_vSetDirection(u8 Copy_u8Dircetion)
{

	switch(Copy_u8Dircetion)
	{
	case MOTOR_DIRECTION_FORWARD:
		DIO_voidSetPinLevel(MOTOR_PORT, MOTOR_FORWARD_PIN, HIGH);
		DIO_voidSetPinLevel(MOTOR_PORT, MOTOR_BACKWARD_PIN, LOW);
		break;
	case MOTOR_DIRECTION_BACKWARD:
		DIO_voidSetPinLevel(MOTOR_PORT, MOTOR_FORWARD_PIN, LOW);
		DIO_voidSetPinLevel(MOTOR_PORT, MOTOR_BACKWARD_PIN, HIGH);
		break;
	default:
		break;
	}

}

/**********************************************************************************************************************
 *  END OF FILE: Motor_Program.c
 *********************************************************************************************************************/


