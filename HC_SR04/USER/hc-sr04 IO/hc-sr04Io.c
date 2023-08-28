#include "hcsr04io.h"

void initPins(void) ;
void HCSR04_Init(void);
void HCSR04_GetDistance(void) ;

int distance ;

void HCSR04_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB1PeriphClockCmd (CLOCK_TIM_USER, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit (TIM_USER, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 15; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM_USER , &TIM_OCInitStructure);
  TIM_OC1PreloadConfig (TIM_USER, TIM_OCPreload_Enable);
  TIM_Cmd (TIM_USER, ENABLE);
}

void HCSR04_GetDistance(void)
{
  uint32_t count = 0;
  distance = 0;
  GPIO_ResetBits(TRIG_PORT, TRIG_PIN);
  Delay_us(2);
  GPIO_SetBits(TRIG_PORT, TRIG_PIN);
  Delay_us(10);
  GPIO_ResetBits(TRIG_PORT, TRIG_PIN);

  while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == Bit_RESET);
  TIM_SetCounter(TIM2, 0);
  while(GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN) == Bit_SET);
  count = TIM_GetCounter(TIM_USER);
  
  distance = count *0.177;
	TIM_SetCounter(TIM2, 0);
}

void initPins(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // PA0 (Echo)
  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(ECHO_PORT, &GPIO_InitStructure);

  // PA1 (Trig) 
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);
}
