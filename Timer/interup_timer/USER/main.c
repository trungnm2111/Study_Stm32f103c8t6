#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

uint8_t led_status = 0;

void LedInit(void);
void Tim2Config(void);


int main()
{
	LedInit();
	Tim2Config();
	while(1)
	{
	}
}
void LedInit(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP ;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOC , &gpio);
}
void Tim2Config(void)
{
	TIM_TimeBaseInitTypeDef tim_innit_structure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	tim_innit_structure.TIM_CounterMode = TIM_CounterMode_Up;
	tim_innit_structure.TIM_Period = 9999;
	tim_innit_structure.TIM_Prescaler = 7199;
	tim_innit_structure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &tim_innit_structure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig (TIM2 , TIM_FLAG_Update, ENABLE);
	NVIC_EnableIRQ (TIM2_IRQn);
	TIM_Cmd (TIM2, ENABLE);
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET)
	{
		if(led_status == 1 )
		{
			GPIO_SetBits(GPIOC , GPIO_Pin_13);
			led_status = 0;
		}
		else 
		{
			GPIO_ResetBits(GPIOC , GPIO_Pin_13);
			led_status = 1;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	}
}
