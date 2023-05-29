/*
 * TIMER1_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  TIMER1_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_Timer_INTERFACE_H_
#define MCAL_Timer_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Private.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define OVERFLOW_INDEX				0
#define COMPARE_MATCH_INDEX			1
#define INPUT_CAPTURE_INDEX			2

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum SenseEdge
{
	SENSE_FALLING_EDGE = 0,
	SENSE_RISING_EDGE = 1,
}ICU_SenseEdge_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void TIMER1_voidInit();
void TIMER1_voidStart();
void TIMER1_voidStop();

void TIMER1_voidSetPreloadVal(u16 Copy_u16PreloadVal);
void TIMER1_voidSetCallBackOVF(void (*Timer_pOvfCallBack)(void));
void TIMER1_voidSetCallBackCTC(void (*TIMER1_pCmpCallBack)(void));
void TIMER1_voidSetCallBackCAPT(void (*TIMER1_pCaptCallBack)(void));

u16 TIMER1_u16GetCountVal(void);
u16 TIMER1_u16GetInCaptVal();

void TIMER1_voidSetCompareVal(u16 Copy_u16compVal);
void TIMER1_voidSetCaptVal(u16 Copy_u16CaptVal);
void TIMER1_vDisICU_INT();
void TIMER1_voidSetTriggerSense(ICU_SenseEdge_t Trigger_Edge);

void TIMER1_voidTurnOn(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);
void TIMER1_voidTurnOff(DIO_Port_t Copy_u8PortId,DIO_Pin_t Copy_u8PinId);


//API-Types


#endif /* MCAL_Timer_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: TIMER1_Interface.h
 *********************************************************************************************************************/








