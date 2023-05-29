/*
 * TWI_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TWI_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_TWI_INTERFACE_H_
#define MCAL_TWI_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include"../DIO/DIO_Interface.h"
#include"../GINT/GINT_Interface.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum TWIStatusCode
{
	TWI_MSTR_START = 0x08,			//A START condition has been transmitted
	TWI_MSTR_REPEATEDSTART = 0x10,	//A repeated START condition has been transmitted
	TWI_MT_SLAW_ACK = 0x18,			//SLA+W has been transmitted; ACK has been received
	TWI_MT_SLAW_NACK = 0x20,		//SLA+W has been transmitted; NOT ACK has been received
	TWI_MT_DATA_ACK = 0x28,			//Data byte has been transmitted; ACK has been received
	TWI_MT_DATA_NACK = 0x30,		//Data byte has been transmitted; NOT ACK has been received

	TWI_MSTR_ARBIT_LOST  = 0x38,	//Arbitration lost in SLA+R/W or data bytes  or NOT ACK bit

	TWI_MR_SLAR_ACK = 0x40,			//SLA+R has been transmitted; ACK has been received
	TWI_MR_SLAR_NACK = 0x48,		//SLA+R has been transmitted; NOT ACK has been received
	TWI_MR_DATA_ACK = 0x50, 		//Data byte has been received; ACK has been RETURNED
	TWI_MR_DATA_NACK = 0x58,		//Data byte has been received; NOT ACK has been RETURNED

	TWI_SR_SLAW_ACK = 0x60,			//SLA+W has been received; ACK has been returned
	TWI_SR_SLAW_NACK = 0x68,		//SLA+W has been received; NOT ACK has been returned
	TWI_SR_GCALL_ACK = 0x70, 		//General call address has been received; ACK has been returned
	TWI_SR_GCALL_NACK  = 0x78,		//Arbitration lost in SLA+R/W as Master; General call address has been received ACK has been returned
	TWI_SR_DATA_ACK = 0x80,
	TWI_SR_DATA_NACK = 0x88,
	TWI_SR_DATA_GCALL_ACK = 0x90,
	TWI_SR_DATA_GCALL_NACK = 0x98,
	TWI_SR_SLAR_STOP = 0xA0,

	TWI_ST_SLAR_ACK = 0xA8,
	TWI_ST_SLAR_NACK = 0xB0,
	TWI_ST_DATA_ACK = 0xB8,
	TWI_ST_DATA_NACK = 0xC0,
	TWI_ST_LAST_DATA_ACK = 0xC8,

	TWI_UNKNOWN_ERROR = 0xF8,
	TWI_BUS_ERROR = 0x00
}TWI_State_t;

typedef enum {
	TWI_NOK = 0,
	TWI_OK = 1,
	TWI_StartCondition,
	TWI_SlaveAddrWithWrite,
	TWI_SlaveAddrWithRead,
	TWI_MasterWriteByte,
	TWI_MasterReadByte,
	TWI_SlaveWriteByte,
	TWI_SlaveReadByte,


}TWI_Error_t;

enum {
	TWI_WRITE = 0,
	TWI_READ = 1
}TWI_Action_t;
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void TWI_vMasterInit(u8 Copy_u8Address, u32 Copy_u32Clock);
void TWI_vSlaveInit(u8 Copy_u8SlaveAddr);

TWI_Error_t TWI_xStartCondition(void);

TWI_Error_t TWI_xReStartCondition(void);

void TWI_vStopCondition(void);

TWI_Error_t TWI_xSendSLA_Write(u8 Copy_u8Address);

TWI_Error_t TWI_xSendSLA_Read(u8 Copy_u8Address);

TWI_Error_t TWI_xSendDataByte(u8 Copy_u8SendData);
TWI_Error_t TWI_xMasterReadDataACK(u8* Copy_pu8ReadData);
TWI_Error_t TWI_xMasterReadDataNACK(u8* Copy_pu8ReadData);
TWI_Error_t TWI_xSlaveReadData(u8* Copy_pu8ReadData);


//API-Types


#endif /* MCAL_TWI_TWIERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TWI_Interface.h
 *********************************************************************************************************************/








