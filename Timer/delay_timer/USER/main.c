#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


uint8_t led_status = 0;

void led_innit(void);
void timer_innit(void);
void delay_ms(uint16_t time_ms);
void delay_1ms(void);
//void delay(uint16_t time );


int main()
{
	led_innit();
//	timer_innit();
	while(1)
	{
		GPIO_ResetBits(GPIOC , GPIO_Pin_13);
		delay_ms(10);
		GPIO_SetBits(GPIOC , GPIO_Pin_13);
		delay_ms(10);
	}
}
void led_innit(void)
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP ;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOC , &gpio);
}
void timer_innit(void)
{
	TIM_TimeBaseInitTypeDef timerInit;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Prescaler = 72-1;
	timerInit.TIM_Period = 65536-1 ;
//	timerInit.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInit);

}

void delay_1ms(void)
{
	timer_innit();
	TIM_Cmd (TIM2, ENABLE);
	TIM_SetCounter(TIM2 , 0);
	while(TIM_GetCounter(TIM2) < 36000 );
	TIM_Cmd(TIM2 , DISABLE);
}
void delay_ms(uint16_t time)
{
	while(time--)
	{
		delay_1ms();
	}
}
