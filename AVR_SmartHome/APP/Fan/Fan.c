/*
 * Fan.c
 *
 *  Created on: Apr 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fan.h"
#include "../../MCAL/Timer1/Timer1_Interface.h"

#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../HAL/Motor/Motor_Interface.h"
#include "../../SERVICES/Admin/Admin.h"
#include "../Menu/Menu.h"
/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/

void Fan_Main(void)
{
	u8 Local_u8Choice = 0,  Local_u8Mode = 0 ;

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)"1.Auto Fan ");
	LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"2.Manual Fan  ");
	LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);
	LCD_voidSendString((u8*)"3.Turn Fan Off");

	Local_u8Mode = Admin_u8GetChoice();



	switch(Local_u8Mode)
	{
		case MENU_CHOICE1:

			ADC_vStartConversion(ADC_CHANNEL0);
			break;
		case MENU_CHOICE2:
			Admin_vSendProadcast((u8*)"Set Fan Speed");
			BTH_vSendText((u8*)"\n Enter Fan Speed(0->10)");
			Local_u8Choice = Admin_u8GetChoice();
			Fan_vSetSpeed(Local_u8Choice);
			break;
		case MENU_CHOICE3:
			Fan_vSetSpeed(0);
			break;
		default:
			LCD_voidClearScreen();
			BTH_vSendText((u8*)"Wrong Choice");
			break;
	}


}



/******************************************************************************
 * @Fn          -Fan_vSetSpeed
 * @brief       -Set Fan Speed value
 * @param [in]  -Copy_u8Speed : Fan Speed options from 0 to 10
 * @return      -none
 *******************************************************************************/

void Fan_vSetSpeed(u8 Copy_u8Speed)
{
	TIMER1_voidStart();
	if(Copy_u8Speed == 0)
	{
		ADC_vStopConversion();
		TIMER1_voidSetCompareVal((Copy_u8Speed*10*254)/100);
		DIO_voidSetPinLevel(FAN_PORT, FAN_PIN, LOW);
	}
	else if(Copy_u8Speed <= 10)
	{
		ADC_vStopConversion();
		TIMER1_voidSetCompareVal((Copy_u8Speed*10*254)/100);
	}
	else
	{
		BTH_vSendText((u8*)"Wrong Value");
	}
}

void Fan_vSenseTemp(void)
{
	TIMER1_voidStart();
	f32 Local_f32TempVal;
	_delay_ms(50);

	Local_f32TempVal = Fan_f32ReadTemp();
	TIMER1_voidSetCompareVal(Local_f32TempVal);

}

f32 Fan_f32ReadTemp(void)
{
	u16 Local_u16DigitalVal;
	f32 Local_f32AnalogVal, Local_f32TempVal;
	Local_u16DigitalVal = ADC_u16GetDigitalVal(ADC_CHANNEL0);
	Local_f32AnalogVal = (f32)(Local_u16DigitalVal * 5UL)/1024;
	Local_f32TempVal = Local_f32AnalogVal * (200/5);
	return Local_f32TempVal;

}

