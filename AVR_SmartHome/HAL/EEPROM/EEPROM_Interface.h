/*
 * EEPROM_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EEPROM_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef HAL_EEPROM_INTERFACE_H_
#define HAL_EEPROM_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"
#include "../../MCAL/TWI/TWI_Interface.h"
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
void EEPROM_vInit(void);
void EEPROM_vWriteByte(u16 Copy_u16LocAddr, u8 Copy_u8WriteData);
void EEPROM_vReadByte(u16 Copy_u16LocAddr,u8* Copy_pu8ReadData);

void EEPROM_vWriteWord(u16 Copy_u16LocAddr, u16 Copy_u16WriteWord);
void EEPROM_vReadWord(u16 Copy_u16LocAddr, u16* Copy_u16ReadWord);

void EEPROM_vWriteString(u16 Copy_u16LocAddr,u8* Copy_pu8WriteStr);
void EEPROM_vReadString(u16 Copy_u16LocAddr, u8* Copy_pu8ReadStr );
//API-Types


#endif /* HAL_EEPROM_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: EEPROM_Interface.h
 *********************************************************************************************************************/







