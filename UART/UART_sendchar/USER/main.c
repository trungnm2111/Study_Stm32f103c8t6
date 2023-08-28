#include "stm32f10x.h"                  // Device header
#include "debug.h"

void  delay ( uint16_t time)
{
	uint16_t i , j ;
	for( i = 0 ; i < time ; i++)
	{
		for( j = 0 ; j < 0x2AFF ; j++);
	}
}
int main()
{
	usart1_innit();
	while(1)
	{
		printf("Lap trinh nhung iot \n");
		delay(500);
	}
}
