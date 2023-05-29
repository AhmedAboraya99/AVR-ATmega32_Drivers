/*
 * Menu.c
 *
 *  Created on: Apr 31, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Menu.h"
#include "../Door/Door.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/Motor/Motor_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../SERVICES/SignUp/SignUp.h"
#include "../Main_App.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../SERVICES/Admin/Admin.h"
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

ProjState_t Menu_Main(void)
{
	u8 Local_u8Option = 0;
	ProjState_t Local_u8State = Menu;
	_delay_ms(150);
	Admin_vSendProadcast((u8*)"Welcome to Home Menu");
	_delay_ms(1500);

		do{
			Local_u8Option = Menu_u8GetChoice();
			switch(Local_u8Option )
			{
			case MENU_CHOICE1:
				Admin_vSendProadcast((u8*)" Door Control ");

				Local_u8State = Door;
				break;

			case MENU_CHOICE2:

				Admin_vSendProadcast((u8*)" Light Intensity Control ");

				Local_u8State = Light;
				break;

			case MENU_CHOICE3:

				Admin_vSendProadcast((u8*)"Fan Control");

				Local_u8State = Fan;
				break;
			case MENU_CHOICE4:

				Admin_vSendProadcast((u8*)"Admin Panel");

				Local_u8State = Admin;
				break;
			default:
				Local_u8State = Menu;
				break;
			}
		}while(Local_u8State == Menu);

		return Local_u8State;
}



u8 Menu_u8GetChoice( void )
{
	u8  Local_u8Choice = 0 ;
	LCD_voidSendString((u8*)"Select Option: ");
	LCD_voidClearScreen();

	LCD_voidSendString((u8*)"1.DOOR ");

	LCD_voidSendString((u8*)"2.LIGHT ");
	LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"3.FAN ");
	LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"4.SUPERUSER ");

	Local_u8Choice = Admin_u8GetChoice();
	if(Local_u8Choice < 1  || Local_u8Choice > 4 )
	{
		Admin_vSendProadcast((u8*)" Select proper option ");
	}

	return Local_u8Choice ;
}


