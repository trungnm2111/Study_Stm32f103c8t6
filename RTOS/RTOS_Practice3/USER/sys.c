#include "sys.h"

QueueHandle_t xQueue;
void RTOS_Task_1(void *p);
void RTOS_Task_2(void *p);
SemaphoreHandle_t my_mutex;

void RTOS_Run()
{
	my_mutex = xSemaphoreCreateMutex();
	xQueue = xQueueCreate(5, sizeof(uint16_t));
	xTaskCreate(RTOS_Task_1, (const char *)"Task Tranmision", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(RTOS_Task_2, (const char *)"Task IO", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
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
				USART_SendString("bat\n");
				queue_send = 1;
				xQueueSend(xQueue, &queue_send, 0);
				xSemaphoreGive(my_mutex);
			}
			else if(USART_Compare("tat") == 1)
			{
				xSemaphoreTake(my_mutex, portMAX_DELAY);
				queue_send = 2;
				USART_SendString("tat\n");
				xQueueSend(xQueue, &queue_send, 0);
				xSemaphoreGive(my_mutex);
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100));	
	}
}

void RTOS_Task_2(void *p)
{
	uint16_t queue_receive;
	while(1)
	{
		
		if (xQueueReceive(xQueue, &queue_receive, portMAX_DELAY) == pdTRUE)
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
		
		vTaskDelay(pdMS_TO_TICKS(100));	
	}
}
