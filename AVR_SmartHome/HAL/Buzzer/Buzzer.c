/*
 * Buzzer.c
 *
 *  Created on: May 3, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Buzzer.h"
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Buzzer_vInit(void)
{
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT) ; // Set pin connected to buzzer as output
    DIO_voidSetPinLevel(BUZZER_PORT, BUZZER_PIN, LOW); // Clear pin initially
}

void Buzzer_vBeep(u16 Copy_u16Frequency, u16 Copy_u16Duration)
{
    //u16 Local_u16Delay = (F_CPU / (Copy_u16Frequency * 2)) - 1; // Calculate delay for given frequency
    u16 Local_u16Counter = Copy_u16Duration *2 / (Copy_u16Frequency ); // Calculate number of cycles for given duration
    for(u8 Local_Index = 0;Local_Index<Local_u16Counter;Local_Index++)
   {
	 DIO_voidSetPinLevel(BUZZER_PORT, BUZZER_PIN,HIGH); // Set pin to turn on buzzer
		 _delay_ms(Copy_u16Frequency); // Delay for half cycle
	DIO_voidSetPinLevel(BUZZER_PORT, BUZZER_PIN, LOW); // Clear pin to turn off buzzer
		 _delay_ms(Copy_u16Frequency); // Delay for half cycle
    }

}
