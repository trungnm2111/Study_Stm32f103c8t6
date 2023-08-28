#include "stm32f10x.h"  
#include "systick.h"
#include "Led7seg.h"
volatile uint16_t count  = 1, data_diplay;
volatile unsigned char systick_tick = 0;

//void systick_Init(void)
//{
//	SystemCoreClockUpdate();
//	SysTick_Config(SystemCoreClock/1000); 
//} 
//void Systick_Handler(void)
//{
//	systick_count ++;
//}
void SysTick_Handler (void)
{
		if(systick_tick == 10)
	{
		systick_tick = 0;
		led7seg_scanled(count , data_diplay );
		count++;
		if(count > 4)
		{
			count = 1;
		}
	}	
	systick_tick++;
}

void systick_scanled( uint16_t numbers_display)
{
	data_diplay = numbers_display ;
}

