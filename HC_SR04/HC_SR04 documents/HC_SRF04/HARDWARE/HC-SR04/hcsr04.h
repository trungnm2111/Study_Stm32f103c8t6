/**
 *	HC-SR04 STM32F4xx devices

 * |----------------------------------------------------------------------
		 * 

 * Default pinout
 * 
 * 	HC-SR04			STM32F1xx		
 * 
 * 	TRIGGER			PB2				Trigger pin, to start sensor measurement
 * 	ECHO			PB3				Echo pin, read sensor signal
 * 	VCC				-				5V
 * 	GND				-				Ground
 * 
 * 
 * |----------------------------------------------------------------------

 */
#ifndef HCSR04_H
#define HCSR04_H 110
/**

 */
/**
 * Includes
 */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"


#define TRIG PBout(8)
#define ECHO PBin(9)
/* Default timeout pulses */
#ifndef HCSR04_TIMEOUT
#define HCSR04_TIMEOUT			1000000
#endif


/* Time to cm */
#define HCSR04_NUMBER			((float)0.027)		//(1s/58)=0.0171821

/**
 * Initialize HC-SR04 sensor
 * 
 * Returns 1 if sensor is ready to use, or 0 if not
 */
extern u8 HCSR04_Init(void);

/**
 * Start sensor measurement and read it's data
 * 
 * This function returns -1 if there was an error, or distance in cm if everything is OK
 */
extern float HCSR04_Read(void);

#endif
