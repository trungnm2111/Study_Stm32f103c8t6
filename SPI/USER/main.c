#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI


int main()
{
	while(1)
	{
		
	}
}

void Spi1Master(void)
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2 , ENABLE);
	 
	GPIO_InitTypeDef GPIO;
	// PB13 - CK , PB15 - 
	GPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_15;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO);
	
	// nhan 
	GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO.GPIO_Pin = GPIO_Pin_14;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO);
	// PB12 - CS 
	GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO.GPIO_Pin = GPIO_Pin_12;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO);
	
	// SPI2
	SPI_InitTypeDef SPI;
	SPI.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		// bo chia 4
	SPI.SPI_CPHA = SPI_CPHA_1Edge;		
	SPI.SPI_CPOL = SPI_CPOL_Low;			// 
	SPI.SPI_DataSize = SPI_DataSize_8b;		// du lieu gui 8 bit
	SPI.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // che do  song cong (truyen + nhan)
	SPI.SPI_FirstBit = SPI_FirstBit_LSB; // gui tu bit thap den bit cao 
	SPI.SPI_Mode = SPI_Mode_Master;
	SPI.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI2, &SPI);
	SPI_Cmd(SPI2, ENABLE);
}