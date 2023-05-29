/*
 * ADC_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  ADC_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*ADC_gpIRQCallBack[8])(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*********************************************************************************/
/* Function: ADC_voidInit			                        				    **/
/* I/P Parameters: Nothing									          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function initializes ADC								       	    **/
/*********************************************************************************/
void ADC_voidInit(void)
{



	/*choose reference volt*/
	ASSIGN_BITS(ADCMUX_REG, ADCMUX_REFS0, TWO_BITS,ADC_REFERENCE_SELECTION);
	/*ADC mode selection*/
	ASSIGN_BITS(ADCSRA_REG,ADCSRA_ADATE, TWO_BITS,ADC_MODE_SELECTION);
	/* Select Trigger Source */
	if(ADC_MODE_SELECTION == ADC_AUTO_TRIGGERING )
		ASSIGN_BITS(SFIOR_REG,SFIOR_ADTS0, THREE_BITS,ADC_TRIGGER_SOURCE);

	/* adjust right */
	ASSIGN_BIT(ADCMUX_REG, ADCMUX_ADLAR,ADC_ADJUST_SELECTION);

	/* Enable / Disable IRQ */
	ASSIGN_BIT(ADCSRA_REG, ADCSRA_ADIE, ADC_IRQ_ACTIVATION);
	if(ADC_IRQ_ACTIVATION == ADC_IRQ_ENABLE)
	{
		GINT_voidEnable();
	}

	/* Choose ADC Prescalar */
	ASSIGN_BITS(ADCSRA_REG, ADCSRA_ADPS0, THREE_BITS, ADC_PRESESCALAR_SELECTION);

	/* enables the ADC */
	ASSIGN_BIT(ADCSRA_REG, ADCSRA_ADEN, ADC_ACTIVATION);


}

/******************************************************************************
 * @Fn          -ADC_vStartConversion, ADC_vStopConversion
 * @brief       -Start and stop ADC conversion
 * @param [in]  -none
 * @return      -none
 *******************************************************************************/

void ADC_vStartConversion(ADC_Channel_t Copy_u8Channel)
{
	// Start ADC conversion on the selected input pin
	if(Copy_u8Channel <= ADC_CHANNEL9)
	{
		DIO_voidSetPinDirection(PORTA,Copy_u8Channel, INPUT_PORT);

		ASSIGN_BITS(ADCMUX_REG,ADCMUX_MUXn,FOUR_BITS,Copy_u8Channel);

		ASSIGN_BIT(ADCSRA_REG, ADCSRA_ADIE, ADC_IRQ_ACTIVATION);
		SET_BIT(ADCSRA_REG, ADCSRA_ADSC);
	}
}
void ADC_vStopConversion(void)
{
	CLEAR_BIT(ADCSRA_REG, ADCSRA_ADSC);
	ASSIGN_BIT(ADCSRA_REG, ADCSRA_ADIE, ADC_IRQ_DISABLE);

}

/******************************************************************************
 * @Fn          -ADC_vSetCallBack
 * @brief       -Set ADC Complete Conversion callback function
 * @param [in]  -Copy_vCallback
 * @return      -none
 *******************************************************************************/


void ADC_vSetCallBack(void (*Copy_vCallback)(void), ADC_Channel_t Copy_xADCChannel)
{
	if(Copy_xADCChannel <= ADC_CHANNEL9)
		ADC_gpIRQCallBack[Copy_xADCChannel] = Copy_vCallback;
}
/******************************************************************************
 * @Fn          -ADC_u16GetDigitalVal
 * @brief       -Read PORT Value
 * @param [in]  -Copy_u8Channel : ADC CHANNELx where x can be (0-->9)
 * @return      -Digital value of ADC

 *******************************************************************************/

u16 ADC_u16GetDigitalVal(ADC_Channel_t Copy_u8Channel)
{

	u16 Local_u16ADCVal = 0;
	DIO_voidSetPinDirection(PORTA,Copy_u8Channel, INPUT_PORT);
	/* Choose Channel */
	if(Copy_u8Channel <= ADC_CHANNEL9)
	{
		ASSIGN_BITS(ADCMUX_REG,ADCMUX_MUXn,FOUR_BITS,Copy_u8Channel);

		SET_BIT(ADCSRA_REG, ADCSRA_ADSC);
		/* Enable Interrupt for Continuous Conversion */
		if(ADC_MODE_SELECTION != ADC_SINGLE_CONVERSION_MODE
				|| ADC_MODE_SELECTION != ADC_STOP_CONVERSION )
			ASSIGN_BIT(ADCSRA_REG, ADCSRA_ADIE ,ADC_IRQ_ENABLE);
		else
		{
			while(!GET_BIT(ADCSRA_REG, ADCSRA_ADIF));
				SET_BIT(ADCSRA_REG, ADCSRA_ADIF);
		}

		Local_u16ADCVal = ADCLH_REG;
	}
	return Local_u16ADCVal;

}


/*============================================================
* 				ISR FUNCTIONS
* ============================================================*/
/* ADC Complete Conversion */
void __vector_16(void)		 __attribute__ ( ( signal ) );
void __vector_16(void)
{

	ADC_Channel_t Local_xChanConv = (READ_BITS(ADCMUX_REG, ADCMUX_MUXn, FOUR_BITS));

		if(ADC_gpIRQCallBack[Local_xChanConv] != NULL_PTR)
			ADC_gpIRQCallBack[Local_xChanConv]();



}

/**********************************************************************************************************************
 *  END OF FILE: ADC_Program.c
 *********************************************************************************************************************/


