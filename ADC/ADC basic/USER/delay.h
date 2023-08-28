/*
  ******************************************************************************
  * @file		delay.h                                                              *
  * @author	Nguyen Minh Trung                                                       *
  * @date		14/11/2022                                                         *
  ******************************************************************************
*/

#ifndef __DELAY__H
#define __DELAY__H

#ifdef __cplusplus
 extern "C" {
#endif
void DelayInit(void);
void DelayUs(uint32_t Time);
void DelayMs(uint32_t Time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

