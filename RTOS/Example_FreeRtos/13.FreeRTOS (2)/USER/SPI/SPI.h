
#ifndef _SPI_
#define _SPI_

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI

#define SPI_PORT		GPIOA
#define SPI_PIN_MOSI	GPIO_Pin_7
#define SPI_PIN_MISO	GPIO_Pin_6
#define SPI_PIN_SCK		GPIO_Pin_5
#define SPI_PIN_SS		GPIO_Pin_4
#define SPIx			SPI1


#ifdef __cplusplus
extern "C"{
#endif

void Fn_SPI_Init (void);
uint8_t Fn_SPIx_Transfer(uint8_t data);

#ifdef __cplusplus
}
#endif




#endif

