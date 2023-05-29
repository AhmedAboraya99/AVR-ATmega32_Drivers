/*
 * TWI_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TWI_Config.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_TWI_CONFIG_H_
#define MCAL_TWI_CONFIG_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CONFIGURATION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


//@ref TWI_Mode_define
/* Transmission Modes */
enum {

 TWI_MODE_MASTER_TRANSMITTER	=	0b00,
 TWI_MODE_MASTER_RECEIVER		=	0b01,
 TWI_MODE_SLAVE_TRANSMITTER		=	0b10,
 TWI_MODE_SLAVE_RECEIVER		=	0b11,

} TWI_Mode_t;



//@ref Prescaler_define

typedef enum{
	TWI_PRESCALER_1 = (0b00),
	TWI_PRESCALER_4 = (0b01),
	TWI_PRESCALER_16 = (0b10),
	TWI_PRESCALER_64 = (0b11),

}TWI_Prescaler_t;

#define TWI_PRESCALER_SELECTION		TWI_PRESCALER_1


//@ref General_Call_define
//Bit 0 – TWGCE: TWI General Call Recognition Enable Bit
enum
{
	TWI_GENERALCALL_DISABLE		=  0b0,
	TWI_GENERALCALL_ENABLE		=  0b1,
}TWI_GeneralCall_t;
#define TWI_GENERALCALL_ACTIVATION		TWI_GENERALCALL_ENABLE

//@ref IRQ_Enable_define
//Bit 0 – TWIE: TWI Interrupt Enable
enum{
  TWI_IRQ_DISABLE			=  0b0,
  TWI_IRQ_ENABLE			=  0b1,
}TWI_IRQ_t;

#define TWI_IRQ_ACTIVATION		TWI_IRQ_DISABLE



#endif /* MCAL_TWI_CONFIG_H_ */
