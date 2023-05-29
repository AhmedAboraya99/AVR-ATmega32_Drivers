/*
 * TIMER0_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIMER0_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define OVERFLOW_INDEX			0
#define COMPAREMATCH_INDEX		1
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
void TIMER0_voidInit();
void TIMER0_voidStart(void);
void TIMER0_voidStop(void);
void TIMER0_voidSetPreloadVal(u8 Copy_u8PreloadVal);
void TIMER0_voidSetCallBackOVF(void (*TIMER0_pOvfCallBack)(void));
void TIMER0_voidSetCallBackCTC(void (*TIMER0_pCmpCallBack)(void));
u8 TIMER0_u8GetCountVal(void);
void TIMER0_voidSetCompareVal(u8 Copy_u8compVal);
void TIMER0_voidSetCmpMatchOvf(u8 Copy_u8CmpVal);

void TIMER0_voidTurnOn(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void TIMER0_voidTurnOff(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void TIMER0_voidToggle(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);

void TIMER0_voidTurnOn_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u8 Copy_u8Duration);
void TIMER0_voidTurnOff_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u8 Copy_u8Duration);
void TIMER0_voidToggle_ms(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId, u8 Copy_u8Duration);



//API-Types


#endif /* MCAL_TIMER0_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIMER0_Interface.h
 *********************************************************************************************************************/








