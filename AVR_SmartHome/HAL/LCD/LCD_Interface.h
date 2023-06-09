/*
 * LCD_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  LCD_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef HAL_LCD_INTERFACE_H_
#define HAL_LCD_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"

#include "LCD_Private.h"
#include "LCD_Config.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void LCD_voidInit(void);

void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendData(u16 Copy_u16Data);
void LCD_voidSendNum(u16 Copy_u16Num);
void LCD_voidSendChar(u8 Copy_u8Char);
void LCD_voidSendString(u8* Copy_pu8String);
u8 LCD_u8GetAddressCounter(void);
u8 LCD_u8GetBusyFlag(void);
void LCD_voidCustomChar(u8 Copy_u8Location,u8 Copy_u8CustomChar[8]);
void LCD_voidSendPattern(u8 Copy_u8CustomChar, u8 Copy_u8X, u8 Copy_u8Y);
void LCD_voidGotoXY(u8 Copy_u8Line, u8 Copy_u8Position);

//API-Types


#endif /* HAL_LCD_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: LCD_Interface.h
 *********************************************************************************************************************/








