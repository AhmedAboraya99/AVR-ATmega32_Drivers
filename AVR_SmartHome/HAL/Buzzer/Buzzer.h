/*
 * Buzzer.h
 *
 *  Created on: May 3, 2023
 *      Author: ahmed
 */


/**
 * @file Buzzer.h
 * @brief Buzzer driver header file
 */

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"

/****************************************
 * @brief Initializes the buzzer port as an output and clears the pin initially.
 *
 * @return None
 ****************************************/
void Buzzer_vInit(void);

/****************************************
 * @brief Generates a tone on the buzzer with the given frequency and duration.
 *
 * This function generates a tone on a buzzer connected to the microcontroller using
 * timer-controlled pulse width modulation (PWM). The Copy_u16Frequency parameter
 * specifies the frequency of the tone in Hz, and the Copy_u16Duration parameter
 * specifies the duration of the tone in ms.
 *
 * @param[in] Copy_u16Frequency Frequency of the tone in Hz
 * @param[in] Copy_u16Duration Duration of the tone in ms
 *
 * @return None
 *****************************************/

void Buzzer_vBeep(u16 Copy_u16Frequency, u16 Copy_u16Duration);


#define BUZZER_PORT 	PORTB // Port connected to buzzer
#define BUZZER_DDR 		DDRB_REG // Data direction register for buzzer port
#define BUZZER_PIN 		PIN1 // Pin connected to buzzer




#endif /* HAL_BUZZER_H_ */
