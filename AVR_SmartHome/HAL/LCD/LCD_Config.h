/*
 * LCD_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

#ifndef HAL_LCD_CONFIG_H_
#define HAL_LCD_CONFIG_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"

/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONFIGURATIONS
 *********************************************************************************************************************/
#define LCD_CR_PORT			PORTA
#define DDR_LCD_CTRL		DDRA_REG

#define LCD_DR_PORT			PORTC
#define DDR_LCD_DATA		DDRC_REG

#define RS_PIN				PIN5
#define RW_PIN				PIN6
#define EN_PIN				PIN7

#define LCD_LINE1					1
#define LCD_LINE2					2
#define LCD_LINE3					3
#define LCD_LINE4					4

#define LCD_LINE1_END				15
#define LCD_LINE2_END				31
#define LCD_LINE3_END				47
#define LCD_LINE4_END				63

#define LCD_LINE1_START_ADDRESS		0x00
#define LCD_LINE2_START_ADDRESS		0x40
#define LCD_LINE3_START_ADDRESS		0x10
#define LCD_LINE4_START_ADDRESS		0x50

#define LCD_POSITION_FIRST			0
#define LCD_POSITION_LAST			15

#define BUSY_FLAG_BIT				7

//LCD Mode Select
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_DATA_SHIFT	4
#define LCD_FIRST_PIN	PIN4
#define LCD_LAST_PIN	PIN7


/* LCD COMMANDS */
#define LCD_FUNCTION_8BIT_1LINE   					(0x30)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)

#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)

#define LCD_ENTRY_DEC   							(0x04)// Entry Mode Decrease > No shifting
#define LCD_ENTRY_DEC_SHIFT   						(0x05)// Entry Mode Decrease > Right shift
#define LCD_ENTRY_MODE								(0x06)// Entry Mode Increase > No shifting
#define LCD_ENTRY_INC_SHIFT   						(0x07)// Entry Mode Increase > Left shift

#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_BEGIN_AT_THIRD_ROW						(0x91)
#define LCD_BEGIN_AT_FORTH_ROW						(0xD0)

#define LCD_RETURN_HOME								(0x02)
#define LCD_CLEAR_SCREEN							(0x01)

#define GO_INTO_4BIT_MODE							(0x33)
#define START_4BIT_MODE								(0x32)
#define LCD_FUNCTION_4BIT_1LINE   					(0x20)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)

#define LCD_SET_CGRAM_ADDRESS						(0x40)


#endif /* HAL_LCD_CONFIG_H_ */
