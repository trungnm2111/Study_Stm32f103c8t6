#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "gpio.h"
#include "uart.h"

uint8_t Recei[1000];

int main()
{
	GPIO_Config();
	SystemInit();
	SystemCoreClockUpdate();
	USART_Config(9600);
	while(1)
	{
		RTOS_Run();
	}
}
