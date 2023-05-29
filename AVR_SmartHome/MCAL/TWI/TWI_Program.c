/*
 * TWI_Program.c
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  TWI_Program.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into groups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "TWI_Private.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
u8 Global_Au8Prescaler[4] = {1, 4, 16, 64};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*Set Master Address to 0 if master will not be addressed*/

void TWI_vMasterInit(u8 Copy_u8Address, u32 Copy_u32Clock)
{

	/*Enable Acknowledge Bit*/
	TWI_vEnableACK();


	/*  Set TWBR with Copy_u32Clock value in KHz */
	TWBR_REG = ((F_CPU/(Copy_u32Clock*1000UL))- 16) / (2*Global_Au8Prescaler[TWI_PRESCALER_SELECTION]);
	/* Set Prescaler */
	ASSIGN_BITS(TWSR_REG, TWSR_TWPSn, TWO_BITS,TWI_PRESCALER_SELECTION);


	/*Check if the master node will be addressed or not*/
		if(Copy_u8Address == 0)
		{
			/*Do Nothing*/
		}
		else
		{
			/*Set The Required Address to The Master*/
			ASSIGN_BITS(TWAR_REG, TWAR_TWAn, SEVEN_BITS,Copy_u8Address);
		}

	/* Enable TWI */
	TWI_vEnable();
}


void TWI_vSlaveInit(u8 Copy_u8SlaveAddr)
{
	/*Enable Acknowledge Bit*/
	TWI_vEnableACK();

	/* Set Salve Address */
	ASSIGN_BITS(TWAR_REG, TWAR_TWAn, SEVEN_BITS, Copy_u8SlaveAddr);

	/* Enable TWI */
	TWI_vEnable();

}


TWI_Error_t TWI_xStartCondition(void)
{

	u8 Local_u8State = TWI_NOK;


	/*Send START condition*/
	SET_BIT (TWCR_REG, TWCR_TWSTA);

	/*Enable Transmission */
	TWI_vEnable_Tx_Rx();

	/* wait for flag to be cleared : the TWINT bit in TWCR is set */
	TWI_vWait_Tx_Rx();

	 if(TWI_xGetState() == TWI_MSTR_START || TWI_xGetState() == TWI_MSTR_REPEATEDSTART)
		 Local_u8State = TWI_StartCondition;


	return Local_u8State;
}


TWI_Error_t TWI_xReStartCondition(void)
{

	return TWI_xStartCondition();
}

void TWI_vStopCondition(void)
{


	/*Send Stop condition*/
	SET_BIT (TWCR_REG, TWCR_TWSTO);

	/*Enable Transmission */
	TWI_vEnable_Tx_Rx();

	//delay to ensure that the stop condition is transmitted .
	// _delay_ms(10);
}

TWI_Error_t TWI_xSendSLA_Write(u8 Copy_u8Address)
{
	u8 Local_u8State = TWI_NOK;



		ASSIGN_BITS(TWDR_REG,BIT1, SEVEN_BITS,Copy_u8Address);
		ASSIGN_BIT(TWDR_REG,BIT0, TWI_WRITE);

		CLEAR_BIT(TWCR_REG, TWCR_TWSTA);
		/* Start data transmission */
		TWI_vEnable_Tx_Rx();

		/* wait for flag to be cleared : the TWINT bit in TWCR is set */
		TWI_vWait_Tx_Rx();


		 if(TWI_xGetState() == TWI_MT_SLAW_ACK || TWI_xGetState() == TWI_MT_SLAW_NACK)
			Local_u8State = TWI_SlaveAddrWithWrite;

	return (Local_u8State);

}

TWI_Error_t TWI_xSendSLA_Read(u8 Copy_u8Address)
{

	u8 Local_u8State = TWI_NOK;



		/*Set 7 bits slave address to the bus with read request*/
		ASSIGN_BITS(TWDR_REG,BIT1, SEVEN_BITS,Copy_u8Address);
		ASSIGN_BIT(TWDR_REG,BIT0, TWI_READ);

		CLEAR_BIT(TWCR_REG, TWCR_TWSTA);
		/*Enable Transmission */
		TWI_vEnable_Tx_Rx();

		/* wait for flag to be cleared : the TWINT bit in TWCR is set */
		TWI_vWait_Tx_Rx();

		 if(TWI_xGetState() == TWI_MR_SLAR_ACK || TWI_xGetState() == TWI_MR_SLAR_NACK )

			 Local_u8State = TWI_SlaveAddrWithRead;


	return (Local_u8State);

}


TWI_Error_t TWI_xSendDataByte(u8 Copy_u8SendData)
{
	TWI_Error_t Local_u8State = TWI_NOK;
	// Write the data to the TWDR register


	// write DATA on SDA
	TWDR_REG = Copy_u8SendData;

	//set the TWINT and TWEN bits in the TWCR register.
	 TWI_vEnable_Tx_Rx();

	/* Wait for empty transmit buffer */
	TWI_vWait_Tx_Rx();

	if (TWI_xGetState() == TWI_MT_DATA_ACK || TWI_xGetState() == TWI_MT_DATA_NACK)
		Local_u8State = TWI_MasterWriteByte;

	return Local_u8State;
}

TWI_Error_t TWI_xMasterReadDataACK(u8* Copy_pu8ReadData)
{
	TWI_Error_t Local_u8State = TWI_NOK;

	/*Clear The TWINT Flag, To Make The Slave To Send its Data*/
	 TWI_vEnable_Tx_Rx();

	/* Wait for data to be received */
	TWI_vWait_Tx_Rx();


	switch (TWI_xGetState())  // Check TWI status
	{
		case TWI_MR_SLAR_ACK:  // Own SLA+W received
		case TWI_MR_SLAR_NACK:  // Arbitration lost, own SLA+W received
			Local_u8State = TWI_SlaveAddrWithRead;
			break;

		case TWI_MR_DATA_NACK:  // Data byte received
		case TWI_MR_DATA_ACK:  // Data byte received, NACK sent
			/* Get and return received data from buffer */
			*Copy_pu8ReadData = TWDR_REG;
			Local_u8State = TWI_MasterReadByte;
			break;
		default:
			Local_u8State = TWI_NOK;
			break;
	}

	return Local_u8State;
}

TWI_Error_t TWI_xMasterReadDataNACK(u8* Copy_pu8ReadData)
{
	TWI_Error_t Local_u8State = TWI_NOK;
	// Disable ACK
	TWI_vDisableACK();
	/*Clear The TWINT Flag, To Make The Slave To Send its Data*/
	 TWI_vEnable_Tx_Rx();

	/* Wait for data to be received */
	TWI_vWait_Tx_Rx();


	switch (TWI_xGetState())  // Check TWI status
	{
		case TWI_MR_SLAR_ACK:  // Own SLA+W received
		case TWI_MR_SLAR_NACK:  // Arbitration lost, own SLA+W received
			Local_u8State = TWI_SlaveAddrWithRead;
			break;

		case TWI_MR_DATA_NACK:  // Data byte received
		case TWI_MR_DATA_ACK:  // Data byte received, NACK sent
			/* Get and return received data from buffer */
			*Copy_pu8ReadData = TWDR_REG;
			Local_u8State = TWI_MasterReadByte;
			break;
		default:
			Local_u8State = TWI_NOK;
			break;
	}

	/*Enable Acknowledge Bit*/
	TWI_vEnableACK();

	return Local_u8State;
}

TWI_Error_t TWI_xSlaveReadData(u8* Copy_pu8ReadData)
{
	TWI_Error_t Local_u8State = TWI_NOK;


	/* Wait for data to be received */
	TWI_vWait_Tx_Rx();


	switch (TWI_xGetState())  // Check TWI status
	{
		case TWI_SR_SLAW_ACK:  // Own SLA+W received
		case TWI_SR_SLAW_NACK:  // Arbitration lost, own SLA+W received
			//TWI_vSendACK();
			break;

		case TWI_SR_DATA_NACK:  // Data byte received
		case TWI_SR_DATA_ACK:  // Data byte received, NACK sent
			/* Get and return received data from buffer */
			*Copy_pu8ReadData = TWDR_REG;
			TWI_vSendACK();

			Local_u8State = TWI_SlaveReadByte;
			break;
		case TWI_SR_SLAR_STOP:	/* Check whether STOP/REPEATED START */

			TWCR_REG |= (1 << TWCR_TWINT);
			break;
	}




	return Local_u8State;
}

void TWI_vSendACK(void)
{

	TWCR_REG |=  (1 << TWCR_TWEA) | (1 << TWCR_TWINT);

}

void TWI_vSendNACK(void)
{

	SET_BIT(TWCR_REG, TWCR_TWINT);
	SET_BIT(TWCR_REG, TWCR_TWEN);

	 TWI_vWait_Tx_Rx();

}

void TWI_vEnable(void)
{

	SET_BIT( TWCR_REG, TWCR_TWEN);

}

void TWI_vEnableACK(void)
{

	SET_BIT(TWCR_REG, TWCR_TWEA);

}
void TWI_vDisableACK(void)
{

	CLEAR_BIT(TWCR_REG, TWCR_TWEA);

}
u8 TWI_xGetState(void)
{
	u8 TWSR_u8TempReg = TWSR_REG;
	ASSIGN_BITS(TWSR_u8TempReg,BIT0,THREE_BITS,0);
	return (TWSR_u8TempReg);

}

void TWI_vWait_Tx_Rx(void)
{
	/* wait for flag to be cleared
	 * >The TWI will not start any operation as long as
	 * the TWINT bit in TWCR is set */
	while(!GET_BIT(TWCR_REG,TWCR_TWINT));

}
void TWI_vEnable_Tx_Rx(void)
{


	 //start transmission
	/* Clear flag by Writing a one to TWINT */

	SET_BIT (TWCR_REG,TWCR_TWINT);


}


/**********************************************************************************************************************
 *  END OF FILE: TWI_Program.c
 *********************************************************************************************************************/


