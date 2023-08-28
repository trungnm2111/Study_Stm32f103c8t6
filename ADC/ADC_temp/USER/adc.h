/*
  ******************************************************************************
  * @file				adc.h                                                                  *
  * @author	    Nguyen Minh Trung                                                   *
  * @date				00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef _ADC_H
#define _ADC_H


#ifdef __cplusplus
 extern "C" {
#endif
/******************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stdio.h"

/******************************************************************************/	 
void GPIO_config(void);
void ADC_Config(void);
int ADCx_Read(void);

/******************************************************************************/	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

