/*
 * UART_Driver.c
 *
 * Created: 12/27/2021 7:21:19 AM
 *  Author: Ahmed Aboraya
 */ 
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "US_Interface.h"
#include "../../MCAL/Timer1/Timer1_Private.h"
#include "../../MCAL/GINT/GINT_Interface.h"
#include "../../MCAL/EXTI/EXTI_Interface.h"
#include "../../SERVICES/Admin/Admin.h"
/**********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/

volatile u8 GTimeCapture ;


/**********************************************************************************************************************
 * GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void US_vInit()
{
	 DIO_voidSetPinDirection (US_PORT,TRIGGER_PIN, OUTPUT ); /* Make trigger pin as output */
	 DIO_voidSetPinDirection (ECHO_PORT,ECHO_PIN, INPUT );		/* Make Echo pin as input */

	EXTI_voidEnable(EXTI_INT0, ON_CHANGE, &US_EchoCallBack);

}

void US_vTrigger(DIO_Port_t Localx_USPort)
{
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	DIO_voidSetPinLevel (Localx_USPort,TRIGGER_PIN, HIGH );

	_delay_us(10);
	DIO_voidSetPinLevel(Localx_USPort,TRIGGER_PIN, LOW );

	SET_BIT (TIFR_REG, TIFR_ICF1);	/* Clear ICP flag (Input Capture flag) */

	SET_BIT (TIFR_REG, TIFR_TOV1);	/* Clear Timer Overflow flag */

}
f32 US_vCaptureInput()
{
	 
	 f32 Local_f32Distance;
	 
	//Test distance = (high level time � velocity of sound (343M/S) / 2

	SET_BIT (TIFR_REG, TIFR_ICF1);	/* Clear ICP flag (Input Capture flag) */
	SET_BIT (TIFR_REG,TIFR_TOV1);	/* Clear Timer Overflow flag */


	/* 8MHz Timer freq, sound speed =343 m/s */
	Local_f32Distance = (f32)GTimeCapture / 466.47;
	
	return Local_f32Distance;
	
}

void US_EchoCallBack(void)
{
	f32 Local_f32Distance = 0;
	if(DIO_u8GetPinLevel(ECHO_PORT, ECHO_PIN) == LOW)
	{
		GTimeCapture = ICR1L_REG - GTimeCapture;
		Local_f32Distance = US_vCaptureInput();
		if (Local_f32Distance<=80)
		{
			Admin_vSendProadcast((u8*)"WELCOME HOME");
		}
	}
	else
	{
		GTimeCapture = ICR1L_REG;

	}
}
