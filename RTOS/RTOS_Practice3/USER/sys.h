/*
  ******************************************************************************
  * @file		rtos.h                                                              *
  * @author	    Nguyen Minh Trung                                                 *
  * @date		00/00/0000                                                     *
  ******************************************************************************
*/
	
#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
 extern "C" {
#endif

/******************************************************************************/

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"
#include "gpio.h"
#include "event_groups.h"

/******************************************************************************/

void RTOS_Run(void);
void RTOS_Task_1(void *p);
void RTOS_Task_2(void *p);

/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
