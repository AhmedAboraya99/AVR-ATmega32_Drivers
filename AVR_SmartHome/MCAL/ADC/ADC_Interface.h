/*
 * ADC_Interface.h
 *
 *  Created on: Mar 27, 2023
 *      Author: ahmed
 */
/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC_Interface.h
 *       Module:  -
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "ADC_Config.h"

#include "../GINT/GINT_Interface.h"
#include "../DIO/DIO_Interface.h"
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
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*******API-Functions******/
void ADC_voidInit(void);
u16 ADC_u16GetDigitalVal(ADC_Channel_t Copy_u8Channel);

void ADC_vStartConversion(ADC_Channel_t Copy_u8Channel);
void ADC_vStopConversion(void);
u8 ADC_u8ReadPort(DIO_Port_t Copy_u8PortId);

void ADC_vSetCallBack(void (*Copy_vCallback)(void), ADC_Channel_t Copy_xADCChannel);

//API-Types


#endif /* MCAL_ADC_INTERFACE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: ADC_Interface.h
 *********************************************************************************************************************/








