#include "hc_sr04_ic.h"

int main()
{
	TimerInit();
	uart_Init();
	initPins();;
	HCSR04_Init ();
	while(1)
	{
		usart_sendstr("<------> \n");
		HCSR04_GetDistance();
		printf("distance: %d mm\n", distance);
		usart_sendstr("-------------------------\n");
		Delay_us(10);
	}
}
