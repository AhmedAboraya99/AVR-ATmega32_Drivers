/*
 * LCD_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  LCD_Program.c
 *        \brief  LCD Driver
 *
 *      \details  API functions for LCD control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define LCD_voidSetNibble(val)						DIO_voidWritePins(LCD_DR_PORT, LCD_FIRST_PIN,FOUR_BITS,val)

#define LCD_4BIT_DIO_SET_DIRECTION(DIRECTION)		for(u8 Local_u8Iter = LCD_FIRST_PIN;Local_u8Iter<=LCD_LAST_PIN;Local_u8Iter++)\
													{DIO_voidSetPinDirection(LCD_DR_PORT, Local_u8Iter, DIRECTION);}

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          :  LCD_voidInit
* \Description     : initialize LCD Module
* \Parameters[in]  : None
* \Parameters[out] : None
* \Return :		   : None
********************************************************************************/
void LCD_voidInit(void)
{
	/* init LCD DIO pins */
	LCD_voidInitDIO();

	/* delay */
	_delay_ms(50);
	/*  function set */
#ifdef EIGHT_BIT_MODE
	LCD_voidSendCommand(LCD_FUNCTION_8BIT_2LINES);
#endif

#ifdef FOUR_BIT_MODE
	LCD_voidSendCommand(LCD_RETURN_HOME);
	LCD_voidSendCommand(LCD_FUNCTION_4BIT_2LINES);
#endif
	_delay_ms(2);

	/*  Display ON */
	LCD_voidSendCommand(LCD_DISP_ON);
	_delay_ms(2);

	/*  Clear Screen */
	LCD_voidClearScreen();
	_delay_ms(2);

	/*Entry Mode Set Control*/
	LCD_voidSendCommand(LCD_ENTRY_MODE);
	_delay_ms(2);

}

/******************************************************************************
* \Syntax          :  LCD_voidInit
* \Description     : initialize LCD DIO Pins
* \Parameters[in]  : None
* \Parameters[out] : None
* \Return :		   : None
********************************************************************************/
void LCD_voidInitDIO(void)
{
	DIO_voidSetPinDirection(LCD_CR_PORT, RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CR_PORT, RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CR_PORT, EN_PIN, OUTPUT);
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT, OUTPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	LCD_4BIT_DIO_SET_DIRECTION(OUTPUT);;
#endif
}
/******************************************************************************
* \Syntax          -  LCD_voidSendCommand
* \Description     - Send Command to LCD Module
* \Parameters[in]  - Copy_u8Command : Command to be send to LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/
void LCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, LOW);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
#ifdef EIGHT_BIT_MODE
	LCD_voidCheckIsBusy();
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, LOW);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
	DIO_voidWritePort(LCD_DR_PORT, Copy_u8Command);
#endif
#ifdef FOUR_BIT_MODE
	LCD_voidSetNibble( (Copy_u8Command & HIGH_NIBBLE)>>LCD_DATA_SHIFT);

	/*Falling Edge on EN pin*/
	LCD_voidEnableSignal();

	LCD_voidSetNibble( Copy_u8Command & LOW_NIBBLE);


#endif
	/*Falling Edge on EN pin*/
	LCD_voidEnableSignal();
}

/******************************************************************************
* \Syntax          -  LCD_voidSendData
* \Description     - Send Data to LCD Module
* \Parameters[in]  - Copy_u8Data : Data to be send to LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidSendData(u16 Copy_u16Data)
{


#ifdef EIGHT_BIT_MODE
	LCD_voidCheckIsBusy();
	LCD_voidCheckLineEnd();
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
	DIO_voidWritePort(LCD_DR_PORT, Copy_u16Data);
#endif

#ifdef FOUR_BIT_MODE
	LCD_voidCheckLineEnd();
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
	LCD_voidSetNibble( (Copy_u16Data & HIGH_NIBBLE)>>LCD_DATA_SHIFT);

	/*Falling Edge on EN pin*/
	LCD_voidEnableSignal();

	LCD_voidSetNibble( Copy_u16Data & LOW_NIBBLE);

#endif
	LCD_voidEnableSignal();
}

/******************************************************************************
* \Syntax          -  LCD_voidSendNum
* \Description     - Send Number to LCD Module
* \Parameters[in]  - Copy_u16Num : Number to be send to LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidSendNum(u16 Copy_u16Num)
{
	u16  Local_u16Num = 0;
	if(Copy_u16Num == 0)
		LCD_voidSendChar(Copy_u16Num+'0');
	else
	{
		while(Copy_u16Num != 0)
		{
			Local_u16Num = (Local_u16Num*10) + (Copy_u16Num %10) ;
			Copy_u16Num /= 10;

		}

		while (Local_u16Num > 0)
		{
			Copy_u16Num = Local_u16Num%10;
			Local_u16Num /= 10;
			LCD_voidSendChar(Copy_u16Num+'0');
		}
	}
}
/******************************************************************************
* \Syntax          -  LCD_voidSendChar
* \Description     - Send Number to LCD Module
* \Parameters[in]  - Copy_u8Char : Character to be send to LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidSendChar(u8 Copy_u8Char)
{


#ifdef EIGHT_BIT_MODE
	LCD_voidCheckIsBusy();
	LCD_voidCheckLineEnd();
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);

	DIO_voidWritePort(LCD_DR_PORT, Copy_u8Char);
#endif
#ifdef FOUR_BIT_MODE

	LCD_voidCheckLineEnd();
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
	LCD_voidSetNibble( (Copy_u8Char & HIGH_NIBBLE)>>LCD_DATA_SHIFT);

	/*Falling Edge on EN pin*/
	LCD_voidEnableSignal();

	LCD_voidSetNibble(Copy_u8Char & LOW_NIBBLE);

#endif
	LCD_voidEnableSignal();
}
/******************************************************************************
* \Syntax          -  LCD_voidSendString
* \Description     - Send String to LCD Module
* \Parameters[in]  - Copy_pu8String : String to be send to LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidSendString(u8* Copy_pu8String)
{
	u8 count = 0;
	while(*Copy_pu8String != '\0')
	{
		count++;
		LCD_voidSendChar(*Copy_pu8String++);
		if (count == 16)
		{
			LCD_voidGotoXY(2,0);
		}
		else if (count == 32)
		{
			LCD_voidClearScreen();
			LCD_voidGotoXY(1,0);
			count = 0;
		}
	}

}

/******************************************************************************
* \Syntax          -  LCD_voidCustomChar
* \Description     - Create Custom Char to LCD Module
* \Parameters[in]  - Copy_u8Location : Location to store custom Char in LCD
* \Parameters[in]  - Copy_u8CustomChar :custom Char value
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidCustomChar(u8 Copy_u8Location,u8 Copy_u8CustomChar[8])
{
	if(Copy_u8Location<8)
	{
		LCD_voidSendCommand(LCD_SET_CGRAM_ADDRESS+ (Copy_u8Location * 8));
		for(u8 i=0;i<8;i++)
			LCD_voidSendChar(Copy_u8CustomChar[i]);
	}
}

/******************************************************************************
* \Syntax          -  LCD_voidSendPattern
* \Description     - Create Custom Char to LCD Module
* \Parameters[in]  - Copy_u8CustomChar :custom Char value
* \Parameters[in]  - Copy_u8X, Copy_u8Y : Location to display custom Char on LCD
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/


void LCD_voidSendPattern(u8 Copy_u8CustomChar, u8 Copy_u8X, u8 Copy_u8Y)
{

	if(Copy_u8CustomChar<8)
	{
		LCD_voidSendCommand(LCD_RETURN_HOME);
		LCD_voidGotoXY(Copy_u8X, Copy_u8Y);
		LCD_voidSendChar(Copy_u8CustomChar);
	}
	_delay_ms(20);
}
/**********************************************************************************************************************
 *  PRIVATE FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          - LCD_voidClearScreen
* \Description     - Clear LCD Module
* \Parameters[in]  - None
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidClearScreen(void)
{
	LCD_voidSendCommand(LCD_CLEAR_SCREEN);
}

/******************************************************************************
* \Syntax          - LCD_voidCheckIsBusy
* \Description     - Check LCD Module before sending data
* \Parameters[in]  - None
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidCheckIsBusy(void)
{
	if(LCD_u8GetBusyFlag() == TRUE)
	{
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,INPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	for(u8 Local_u8Iter = LCD_FIRST_PIN;Local_u8Iter <= LCD_LAST_PIN ; Local_u8Iter++ )
		DIO_voidSetPinDirection(LCD_DR_PORT, Local_u8Iter, INPUT);
#endif
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, LOW);
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,OUTPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	LCD_4BIT_DIO_SET_DIRECTION(OUTPUT);
#endif

	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, LOW);
	}
}


/******************************************************************************
* \Syntax          - LCD_voidGotoXY
* \Description     - Navigating in LCD Module by setting DDRAM address
* \Parameters[in]  - None
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidGotoXY(u8 Copy_u8Line, u8 Copy_u8Position)
{
    /* i/p validation */
    if ( Copy_u8Line >= 4 && (Copy_u8Position >= 0 && Copy_u8Position < 16) )
    {
        // Do Nothing
    }
	switch(Copy_u8Line)
	{
	case(1):
		LCD_voidSendCommand(LCD_BEGIN_AT_FIRST_ROW+Copy_u8Position);
		break;
	case(2):
		LCD_voidSendCommand(LCD_BEGIN_AT_SECOND_ROW+Copy_u8Position);
		break;
	case(3):
		LCD_voidSendCommand(LCD_BEGIN_AT_THIRD_ROW+Copy_u8Position);
		break;
	case(4):
		LCD_voidSendCommand(LCD_BEGIN_AT_FORTH_ROW+Copy_u8Position);
		break;
	}
}



void LCD_voidCheckLineEnd(void)
{
	//Start value of DDRAM counter = 0x00 -> must be cast because it contains sign bit
	u8 Local_u8Position = (u8)LCD_u8GetAddressCounter();



	/*First Line Check */
	if(Local_u8Position <= LCD_LINE1_END+1)
	{
		/* Check first Line end */
		if(Local_u8Position == LCD_POSITION_LAST+1)
			LCD_voidGotoXY(LCD_LINE2, LCD_POSITION_FIRST);
	}
	/*Second Line Check */
	else if(Local_u8Position > LCD_LINE2_START_ADDRESS && Local_u8Position < LCD_LINE2_START_ADDRESS+LCD_POSITION_LAST)
	{
		/* Check second Line end */
		// Start value of the second line  = 0x40
		//to convert it to the right sequence of displayed positions (0x50 -  64) = 16
		Local_u8Position = Local_u8Position- (LCD_LINE2_START_ADDRESS);
		if(Local_u8Position == LCD_POSITION_LAST+1)
			LCD_voidGotoXY(LCD_LINE3, LCD_POSITION_FIRST);
	}
	else if(Local_u8Position >= LCD_LINE3_START_ADDRESS && Local_u8Position < LCD_LINE3_START_ADDRESS+LCD_POSITION_LAST)
	{
		/* Check third Line end */
		// Start value of the third line  = 0x10
		//to convert it to the right sequence of displayed positions (0x20-16) = 16
		Local_u8Position = Local_u8Position-  (LCD_LINE3_START_ADDRESS+1);
		if(Local_u8Position == LCD_POSITION_LAST+1)
			LCD_voidGotoXY(LCD_LINE4, LCD_POSITION_FIRST);
	}
	else if(Local_u8Position >= LCD_LINE4_START_ADDRESS && Local_u8Position < LCD_LINE4_START_ADDRESS+LCD_POSITION_LAST)
	{
		/* Check forth Line end */
		// Start value of the forth line  = 0x50
		//to convert it to the right sequence of displayed positions (0x60 - 48) = 16
		Local_u8Position = Local_u8Position - (LCD_LINE4_START_ADDRESS+1);
		if(Local_u8Position == LCD_POSITION_LAST+1)
			LCD_voidGotoXY(LCD_LINE1, LCD_POSITION_FIRST);
	}

}


/******************************************************************************
* \Syntax          - LCD_voidEnableSignal
* \Description     - Enable data to be displayed on LCD Module
* \Parameters[in]  - None
* \Parameters[out] - None
* \Return :		   - None
********************************************************************************/

void LCD_voidEnableSignal(void)
{
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, HIGH);
	_delay_ms(2);
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, LOW);
}

/******************************************************************************
* \Syntax          - LCD_u8GetAddressCounter, LCD_u8GetBusyFlag
* \Description     - Read Busy Flag and Address counter
* \Parameters[in]  - None
* \Parameters[out] - None
* \Return :		   - Busy Flag and Address counter
********************************************************************************/

u8 LCD_u8GetAddressCounter(void)
{
	u8 Local_u8Address = 0;
	 // read mode
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, LOW);
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,INPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	LCD_4BIT_DIO_SET_DIRECTION(INPUT);
#endif
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, HIGH);
    // Wait for setup time
    _delay_us(1);
#ifdef EIGHT_BIT_MODE
	Local_u8Address = DIO_u8ReadPort(LCD_DR_PORT);
#endif
#ifdef FOUR_BIT_MODE
	ASSIGN_BITS(Local_u8Address,LCD_DATA_SHIFT, LCD_DATA_SHIFT, DIO_u8ReadPort(LCD_DR_PORT)>>LCD_FIRST_PIN);

	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, LOW);
    // Wait for hold time
    _delay_us(1);
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, HIGH);
    // Wait for setup time
    _delay_us(1);
	ASSIGN_BITS(Local_u8Address, BIT0, LCD_DATA_SHIFT,DIO_u8ReadPort(LCD_DR_PORT)>>LCD_FIRST_PIN);
#endif
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, LOW);
    // Wait for hold time
    _delay_us(1);
	//clear BF
	CLEAR_BIT(Local_u8Address, BUSY_FLAG_BIT);
	// Set data lines back to output mode
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,OUTPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE

	LCD_4BIT_DIO_SET_DIRECTION(OUTPUT);
#endif

	return Local_u8Address;
}



u8 LCD_u8GetBusyFlag(void)
{
	u8 Local_u8Address = 0;
	DIO_voidSetPinLevel(LCD_CR_PORT, RW_PIN, HIGH);
	DIO_voidSetPinLevel(LCD_CR_PORT, RS_PIN, LOW);
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,INPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	LCD_4BIT_DIO_SET_DIRECTION(INPUT);
#endif

	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, HIGH);
	_delay_us(2);
#ifdef EIGHT_BIT_MODE
	Local_u8Address = DIO_u8ReadPort(LCD_DR_PORT);
#endif
#ifdef FOUR_BIT_MODE
	ASSIGN_BITS(Local_u8Address,LCD_DATA_SHIFT, LCD_DATA_SHIFT, DIO_u8ReadPort(LCD_DR_PORT)>>LCD_FIRST_PIN);
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, LOW);
    // Wait for hold time
    _delay_us(1);
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, HIGH);
    // Wait for setup time
    _delay_us(1);
	ASSIGN_BITS(Local_u8Address, BIT0, LCD_DATA_SHIFT,DIO_u8ReadPort(LCD_DR_PORT)>>LCD_FIRST_PIN);

#endif
	DIO_voidSetPinLevel(LCD_CR_PORT, EN_PIN, LOW);
	_delay_us(2);
#ifdef EIGHT_BIT_MODE
	DIO_voidSetPortDirection(LCD_DR_PORT,OUTPUT_PORT);
#endif
#ifdef FOUR_BIT_MODE
	LCD_4BIT_DIO_SET_DIRECTION(OUTPUT);
#endif
	return GET_BIT(Local_u8Address, BUSY_FLAG_BIT);
}

/**********************************************************************************************************************
 *  END OF FILE: LCD_Program.c
 *********************************************************************************************************************/


