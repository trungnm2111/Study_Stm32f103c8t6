#ifndef _DEBUG_H
#define _DEBUG_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "string.h"
#include "stdio.h"

void usart_sendchar(char _chr);
void usart_sendstr(char *str);
void usart1_innit(void);


#endif
