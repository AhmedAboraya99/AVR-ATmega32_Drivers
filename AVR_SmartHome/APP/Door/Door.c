/*
 * Door_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Door_Program.c
 *        \brief  Door Driver
 *
 *      \details  API functions for Door control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../HAL/Motor/Motor_Config.h"
#include "../../HAL/Motor/Motor_Interface.h"
#include "../Menu/Menu.h"
#include "../../SERVICES/Admin/Admin.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/US/US_Interface.h"
#include "Door.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
bool Global_DoorState = FALSE;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MACRO FUNCTIONS
 *********************************************************************************************************************/
#define DOOR_vOPEN()				Motor_vTurnOnRight_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS)
#define DOOR_vCLOSE()				Motor_vTurnOnLeft_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS)

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Door_Main(void)
{
	u8 Local_u8Mode = 0 ;



	while(1){
		LCD_voidClearScreen();

		LCD_voidSendString((u8*)"1.Open/CloseDoor ");

		LCD_voidSendString((u8*)" 2.Auto Door ");
		LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);
		LCD_voidSendString((u8*)" 3.Menu ");

		Local_u8Mode = Admin_u8GetChoice();
		switch(Local_u8Mode)
		{
		case MENU_CHOICE1:
			Door_vControl();
			break;

		case MENU_CHOICE2:
			US_vTrigger(US_PORT);

			break;

		case MENU_CHOICE3:
			break;

		default:
			BTH_vSendText((u8*)"Wrong Choice ");
			break;
		}
		if(Local_u8Mode == MENU_CHOICE3)
			break;
	}


}

void Door_vInit(void)
{
	DIO_voidSetPinDirection(DOOR_PORT, MOTOR_FORWARD_PIN, OUTPUT);
	DIO_voidSetPinDirection(DOOR_PORT, MOTOR_BACKWARD_PIN, OUTPUT);


}

void Door_vControl(void)
{

	TOGGLE_BIT(Global_DoorState, BIT0);
	if(Global_DoorState == TRUE)
	{
		Admin_vSendProadcast((u8*)"WELCOME HOME");
		//Door_vOpen();
		DOOR_vOPEN();
	}
	else if (Global_DoorState == FALSE)
	{
		Admin_vSendProadcast((u8*)"NICE TO MEET YOU");
		Motor_vTurnOnLeft_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);
		DOOR_vCLOSE();
		//Door_vClose();
	}

}
/******************************************************************************
 * @Fn          -Door_vOpen
 * @brief       -Open door
 * @param [in]  -none
 * @return      -none
 *******************************************************************************/

void Door_vOpen()
{
	Motor_vTurnOnRight_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);

}


/******************************************************************************
 * @Fn          -Door_vClose
 * @brief       -Close door
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select Door peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Door_vClose()
{
	Motor_vTurnOnLeft_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);
}



/******************************************************************************
 * @Fn          -Door_vOpen_ms
 * @brief       - Close Door on specific PIN for duration in ms
 * @param [in]  -none
 * @return      -none
 *******************************************************************************/

void Door_vOpen_ms(u8 Copy_u8Duration)
{
	Motor_vTurnOnRight_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);
	delay_ms(Copy_u8Duration);
	Motor_vTurnOnLeft_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);

}
/******************************************************************************
 * @Fn          -Door_vClose_ms
 * @brief       -Close door for duration in ms
 * @param [in]  -Copy_u8Duration
 * @return      -none
 *******************************************************************************/

void Door_vClose_ms( u8 Copy_u8Duration)
{
	Motor_vTurnOnLeft_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);
	delay_ms(Copy_u8Duration);
	Motor_vTurnOnRight_ms(DOOR_PORT, MOTOR_FORWARD_PIN, DOOR_DELAY_MS);

}


/**********************************************************************************************************************
 *  END OF FILE: Door_Program.c
 *********************************************************************************************************************/


