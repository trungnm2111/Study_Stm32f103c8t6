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

extern uint8_t arr_data_fsm[50];
extern uint8_t string_receive[500];
extern uint8_t fsm_flag_receive ;

/******************************************************************************/	

void Usart_Config (USART_TypeDef * USARTx, uint32_t BaudRate );
void Usart_Send_Char(char _chr);
void Usart_Send_String(char *str);
void Usart_SendNumber(float number);
uint16_t Usart_Compare(char *string);
uint8_t Usart_CheckFlag (void );
void Usart_Put_Char_Receive (void);
void Uart_Send_Byte(uint8_t byte);
uint8_t Usart_CheckFlag_Fsm (void );

/******************************************************************************/	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
