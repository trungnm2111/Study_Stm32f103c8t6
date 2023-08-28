#include "stm32f10x.h"                  // Device header          // Keil::Device:StdPeriph Drivers:RCC
#include "uart_lib.h"
#include "string.h"


int main (void){
	config_GPIO_LED();
	config_USART(9600);
	GPIO_SetBits(GPIOC, LED);
	while(1)
	{
		if(RX_FLAG_END_LINE == 1) // ket thuc qua trinh nhan 
		{	
			Putchar("<->");
			if(strstr(RRX,"ON")!= NULL)  // kiem tra chuoi ki tu co giong on?
			{
				GPIO_ResetBits(GPIOC,LED);
				Putchar(RRX);
			}
			if(strstr(RRX,"OFF")!= NULL)
			{
				GPIO_SetBits(GPIOC,LED);
				Putchar(RRX);
			}			
			Putchar("\n-------------------------\n");
			RX_FLAG_END_LINE = 0;		
		}
	}
}
