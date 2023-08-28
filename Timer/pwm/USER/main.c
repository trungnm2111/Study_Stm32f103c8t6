#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

void pwm_config(void);

int main()
{
	pwm_config();
	TIM_SetCompare2(TIM2 , 5);
	while(1)
	{	
	}
}
void pwm_config(void)
{
	TIM_TimeBaseInitTypeDef tim2Init;
	TIM_OCInitTypeDef TIM_OCInit_str;
	GPIO_InitTypeDef gpio_initstr;
	// init tim2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	tim2Init.TIM_Prescaler = 72-1;
	tim2Init.TIM_Period = 100-1;
	tim2Init.TIM_RepetitionCounter = TIM_CounterMode_Up;
	tim2Init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit (TIM2 , &tim2Init);
	TIM_Cmd (TIM2 , ENABLE);

	//start tim2
	// init pwm seting
	TIM_OCInit_str.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit_str.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInit_str.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInit_str.TIM_Pulse = 10;
	TIM_OC1Init (TIM2 , &TIM_OCInit_str);

	
	// init gpio
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA , ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable ,ENABLE);
	gpio_initstr.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initstr.GPIO_Pin = GPIO_Pin_0;
	gpio_initstr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA , &gpio_initstr);
}
