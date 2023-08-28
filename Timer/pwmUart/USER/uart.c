#include "uart.h"

char RX_FLAG_END_LINE = 0;  
char RRX[string_size];
char RRX2[string_size];
unsigned int RXI = 0; 
char temp_char;   
 

void config_GPIO_LED(void);
void uart_Init(void);
void Usart_SendChar(char _ch);
void Usart_SendString(char *_str);
void Putchar(char *String);


struct __FILE {
    int dummy;
};
FILE __stdout;
 
int fputc(int ch, FILE *f) {
 
    uart_SendChar(ch);
  
    return ch;
}

void uart_Init(void)
{
	GPIO_InitTypeDef gpio_typedef;
	USART_InitTypeDef usart_typedef;
	// enable clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// congifgure pin Tx - A9;
	gpio_typedef.GPIO_Pin = GPIO_Pin_9;
	gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_typedef);	
	// configure pin Rx - A10;
	gpio_typedef.GPIO_Pin = GPIO_Pin_10;
	gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_typedef);
	// usart configure
	usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_typedef);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	USART_Cmd(USART1, ENABLE);
}

void uart_SendChar(char _chr){
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void uart_SendStr(char *str){
	while(*str != NULL){
		uart_SendChar(*str++);		
	}
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
		}
		else
		{
			RRX[RXI] = 0x00;
			RX_FLAG_END_LINE = 1;  
			RXI = 0;        
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
}
int count , tmp;
void cut_string(void)
{
	for( count = 0 ; count < strlen(RRX) - 1 ; count++)
	{
		if( RRX [count] == ' ' && RRX[count + 1] != ' ' )
		{
			 tmp = count;
		}	
	}
	strncpy(RRX2 ,RRX + tmp , strlen(RRX) -tmp  );
}

void Putchar(char *String)
{
	while(*String)
	{
		uart_SendChar(*String);
		String++;
	}
}

				
