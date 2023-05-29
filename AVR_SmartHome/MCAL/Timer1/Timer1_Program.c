/*
 * TIMER1_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  TIMER1_Program.c
 *        \brief  Timer Driver
 *
 *      \details  API functions for Timer control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../GINT/GINT_Interface.h"
#include "../Timer1/Timer1_Config.h"
#include "../Timer1/Timer1_Interface.h"
#include "../Timer1/Timer1_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*TIMER1_gpIRQCallBack[3])(void) = {NULL_PTR, NULL_PTR, NULL_PTR};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void TIMER1_voidInit()
{

	/* Select Timer Mode */

	ASSIGN_BITS(TCCR1A_REG, TCCR1A_WGM10, TWO_BITS, TIMER1_MODE_SELECTION);
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_WGM12, TWO_BITS, TIMER1_MODE_SELECTION>>2);

	/* Set  Compare Output Mode  */
	ASSIGN_BITS(TCCR1A_REG, TCCR1A_COM1A0 , TWO_BITS,TIMER1_COMPARE_MODE);
	if(TIMER1_COMPARE_MODE != TIMER1_TOGGLE_OC1_CM || TIMER1_COMPARE_MODE == TIMER1_NORMAL_PORT_OP)
	{
		/* Configure OC1A (PIND5) as Output */
		DIO_voidSetPinDirection(PORTD, PIN5, OUTPUT);


	}//else OC0 is Disconnected


	/* Select Clock Source */
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_CS10, THREE_BITS,TIMER1_CLOCK_SOURCE);
	if(TIMER1_CLOCK_SOURCE == TIMER1_EXTCLKSRC_FALLING || TIMER1_CLOCK_SOURCE == TIMER1_EXTCLKSRC_RISING)
		{
			/* Configure T0 (PINB0) as Input */
			DIO_voidSetPinDirection(PORTB, PIN0, INPUT);
		}

	/* Enable Or Disable IRQ */
	ASSIGN_BITS(TIMSK1_REG, TIMSK1_TOIE1, FOUR_BITS,TIMER1_IRQSRC_SELECTION);
	if(TIMER1_IRQSRC_SELECTION != TIMER1_IRQ_DISABLE)
	{
		/* Enable Global Interrupt */
		 GINT_voidEnable();


	}




}

void TIMER1_voidStart()
{

	/* Enable Timer1 interrupt and start Timer1 */


	ASSIGN_BITS(TCCR1A_REG, TCCR1A_WGM10, TWO_BITS, TIMER1_MODE_SELECTION);
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_WGM12, TWO_BITS, TIMER1_MODE_SELECTION>>2);

	/* Set  Compare Output Mode  */
	ASSIGN_BITS(TCCR1A_REG, TCCR1A_COM1A0 , TWO_BITS,TIMER1_COMPARE_MODE);

	/* Select Clock Source */
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_CS10, THREE_BITS,TIMER1_CLOCK_SOURCE);

	/* Enable Or Disable IRQ */
	ASSIGN_BITS(TIMSK1_REG, TIMSK1_TOIE1, FOUR_BITS,TIMER1_IRQSRC_SELECTION);


}
void TIMER1_voidStop()
{
	/* Disable Timer1 interrupt and stop Timer1 */
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_CS10, THREE_BITS,TIMER1_NOCLKSRC);

	ASSIGN_BITS(TCCR1A_REG, TCCR1A_WGM10, TWO_BITS, TIMER1_NORMAL_MODE);
	ASSIGN_BITS(TCCR1B_REG, TCCR1B_WGM12, TWO_BITS, TIMER1_NORMAL_MODE>>2);

	/* Set  Compare Output Mode  */
	ASSIGN_BITS(TCCR1A_REG, TCCR1A_COM1A0 , TWO_BITS,TIMER1_NORMAL_PORT_OP);



	/* Disable Timer1 interrupt and stop Timer1 */
	ASSIGN_BITS(TIMSK1_REG, TIMSK1_TOIE1, FOUR_BITS,TIMER1_IRQ_DISABLE);

}
void TIMER1_voidSetTriggerSense(ICU_SenseEdge_t Trigger_Edge)
{
	ASSIGN_BIT(TCCR1B_REG, TCCR1B_ICES1, Trigger_Edge);
}

void TIMER1_voidSetPreloadVal(u16 Copy_u16PreloadVal)
{
	TCNT1_REG = Copy_u16PreloadVal;
}
void TIMER1_voidSetCallBackOVF(void (*TIMER1_pOvfCallBack)(void))
{
	/* Call back function address */
	TIMER1_gpIRQCallBack[OVERFLOW_INDEX] = TIMER1_pOvfCallBack;

}

void TIMER1_voidSetCallBackCTC(void (*TIMER1_pCmpCallBack)(void))
{
	/* Call back function address */
	TIMER1_gpIRQCallBack[COMPARE_MATCH_INDEX] = TIMER1_pCmpCallBack;

}

void TIMER1_voidSetCallBackCAPT(void (*TIMER1_pCaptCallBack)(void))
{
	/* Call back function address */
	TIMER1_gpIRQCallBack[INPUT_CAPTURE_INDEX] = TIMER1_pCaptCallBack;

}



/**================================================================
* @Fn			- TIMER1_u8GetCountVal
* @brief 		- Get Timer counter value
* @param [in] 	- countVal :  8-bit value of counter value (TCNT0) Register
* @retval		- none
* ============================================================*/
u16 TIMER1_u16GetCountVal(){
	return TCNT1_REG;
}

u16 TIMER1_u16GetInCaptVal(){
	return ICR1_REG;
}


/**================================================================
* @Fn			- TIMER1_voidSetCompareVal
* @brief 		- The Output Compare Register contains an 8-bit value
*				  that is continuously compared with the counter value (TCNT0)
* @param [in] 	- compVal :  8-bit value of  Output Compare Register
* @retval		- none
* ============================================================*/
void TIMER1_voidSetCompareVal(u16 Copy_u16compVal)
{
	OCR1A_REG = Copy_u16compVal;
}

/**================================================================
* @Fn			- TIMER1_voidSetCaptVal
* @brief 		- The Input capture Register contains an 16-bit value
*				  that is continuously compared with the counter value (TCNT0)
* @param [in] 	- compVal :  8-bit value of  Output Compare Register
* @retval		- none
* ============================================================*/
void TIMER1_voidSetCaptVal(u16 Copy_u16CaptVal)
{
	ICR1_REG = Copy_u16CaptVal;
}


void TIMER1_vDisICU_INT()
{
	ASSIGN_BIT(TIMSK1_REG, TIMSK1_ICRIE1, LOW);
}



/*============================================================
* 				ISR FUNCTIONS
* ============================================================*/
/* Timer/Counter1 Capture Event */
void __vector_6(void)		 __attribute__ ( ( signal ) );
void __vector_6(void)
{

		if(TIMER1_gpIRQCallBack[INPUT_CAPTURE_INDEX] != NULL_PTR)
			TIMER1_gpIRQCallBack[INPUT_CAPTURE_INDEX]();



}

/* COMPARE MATCH A ISR */

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void){

		if(TIMER1_gpIRQCallBack[COMPARE_MATCH_INDEX] != NULL_PTR)
			TIMER1_gpIRQCallBack[COMPARE_MATCH_INDEX]();

}


/**********************************************************************************************************************
 *  END OF FILE: TIMER1_Program.c
 *********************************************************************************************************************/


