/*
 * Admin.c
 *
 *  Created on: Apr 31, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/EEPROM/EEPROM_Interface.h"
#include "../../HAL/Buzzer/Buzzer.h"
#include "../../HAL/BTH/BTH_Interface.h"
#include "../../SERVICES/SignUp/SignUp.h"
#include "../Admin/Admin.h"


/**********************************************************************************************************************
 *  MACRO FUNCTIONS
 *********************************************************************************************************************/
#define ADMIN_vGetUsersCount(Copy_pu8UserCount)			 EEPROM_vReadByte(USERS_NUM_ADDRESS, Copy_pu8UserCount)
#define ADMIN_vGetCurrPos(Copy_pu8UserPos)			 EEPROM_vReadByte(USERS_POS_ADDRESS, Copy_pu8UserPos)
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Admin_Main(){
	u8 Local_u8Mode = 0, Local_u8Attempts = 0;
	u8 Local_u8UsersCount = 0;
	u8 Local_pu8UserPswd[MAX_USER_INPUT], Local_pu8UserID[MAX_USER_INPUT] ;

	_delay_ms(50);


	_delay_ms(100);
	Admin_vSendProadcast((u8*)"Welcome to Home Admin");
	_delay_ms(1500);
	LCD_voidClearScreen();



		bool Local_u8PassFlag = Admin_xCheckPass();
	while(1)
	{

		if(Local_u8PassFlag == TRUE)
		{

			Admin_vSendProadcast((u8*)"Successful Admin Login");


			_delay_ms(500);
			Admin_vSendProadcast((u8*)"Enter options:");
			LCD_voidClearScreen();
			LCD_voidSendString((u8*)"1-Add User");
			LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);

			LCD_voidSendString((u8*)"2-Delete User");
			LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);

			LCD_voidSendString((u8*)"3-Users Count");

			Local_u8Mode = Admin_u8GetChoice();
			switch(Local_u8Mode )
			{
			case ADMIN_CHOICE1:

				Admin_vSendProadcast((u8*)"Enter User ID");
				 BTH_vReceiveText(Local_pu8UserID);

				Admin_vSendProadcast((u8*)"Enter User Password");
				BTH_vReceivePass(Local_pu8UserPswd);
				SignUp_xAddUser(Local_pu8UserID, Local_pu8UserPswd);

				_delay_ms(500);
				break;
			case ADMIN_CHOICE2:
				Admin_vSendProadcast((u8*)"Enter User ID");
				BTH_vReceiveText(Local_pu8UserID);

				Admin_vSendProadcast((u8*)"Enter User Password");
				BTH_vReceivePass(Local_pu8UserPswd);

				SignUp_xDeleteUser(Local_pu8UserID, Local_pu8UserPswd);
				_delay_ms(500);
				break;
			case ADMIN_CHOICE3:

				ADMIN_vGetUsersCount(&Local_u8UsersCount);

				LCD_voidClearScreen();
				LCD_voidSendString((u8*)"Number of Users");

				LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
				LCD_voidSendString(NumtoStr(Local_u8UsersCount));
				_delay_ms(2000);

				break;
			case ADMIN_CHOICE4:
				break;
			default:
				Local_u8Mode = ADMIN_CHOICE4;
				break;
			}
			if(Local_u8Mode == ADMIN_CHOICE4)
				break;
		}
		else
		{
			LCD_voidClearScreen();
			Local_u8Attempts++;
			Admin_vSendProadcast((u8*)"Wrong Password! ReEnter :>");
			if(Local_u8Attempts == 3)
			{
				Buzzer_vBeep(1000, 500);
				Local_u8Attempts = 0;
			}
			Local_u8PassFlag = Admin_xCheckPass();
		}
	}

}



bool Admin_xCheckPass(void)
{
	bool Local_u8PassFlag = FALSE;
	u8 Local_pu8Pswd[MAX_USER_INPUT];
	//u8 Local_u8Mode = 0;
	u8 EEPROM_pu8AdminPswd[MAX_USER_INPUT];
	EEPROM_vReadString(ADMIN_PASSWORD_ADDRESS, EEPROM_pu8AdminPswd);

	//admin password not initialized
	if(*EEPROM_pu8AdminPswd == '\0' ||*EEPROM_pu8AdminPswd == 0xFF )
		EEPROM_vWriteString(ADMIN_PASSWORD_ADDRESS, (u8*)ADMIN_DEFAULT_PASSWORD);

	Admin_vSendProadcast((u8*)"Enter Admin Password");


	BTH_vReceivePass(Local_pu8Pswd);
		if(!compare_string(Local_pu8Pswd, EEPROM_pu8AdminPswd))
			Local_u8PassFlag = TRUE ;
		else
			Admin_vSendProadcast((u8*)"Wrong Admin Password");

	return Local_u8PassFlag;
}

bool Admin_vGetUser(u16 Copy_u16LocAddr, u8*Copy_pu8UserID, u8* Copy_pu8Pswd)
{

	u8 Copy_u8UserValid = 0;
	EEPROM_vReadByte(Copy_u16LocAddr, &Copy_u8UserValid);

	if (Copy_u8UserValid == '\0')
	{

			return FALSE;

	}
	else if(Copy_u8UserValid != 0xFF)
	{
		 EEPROM_vReadString(Copy_u16LocAddr, Copy_pu8UserID);

		 EEPROM_vReadString(Copy_u16LocAddr+USER_ID_START_ADDRESS, Copy_pu8Pswd);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return FALSE;
}



void Admin_vSendProadcast(u8* Copy_pu8Text)
{

	LCD_voidClearScreen();
	LCD_voidSendString((u8*)Copy_pu8Text);
	_delay_ms(2000);

}

u8 Admin_u8GetChoice( void )
{
	u8 Local_u8Input , Local_u8Num = 0 ;

	 BTH_vReceiveText(&Local_u8Input);
	Local_u8Num = GET_NUM(Local_u8Input);

	return Local_u8Num ;
}

/******************************************************************************
 * @Fn          -Admin_u8CheckUser
 * @brief       -Check user and return its address at eeprom
 * @param [in]  -Copy_pu8UserID
 * @param [in]  -Copy_pu8Pswd
 * @return      -User ID address at eeprom
 *******************************************************************************/

u8 Admin_u8CheckUser(u8* Copy_pu8UserID,u8* Copy_pu8Pswd)
{
	u16 Local_u8UserFlag = FALSE;
	u8 Local_u8Pos = 0, Local_u8CurrIndex = 0;
	u8 Local_st8UserID[MAX_USER_INPUT], Local_st8Pswd[MAX_USER_INPUT];


	//get current position
	EEPROM_vReadByte(USERS_POS_ADDRESS, &Local_u8Pos);

	while ((Local_u8CurrIndex <= Local_u8Pos && Local_u8CurrIndex <= (MAX_USERS_NUM * USER_RECORD_SIZE)))
	 {
		  // Read user ID and password from EEPROM
			if(Admin_vGetUser((Local_u8CurrIndex*USER_RECORD_SIZE)+USER_ID_START_ADDRESS, Local_st8UserID, Local_st8Pswd) == TRUE)
			{
				Local_u8CurrIndex += USER_RECORD_SIZE;

				//Local_u8UserFlag = (Local_u8CurrIndex);
				if(!compare_string(Local_st8UserID , Copy_pu8UserID) && !compare_string( Local_st8Pswd, Copy_pu8Pswd))
				{
					Local_u8UserFlag = (Local_u8CurrIndex);
					break;
				}
			}else
			{
				Local_u8CurrIndex++;
			}
	 }

	return Local_u8UserFlag;
}


