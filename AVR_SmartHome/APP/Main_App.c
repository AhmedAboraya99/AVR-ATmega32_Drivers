/*
 * main.c
 *
 *  Created on: Mar 29, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Main_App.h"
#include "../SERVICES/Admin/Admin.h"
#include "../SERVICES/SignUp/SignUp.h"
#include "../SERVICES/Login/Login.h"
#include "../APP/Door/Door.h"
#include "../APP/Fan/Fan.h"
#include "../APP/Light/Light.h"
#include "../APP/Menu/Menu.h"
#include "../HAL/Buzzer/Buzzer.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/TWI/TWI_Interface.h"
#include "../MCAL/Timer0/Timer0_Interface.h"
#include "../MCAL/Timer1/Timer1_Interface.h"
#include "../HAL/BTH/BTH_Interface.h"
#include "../HAL/US/US_Interface.h"
/**********************************************************************************************************************
 *  FUNCTIONS PROTOTYPE
 *********************************************************************************************************************/
void ADC_FanCallBack(void);
void ADC_LightCallBack(void);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

int main()
{

	ProjState_t Main_State = Login;
	TIMER0_voidInit();
	TIMER1_voidInit();
	TIMER0_voidStop();
	TIMER1_voidStop();



	TWI_vMasterInit(0, 400);

	BTH_vInit();
	Buzzer_vInit();
	LED_voidInit(LOGIN_LED_PORT, LOGIN_LED_PIN);
	LED_voidInit(ALERT_LED_PORT, ALERT_LED_PIN);

	LCD_voidInit();

	ADC_voidInit();
	ADC_vSetCallBack(&ADC_FanCallBack, ADC_CHANNEL0);
	ADC_vSetCallBack(&ADC_LightCallBack, ADC_CHANNEL1);
	ADC_vStopConversion();

	US_vInit();
	US_vTrigger(US_PORT);

	SignUp_vInit();
	Door_vInit();
	Light_vInit();




	while(1)
	{
		switch (Main_State){
			case Login:
				if(Login_Main()!=FALSE){Main_State = Menu;}
				else{Main_State = Login;}
				break;
			case Menu:
				Main_State = Menu_Main();
				break;
			case Door:
				Door_Main();
				Main_State=Menu;
				break;
			case Light:
				Light_Main();
				Main_State=Menu;
				break;
			case Fan:
				Fan_Main();
				Main_State=Menu;
				break;
			case Admin:
				Admin_Main();
				Main_State=Menu;
				break;

			default:
				Main_State=Menu;
				break;
			}
	}

}

void ADC_FanCallBack()
{
	Fan_vSenseTemp();
}
void ADC_LightCallBack()
{
	Light_vSenseIntensity();
}
