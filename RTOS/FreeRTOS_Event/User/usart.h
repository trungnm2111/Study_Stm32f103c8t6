/*
  ******************************************************************************
  * @file		usart.h                                                              *
  * @author	    Nguyen Van An                                                *
  * @date		23/04/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __USART__
#define __USART__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x_usart.h"  
#include "stdio.h"
#include <stdarg.h>

extern uint8_t Recei[1000];
int USART_FlagDB(void);
int USART_Compare(char *String);
void USART_SendChar(char Char);
void USART_SendString(char *Str);
void USART_Config(unsigned int Baurates);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
