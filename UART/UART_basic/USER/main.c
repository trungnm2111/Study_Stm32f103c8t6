#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "string.h"

void init_gpio(void)
{
	GPIO_InitTypeDef gpio_typerdef;

	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA , ENABLE);
	// CAU HINH TX - A9
	gpio_typerdef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_typerdef.GPIO_Pin = GPIO_Pin_9;
	gpio_typerdef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA , &gpio_typerdef);
	//CAU HINH RX - A10
	gpio_typerdef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_typerdef.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_typerdef);
}
void innit_usart(void)
{
	USART_InitTypeDef usart_typedef;
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_USART1, ENABLE);
	usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	usart_typedef.USART_Mode = USART_Mode_Tx;
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength = USART_WordLength_8b;
	
	USART_Init (USART1 , &usart_typedef);
	USART_Cmd (USART1 , ENABLE );
}
void usart_sendchar(void)
{
	USART_SendData(USART1, 'A');
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)== RESET);
}
void delay(unsigned int time)
{
	unsigned int i ,j ;
	for( i = 0 ; i < time; i++)
	{
		for(j = 0; j < 0x2aff ; j++);
	}
}
int main()
{
	char arr[] ="Hello world \n";
	init_gpio();
	innit_usart();
	while(1)
	{
		int i ;
		for(i = 0 ; i < strlen(arr) ; i++)
		{
			USART_SendData(USART1 , '*');
			USART_SendData(USART1 , arr[i]);
			delay(100);
		}
	}
}