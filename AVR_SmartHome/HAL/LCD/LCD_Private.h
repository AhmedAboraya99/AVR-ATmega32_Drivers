/*
 * DIO_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef HAL_LCD_PRIVATE_H_
#define HAL_LCD_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
//=======Private-Functions=======
void LCD_voidInitDIO(void);
void LCD_voidWriteNibble(u8 Copy_u8Nibble);
void LCD_voidClearScreen(void);
void LCD_voidCheckIsBusy(void);
void LCD_voidCheckLineEnd(void);
void LCD_voidEnableSignal(void);



#endif /* HAL_LCD_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: DIO_Private.h
 *********************************************************************************************************************/


