#include "system.h"
#include "usart.h"
#include "gpio.h"
xQueueHandle queue_led,queue_usart;
xSemaphoreHandle xMutex;
EventGroupHandle_t xEvent;
uint8_t n = 1;
typedef struct
{
	EventGroupHandle_t event_bt1;
}event_System_t;

void Rtos_Run()
{
	xMutex = xSemaphoreCreateMutex();
	queue_led = xQueueCreate(10, 32);
	queue_usart = xQueueCreate(10, 32);
	xEvent = xEventGroupCreate();
	
	xTaskCreate(Rtos_Task_Led1, (const char *) "Led2", 128, NULL, 1, NULL);
	xTaskCreate(Rtos_Task_Usart, (const char *) "USART", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}

void Rtos_Task_Led1(void *p)
{
	n = 0;
	uint32_t vri_queue_send = 0;
	uint32_t vri_queue_flag1, vri_queue_flag2, vri_queue_flag3;
	while(1)
	{
		vri_queue_flag1 = xEventGroupWaitBits(xEvent,EVENT0,pdTRUE, pdFALSE, 10);
		vri_queue_flag2 = xEventGroupWaitBits(xEvent,EVENT1,pdTRUE, pdFALSE, 10);
		vri_queue_flag3 = xEventGroupWaitBits(xEvent,EVENT2,pdTRUE, pdFALSE, 10);
		if(vri_queue_flag1 & EVENT0)
		{
			Task_Led1();
		}
		if(vri_queue_flag2 & EVENT1)
		{
			Task_Led2();
		}
		if(vri_queue_flag3 & EVENT2)
		{
			Task_Led3();
		}
	}
}

void Rtos_Task_Usart(void *p)
{
	while(1)
	{
		Task_Usart();
		vTaskDelay(100/portTICK_RATE_MS);
	}
}

void Task_Usart(void)
{
	if(USART_FlagDB() == 1)
	{
		if(USART_Compare("set1") == 1)
		{
			xEventGroupSetBits(xEvent,EVENT0);
		}
		else if(USART_Compare("set2") == 1)
		{
			xEventGroupSetBits(xEvent,EVENT1);
		}
		else if(USART_Compare("set3") == 1)
		{
			xEventGroupSetBits(xEvent,EVENT2);
		}
	}
}

void Task_Led1(void)
{
	USART_Printf("Led1\n");	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13, 1);
}

void Task_Led2(void)
{
	USART_Printf("Led2\n");	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13, 0);
}

void Task_Led3(void)
{
	USART_Printf("Led3\n");	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13, 1);
}
