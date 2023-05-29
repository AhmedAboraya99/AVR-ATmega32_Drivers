/*
 * EXTI_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  EXTI_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EXTI_Config.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void (*EXTI_gpCallBackFn[3])(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


void EXTI_voidInit(void)
{	//enable external interrupt 0 request
	ASSIGN_BITS(GICR_REG, GICR_INT2, THREE_BITS,EXTI_IRQ_SELECTION);
	
	
#if	(EXTI_IRQ_SELECTION == EXTI_INT0)
	ASSIGN_BITS(MCUCR_REG,MCUCR_ISC00, TWO_BITS,EXTI_SENSE_CONTROL );

#elif (EXTI_IRQ_SELECTION == EXTI_INT1)
		ASSIGN_BITS(MCUCR_REG,MCUCR_ISC10, TWO_BITS,EXTI_SENSE_CONTROL );
		
#elif (EXTI_IRQ_SELECTION == EXTI_INT2)

		ASSIGN_BITS(MCUCSR_REG,MCUCSR_ISC2, TWO_BITS,EXTI_SENSE_CONTROL );

#endif

}
/******************************************************************************
 * @Fn          -EXTI_voidEnable
 * @brief       -Enable EXTI
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/

void EXTI_voidEnable(EXTI_IRQ_t Copy_xIntNo, EXTI_Sense_t Copy_xSenseControl, void (*Local_pCallBackFn)(void))
{	
	if(Local_pCallBackFn != NULL_PTR)	
		EXTI_gpCallBackFn[Copy_xIntNo] = Local_pCallBackFn;

	 EXTI_voidInitDIO(Copy_xIntNo);

	//enable external interrupt request
	ASSIGN_BITS(GICR_REG, GICR_INT2, THREE_BITS,Copy_xIntNo);
	
	switch(Copy_xIntNo)
		{
		case EXTI_INT0:

			ASSIGN_BITS(MCUCR_REG,MCUCR_ISC00, TWO_BITS,Copy_xSenseControl );

			break;
		case EXTI_INT1:
			ASSIGN_BITS(MCUCR_REG,MCUCR_ISC10, TWO_BITS,Copy_xSenseControl );

			break;
		case EXTI_INT2:
			ASSIGN_BITS(MCUCSR_REG,MCUCSR_ISC2, TWO_BITS,Copy_xSenseControl );

			break;

		}



}
/******************************************************************************
 * @Fn          -EXTI_voidDisable
 * @brief       -Enable EXTI
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/

void EXTI_voidDisable(EXTI_IRQ_t Copy_xIntNo)
{


	EXTI_gpCallBackFn[Copy_xIntNo] = NULL_PTR;

	//Disable external interrupt request
	
	switch(Copy_xIntNo)
		{
		case EXTI_INT0:
			CLEAR_BIT(GICR_REG, GICR_INT0);
			break;

		case EXTI_INT1:
			CLEAR_BIT(GICR_REG, GICR_INT1);
			break;

		case EXTI_INT2:
			CLEAR_BIT(GICR_REG, GICR_INT2);
			break;

		}


}

/******************************************************************************
 * @Fn          -EXTI_voidInitDIO
 * @brief       -Initialize EXTI pins
 * @param [in]  -Copy_u8IntNo : to select EXTI number
 * @param [in]  -Copy_u8SenseControl
 * @return      -None
 *******************************************************************************/
void EXTI_voidInitDIO(EXTI_IRQ_t Copy_xIntNo)
{
	switch(Copy_xIntNo)
	{
	case EXTI_INT0:
		DIO_voidSetPinDirection(PORTD,PIN2, INPUT);
		break;
	case EXTI_INT1:
		DIO_voidSetPinDirection(PORTD,PIN3, INPUT);
		break;
	case EXTI_INT2:
		DIO_voidSetPinDirection(PORTB,PIN2, INPUT);
		break;

	}
}


/*******ISR-Functions******/
void __vector_1(void)		 __attribute__ ( ( signal ) );
void __vector_1(void)
{
	if(EXTI_gpCallBackFn[0] != NULL_PTR)
		EXTI_gpCallBackFn[0]();

}

void __vector_2(void)		 __attribute__ ( ( signal ) );
void __vector_2(void)
{
	if(EXTI_gpCallBackFn[1] != NULL_PTR)
		EXTI_gpCallBackFn[1]();

}

void __vector_3(void)		 __attribute__ ( ( signal ) );
void __vector_3(void)
{
	if(EXTI_gpCallBackFn[2] != NULL_PTR)
		EXTI_gpCallBackFn[2]();

}




/**********************************************************************************************************************
 *  END OF FILE: EXTI_Program.c
 *********************************************************************************************************************/


