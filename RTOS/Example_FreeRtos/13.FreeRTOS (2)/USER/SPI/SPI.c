
#include "SPI.h"

void SPI_EnableSlave (void){
    // Set slave SS pin low
    //SPI_PORT->BRR = SPI_PIN_SS;
	GPIO_ResetBits(SPI_PORT, SPI_PIN_SS);
}

static void SPI_DisableSlave (void){
    // Set slave SS pin high
    //SPI_PORT->BSRR = SPI_PIN_SS;
	GPIO_SetBits(SPI_PORT, SPI_PIN_SS);
}



void Fn_SPI_Init (void){
	SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
    // GPIO pins for MOSI, MISO, and SCK
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // GPIO pin for SS
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
	SPI_EnableSlave();
}

uint8_t Fn_SPIx_Transfer(uint8_t data)
{
    // Wait until transmit complete
    while ((SPIx->SR & (SPI_I2S_FLAG_TXE)) == RESET);
	// Write data to be transmitted to the SPI data register
	SPI_I2S_SendData(SPIx,data);
	// Wait until transmit complete
	while ((SPIx->SR & (SPI_I2S_FLAG_TXE))== RESET);
    // Wait until receive complete
    while (!(SPIx->SR & (SPI_I2S_FLAG_RXNE)));
    // Wait until SPI is not busy anymore
    while (SPIx->SR & (SPI_I2S_FLAG_BSY));
    // Return received data from SPI data register
    return SPIx->DR;
}

