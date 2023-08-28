#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "uart.h"
#include "flash.h"



int main() 
{
	Informations structure = {2, "08/08/2022", "Luu Ngoc Anh"};
	Information data = {"Hello", "Hi", 1,2,4,5,2 };
//	data.Point1 = 4;
//	data.Point2 = 5;
//	data.Score1 = 1;
//	data.Score2 = 2;
//	uint8_t string1[]= "Hello";
//	uint8_t string2[]= "Hi";
//	
//	char* mystring = "Hello";
	uint32_t add = 0x0801C000;
	Flash_Unlock();
	Flash_Erase(0x0800FC00);
//	Flash_Write_4byte(0x0800FC00, (uint32_t)123456789);
//	Flash_Write_2byte(add, (uint16_t) 0x2234);
//	Flash_Write_String(0x0800FC00, mystring);
	Flash_Write_Structs(0x0800FC00, structure);
	
	Flash_Lock();
  while(1) 
	{
		
  }
}

