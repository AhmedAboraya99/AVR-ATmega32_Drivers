/*
 * TIMER0_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TIMER0_CONFIG_H_
#define MCAL_TIMER0_CONFIG_H_

//-----------------------------
//User type definitions (Enum)
//-----------------------------

enum {
	TIMER0,
	TIMER1,
	TIMER2
}TIMER0_eID;

//@ref TIMER0_Clock_Define
typedef enum{
	TIMER0_NOCLKSRC = 0,
	TIMER0_NOPRESCALER = 1,
	TIMER0_CLKPRESCALER_8,
	TIMER0_CLKPRESCALER_64,
	TIMER0_CLKPRESCALER_256,
	TIMER0_CLKPRESCALER_1024,
	TIMER0_EXTCLKSRC_FALLING,
	TIMER0_EXTCLKSRC_RISING,
}TIMER0_eClkSrc;

#define TIMER0_CLOCK_SOURCE				TIMER0_CLKPRESCALER_8


//@ref TIMER0_Mode_Define
typedef enum{
	TIMER0_NORMAL_MODE 		=	0b0000,		//(WGM01:0 = 0). In this mode the counting direction is always up (incrementing), and no counter clear is performed.
	TIMER0_PHASE_PWM_MODE 	= 	0b0001,		//(WGM01:0 = 1) provides a high resolution (phase correct PWM) waveform generation option.
	TIMER0_CTC_MODE 		= 	0b1000,		//(WGM01:0 = 2) Clear Timer on Compare Match (CTC) Mode
	TIMER0_FAST_PWM_MODE 	= 	0b1001,		//(WGM01:0 = 3) provides a high frequency PWM waveform generation option
}TIMER0_eMode;

#define TIMER0_MODE_SELECTION		TIMER0_FAST_PWM_MODE

// @ref TIMER0_IRQ_Define
typedef enum{
	TIMER0_IRQ_DISABLE = 0b0,
	TIMER0_IRQ_TOIE  = 0b1,
	TIMER0_IRQ_OCIE ,
	TIMER0_IRQ_TOIE_OCIE
}TIMER0_eIRQ;

#define TIMER0_IRQSRC_SELECTION			TIMER0_IRQ_DISABLE


//@ref Compare_Mode_Define
typedef enum{
	TIMER0_NORMAL_PORT_OP = 0b00,
	TIMER0_TOGGLE_OC0_CM =  0b01,
	TIMER0_NONINVERTING_CLEAR = 0b10,
	TIMER0_INVERTING_SET = 0b11,
}Compare_Mode_t;

#define TIMER0_COMPARE_MODE			TIMER0_NONINVERTING_CLEAR


#endif /* MCAL_TIMER0_CONFIG_H_ */
