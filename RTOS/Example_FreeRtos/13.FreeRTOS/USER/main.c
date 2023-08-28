
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "Delay.h"
#include "FreeRTOS.h"
#include "task.h"



#include "N5110.h"
#include "semphr.h"

xSemaphoreHandle xMutex;

char TextTemp[200];

int Number1;
int Number2;

// Viet Doan nay thoi!
GPIO_InitTypeDef  GPIO_InitStructure;
void Fn_GPIO_Init (void);
void Fn_RTOS_TaskLed1(void *p);
void Fn_RTOS_TaskLed2(void *p);


void Fn_GLCD_Init (void);
void Fn_RTOS_N5110_Text1 (void *p);
void Fn_RTOS_N5110_Text2 (void *p);


int main (void){
	xMutex = xSemaphoreCreateMutex();
	
	SystemInit();
	SystemCoreClockUpdate();
	
	Fn_GPIO_Init();
	Fn_N5110_Init();
	sprintf(TextTemp,"Task1:%4d",1234);
	Fn_N5110_GotoXY(0,0);
	Fn_N5110_Puts(TextTemp);
	xTaskCreate(Fn_RTOS_N5110_Text1, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
	xTaskCreate(Fn_RTOS_N5110_Text2, (const char*) "Red LED Blink", 128, NULL, 1, NULL);
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
void Fn_RTOS_TaskLed1(void *p){
	while(1){
		GPIOE->ODR ^= GPIO_Pin_15;
		vTaskDelay(100/portTICK_RATE_MS);
	}
}
void Fn_RTOS_TaskLed2(void *p){
	while(1){
		GPIOE->ODR ^= GPIO_Pin_13;
		vTaskDelay(500/portTICK_RATE_MS);
	}
}


void Fn_RTOS_N5110_Text1 (void *p){
	while(1){
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Number1++;
		sprintf(TextTemp,"Task1:%4d",Number1);
		Fn_N5110_GotoXY(0,0);
		Fn_N5110_Puts(TextTemp);
		xSemaphoreGive( xMutex );
		vTaskDelay(100/portTICK_RATE_MS);
	}
}


void Fn_RTOS_N5110_Text2 (void *p){
	while(1){
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Number2++;
		sprintf(TextTemp,"Task2:%4d",Number2);
		Fn_N5110_GotoXY(0,3);
		Fn_N5110_Puts(TextTemp);
		xSemaphoreGive( xMutex );
		vTaskDelay(500/portTICK_RATE_MS);
	}
}