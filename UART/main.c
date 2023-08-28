#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "string.h"
#include "stdio.h"

#define TX GPIO_Pin_9
#define RX GPIO_Pin_10
#define LED GPIO_Pin_13

#define string_size 80

char RX_FLAG_END_LINE = 0;
char RRX[string_size];
unsigned int RXI = 0;
char temp_char;
char a[1];

void config_GPIO_LED(void);
void config_USART(unsigned int BaudRates);

void Usart_SendChar(char _ch);
void Usart_SendString(char *_str);
void Usart_SendNumber(int _number);
void Putchar(char *String);

int main (void){
	config_GPIO_LED();
	config_USART(9600);
	
	GPIO_SetBits(GPIOC, LED);
	while(1)
	{
		if(RX_FLAG_END_LINE == 1)
		{	
			if(strstr(RRX,"ON")!= NULL)
			{
				GPIO_ResetBits(GPIOC,LED);
			}
			if(strstr(RRX,"OFF")!= NULL)
			{
				GPIO_SetBits(GPIOC,LED);
			}
			Putchar("<->");
			Putchar(RRX);
			Putchar("\n-------------------------\n");
			RX_FLAG_END_LINE = 0;		
		}
	}
}
void config_GPIO_LED(void)
{
	GPIO_InitTypeDef GPIO_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_init.GPIO_Pin = LED;
	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_init);
}

struct FILE{
	int dummy;
};
FILE __stdout;

int fputc(int ch, FILE *f){
	Usart_SendChar(ch);
	return ch;
}

void config_USART(unsigned int BaudRates)
{
	USART_InitTypeDef Usart;
	GPIO_InitTypeDef Gpio;
	// enable clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// config Tx-A9
	Gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	Gpio.GPIO_Pin = GPIO_Pin_9;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	// config Rx-A10
	Gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Gpio.GPIO_Pin = GPIO_Pin_10;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	// config Usart
	Usart.USART_BaudRate = 9600;
	Usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	Usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	Usart.USART_Parity = USART_Parity_No;
	Usart.USART_StopBits = USART_StopBits_1;
	Usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &Usart);
	// enable usart1 global interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		temp_char = USART_ReceiveData(USART1);
		
		if(temp_char != '\n')
		{	
			RRX[RXI] = temp_char;
			RXI++;
			printf(a,"%d",RXI);
			Putchar(a);
		}
		else
		{
			RRX[RXI] = 0x00;
			RX_FLAG_END_LINE=1;
			RXI = 0;
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

/*ham gui du lieu*/
void Usart_SendChar(char _ch){
	USART_SendData(USART1, _ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/* ham nhan du lieu */
void Putchar(char *String)
{
	while(*String)
	{
		Usart_SendChar(*String);
		String++;
	}
}
