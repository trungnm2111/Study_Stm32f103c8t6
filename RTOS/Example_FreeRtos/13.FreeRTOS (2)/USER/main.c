
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "Delay.h"
#include "N5110.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

xQueueHandle xQueue;

char TextTemp[200];

int Number1;
int Number2;

GPIO_InitTypeDef  GPIO_InitStructure;
void Fn_GPIO_Init (void);
void Fn_GLCD_Init (void);
void Fn_RTOS_N5110_Send (void *p);
void Fn_RTOS_N5110_Disp (void *p);


int main (void){
	xQueue = xQueueCreate( 10, sizeof( uint32_t ) );
	
	SystemInit();
	SystemCoreClockUpdate();
	
	Fn_GPIO_Init();
	Fn_N5110_Init();
	Fn_N5110_GotoXY(0,0);
	Fn_N5110_Puts(TextTemp);
	xTaskCreate(Fn_RTOS_N5110_Send, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	xTaskCreate(Fn_RTOS_N5110_Disp, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	vTaskStartScheduler();
	return 0;
}


void Fn_GPIO_Init (void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}



void Fn_RTOS_N5110_Send (void *p){
	char * DataSend = "xin chao";
	while(1){
		xQueueSend(xQueue, (void*)&DataSend, (portTickType)0);
//		DataSend++;
//		vTaskDelay(1000);
//		xQueueSend(xQueue, (void*)&DataSend, (portTickType)0);
//		DataSend++;
//		vTaskDelay(5000);
	}
}


void Fn_RTOS_N5110_Disp (void *p){
	uint32_t DataReceive;
	while(1){
		if(xQueueReceive(xQueue, (void*)&DataReceive, (portTickType)0xFFFFFFFF))
		{
			sprintf(TextTemp,"Number:%5d", DataReceive);
			Fn_N5110_GotoXY(0,0);
			Fn_N5110_Puts(TextTemp);
			
		}
	}
}