#include "gpio.h"                  // Device header

void GPIO_delay(uint16_t time)
{
	uint16_t i, j;
	for(i = 0 ; i < time ; i++)
	{
		for(j = 0 ; j < 0x2aff ; j++);
	}
}
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_13 ;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOC, &GPIO );
}
void GPIO_TurnOn_Led(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13 );
	GPIO_delay(1000);
}

void GPIO_TurnOff_Led(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13 );
	GPIO_delay(1000);
}
