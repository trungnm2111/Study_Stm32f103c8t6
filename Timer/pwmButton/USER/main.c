#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "uart.h"

uint16_t  duty = 50 , count = 100  ;
uint8_t sttDutyUp_old = 1,   sttDutyUp_new = 1;
uint8_t sttDutyDown_old = 1, sttDutyDown_new = 1;
uint8_t sttFreqUp_old = 1,   sttFreqUp_new = 1;
uint8_t sttFreqDown_new = 1, sttFreqDown_old = 1;

int period ;
int x;

void gpioInit(void );
void pwmInit(void );
void button_duty(void );
//void button_freq(void);
void Delay_ms(uint16_t _time);
void button_freq(int duty, int freq);

int main()
{
	gpioInit();
	pwmInit();
	uart_Init();
	while(1)
	{		
		button_duty();
		button_freq(54 , 3000);
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

void button_duty(void )
{
	sttDutyUp_old = sttDutyUp_new;
	sttDutyUp_new = GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_8);
	if(sttDutyUp_new == 0 && sttDutyUp_old == 1) 
	{ 
		duty +=5;
	}
	sttDutyDown_old = sttDutyDown_new;
	sttDutyDown_new = GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_9);
	if(sttDutyDown_new == 0 && sttDutyDown_old == 1) 
	{
		duty -= 5;
	}
	Delay_ms(1);  //3khz 72
	TIM_SetCompare1(TIM2 , duty );
}

//void button_freq(void)
//{
//	sttFreqUp_old = sttFreqUp_new;
//	sttFreqUp_new = GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_7);
//	if(sttFreqUp_new == 0 && sttFreqUp_old == 1) 
//	{
//		count -= 10;
//		
//	}
//	sttFreqDown_old = sttFreqDown_new;
//	sttFreqDown_new = GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_6);
//	if(sttFreqDown_new == 0 && sttFreqDown_old == 1) 
//	{
//		count += 10;
//	}
//	Delay_ms(1);
//	TIM_SetAutoreload(TIM2 , count);
//}
void Delay_ms(uint16_t _time)
{
	uint16_t i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2AFF; j++);
	}
}
void button_freq(int duty, int freq)
{
	sttFreqUp_old = sttFreqUp_new;
	sttFreqUp_new = GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_7);
	if(sttFreqUp_new == 0 && sttFreqUp_old == 1) 
	{
		period = 1000000 / freq ;
	x = (float)1000000 / freq /100 * 54 ;
	TIM_SetAutoreload (TIM2, period - 1);
	TIM_SetCompare1 (TIM2, x );
	printf("%d", x);
		
	}

}