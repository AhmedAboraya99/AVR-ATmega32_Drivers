#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <util/delay.h>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#define DPRINTF(...) {fflush(stdin);fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);fflush(stdout);\
				 }

/*	========================================================
	==================standard Type definition==============
	======================================================== */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long int s32;
typedef unsigned long long s64;

typedef float f32;
typedef double f64;
typedef long double f96;


typedef enum Boolean{
	FALSE,
	TRUE
}bool;

typedef enum
{
	RESET,
	SET
}STD_Status;

typedef enum
{
	DISABLE,
	ENABLE
}Functional_State;

/*
#define delay_ms(time) for(int i = 0;i<time;i++)\
						for(int j = 0;j<255;j++)
*/


#define SYSTEM_BUS_LENGTH		8

#define NULL_PTR		(void*)0
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#endif
