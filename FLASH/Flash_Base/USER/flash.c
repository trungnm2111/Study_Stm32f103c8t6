#include "flash.h"

void Flash_Unlock(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;	
}

void Flash_Lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void Flash_Erase(uint32_t Address)
{
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = Address;
	FLASH->CR |= FLASH_CR_STRT;
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR &= ~FLASH_SR_BSY;
	FLASH->CR &= ~FLASH_CR_PER;	
}

/******************************************************************************/

void Flash_Write_2byte(uint32_t Address, uint16_t Data)
{
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR |= FLASH_CR_PG;
	*(volatile uint16_t*)Address = Data;
	while(FLASH->SR & FLASH_SR_BSY);
	FLASH->CR &= ~FLASH_CR_PG;	
}

void Flash_Write_4byte(uint32_t Address, uint32_t Data)
{
	uint16_t data;
	data =  (uint16_t)Data;
	Flash_Write_2byte(Address,data);
	data = (uint16_t)(Data >> 16);
	Flash_Write_2byte(Address + 2,data);	
}

void Flash_Write_8byte(uint32_t Address, uint64_t Data)
{
	uint32_t data;
	data = (uint32_t) Data;
	Flash_Write_4byte(Address, data);
	data = (uint32_t)(Data >> 32);
	Flash_Write_4byte(Address + 4, data);
}

void Flash_Write_Byte_Array(uint32_t Address, uint8_t *buff, uint16_t Length)
{
	uint16_t i;
	for(i=0; i < (Length/2) + (Length % 2); i++)
	{
		uint16_t data = buff[i * 2] | (uint16_t)buff[i * 2 + 1] << 8;
		Flash_Write_2byte(Address, data);
		Address = Address + 2;
	}	
}

void Flash_Write_String(uint32_t Address, char *buff)
{
	uint16_t len = strlen(buff);
	Flash_Write_Byte_Array(Address,(uint8_t *) buff, len+1);	
}

void Flash_Write_Struct(uint32_t Address, Information DATA)
{
	Flash_Unlock();
	Flash_Write_String(Address,DATA.Name_Player1);
	Address = Address + sizeof(DATA.Name_Player1);
	Flash_Write_String(Address, DATA.Name_Player2);
	Address = Address + sizeof(DATA.Name_Player2);
	Flash_Write_2byte(Address, DATA.Point1);
	Address = Address + sizeof(DATA.Point1);
	Flash_Write_2byte(Address, DATA.Point2);
	Address = Address + sizeof(DATA.Point2);
	Flash_Write_2byte(Address, DATA.Score1);
	Address = Address + sizeof(DATA.Score1);
	Flash_Write_2byte(Address, DATA.Score2);
	Address = Address + sizeof(DATA.Score2);
	Flash_Write_2byte(Address, DATA.Round);
	Address = Address + sizeof(DATA.Round);	
}

void Flash_Write_Structs(uint32_t Address, Informations STR)
{
	Flash_Unlock();
	Flash_Write_4byte(Address, STR.ersionCode);
	Address = Address + sizeof(STR.ersionCode);
	Flash_Write_String(Address,STR.Date);
	Address = Address + sizeof(STR.Date);
	Flash_Write_String(Address,STR.Human);
	Address = Address + sizeof(STR.Human);	
}

/******************************************************************************/

uint16_t Flash_Read_2byte(uint32_t Address)
{
	return *(volatile uint16_t*)Address;
}
uint32_t Flash_Read_4byte(uint32_t Address)
{
	return *(volatile uint32_t*)Address;
}

uint64_t Flash_Read_8byte(uint32_t Address)
{
	return *(volatile uint64_t*)Address;
}

void Flash_Read_Byte_Array(uint32_t Address, uint8_t *buff, uint16_t Length)
{
	uint16_t i;
	for(i = 0; i < (Length / 2); i++)
	{
		uint16_t data = Flash_Read_2byte(Address);
		buff[i * 2]   = (uint8_t)data;
		buff[i * 2 + 1] = (uint8_t) (data >> 8);
		Address = Address + 2;
	}	
}
void Flash_Read_String_1byte(uint32_t Address, char *buff)
{
	uint16_t i = 0;
	while(1)
	{
		*(uint8_t *)(buff + i) = *(uint8_t*)(Address + i);
		if(*(buff + i) == 0)
			break;
		i++;
	}	
}