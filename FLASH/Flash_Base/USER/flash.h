/*
  ******************************************************************************
  * @file				flash.h                                                                  *
  * @author	    Nguyen Minh Trung                                                   *
  * @date				00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef _FLASH_H
#define _FLASH_H


#ifdef __cplusplus
 extern "C" {
#endif

/******************************************************************************/

#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stdio.h"
#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "stdio.h"

/******************************************************************************/

#define START_ADDRESS 0x0800FC00
#define WAIT_BUSY 		while(FLASH->SR & FLASH_SR_BSY);
typedef struct{
	char Name_Player1[40];
	char Name_Player2[40];
	uint16_t		Score1;
	uint16_t		Score2;
	uint16_t 		Point1;
	uint16_t		Point2;
	uint16_t 		Round;
}Information;

typedef struct{
	unsigned int ersionCode;
	char Date[24];
	char Human[24];
}Informations;
/******************************************************************************/	

void Flash_Unlock(void);
void Flash_Lock(void);
void Flash_Erase(uint32_t Address);

void Flash_Write_2byte(uint32_t Address, uint16_t Data);
void Flash_Write_4byte(uint32_t Address, uint32_t Data);
void Flash_Write_8byte(uint32_t Address, uint64_t Data);
void Flash_Write_Byte_Array(uint32_t Address, uint8_t *buff, uint16_t Length);
void Flash_Write_String(uint32_t Address, char *buff);
void Flash_Write_Struct(uint32_t Address, Information DATA);


void Flash_Write_Structs(uint32_t Address, Informations STR);

uint16_t Flash_Read_2byte(uint32_t Address);
uint32_t Flash_Read_4byte(uint32_t Address);
uint64_t Flash_Read_8byte(uint32_t Address);
void Flash_Read_Byte_Array(uint32_t Address, uint8_t *buff, uint16_t Length);
void Flash_Read_String_1byte(uint32_t Address, char *buff);

/******************************************************************************/	 
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
