/*
  ******************************************************************************
  * @file		rtos.h                                                              *
  * @author	    Nguyen Van An                                                *
  * @date		09/01/2022                                                      *
  ******************************************************************************
*/
	
#ifndef __RTOS__
#define __RTOS__

#ifdef __cplusplus
 extern "C" {
#endif
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#define EVENT0		(1<<0)
#define EVENT1		(1<<1)
#define EVENT2		(1<<2)

void Rtos_Task_Led1(void *p);
void Rtos_Task_Usart(void *p);
void Rtos_Run(void);
void Task_Usart(void);
void Task_Led1(void);
void Task_Led2(void);
void Task_Led3(void);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
