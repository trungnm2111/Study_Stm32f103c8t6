/**	
 * |----------------------------------------------------------------------
		 * 

 * Default pinout
 * 
 * 	HC-SR04			STM32F4xx		Description
 * 
 * 	TRIGGER			PB2				Trigger pin, to start sensor measurement
 * 	ECHO			PB3				Echo pin, read sensor signal
 * 	VCC				-				5V
 * 	GND				-				Ground
 * 
 * 
 * |----------------------------------------------------------------------
 */
#include "hcsr04.h"

u8 HCSR04_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	/* Initialize pins */
	/* Enable clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	

	
	/* Set common settings */
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* Trigger pin */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* Echo pin */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* Trigger set to low */
	TRIG=0;
	
	/* Start measurement, check if sensor is working */
	if (HCSR04_Read() >= 0) {
		/* Sensor OK */
		return 1;
	}
	/* Sensor not ok */
	return 0;
}

float HCSR04_Read(void) {
	uint32_t time, timeout;
	float dis;
	/* Trigger low */
	TRIG=0;
	/* delay_us 2 us */
	delay_us(2);
	/* Trigger high for 10us */
	TRIG=1;
	/* delay_us 10 us */
	delay_us(10);
	/* Trigger low */
	TRIG=0;
	
	/* Give some time for response */
	timeout = HCSR04_TIMEOUT;
	while (ECHO == 0) {
		if (timeout-- == 0x00) {
			return -1;
		}
	}
	
	/* Start time */
	time = 0;
	/* Wait till signal is low */
	while (ECHO == 1) {
		/* Increase time */
		time++;
		/* delay_us 1us */
		delay_us(1);
	}
	
	/* Convert us to cm */
	dis = (float)time * HCSR04_NUMBER;
	/* Return distance */
	return dis;
}
