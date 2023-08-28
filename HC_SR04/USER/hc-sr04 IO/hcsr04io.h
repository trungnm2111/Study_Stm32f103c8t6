
/*
  ******************************************************************************
  * @file		hc-sr04io.h                                                              *
  * @author	NGUYEN MINH TRUNG                                                        *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/

#ifndef _HCSR04IO_H_
#define _HCSR04IO_H_

/******************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "delay.h"
#include "uart.h"
/******************************************************************************/

#define   TRIG_PIN					GPIO_Pin_8		// TRIG : PA1 
#define   TRIG_PORT					GPIOB
#define   ECHO_PIN					GPIO_Pin_6		// ECHO : PA0
#define   ECHO_PORT					GPIOB
#define   TIM_USER					TIM4
#define   CLOCK_TIM_USER		RCC_APB1Periph_TIM4	


extern int distance;
/******************************************************************************/

extern void initPins(void) ;
extern void HCSR04_Init(void);
extern void HCSR04_GetDistance(void) ;

/******************************************************************************/
#endif
