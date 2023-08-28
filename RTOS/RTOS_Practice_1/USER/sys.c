#include "sys.h"


QueueHandle_t xQueue;
void RTOS_Task_1(void *p);
void RTOS_Task_2(void *p);

void RTOS_Run()
{

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
				USART_SendString("bat\n");
				queue_send = 1;
				xQueueSend(xQueue, &queue_send, 0);
			}
			else if(USART_Compare("tat") == 1)
			{
				queue_send = 2;
				USART_SendString("tat\n");
				xQueueSend(xQueue, &queue_send, 0);
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
				GPIO_TurnOn_Led();
				USART_SendString("da bat");
			}
			else if (queue_receive == 2)
			{
				GPIO_TurnOff_Led();
				USART_SendString("da tat");
			}
		}
		vTaskDelay(pdMS_TO_TICKS(100));	
	}
}









//void SYS_Func_1(void *p);
//void SYS_Func_2(void *p);

//SemaphoreHandle_t my_mutex;
//QueueHandle_t xQueue;

//void RTOS_Run()
//{
//	my_mutex = xSemaphoreCreateMutex();
//	xQueue = xQueueCreate(10, sizeof(char));
//	
//	xTaskCreate(SYS_Func_1, "Task 1", configMINIMAL_STACK_SIZE, NULL,1, NULL );
//	xTaskCreate(SYS_Func_2, "Task 1", configMINIMAL_STACK_SIZE, NULL,1, NULL );
//	vTaskStartScheduler();
//}

//void SYS_Func_1(void *p)
//{
//	char buffer[10];
//	uint32_t queue_send;
//	while(1)
//	{
//		xSemaphoreTake(my_mutex, portMAX_DELAY);
//		if(USART_FlagDB() == 1)
//		{
//			if((strncmp(buffer, "b?t", 3) == 0))
//			{
//				queue_send = 1;
//				xQueueSend(xQueue, &queue_send, 0);
//			}
//			else if(USART_Compare("tat") == 1)
//			{
//				queue_send = 2;
//				xQueueSend(xQueue, &queue_send, 0);
//			}	
//		}
//		xSemaphoreGive(my_mutex);
//		vTaskDelay(pdMS_TO_TICKS(10));
//	}
//	
//}	

//void SYS_Func_2(void *p)
//{
//	char message[10];
//	uint32_t queue_receive;
//	while(1)
//    {
//			if(xSemaphoreTake(my_mutex, portMAX_DELAY) == pdTRUE)
//			{
//				if (xQueueReceive(xQueue, &queue_receive, portMAX_DELAY) == pdTRUE)
//				{
//					if (queue_receive == 1)
//					{
//						GPIO_TurnOn_Led();
//						USART_SendString("da bat");
//					}
//					else if (queue_receive == 2)
//					{
//						GPIO_TurnOff_Led();
//						USART_SendString("da tat");
//					}
//				}
//			xSemaphoreGive(my_mutex);
//    }
//			vTaskDelay(pdMS_TO_TICKS(100));
//	}
//}

