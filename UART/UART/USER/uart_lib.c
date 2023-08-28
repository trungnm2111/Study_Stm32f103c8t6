#include "stm32f10x.h"                  
#include "string.h"
#include "stdio.h"
#include "uart_lib.h"


char RX_FLAG_END_LINE = 0; // bien danh dau trang thai 
char RRX[string_size];
unsigned int RXI = 0; // bien dem
char temp_char;   //bien de luu ki tu nhan 

void config_GPIO_LED(void);
void config_USART(unsigned int BaudRates);
void Usart_SendChar(char _ch);
void Usart_SendString(char *_str);
void Usart_SendNumber(int _number);
void Putchar(char *String);


void config_GPIO_LED(void) // cau hinh led pc 13
{
	GPIO_InitTypeDef GPIO_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_init.GPIO_Pin = LED;
	GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_init);
}
	/*de su dung ham printf trong thu vien stdio.h  */
struct __FILE
{
	int dummy;
};

FILE __stdout;			
		
int fputc(int ch, FILE *f)	  		
{
	Usart_SendChar(ch);
	return ch;
}

void config_USART(unsigned int BaudRates)
{
	USART_InitTypeDef Usart;
	GPIO_InitTypeDef Gpio;
	// cap xung clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// cau hinh chan truyen Tx-A9
	Gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	Gpio.GPIO_Pin = GPIO_Pin_9;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	// cau hinh cho chan nhan Rx-A10
	Gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Gpio.GPIO_Pin = GPIO_Pin_10;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	// cau hinh usart 
	
	Usart.USART_BaudRate = BaudRates; // cau hinh toc do truyen du lieu
	Usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 	// cau hinh luong dieu khien phan cung
	Usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // cau hinh che do truyen nhan 
	Usart.USART_Parity = USART_Parity_No; // cau hinh bit kiem tra
	Usart.USART_StopBits = USART_StopBits_1; // cau hinh bit ket thuc  
	Usart.USART_WordLength = USART_WordLength_8b; // cau hinh so bit 1 du lieu 
	USART_Init(USART1, &Usart); // cau hinh uart1 theo thong so tren 
	USART_Cmd(USART1, ENABLE); 						//CAU HINH CHO PHEP USART HOAT DONG
	// enable usart1 global interrupt        
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // cau hinh uart1 ngat nhan
	
	USART_ClearFlag(USART1, ENABLE);			// xoa co ngat nhan cho lan dau su dung 
	NVIC_EnableIRQ(USART1_IRQn);					// cau hinh ngat tong quat cho USART1
}

void USART1_IRQHandler() //HAM NGAT USART1 de nhan du lieu chinh xac 
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET) // kiem tra trang thai ngat cua co nhan 
	{
		temp_char = USART_ReceiveData(USART1);		// lu ki tu nhan vao bien temp_char
		if(temp_char != '\n') // ki tu khac ki tu ket thuc enter
		{	
			RRX[RXI] = temp_char;   //gan gia tri vao mang 
			RXI++;
		}
		else
		{
			RRX[RXI] = 0x00; // cho phan tu cuoi cung = NULL :phan tu ket thuc chuoi 
			RX_FLAG_END_LINE = 1;   // bat co danh dau trang thai danh dau qua trinh truyen nhan ket thuc
			RXI = 0;        // reset bo dem
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);  //xoa cac bit tro ngat nhan
}


void Usart_SendChar(char _ch)
{
	USART_SendData(USART1, _ch);    //ham truyen du lieu 
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);   // cho dem khi du lieu truyen xong
}

void Putchar(char *String)
{
	while(*String)
	{
		Usart_SendChar(*String);
		String++;
	}
}
