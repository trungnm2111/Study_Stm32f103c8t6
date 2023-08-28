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

void RTOS_Run(void);
void RTOS_Task_1(void *p);
void RTOS_Task_2(void *p);
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
