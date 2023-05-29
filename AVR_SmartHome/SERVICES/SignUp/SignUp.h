/*
 * SignUp.h
 *
 *  Created on: Mar 29, 2023
 *      Author: ahmed
 */

#ifndef SRV_SIGNUP_H_
#define SRV_SIGNUP_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define USERS_POS_ADDRESS 		00
#define USERS_NUM_ADDRESS 		02

#define USER_ID_START_ADDRESS 	10
#define USER_PW_START_ADDRESS 	20

#define USER_RECORD_SIZE		20

#define MAX_USERS_NUM 		10
#define MAX_USER_INPUT		10

#define User1_ID (u8*)"Lala"
#define User2_ID (u8*)"Tata"
#define User3_ID (u8*)"Sasa"

#define User1_PW (u8*)"1234"
#define User2_PW (u8*)"5678"
#define User3_PW (u8*)"9876"


/**********************************************************************************************************************
 *  GLOBAL VARIABLES
 *********************************************************************************************************************/

extern u8* User_Au8IDs[MAX_USERS_NUM] ;
extern u8* User_Au8Passwords[MAX_USERS_NUM];

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void SignUp_Main(void);
void SignUp_vInit(void);
bool SignUp_xAddUser(u8* Copy_pu8UserID, u8* Copy_pu8Pswd);
bool SignUp_xDeleteUser(u8* Copy_pu8UserID, u8* Copy_pu8Pswd);




#endif /* SRV_SIGNUP_H_ */
