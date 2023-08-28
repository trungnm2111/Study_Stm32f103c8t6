/*
  ******************************************************************************
  * @file				uart.h                                                                  *
  * @author	    Nguyen Minh Trung                                                   *
  * @date				00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef _UART_H
#define _UART_H


#ifdef __cplusplus
 extern "C" {
#endif
/******************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stdio.h"
#include "string.h"
#include <stdarg.h>

extern uint8_t Recei[1000];

/******************************************************************************/	 
void USART_Config(unsigned int Baurates);
void USART_SendChar(char Char);
void USART_SendString(char *Str);
int USART_Compare(char *String);
int USART_FlagDB(void);

/******************************************************************************/	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
