/*
 * DIO_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_TIMER_PRIVATE_H_
#define MCAL_TIMER_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*TCNT0 – Timer/Counter Register*/
#define TCNT0_REG	*((volatile u8*)0x52)
/* OCR0 – Output Compare Register*/
#define OCR0_REG	*((volatile u8*)0x5C)

/*TCCR0 – Timer/Counter Control Register */
#define TCCR0_REG	*((volatile u8*)0x53)

/*FOC0: Force Output Compare*/
#define	TCCR0_FOC0 		7
/*Waveform Generation Mode bit*/
#define TCCR0_WGM00 	6
#define TCCR0_WGM01 	3

#define TCCR0_COM01		5
#define TCCR0_COM00 	4

#define TCCR0_CS02 		2
#define	TCCR0_CS01 		1
#define TCCR0_CS00	 	0

/*TIMSK – Timer/Counter Interrupt Mask Register*/
#define TIMSK0_REG	*((volatile u8*)0x59)

/*Bit 1 – OCIE0: Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable*/

#define TIMSK0_OCIE0		1
/*Bit 0 – TOIE0: Timer/CounterTimer/Counter0 Overflow Interrupt Enable*/
#define TIMSK0_TOIE0		0
#endif /* MCAL_TIMER_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Timer_Private.h
 *********************************************************************************************************************/


