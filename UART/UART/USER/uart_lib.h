/*
  ******************************************************************************
  * @file		uart_lib.h                                                              *
  * @author	NGUYEN MINH TRUNG                                                        *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/

#ifndef _UART_LIB_H_
#define _UART_LIB_H_

/******************************************************************************/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"             
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"

/******************************************************************************/
#define TX GPIO_Pin_9
#define RX GPIO_Pin_10
#define LED GPIO_Pin_13
#define string_size 80  // kich co mang 

extern char RX_FLAG_END_LINE;
extern char RRX[string_size];

/******************************************************************************/

void config_GPIO_LED(void);
void config_USART(unsigned int BaudRates);
void Usart_SendChar(char _ch);
void Usart_SendString(char *_str);
void Usart_SendNumber(int _number);
void Putchar(char *String);

/******************************************************************************/
#endif


