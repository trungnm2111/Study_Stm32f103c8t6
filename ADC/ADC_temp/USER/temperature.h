/*
  ******************************************************************************
  * @file				adc.h                                                                  *
  * @author	    Nguyen Minh Trung                                                   *
  * @date				00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H


#ifdef __cplusplus
 extern "C" {
#endif
	 
/******************************************************************************/
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stdio.h"
#include "adc.h"
#include "math.h"
#include "delay.h" 
#include "uart.h"
	 
/******************************************************************************/	 
//double Convert_Thermistor();
double Convert_Thermistor(float v_out);
/******************************************************************************/	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

