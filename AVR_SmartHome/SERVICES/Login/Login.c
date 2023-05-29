/*
 * Login.c
 *
 *  Created on: Apr 31, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../Login/Login.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/Motor/Motor_Interface.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/Buzzer/Buzzer.h"
#include "../../SERVICES/SignUp/SignUp.h"
#include "../Admin/Admin.h"
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

bool Login_Main()
{

	u8  Local_u8Attempts = 0,  Local_u8PassFlag = FALSE;
	u8 Local_pu8Pswd [MAX_USER_INPUT], Local_pu8UserID[MAX_USER_INPUT];

	Admin_vSendProadcast((u8*)"Welcome to Home Login");



	while(1)
	{
		 // Receive user ID from USART
		Admin_vSendProadcast((u8*)"Enter Username");

		 BTH_vReceiveText(Local_pu8UserID);

		 // Receive user Password from USART
		Admin_vSendProadcast((u8*)"Enter Password");
		BTH_vReceivePass(Local_pu8Pswd);

		Local_u8PassFlag = Admin_u8CheckUser(Local_pu8UserID,Local_pu8Pswd);

		if(Local_u8PassFlag != FALSE)
		{
			LCD_voidClearScreen();
			Admin_vSendProadcast((u8*)"Successful Login");
			LCD_voidClearScreen();
			LCD_voidSendString((u8*)("Welcome "));
			LCD_voidSendString((u8*)Local_pu8UserID);
			LED_voidTurnOn_ms(LOGIN_LED_PORT, LOGIN_LED_PIN, 500);

			break;

		}
		else
		{

			Local_u8Attempts++;

			Admin_vSendProadcast((u8*)"Wrong ID or Password!");
			if(Local_u8Attempts == 3)
			{
				LED_voidTurnOn(ALERT_LED_PORT, ALERT_LED_PIN);

				Buzzer_vBeep(500, 1000);

				Admin_vSendProadcast((u8*)"Emsek 7arami !!");
				LED_voidTurnOff(ALERT_LED_PORT, ALERT_LED_PIN);
				Local_u8Attempts = 0;

			}
		}
	}
	return Local_u8PassFlag;

}


