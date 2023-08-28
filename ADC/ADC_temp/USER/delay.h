/*
  ******************************************************************************
  * @file		delay.h                                                              *
  * @author	Nguyen Minh Trung                                                       *
  * @date		00/00/0000                                                        *
  ******************************************************************************
*/

#ifndef __DELAY__H
#define __DELAY__H

#ifdef __cplusplus
 extern "C" {
#endif
/******************************************************************************/

#include "stm32f10x.h"                  // Device header
/******************************************************************************/

void DelayInit(void);
void DelayUs(uint32_t Time);
void DelayMs(uint32_t Time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
