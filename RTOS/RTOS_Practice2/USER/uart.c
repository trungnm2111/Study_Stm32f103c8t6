#include "uart.h"

char Buffer_Numberal[100][100];
char GetChar;
int locate = 0;
unsigned int count=0;
unsigned int stt_flag=0;
uint16_t Tx_pin,Rx_pin;

int USART_FlagDB(void)
{
	if(stt_flag==1)
	{
		stt_flag=0;
		return 1;
	}
	else 
		return 0;
}

void USART_Config(unsigned int Baurates)
{
	
    GPIO_InitTypeDef GPIO_Struct;
	USART_InitTypeDef USART_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	Tx_pin = GPIO_Pin_9;
	Rx_pin = GPIO_Pin_10;
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin     = Tx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_IN_FLOATING;
	GPIO_Struct.GPIO_Pin     = Rx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	USART_Struct.USART_BaudRate 			= Baurates;
	USART_Struct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode 				= USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity      			= USART_Parity_No;
	USART_Struct.USART_StopBits 			= USART_StopBits_1;
	USART_Struct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USART1,&USART_Struct);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	USART_Cmd(USART1,ENABLE);
}

void USART_SendChar(char Char)
{
	USART_SendData(USART1,Char);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void USART_SendString(char *Str)
{
	while(*Str != 0)
	{
		USART_SendChar(*Str++);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		GetChar = USART_ReceiveData(USART1);
		if(GetChar != '\n')
		{
			Recei[count] = GetChar;
			count++;
		}
		else
		{
			stt_flag=1;
			Recei[count-1] = 0;
			count = 0;
		}
	}
}

int USART_Compare(char* String)
{
	unsigned char stt_compare=1;
	if(strcmp(String,(char *)Recei)!=0)
	{
		stt_compare=0;
	}
	return stt_compare;
}
