#include "adc.h"
void GPIO_config(void)
{
	GPIO_InitTypeDef GPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		// cau hinh chan 
	GPIO.GPIO_Mode = GPIO_Mode_AIN;
	GPIO.GPIO_Pin = GPIO_Pin_0;

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