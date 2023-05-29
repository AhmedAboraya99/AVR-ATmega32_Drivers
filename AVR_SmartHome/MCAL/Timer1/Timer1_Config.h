/*
 * Timer_Config.h
 *
 *  Created on: Mar 28, 2023
 *      Author: ahmed
 */

#ifndef MCAL_TIMER_CONFIG_H_
#define MCAL_TIMER_CONFIG_H_

//-----------------------------
//User type definitions (Enum)
//-----------------------------


//@ref Timer_Clock_Define
typedef enum{
	TIMER1_NOCLKSRC = 0,
	TIMER1_NOPRESCALER = 1,
	TIMER1_CLKPRESCALER_8,
	TIMER1_CLKPRESCALER_64,
	TIMER1_CLKPRESCALER_256,
	TIMER1_CLKPRESCALER_1024,
	TIMER1_EXTCLKSRC_FALLING,
	TIMER1_EXTCLKSRC_RISING,

}TIMER1_eClkSrc;

#define TIMER1_CLOCK_SOURCE				TIMER1_CLKPRESCALER_8


//@ref TIMER1_Mode_Define
typedef enum{
	TIMER1_NORMAL_MODE 			=	0b0000,		//(WGM01:0 = 0). In this mode the counting direction is always up (incrementing), and no counter clear is performed.
	TIMER1_PHASE_PWM_8BIT_MODE 	= 	0b0001,		//(WGM01:0 = 1) provides a high resolution (phase correct PWM) waveform generation option.
	TIMER1_PHASE_PWM_9BIT_MODE 	= 	0b000,		//(WGM01:0 = 1) provides a high resolution (phase correct PWM) waveform generation option.
	TIMER1_PHASE_PWM_10BIT_MODE = 	0b0001,		//(WGM01:0 = 1) provides a high resolution (phase correct PWM) waveform generation option.
	TIMER1_FAST_PWM_8BIT_MODE 	= 	0b0101,
	TIMER1_CTC_MODE 			= 	0b1000,		//(WGM13:10 = 2) Clear Timer on Compare Match (CTC) Mode
	TIMER1_FAST_PWM_MODE_ICR1 	= 	0b1110,		//(WGM13:10 = 3) provides a high frequency PWM waveform generation option
	TIMER1_FAST_PWM_MODE_OCR1A 	= 	0b1111,		//(WGM13:10 = 3) provides a high frequency PWM waveform generation option

}TIMER1_eMode;

#define TIMER1_MODE_SELECTION		TIMER1_FAST_PWM_8BIT_MODE

// @ref TIMER1_IRQ_Define
typedef enum{
	TIMER1_IRQ_DISABLE = 0b0000,
	TIMER1_IRQ_TOIE1  = 0b0001,
	TIMER1_IRQ_OCIE1B = 0b0010,
	TIMER1_IRQ_TOIE1_OCIE1B = 0b0011,
	TIMER1_IRQ_OCIE1A = 0b0100,
	TIMER1_IRQ_TOIE1_OCIE1A = 0b0101,
	TIMER1_IRQ_TOIE1_OCIE1B_OCIE1A = 0b0111,
	TIMER1_IRQ_TICIE1 = 0b1000,
	TIMER1_IRQ_TICIE1_TOIE1 = 0b1001,
	TIMER1_IRQ_TICIE1_OCIE1B ,
	TIMER1_IRQ_TICIE1_TOIE1_OCIE1B,
	TIMER1_IRQ_TICIE1_OCIE1A,
	TIMER1_IRQ_TICIE1_TOIE1_OCIE1A,
	TIMER1_IRQ_TICIE1_OCIE1B_OCIE1A,
	TIMER1_IRQ_TICIE1_TOIE1_OCIE1B_OCIE1A
}TIMER1_eIRQ;

#define TIMER1_IRQSRC_SELECTION			TIMER1_IRQ_DISABLE


//@ref Compare_Mode_Define
typedef enum{
	TIMER1_NORMAL_PORT_OP = 0b00,
	TIMER1_TOGGLE_OC1_CM =  0b01,
	TIMER1_NONINVERTING_CLEAR= 0b10,
	TIMER1_INVERTING_SET = 0b11,
}Compare_eMode;

#define TIMER1_COMPARE_MODE			TIMER1_NONINVERTING_CLEAR


#endif /* MCAL_TIMER_CONFIG_H_ */
