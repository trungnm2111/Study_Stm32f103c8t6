#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x_usart.h"
#include "string.h"
#include "stdio.h"

#define string_size 80  

extern char RX_FLAG_END_LINE;
extern char RRX[string_size];
extern char RRX2[string_size];
extern char temp_char;   

void uart_Init(void);
void uart_SendChar(char _chr);
void uart_SendStr(char *str);
void Putchar(char *String);
void cut_string(void);


#endif

