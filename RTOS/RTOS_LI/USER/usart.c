#include "usart.h"
#include "string.h"


GPIO_TypeDef* GPIOx;
USART_TypeDef* USARTx = USART1;
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

unsigned int Numberal(int Num, int locate)
{
	unsigned int number_of_digits=1;
	while(Num>0)
	{
		Buffer_Numberal[locate][number_of_digits++] = Num%10;
//		003 012 031
		Num /= 10;
	}
	return number_of_digits;
}
//123
void USART_SendNum(int Num) 
{
	int number_of_digits;
	
	number_of_digits = Numberal(Num,locate)-1;
	while(number_of_digits>0)
	{
		USART_SendChar(Buffer_Numberal[locate][number_of_digits]+'0');
		number_of_digits--;
	}
	
}

void USART_Config(unsigned int Baurates)
{
	
    GPIO_InitTypeDef GPIO_Struct;
	USART_InitTypeDef USART_Struct;
	if(USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
		Tx_pin = GPIO_Pin_9;
		Rx_pin = GPIO_Pin_10;
		GPIOx = GPIOA;
	}
	else if(USARTx == USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		Tx_pin = GPIO_Pin_2;
		Rx_pin = GPIO_Pin_3;
		GPIOx = GPIOA;
	}
	else if(USARTx == USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		Tx_pin = GPIO_Pin_10;
		Rx_pin = GPIO_Pin_11;
		GPIOx = GPIOB;
	}
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Pin     = Tx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode	 = GPIO_Mode_IN_FLOATING;
	GPIO_Struct.GPIO_Pin     = Rx_pin;
	GPIO_Struct.GPIO_Speed	 = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_Struct);
	
	USART_Struct.USART_BaudRate 			= Baurates;
	USART_Struct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode 				= USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity      			= USART_Parity_No;
	USART_Struct.USART_StopBits 			= USART_StopBits_1;
	USART_Struct.USART_WordLength 			= USART_WordLength_8b;
	USART_Init(USARTx,&USART_Struct);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	USART_Cmd(USARTx,ENABLE);
}

void USART_SendChar(char Char)
{
	USART_SendData(USARTx,Char);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
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

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		GetChar = USART_ReceiveData(USART2);
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

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		GetChar = USART_ReceiveData(USART3);
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

void USART_Printf(const char* str, ...)
{
	char stringArray[100];
	va_list args;
	va_start(args, str);
	vsprintf(stringArray, str, args);
	va_end(args);
	USART_SendString(stringArray);
}

int USART_Compare(char* String)
{
	unsigned char stt_compare=1;
	if(strcmp(String,Recei)!=0)
	{
		stt_compare=0;
	}
	return stt_compare;
}
