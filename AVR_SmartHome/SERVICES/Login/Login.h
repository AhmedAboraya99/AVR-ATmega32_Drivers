/*
 * Login.h
 *
 *  Created on: Mar 29, 2023
 *      Author: ahmed
 */

#ifndef SRV_LOGIN_H_
#define SRV_LOGIN_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define PASS_DIGITS_NUMBER 	3
#define LOGIN_PASSWORD		1234

#define LOGIN_CHOICE1		1
#define LOGIN_CHOICE2		2
#define LOGIN_CHOICE3		3


#define LOGIN_LED_PORT		PORTB
#define LOGIN_LED_PIN		PIN0

#define ALERT_LED_PORT		PORTD
#define ALERT_LED_PIN		PIN4
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

bool Login_Main(void);
bool Login_xCheckUser();


#endif /* SRV_LOGIN_H_ */
