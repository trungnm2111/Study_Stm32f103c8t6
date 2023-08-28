
/*
  ******************************************************************************
  * @file		hc-sr04_ic.h                                                              *
  * @author	NGUYEN MINH TRUNG                                                        *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/

#ifndef _HC_SR04_IC_H_
#define _HC_SR04_IC_H_

/******************************************************************************/

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "delay.h"
#include "uart.h"

/******************************************************************************/

#define   TRIG_PIN					GPIO_Pin_8		// TRIG : PB8 CHAN TRIG PHAI LA CHANNEL 3, 4
#define   TRIG_PORT					GPIOB
#define   ECHO_PIN					GPIO_Pin_6		// ECHO : PB6 CHAN ECHO PHAI LA CHANNEL 1, 2
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
