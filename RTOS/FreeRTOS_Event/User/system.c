#include "system.h"
#include "usart.h"
#include "gpio.h"

//QueueHandle_t xQueue;

//void RTOS_Run()
//{
//	 xQueue = xQueueCreate(10, sizeof(char));

//    xTaskCreate(RTOS_Task_1, "Task_Tramission", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//    xTaskCreate(RTOS_Task_2, "Task_IO", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//    vTaskStartScheduler();
//}

//void RTOS_Task_1(void *p)
//{
//    char buffer[10];
//		uint32_t queue_send;
//    while(1)
//    {
//			if(USART_FlagDB() == 1)
//			{
//				if(USART_Compare("bat") == 1)
//				{
//					//gui du lieu vao Queue
//					queue_send = 1;
//					xQueueSend(xQueue, &queue_send, 0);
//				}
//				else if(USART_Compare("tat") == 1)
//				{
//					queue_send = 2;
//					xQueueSend(xQueue, &queue_send, 0);
//			}
//    }
//	}
//}

//void RTOS_Task_2(void *p)
//{
//	char message[10];
//	uint32_t queue_receive;
//	while(1)
//    {
//			// Nhan du lieu Queue
//			if (xQueueReceive(xQueue, &queue_receive, portMAX_DELAY) == pdTRUE)
//			{
//					if (queue_receive == 1)
//					{
//							GPIO_TurnOn_Led();
//					}
//					else if (queue_receive == 2)
//					{
//							GPIO_TurnOff_Led();
//					}
//			}
//    }
//}

















EventGroupHandle_t Event;
uint8_t event_bit1, event_bit2;

void RTOS_Run()
{
	Event = xEventGroupCreate();
	event_bit1 = (1 << 0);
	event_bit2 = (1 << 1);
	xTaskCreate(RTOS_Task_1, (const char *)"Task Tranmision", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(RTOS_Task_2, (const char *)"Task IO", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	xTaskCreate(RTOS_Task_3, (const char *)"Task Systems", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}



void RTOS_Task_1(void *p)
{
	while(1)
	{
		if(USART_FlagDB() == 1)
		{
			if(USART_Compare("bat") == 1)
			{
			USART_SendString("da bat");
				xEventGroupSetBits(Event, event_bit1);
			}
			else if(USART_Compare("tat") == 1)
			{
				xEventGroupSetBits(Event, event_bit2);
				USART_SendString("da tat");
			}
		}
	}
}

void RTOS_Task_2(void *p)
{
	uint8_t event_bit;
	while(1)
	{
		event_bit = xEventGroupWaitBits(Event, event_bit1, pdTRUE, pdFALSE, 0);
		if(event_bit & event_bit1)
		{
			USART_SendString("bat \n");
			GPIO_TurnOn_Led();
		}
		event_bit = xEventGroupWaitBits(Event, event_bit2, pdTRUE, pdFALSE, 0);
		if(event_bit & event_bit2)
		{
			USART_SendString("tat \n");
			GPIO_TurnOff_Led();
		}
	}
}

//void RTOS_Task_3(void *p)
//{
//	uint8_t event_bit;
//}