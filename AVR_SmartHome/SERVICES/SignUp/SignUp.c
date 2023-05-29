/*
 * SignUp.c
 *
 *  Created on: Apr 31, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/Motor/Motor_Interface.h"
#include "../../HAL/LED/LED_Interface.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../HAL/EEPROM/EEPROM_Interface.h"
#include "../Admin/Admin.h"
#include "SignUp.h"
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u8* User_Au8IDs[MAX_USERS_NUM] = {User1_ID,User2_ID,User3_ID};
u8* User_Au8Passwords[MAX_USERS_NUM] = {User1_PW, User2_PW, User3_PW};
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



void SignUp_vInit(void)
{

	u8 EEPROM_UsersNum = 0;
	EEPROM_vReadByte(USERS_NUM_ADDRESS, &EEPROM_UsersNum);

	//User States not initialized
	if(EEPROM_UsersNum == 0xFF)
	{
		//User States initialization
		EEPROM_vWriteWord(USERS_POS_ADDRESS,0);
		EEPROM_vWriteWord(USERS_NUM_ADDRESS,0);



		for(u8 Local_u8Iter = 0; Local_u8Iter < 3;Local_u8Iter++)
		{

			//storing data

			if(SignUp_xAddUser(User_Au8IDs[Local_u8Iter], User_Au8Passwords[Local_u8Iter]) == FALSE)
				break;
		}
	}
}

bool SignUp_xAddUser(u8* Copy_pu8UserID, u8* Copy_pu8Pswd)
{
	bool SignUp_Success_flag = FALSE;
	u8 EEPROM_CurrUserPosition = 0	, EEPROM_LastUserPosition = 0;
	u8 EEPROM_UsersNum = 0;

	EEPROM_vReadByte(USERS_POS_ADDRESS, &EEPROM_LastUserPosition);
	EEPROM_vReadByte(USERS_NUM_ADDRESS, &EEPROM_UsersNum);


	if(EEPROM_UsersNum <= MAX_USERS_NUM)
	{
		//storing data
		EEPROM_vWriteString((EEPROM_LastUserPosition+USER_ID_START_ADDRESS),(u8*) Copy_pu8UserID);
		EEPROM_vWriteString((EEPROM_LastUserPosition+USER_PW_START_ADDRESS),(u8*) Copy_pu8Pswd);

		//increment info
		EEPROM_UsersNum++;
		EEPROM_CurrUserPosition = EEPROM_LastUserPosition+ USER_RECORD_SIZE;

		//Update info
		EEPROM_vWriteByte(USERS_POS_ADDRESS, EEPROM_CurrUserPosition);

		EEPROM_vWriteByte(USERS_NUM_ADDRESS, EEPROM_UsersNum);

		Admin_vSendProadcast((u8 *) "Num of users ");
		LCD_voidSendNum(EEPROM_UsersNum);
		_delay_ms(50);

		SignUp_Success_flag = TRUE;
	}
		else
		{
			Admin_vSendProadcast((u8 *) "Max Users Reached");
			SignUp_Success_flag = FALSE;
		}
	return SignUp_Success_flag;
}

bool SignUp_xDeleteUser(u8* Copy_pu8UserID, u8* Copy_pu8Pswd)
{
	bool SignUp_Success_flag = FALSE;
	u8 EEPROM_LastUserPosition = 0;
	u8 EEPROM_UsersNum = 0, EEPROM_UserAddr = 0;

	EEPROM_vReadByte(USERS_POS_ADDRESS, &EEPROM_LastUserPosition);
	EEPROM_vReadByte(USERS_NUM_ADDRESS, &EEPROM_UsersNum);

	if(EEPROM_UsersNum != 0)
	{
		//storing data
		EEPROM_UserAddr = Admin_u8CheckUser( Copy_pu8UserID, Copy_pu8Pswd);
		EEPROM_vWriteString(EEPROM_UserAddr,(u8*) 0xFF);
		EEPROM_vWriteString(EEPROM_UserAddr,(u8*) 0xFF);

		//increment info
		EEPROM_UsersNum--;

		//Update info
		EEPROM_vWriteByte(USERS_NUM_ADDRESS, EEPROM_UsersNum);

		Admin_vSendProadcast((u8 *) "Num of users");
		LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
		LCD_voidSendString(NumtoStr(EEPROM_UsersNum));

		_delay_ms(50);
		LCD_voidClearScreen();
		SignUp_Success_flag = TRUE;
	}
		else
		{
			Admin_vSendProadcast((u8 *) "There is no Users");
			SignUp_Success_flag = FALSE;
		}
	return SignUp_Success_flag;
}




