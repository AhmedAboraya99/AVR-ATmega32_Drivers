/*
 * EEPROM_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  EEPROM_Program.c
 *        \brief  EEPROM Driver
 *
 *      \details  API functions for EEPROM control
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

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
void EEPROM_vInit()
{
	EEPROM_vWriteByte(0, 10);
	EEPROM_vWriteByte(1, 0);
}

/* @brief: This function writes a byte of data to a specific memory address in the EEPROM.
 *  It uses the I2C helper functions to send
 * @parameter: the device address, memory address, and data byte to the EEPROM using the correct sequence of operations.
 */

void EEPROM_vWriteByte(u16 Copy_u16LocAddr, u8 Copy_u8WriteData)
{
	u8 Local_u8Addr = 0;
	ASSIGN_BITS(Local_u8Addr, BIT0, SEVEN_BITS,EEPROM_ADDRESS);
	ASSIGN_BITS(Local_u8Addr, BIT0, TWO_BITS,Copy_u16LocAddr>>8);

	  // Generate a start condition on the I2C bus.

	TWI_xStartCondition();

	/* Send the device address with the read/write bit set to 0 (write)
	 *  and the upper 2 bits of the memory address. */
	TWI_xSendSLA_Write(Local_u8Addr);

	// Send the lower 8 bits of the memory address.
	TWI_xSendDataByte((u8)(Copy_u16LocAddr ));

	// Send the data byte to be written to the EEPROM.
	TWI_xSendDataByte(Copy_u8WriteData);

	//_delay_ms(1);
    // Generate a stop condition on the I2C bus.
	TWI_vStopCondition();

	// Include a delay of 10ms to ensure that the data is written to the EEPROM before continuing with other operations.
	_delay_ms(10);
}

void EEPROM_vWriteWord(u16 Copy_u16LocAddr, u16 Copy_u16WriteWord)
{
	EEPROM_vWriteByte(Copy_u16LocAddr, (u8) Copy_u16WriteWord);
	EEPROM_vWriteByte( Copy_u16LocAddr+1,(u8)(Copy_u16WriteWord>>8));
}

/*
 * @brief: This function reads a byte of data from a specific memory address in the EEPROM.
 *  It uses the I2C helper functions to send the device address and memory address to the EEPROM using the correct sequence of operations.
 * 	It then reads the data byte from the EEPROM using the i2c_read_nack() function and returns its value.
 */

void EEPROM_vReadByte(u16 Copy_u16LocAddr,u8* Copy_pu8ReadData)
{
	u8 Local_u8Addr = 0;
	ASSIGN_BITS(Local_u8Addr, BIT0, SEVEN_BITS, EEPROM_ADDRESS);
	ASSIGN_BITS(Local_u8Addr, BIT0, TWO_BITS, (Copy_u16LocAddr>>8));

	  // Generate a start condition on the I2C bus.

	TWI_xStartCondition();

	/* Send the device address with the read/write bit set to 0 (write)
	 *  and the upper 2 bits of the memory address. */
	TWI_xSendSLA_Write(Local_u8Addr);

	// Send the lower 8 bits of the memory address.
	TWI_xSendDataByte((u8)Copy_u16LocAddr);


	  // Generate a start condition on the I2C bus.
	TWI_xReStartCondition();
	/*	Send the device address with the read*/
	TWI_xSendSLA_Read(Local_u8Addr);

	// Send the data byte to be written to the EEPROM.
	TWI_xMasterReadDataNACK(Copy_pu8ReadData);
    // Generate a stop condition on the I2C bus.

	TWI_vStopCondition();
	// Include a delay of 10ms to ensure that the data is written to the EEPROM before continuing with other operations.
	_delay_ms(10);

}

void EEPROM_vReadWord(u16 Copy_u16LocAddr, u16* Copy_u16ReadWord)
{
	u8 Local_u8ReadByte;
	EEPROM_vReadByte( Copy_u16LocAddr, &Local_u8ReadByte);
	*Copy_u16ReadWord = Local_u8ReadByte;
	EEPROM_vReadByte( Copy_u16LocAddr+1, &Local_u8ReadByte);
	*Copy_u16ReadWord &= (((u16)Local_u8ReadByte)<<8);
}


void EEPROM_vWriteNum(u16 Copy_u16LocAddr,u8 Copy_pu8WriteNum)
{
	while(Copy_pu8WriteNum != 0)
	{
		EEPROM_vWriteByte(Copy_u16LocAddr ++ , Copy_pu8WriteNum %(10 )  );
		Copy_pu8WriteNum = Copy_pu8WriteNum / 10;
	}
	EEPROM_vWriteByte((Copy_u16LocAddr++),'/');
}

void EEPROM_vWriteString(u16 Copy_u16LocAddr,u8* Copy_pu8WriteStr)
{
	u8 Local_u8Iter=0;
	while(Copy_pu8WriteStr[Local_u8Iter]!='\0')
	{
		EEPROM_vWriteByte((Copy_u16LocAddr+Local_u8Iter),Copy_pu8WriteStr[Local_u8Iter]);
		Local_u8Iter++;
	}
	EEPROM_vWriteByte((Copy_u16LocAddr+Local_u8Iter),'\0');

}

void EEPROM_vReadString(u16 Copy_u16LocAddr, u8* Copy_pu8ReadStr )
{

	u8 Local_u8Iter=0;
	while(1)
	{
		EEPROM_vReadByte(Copy_u16LocAddr+Local_u8Iter, Copy_pu8ReadStr+Local_u8Iter);
		if((Copy_pu8ReadStr[Local_u8Iter] =='\0')|| Copy_pu8ReadStr[Local_u8Iter] == 0xFF)
		{
			Copy_pu8ReadStr[Local_u8Iter] = '\0';
			break;
		}

		Local_u8Iter++;

	}

}
/**********************************************************************************************************************
 *  END OF FILE: EEPROM_Program.c
 *********************************************************************************************************************/


