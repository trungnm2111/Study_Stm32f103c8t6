#include "hc_sr04_ic.h" 

int distance = 0;

void initPins(void) ;
void HCSR04_Init(void);
void HCSR04_GetDistance(void) ;

void initPins(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	 // PB8 (trigle) channel 3
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(TRIG_PORT , &GPIO_InitStructure);
	// PB6 (echo) channel 1
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);
}

void HCSR04_Init(void) 
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(CLOCK_TIM_USER, ENABLE);
	//////////////////////////////////////////////////////
	TIM_DeInit(TIM_USER);
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM_USER, &TIM_TimeBaseInitStruct);

	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 10; //us
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM_USER, &TIM_OCInitStruct);

	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_PWMIConfig (TIM_USER, &TIM_ICInitStruct);
	
	TIM_SelectInputTrigger(TIM_USER, TIM_TS_TI1FP1 );
	TIM_SelectMasterSlaveMode(TIM_USER, TIM_MasterSlaveMode_Enable);
	
	TIM_CtrlPWMOutputs(TIM_USER, ENABLE);
	TIM_ClearFlag(TIM_USER, TIM_FLAG_Update);
}

void HCSR04_GetDistance(void) 
{
	(TIM_USER)-> CNT = 0;
	TIM_Cmd(TIM_USER, ENABLE);
	while(!TIM_GetFlagStatus(TIM_USER, TIM_FLAG_Update));
	TIM_Cmd(TIM_USER, DISABLE);
	TIM_ClearFlag(TIM_USER, TIM_FLAG_Update);
	distance = (TIM_GetCapture2(TIM_USER) - TIM_GetCapture1(TIM_USER)) *0.177;  //////mm=//=>cm=T*0.0177=(1s/58)
}
