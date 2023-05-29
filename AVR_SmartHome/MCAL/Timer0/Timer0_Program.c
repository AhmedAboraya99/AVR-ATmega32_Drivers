/*
 * TIMER0_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  TIMER0_Program.c
 *        \brief  Timer Driver
 *
 *      \details  API functions for Timer control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../GINT/GINT_Interface.h"
#include "Timer0_Config.h"
#include "Timer0_Interface.h"
#include "Timer0_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*TIMER0_gpIRQCallBack[2])(void) = {NULL_PTR, NULL_PTR};

static u16 Global_u16OvfVal, Global_u16CmpVal;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void TIMER0_voidInit()
{

	u8 Local_u8TempTCCR0 = 0;
	/* Select Timer Mode */
	ASSIGN_BITS(Local_u8TempTCCR0, TCCR0_WGM00, FOUR_BITS, TIMER0_MODE_SELECTION);


	/* Set  Compare Output Mode  */
	ASSIGN_BITS(Local_u8TempTCCR0, TCCR0_COM00, TWO_BITS,TIMER0_COMPARE_MODE);
	if(TIMER0_COMPARE_MODE != TIMER0_TOGGLE_OC0_CM || TIMER0_COMPARE_MODE == TIMER0_NORMAL_PORT_OP)
	{
		/* Configure OC0 (PINB3) as Output */
		DIO_voidSetPinDirection(PORTB, PIN3, OUTPUT);

	}//else OC0 is Disconnected


	/* Select Clock Source */
	ASSIGN_BITS(Local_u8TempTCCR0, TCCR0_CS00, TWO_BITS,TIMER0_CLOCK_SOURCE);
	if(TIMER0_CLOCK_SOURCE == TIMER0_EXTCLKSRC_FALLING || TIMER0_CLOCK_SOURCE == TIMER0_EXTCLKSRC_RISING)
		{
			/* Configure T0 (PINB0) as Input */
		DIO_voidSetPinDirection(PORTB, PIN0, INPUT);
		}

	/* Enable Or Disable IRQ */
	ASSIGN_BITS(TIMSK0_REG, TIMSK0_TOIE0, TWO_BITS,TIMER0_IRQSRC_SELECTION);
	if(TIMER0_IRQSRC_SELECTION != TIMER0_IRQ_DISABLE)
	{
		/* Enable Global Interrupt */
		 GINT_voidEnable();


	}
	TCCR0_REG = Local_u8TempTCCR0;


}

void TIMER0_voidStart(void)
{
	/* Select Clock Source */
	ASSIGN_BITS(TCCR0_REG, TCCR0_CS00, TWO_BITS,TIMER0_CLOCK_SOURCE);
	/* Stop Timer Operation */
	ASSIGN_BITS(TCCR0_REG, TCCR0_WGM00, FOUR_BITS, TIMER0_MODE_SELECTION);
	/* Reset  Compare Output Mode  */
	ASSIGN_BITS(TCCR0_REG, TCCR0_COM00, TWO_BITS, TIMER0_COMPARE_MODE);
	/* Disable IRQ */
	ASSIGN_BITS(TIMSK0_REG, TIMSK0_TOIE0, TWO_BITS, TIMER0_IRQSRC_SELECTION);
}


void TIMER0_voidStop(void)
{
	/* Select No Clock Source : Disable Timer*/
	ASSIGN_BITS(TCCR0_REG, TCCR0_CS00, TWO_BITS,TIMER0_NOCLKSRC);
	/* Stop Timer Operation */
	ASSIGN_BITS(TCCR0_REG, TCCR0_WGM00, FOUR_BITS,TIMER0_NORMAL_MODE);
	/* Reset  Compare Output Mode  */
	ASSIGN_BITS(TCCR0_REG, TCCR0_COM00, TWO_BITS,TIMER0_NORMAL_PORT_OP);
	/* Disable IRQ */
	ASSIGN_BITS(TIMSK0_REG, TIMSK0_TOIE0, TWO_BITS,TIMER0_IRQ_DISABLE);
}

void TIMER0_voidSetPreloadVal(u8 Copy_u8PreloadVal)
{
	TCNT0_REG = Copy_u8PreloadVal;
}
void TIMER0_voidSetCallBackOVF(void (*TIMER0_pOvfCallBack)(void))
{
	/* Call back function address */
	TIMER0_gpIRQCallBack[OVERFLOW_INDEX] = TIMER0_pOvfCallBack;

}

void TIMER0_voidSetCallBackCTC(void (*TIMER0_pCmpCallBack)(void))
{
	/* Call back function address */
	TIMER0_gpIRQCallBack[COMPAREMATCH_INDEX] = TIMER0_pCmpCallBack;

}



/**================================================================
* @Fn			- TIMER0_u8GetCountVal
* @brief 		- Get Timer counter value
* @param [in] 	- countVal :  8-bit value of counter value (TCNT0) Register
* @retval		- none
* ============================================================*/
u8 TIMER0_u8GetCountVal(){
	return TCNT0_REG;
}

/**================================================================
* @Fn			- TIMER0_voidSetCompareVal
* @brief 		- The Output Compare Register contains an 8-bit value
*				  that is continuously compared with the counter value (TCNT0)
* @param [in] 	- compVal :  8-bit value of  Output Compare Register
* @retval		- none
* ============================================================*/
void TIMER0_voidSetCompareVal(u8 Copy_u8compVal){
	OCR0_REG = Copy_u8compVal;
}



/*============================================================
* 				ISR FUNCTIONS
* ============================================================*/
void __vector_11(void)		 __attribute__ ( ( signal ) );
void __vector_11(void)
{
	Global_u16OvfVal++;
	if(Global_u16OvfVal == 3921)
	{
		if(TIMER0_gpIRQCallBack[OVERFLOW_INDEX] != NULL_PTR)
			TIMER0_gpIRQCallBack[OVERFLOW_INDEX]();
		Global_u16OvfVal = 0;
		TIMER0_voidSetPreloadVal(192);
	}


}

/* COMPARE MATCH ISR */

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){

	Global_u16CmpVal++;
	if(Global_u16CmpVal == 4000)
	{
		if(TIMER0_gpIRQCallBack[COMPAREMATCH_INDEX] != NULL_PTR)
			TIMER0_gpIRQCallBack[COMPAREMATCH_INDEX]();
		Global_u16CmpVal = 0;
		TIMER0_voidSetCompareVal(200);
	}
}


/**********************************************************************************************************************
 *  END OF FILE: TIMER0_Program.c
 *********************************************************************************************************************/


