/*
 * Admin.h
 *
 *  Created on: Apr 29, 2023
 *      Author: ahmed
 */

#ifndef SRV_ADMIN_H_
#define SRV_ADMIN_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define ADMIN_CHOICE1		1
#define ADMIN_CHOICE2		2
#define ADMIN_CHOICE3		3
#define ADMIN_CHOICE4		4

#define INPUT_KEY_SUBMIT  		'\n'
#define INPUT_KEY_CLEAR			'\b'

#define ADMIN_PASSWORD_ADDRESS	4
#define ADMIN_DEFAULT_PASSWORD	"1234"
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Admin_Main(void);
bool Admin_vGetUser(u16 Copy_u16LocAddr, u8*Copy_pu8UserID, u8* Copy_pu8Pswd);
void Admin_vSendProadcast(u8* Copy_pu8Text);


bool Admin_xCheckPass();
u8 Admin_u8CheckUser(u8* Copy_pu8UserID,u8* Copy_pu8Pswd);
u8 Admin_u8GetChoice();


#endif /* SRV_ADMIN_H_ */
