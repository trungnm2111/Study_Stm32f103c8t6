#include "sys.h"

EventGroupHandle_t Event;
QueueHandle_t xQueue;
SemaphoreHandle_t my_mutex;
uint8_t event_bit1, event_bit2;

void RTOS_Task_1(void *p);
void RTOS_Task_2(void *p);
void RTOS_Task_3(void *p);


void RTOS_Run()
{
	Event = xEventGroupCreate();
	event_bit1 = (1 << 0); // dich bit sang trai 1 bit 0-> 1
	event_bit2 = (1 << 1);	// dich bit sang trai 1 bit 1->2
	my_mutex = xSemaphoreCreateMutex();
	xQueue = xQueueCreate(5, sizeof(uint16_t));
	xTaskCreate(RTOS_Task_1, (const char *)"Task Tranmision", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(RTOS_Task_2, (const char *)"Task IO", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(RTOS_Task_3, (const char *)"Task System", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

void RTOS_Task_1(void *p)
{
	uint16_t queue_send;
	while(1)
	{
		if(USART_FlagDB() == 1)
		{
			if(USART_Compare("bat") == 1)
			{
				xSemaphoreTake(my_mutex, portMAX_DELAY);
				USART_SendString("event1\n");
				queue_send = 1;
				xQueueSend(xQueue, &queue_send, 0);
				xEventGroupSetBits(Event, event_bit1);
				xSemaphoreGive(my_mutex);
			}
			else if(USART_Compare("tat") == 1)
			{
				xSemaphoreTake(my_mutex, portMAX_DELAY);
				queue_send = 2;
				USART_SendString("event1 \n");
				xQueueSend(xQueue, &queue_send, 0);
				xEventGroupSetBits(Event, event_bit1);
				xSemaphoreGive(my_mutex);
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100));	
	}
}

void RTOS_Task_2(void *p)
{
	uint16_t queue_receive;
	uint8_t event_bit;
	while(1)
	{
		event_bit = xEventGroupWaitBits(Event, event_bit2, pdTRUE, pdFALSE, 0);
		if(event_bit == event_bit2)
		{
			if(xQueueReceive(xQueue, &queue_receive, portMAX_DELAY) == pdTRUE)
			{
				if (queue_receive == 1)
				{
					xSemaphoreTake(my_mutex, portMAX_DELAY);
					GPIO_TurnOn_Led();
					USART_SendString("da bat");
					xSemaphoreGive(my_mutex);
				}
				else if (queue_receive == 2)
				{
					xSemaphoreTake(my_mutex, portMAX_DELAY);
					GPIO_TurnOff_Led();
					USART_SendString("da tat");
					xSemaphoreGive(my_mutex);
				}				
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100));	
	}
}

void RTOS_Task_3(void *p)
{
	uint8_t event_bit;
	uint16_t queue_receive;
	while(1)
	{
		event_bit = xEventGroupWaitBits(Event, event_bit1, pdTRUE, pdFALSE, 0);
		if(event_bit ==  event_bit1)
		{
			USART_SendString("event2 \n");
			xEventGroupSetBits(Event, event_bit2);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));	
	}
}

