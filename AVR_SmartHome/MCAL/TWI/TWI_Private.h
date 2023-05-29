/*
 * TWI_Private.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TWI_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_TWI_PRIVATE_H_
#define MCAL_TWI_PRIVATE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "TWI_Interface.h"

/**********************************************************************************************************************
 *  PRIVATE CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*TWCR - TWI Control Register*/
#define TWCR_REG 		*((volatile u8*) 0x56)

/*The TWINT bit in the TWCR is used to initiate
and ACKnowledge the completion of I2C operations*/
#define TWCR_TWINT		7	//TWI Interrupt Flag

/*The TWEA bit controls the generation of the ACKnowledge pulse. If the TWEA bit is Set to one,
 *  the ACK pulse is generated on the TWI bus if the following conditions are met:
1. The device’s own slave address has been received.
2. A general call has been received, while the TWGCE bit in the TWAR is set.
3. A data byte has been received in Master Receiver or Slave Receiver mode.*/
#define TWCR_TWEA		6	//TWI Enable ACKnowledge

#define TWCR_TWSTA		5	//
#define TWCR_TWSTO		4	//
#define TWCR_TWWC		3	//

/* The TWEN bit is used to enable the I2C interface.
 * When this bit is set to 1, the I2C interface is enabled and ready to transmit and receive data.
 * When this bit is cleared to 0, the I2C interface is disabled.*/
#define TWCR_TWEN		2	//TWI Enable

#define TWCR_TWIE		0	//TWI Interrupt Enable

/*TWSR - TWI Status Register*/
#define TWSR_REG 		*((volatile u8*) 0x21)
/*Bits 7:3 – TWSn: TWI Status Bit 7 [n = 7:3]*/
#define	TWSR_TWSn		3
/*Bits 1:0 – TWPSn: TWI Prescaler [n = 1:0]*/
#define TWSR_TWPSn		0

/*TWDR - TWI Data Register is a read/write register */
#define TWDR_REG 		*((volatile u8*) 0x23)

/* TWAR – TWI (Slave) Address Register */
#define TWAR_REG 		*((volatile u8*) 0x22)

/* Bit 0 – TWGCE: TWI General Call Recognition Enable Bit */
#define TWAR_TWCGE 		0

/* Bits 7:1 – TWAn: TWI (Slave) Address [n = 6:0] */
#define TWAR_TWAn 		1


/*TWBR – TWI Bit Rate Register*/
#define TWBR_REG 		*((volatile u8*) 0x20)
/* TWI DIO Pins */
#define	TWI_PORT		PORTB
#define	SDA_PIN			4
#define SCL_PIN			5


/*******************************
 * PRIVATE FUNCTIONS
 *******************************/
void TWI_vSendACK(void);
void TWI_vSendNACK(void);
void TWI_vEnable(void);

void TWI_vEnableACK(void);
void TWI_vDisableACK(void);
u8 TWI_xGetState(void);
void TWI_vWait_Tx_Rx(void);
void TWI_vEnable_Tx_Rx(void);


#endif /* MCAL_TWI_PRIVATE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TWI_Private.h
 *********************************************************************************************************************/


