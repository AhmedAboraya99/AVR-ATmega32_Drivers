#ifndef	BIT_MATH_H_
#define	BIT_MATH_H_
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STD_TYPES.h"

/**********************************************************************************************************************
 *  GLOBAL DATA DEFITNITIONS
 *********************************************************************************************************************/
enum{
    ONE_BIT = 1,
    TWO_BITS,
    THREE_BITS,
    FOUR_BITS,
    FIVE_BITS,
    SIX_BITS,
    SEVEN_BITS,
	EIGHT_BITS
}BitsLength_t;

//@ pin_id_options
typedef enum {
    BIT0,
    BIT1,
    BIT2,
    BIT3,
    BIT4,
    BIT5,
    BIT6,
    BIT7
}Bits_t;
/**********************************************************************************************************************
 *  GLOBAL MACROS
 *********************************************************************************************************************/
#define LOW_NIBBLE		0x0F
#define HIGH_NIBBLE		0xF0

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/* BIT Math functions like macros */
#define SET_BIT(VAR,BIT)			(VAR |= (1<<BIT))
#define GET_BIT(VAR,BIT)			((VAR >> BIT) & 1)
#define CLEAR_BIT(VAR,BIT)			(VAR &= ~(1<<BIT))
#define TOGGLE_BIT(VAR,BIT)			(VAR ^= (1<<BIT))
#define TOGGLE_PORT(VAR)			(VAR ^= 1)
#define MASK(LEN)				 	(( 1<<(LEN))-1)
#define BITS_MASK(START,LEN) 		( MASK(LEN)<<(START) )

#define WRITE_BITS(REG, MASK, VALUE)  	(REG = ((REG & ~(MASK)) | ((VALUE) & (MASK))))

#define	READ_BITS(VAR,START,LEN)		(VAR & (BITS_MASK(START,LEN)) )

#define ASSIGN_BITS(VAR,START,LEN,VAL)		(VAR =	(VAR & (~( (BITS_MASK(START,LEN)) ))) | ( ((VAL<<START)&BITS_MASK(START,LEN))))
#define ASSIGN_BIT(VAR,START,VAL)			ASSIGN_BITS(VAR,START,ONE_BIT,VAL)

#define WRITE_REG(REG, VAL)             (REG = VAL)
#define RESET_REG(REG)                  (REG = 0)
#define SET_REG(REG, VAL)               (REG = ~0)
#define READ_REG(REG)                   (REG)

#define RESET_CONFIG(VAR,VAL,BIT)	    (VAR &= ~(VAL<<BIT))
#define GET_NUM(VAR)				    (VAR-'0')


#endif
