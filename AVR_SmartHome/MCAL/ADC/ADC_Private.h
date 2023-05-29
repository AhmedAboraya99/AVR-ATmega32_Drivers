/*
 * ADC_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_ADC_PRIVATE_H_
#define MCAL_ADC_PRIVATE_H_

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

 /*ADC Multiplexer Selection Register*/
#define ADCMUX_REG	*((volatile u8*) 0x27)
/*Bits 7:6 – REFSn: Reference Selection [n = 1:0]*/
#define ADCMUX_REFS0		6
#define ADCMUX_REFS1		7
/*Bit 5 – ADLAR: ADC Left Adjust Result*/
#define ADCMUX_ADLAR		5
#define ADCMUX_MUXn			0

/*ADC Control and Status Register A*/
#define ADCSRA_REG	*((volatile u8*) 0x26)
/*Bit 7 – ADEN: ADC Enable*/
#define ADCSRA_ADEN		7
/*Bit 6 – ADSC: ADC Start Conversion*/
#define ADCSRA_ADSC		6

/*Bit 5 – ADATE: ADC Auto Trigger Enable*/
#define ADCSRA_ADATE	5
/*Bit 4 – ADIF: ADC Interrupt Flag*/
#define ADCSRA_ADIF		4
/*Bit 3 – ADIE: ADC Interrupt Enable*/
#define ADCSRA_ADIE		3

/*Bits 0:2 – ADPS: ADC Prescaler Select*/
#define ADCSRA_ADPS0		0
#define ADCSRA_ADPS1		1
#define ADCSRA_ADPS2		2


/*ADCL – ADC Data Register Low */
#define ADCL_REG	*((volatile u8*) 0x24)
/*ADCH – ADC Data Register High */
#define ADCH_REG	*((volatile u8*) 0x25)

#define ADCLH_REG	*((volatile u16*) 0x24)

/* special function I/O register */
#define SFIOR_REG	*((volatile u16*) 0x50)
/* Auto trigger source select */
#define SFIOR_ADTS0			5
#define SFIOR_ADTS1			6
#define SFIOR_ADTS2			7

#endif /* MCAL_ADC_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: ADC.h
 *********************************************************************************************************************/


