/*
 * Light.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Light.c
 *        \brief  Light Intensity using PWM
 *
 *      \details  API functions for Light control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Light.h"
#include "../../MCAL/Timer0/Timer0_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../SERVICES/Admin/Admin.h"
#include "../Menu/Menu.h"
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
void Light_Main(void)
{
	u8 Local_u8Choice = 0, Local_u8Mode = 0 ;

	while(1)
	{
		LCD_voidClearScreen();
		LCD_voidSendString((u8*)"1.Light ON/OFF ");
		LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
		LCD_voidSendString((u8*)"2.Auto Light ");
		LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);
		LCD_voidSendString((u8*)"3.Control Light");
		LCD_voidSendString((u8*)"4. Menu ");

		Local_u8Mode = Admin_u8GetChoice();
		switch(Local_u8Mode)
		{
		case MENU_CHOICE1:
			Light_vClick();

			break;
		case MENU_CHOICE2:
			ADC_vStartConversion(ADC_CHANNEL1);
			Light_vSenseIntensity();
			break;
		case MENU_CHOICE3:
			Admin_vSendProadcast((u8*)"Enter Light Intensity Value");
			BTH_vSendText((u8*)"Enter Light Intensity (0->10)");
			Local_u8Choice = Admin_u8GetChoice();
			Light_vCtrlIntensity(Local_u8Choice);
			break;
		case MENU_CHOICE4:
			break;
		default:
			BTH_vSendText((u8*)"Wrong Choice");
			break;
		}
		if(Local_u8Mode == MENU_CHOICE4)
			break;
	}

}


void Light_vInit(void)
{
	LED_voidInit(LIGHT_PORT, HOME_LIGHT1_PIN);
	LED_voidInit(LIGHT_PORT, HOME_LIGHT2_PIN);


}


/******************************************************************************
 * @Fn          -Light_vCtrlIntensity
 * @brief       -Set light Intensity value
 * @param [in]  -Copy_u8Intensity : light intensity options from 0 to 10
 * @return      -none
 *******************************************************************************/

void Light_vCtrlIntensity(u8 Copy_u8Intensity)
{
	TIMER0_voidStart();
	if(Copy_u8Intensity <= 10)
	{
		TIMER0_voidSetCompareVal((Copy_u8Intensity*10*255)/100);
	}else
	{
		BTH_vSendText((u8*)"Wrong Value");
	}
}

void Light_vClick(void)
{
	TIMER0_voidStop();

	LED_voidToggle(LIGHT_PORT, HOME_LIGHT1_PIN);
	if(DIO_u8GetPinLevel(LIGHT_PORT, HOME_LIGHT1_PIN) == HIGH)
		Admin_vSendProadcast((u8*)"Light is ON");
	else if (DIO_u8GetPinLevel(LIGHT_PORT, HOME_LIGHT1_PIN) == LOW)
		Admin_vSendProadcast((u8*)"Light is OFF");

}

/******************************************************************************
 * @Fn          -Light_vOpen
 * @brief       -Open door
 * @param [in]  -none
 * @return      -none
 *******************************************************************************/
void Light_vOpen(void)
{
	TIMER0_voidStop();

		LED_voidInit(LIGHT_PORT, HOME_LIGHT1_PIN);
		LED_voidInit(LIGHT_PORT, HOME_LIGHT2_PIN);
		LED_voidTurnOn(LIGHT_PORT, HOME_LIGHT1_PIN);

}

/******************************************************************************
 * @Fn          -Light_vClose
 * @brief       -Close door
 * @param [in]  -Copy_u8PortId : PORTx where x can be (A-->D) to select Light peripheral
 * @param [in]  -Copy_u8PinId : set pin number to read (0-->7)
 * @return      -none
 *******************************************************************************/

void Light_vClose(void)
{
	TIMER0_voidStop();
	LED_voidTurnOff(LIGHT_PORT, HOME_LIGHT1_PIN);

}
/******************************************************************************
 * @Fn          -Light_vOpen_ms
 * @brief       - Close Light on specific PIN for duration in ms
 * @param [in]  -none
 * @return      -none
 *******************************************************************************/

void Light_vOpen_ms(u8 Copy_u8Duration)
{
	TIMER0_voidStop();
	LED_voidTurnOn_ms(LIGHT_PORT, HOME_LIGHT1_PIN, Copy_u8Duration);
}
/******************************************************************************
 * @Fn          -Light_vClose_ms
 * @brief       -Close door for duration in ms
 * @param [in]  -Copy_u8Duration
 * @return      -none
 *******************************************************************************/

void Light_vClose_ms( u8 Copy_u8Duration)
{
	TIMER0_voidStop();
	LED_voidInit(LIGHT_PORT, HOME_LIGHT1_PIN);
	LED_voidTurnOff_ms(LIGHT_PORT, HOME_LIGHT1_PIN, Copy_u8Duration);

}




void Light_vSenseIntensity(void)
{
	f32 Local_f32LightVal;
	_delay_ms(50);

	Local_f32LightVal = Light_f32ReadLDR();
	u8 Local_u8Intensity = (u8)(10-((f32)(Local_f32LightVal*10)/LDR_RANGE));
	Light_vCtrlIntensity(Local_u8Intensity);

}

f32 Light_f32ReadLDR(void)
{
	u16 Local_u16DigitalVal;
	f32 Local_f32AnalogVal, Local_f32LDRVal;
	Local_u16DigitalVal = ADC_u16GetDigitalVal(ADC_CHANNEL1);
	Local_f32AnalogVal = (f32)(Local_u16DigitalVal * ADC_REF_VOLTAGE)/ADC_RESOLUTION;
	Local_f32LDRVal = ( Local_f32AnalogVal * LDR_RANGE)/ADC_REF_VOLTAGE;
	return Local_f32LDRVal;

}

/**********************************************************************************************************************
 *  END OF FILE: Light.c
 *********************************************************************************************************************/


