#include "stm32f10x.h"                  // Device header
#include "delay.h"  

volatile int usTicks = 0;

void SysTick_Handler(void) 
{
	if(usTicks != 0)
	{
		usTicks --;
	}
}

void DelayInit(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000000);
}
void DelayUs(uint32_t Time)
{
	usTicks = Time;
	while(usTicks);
}
void DelayMs(uint32_t Time)
{
	while(Time--) 
	{
		DelayUs(1000);
	}
}
