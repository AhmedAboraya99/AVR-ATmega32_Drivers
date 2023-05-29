/*
 * STD_API.c
 *
 *  Created on: May 13, 2023
 *      Author: ahmed
 */
#include "STD_API.h"


s8 compare_string(u8 *Copy_st8First, u8 *Copy_st8Second)
{
   while(*Copy_st8First==*Copy_st8Second)
   {
      if ( *Copy_st8First == '\0' || *Copy_st8Second == '\0' )
         break;

      Copy_st8First++;
      Copy_st8Second++;
   }
   if( *Copy_st8First == '\0' && *Copy_st8Second == '\0' )
      return 0;
   else
      return -1;
}

void delay_ms(u16 ms)
{
    for (u16 i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

u8* NumtoStr(u16 num)
{
    u16 i = 0;
    u16 sign = 0;
    u8* str = malloc(sizeof(u8*));

    // Extract digits in reverse order
    do {
        str[i++] = num % 10 + 48;
        num /= 10;
    } while (num > 0);


    // Reverse the string
    for (u16 j = 0; j < i / 2; j++) {
        u8 tmp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = tmp;
    }

    // Add null terminator
    str[i] = '\0';

    return str;
}
