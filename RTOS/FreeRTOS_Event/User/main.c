#include "stm32f10x.h"                  // Device header
#include "system.h"
#include "usart.h"
#include "stdio.h"
#include "gpio.h"
uint8_t Recei[1000];

int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	GPIO_config();
	USART_Config(9600);
	RTOS_Run();
	return 0;
}