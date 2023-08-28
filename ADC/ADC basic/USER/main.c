#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "uart.h"
#include "delay.h" 

void ADC_Config(void);
int ADCx_Read(void);
static double v_out = 0 ;
static double i= 0;

int main()
{
	ADC_Config();
	DelayInit();
	Usart_Config(USART1, 9600);
	while(1)
	{
		if(i == 100)
		{
			v_out /= 100;
			Usart_SendNumber(v_out);
			Usart_Send_String("\n");
			v_out =  0;
			DelayMs(500);
			i = 0;
		}
		else 
		{
			i++;
			v_out += ADCx_Read();
		}
	}
}
void GPIO_config(void)
{
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		// cau hinh chan 
	GPIO.GPIO_Mode = GPIO_Mode_AIN;
	GPIO.GPIO_Pin = GPIO_Pin_0;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO);
}

void ADC_Config(void)
{
	
	ADC_InitTypeDef ADC;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	// cau hinh ADC1
	ADC.ADC_ContinuousConvMode = ENABLE;
	ADC.ADC_DataAlign = ADC_DataAlign_Right;
	ADC.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC.ADC_Mode = ADC_Mode_Independent;
	ADC.ADC_NbrOfChannel= 1;
	ADC.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC);
	// Cau hinh adc/ channel / rank / thoi gian lay mau 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	// cho phep adc 1 hoat dong
	ADC_Cmd(ADC1, ENABLE);
	// cho phep cam bien nhiet do hoat dong
	//ADC_TempSensorVrefintCmd(ENABLE);
	// reset thanh ghi
	ADC_ResetCalibration(ADC1);
	// cho thanh ghi reset xong
	while(ADC_GetResetCalibrationStatus(ADC1));
	// khoi dong bo adc
	ADC_StartCalibration(ADC1);
	// cho trang thai calib bat 
	while(ADC_GetCalibrationStatus(ADC1));
	// bat dau chuyen doi 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int ADCx_Read(void)
{
	return(ADC_GetConversionValue(ADC1));
}


