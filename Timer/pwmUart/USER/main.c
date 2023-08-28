#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "string.h"
#include "uart.h"
#include "stdlib.h"

void gpioInit(void);
void pwmInit(void );
void dutyFreq_uartCf(uint16_t duty, uint16_t freq);
uint16_t period, duty, freq, dutySet;

int main()
{
	gpioInit();
	pwmInit();
	uart_Init();
	while(1)
	{

	}
}

void gpioInit(void)
{
	GPIO_InitTypeDef gpio;
	//init gpio 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable ,ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA , &gpio);
	// init button
	gpio.GPIO_Mode = GPIO_Mode_IPU ;
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 
								| GPIO_Pin_8 | GPIO_Pin_9 ;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOB , &gpio);
}

void pwmInit(void )
{
	TIM_TimeBaseInitTypeDef tim2Init;
	TIM_OCInitTypeDef timocInit;
	
	//innit  tim2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	tim2Init.TIM_CounterMode = TIM_CounterMode_Up;
	tim2Init.TIM_Prescaler = 72 - 1;
	tim2Init.TIM_Period = 100 - 1;
	tim2Init.TIM_ClockDivision = TIM_CKD_DIV1;
	tim2Init.TIM_RepetitionCounter = 0 ;
	TIM_TimeBaseInit (TIM2 , &tim2Init);
	TIM_Cmd(TIM2, ENABLE);
	
	// swm init 
	timocInit.TIM_OCMode = TIM_OCMode_PWM1;
	timocInit.TIM_OCPolarity = TIM_OCPolarity_High;
	timocInit.TIM_OutputState = TIM_OutputState_Enable;
	timocInit.TIM_Pulse = 50 ;
	TIM_OC1Init (TIM2, &timocInit);
}

void dutyFreq_uartCf(uint16_t duty, uint16_t freq)
{
	period = (float)1000000 / freq ;
	dutySet = (float)period /1000 * duty;
	TIM_SetAutoreload (TIM2, period - 1);
	TIM_SetCompare1 (TIM2, dutySet + 1 );
}

void uartCf(void)
{
	if(RX_FLAG_END_LINE == 1)  
		{	
			cut_string();
			printf("<->");		
			duty = atoi(RRX);
			freq = atoi(RRX2);
			printf("duty : %d ", duty);
			printf("freq : %d ", freq);
			dutyFreq_uartCf(duty , freq);
			printf("\n-------------------------\n");
			RX_FLAG_END_LINE = 0;		
		}
}