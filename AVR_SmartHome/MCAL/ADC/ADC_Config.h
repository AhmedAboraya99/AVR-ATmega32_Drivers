/*
 * ADC_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC_Private.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>
 *
 *********************************************************************************************************************/
#ifndef MCAL_ADC_CONFIG_H_
#define MCAL_ADC_CONFIG_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ADC_Private.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ADC_PIN 0 // ADC input pin (e.g. ADC0)
#define ADC_REF_VOLTAGE 5 // ADC reference voltage (in volts)
#define ADC_RESOLUTION 1024UL // ADC resolution (10 bits)
#define ADC_PRESCALER 128 // ADC prescaler (division factor)
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

//-----------------------------
//User type definitions (Enum)
//-----------------------------

enum{
	/*Bit 7 - ADEN: ADC Enable*/
	ADC_DISABLE = 0b0,
	ADC_ENABLE = 0b1,
}ACD_State_t;

#define ADC_ACTIVATION	ADC_ENABLE
 //@ref ADC_Mode_Define
 typedef enum{
	 //  Bit 5,6 -  ADATE: ADC Auto Trigger Enable, ADSC: ADC Start Conversion
	 ADC_STOP_CONVERSION = 0b00,
	 ADC_SINGLE_CONVERSION_MODE = 0b01,
	 ADC_AUTO_TRIGGERING = 0b10,
	 ADC_START_AUTO_TRIGGERING = 0b11,
 }ADC_Mode_t;

#define ADC_MODE_SELECTION		ADC_AUTO_TRIGGERING

//@ref Reference_Selection_Define
enum{
	// Bit 7:6 - REFS1:0: Reference Selection Bits
	ADC_AREF_PIN = 0b00,
	ADC_EXTERNAL_AVCC = 0b01,
	ADC_INTERNAL_256V = 0b11
}ACD_RefSelect_t;

#define ADC_REFERENCE_SELECTION		ADC_INTERNAL_256V

//@ref ADC_Channels_Define
//select ADC Channel to receive from
typedef enum{
	//  Bits 4:0 - MUX4:0: Analog Channel and Gain Selection Bits
	ADC_CHANNEL0 = 0b0000,
	ADC_CHANNEL1 = 0b0001,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
	ADC_CHANNEL8,
	ADC_CHANNEL9

}ADC_Channel_t;

#define ADC_CHANNEL_SELECTION		ADC_CHANNEL0

//@ref  ADC_TriggerSrc_Define
typedef enum{
	//  Bit 7:5 - ADTS2:0: ADC Auto Trigger Source
	ADC_FREE_RUNNING = 0b000,
	ADC_ANALOG_COMPARATOR_TRIGGER = 0b001,
	ADC_EXTERNAL_IRQ0_TRIGGER = 0b010,
	ADC_TIMER0_COMPMATCH_TRIGGER = 0b011,
	ADC_TIMER0_OVERFLOW_TRIGGER = 0b100,
	ADC_TIMER1_COMPMATCHB_TRIGGER = 0b101,
	ADC_TIMER1_OVERFLOW_TRIGGER = 0b110,
	ADC_TIMER1_CAPTUREEVENT_TRIGGER = 0b111

}ADC_TriggerSrc_t;

#define ADC_TRIGGER_SOURCE		ADC_FREE_RUNNING

//@ref  ADC_Prescaler_Define
typedef enum{
	//  Bits 2:0 - ADPS2:0: ADC Prescaler Select Bits
	ADC_PRESCALER_2 = (0b000),
	ADC_PRESCALER_4 = (0b010),
	ADC_PRESCALER_8 = (0b011),
	ADC_PRESCALER_16 = (0b100),
	ADC_PRESCALER_32 = (0b101),
	ADC_PRESCALER_64 = (0b110),
	ADC_PRESCALER_128 = (0b111),

}ADC_Prescaler_t;

#define ADC_PRESESCALAR_SELECTION	ADC_PRESCALER_128

// @ref ADC_IRQ_Define
typedef enum{
	ADC_IRQ_DISABLE = 0b0,
	ADC_IRQ_ENABLE  = 0b1,
}ADC_IRQ_t;

#define ADC_IRQ_ACTIVATION		ADC_IRQ_ENABLE

typedef enum{
	ADC_ADJUST_RIGHT = 0b0,
	ADC_ADJUST_LEFT  = 0b1,
}ADC_Adjust_t;

#define ADC_ADJUST_SELECTION	ADC_ADJUST_RIGHT

#define ADC_PORT		PORTA

#endif /* MCAL_ADC_CONFIG_H_ */
