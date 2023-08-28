/*
  ******************************************************************************
  * @file		gpio.h                                                              *
  * @author	NGUYEN MINH TRUNG                                                        *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
#ifndef _GPIO_H_
#define _GPIO_H_

/******************************************************************************/

#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

/******************************************************************************/

/******************************************************************************/

void GPIO_delay(uint16_t time);
void GPIO_Config(void);
void GPIO_TurnOn_Led (void);
void GPIO_TurnOff_Led (void);

/******************************************************************************/
#endif
