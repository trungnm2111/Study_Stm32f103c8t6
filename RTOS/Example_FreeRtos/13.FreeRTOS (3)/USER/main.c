
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "Delay.h"
#include "N5110.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

EventGroupHandle_t event_hdl;
char TextTemp[200];

#define EVENT0		(1<<0)
#define EVENT1		(1<<1)
#define EVENT2		(1<<2)
#define EVENT_ALLS	((EVENT2<<1) - 1)

void Fn_GPIO_Init (void);

void TaskMain(void *pvParameters);
void TaskA(void *pvParameters);
void TaskB(void *pvParameters);


int main (void){
	
	SystemInit();
	SystemCoreClockUpdate();
	
	Fn_GPIO_Init();
	Fn_N5110_Init();
	xTaskCreate(TaskMain, "TaskMain", 128, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(TaskA, "TaskA", 128, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(TaskB, "TaskB", 128, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
	return 0;
}


void Fn_GPIO_Init (void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void TaskMain(void *pvParameters){
	event_hdl = xEventGroupCreate();
	while(1){
		xEventGroupSetBits(event_hdl, EVENT0);
		vTaskDelay(2000);
		xEventGroupSetBits(event_hdl, EVENT1);
		vTaskDelay(2000);
		xEventGroupSetBits(event_hdl, EVENT_ALLS);
		vTaskDelay(2000);
	}
}

void TaskA(void *pvParameters){
	EventBits_t event;
	while(1){
		event = xEventGroupWaitBits(event_hdl, EVENT_ALLS, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT0){
			GPIOE->ODR ^= 0x000FF00;
		}
		
	}
}
void TaskB(void *pvParameters){
	int Number = 0;
	EventBits_t event;
	while(1){
		event = xEventGroupWaitBits(event_hdl, EVENT_ALLS, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT1){
			Number++;
			sprintf(TextTemp,"Number:%5d", Number);
			Fn_N5110_GotoXY(0,0);
			Fn_N5110_Puts(TextTemp);
		}
		
	}
}
