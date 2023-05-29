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
#ifndef MCAL_TIMER1_PRIVATE_H_
#define MCAL_TIMER1_PRIVATE_H_

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
/*TCNT1 - Timer/Counter Register*/
#define TCNT1L_REG	*((volatile u8*)0x4C)
#define TCNT1H_REG	*((volatile u8*)0x4D)
#define TCNT1_REG	*((volatile u16*)0x4C)
/* OCR1 - Output Compare Register*/
#define OCR1AL_REG	*((volatile u8*)0x4A)
#define OCR1AH_REG	*((volatile u8*)0x4B)
#define OCR1A_REG	*((volatile u16*)0x4A)

#define OCR1BL_REG	*((volatile u8*)0x48)
#define OCR1BH_REG	*((volatile u8*)0x49)
#define OCR1B_REG	*((volatile u16*)0x48)
/*TCCR1 - Timer/Counter Control Register */
#define TCCR1A_REG	*((volatile u8*)0x4F)
#define TCCR1B_REG	*((volatile u8*)0x4E)

/* ICR1 - Output Compare Register*/
#define ICR1L_REG	*((volatile u8*)0x46)
#define ICR1H_REG	*((volatile u8*)0x47)
#define ICR1_REG	*((volatile u16*)0x46)

/*FOC1:- Force Output Compare*/
#define	TCCR1A_FOC1A 		3
#define	TCCR1A_FOC1B 		2

/*Waveform Generation Mode bit*/
#define TCCR1A_WGM10 	0
#define TCCR1A_WGM11 	1

#define TCCR1A_COM1B1		5
#define TCCR1A_COM1B0	 	4
#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0	 	6



#define TCCR1B_WGM12 		4
#define TCCR1B_WGM13 		3

#define TCCR1B_ICES1		6
#define TCCR1B_COM11		5
#define TCCR1B_COM10 		4

#define TCCR1B_CS12 		2
#define	TCCR1B_CS11 		1
#define TCCR1B_CS10	 		0


#define TIFR_REG   (*(volatile u8*)0x58) // TIFR register address

#define TIFR_OCF2   7 // Output Compare Flag 2 bit
#define TIFR_TOV2   6 // Timer/Counter 2 Overflow Flag bit
#define TIFR_ICF1   5 // Input Capture Flag 1 bit
#define TIFR_OCF1A  4 // Output Compare A Flag 1 bit
#define TIFR_OCF1B  3 // Output Compare B Flag 1 bit
#define TIFR_TOV1   2 // Timer/Counter 1 Overflow Flag bit
#define TIFR_OCF0   1 // Output Compare Flag 0 bit
#define TIFR_TOV0   0 // Timer/Counter 0 Overflow Flag bit

/*TIMSK - Timer/Counter Interrupt Mask Register*/
#define TIMSK1_REG	*((volatile u8*)0x59)
/*Bits 3,4 - OCIE1: Timer/CounterTimer/Counter1 Output Compare Match Interrupt Enable*/

#define TIMSK1_OCIE1B			3
#define TIMSK1_OCIE1A			4
/*Bit 2 - TOIE1: Timer/CounterTimer/Counter1 Overflow Interrupt Enable*/
#define TIMSK1_TOIE1			2

#define TIMSK1_ICRIE1			5
#endif /* MCAL_TIMER1_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIMER1_Private.h
 *********************************************************************************************************************/


