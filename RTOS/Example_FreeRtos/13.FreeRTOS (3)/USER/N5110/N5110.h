
#ifndef _N5110_
#define _N5110_


#include "Delay.h"
#include "SPI.h"

#define N5110_PIN_CD_Port		GPIOA
#define N5110_PIN_CD_Pin		GPIO_Pin_1
#define N5110_PIN_RS_Port		GPIOA
#define N5110_PIN_RS_Pin		GPIO_Pin_2
#define N5110_PIN_CS_Port		GPIOA
#define N5110_PIN_CS_Pin		GPIO_Pin_3

extern const unsigned char  font6x8[92][6];

#define NOKIA5110_X_SIZE                                  84
#define NOKIA5110_Y_SIZE                                  48
#define NOKIA5110_Y_ARRAY_SIZE                            (NOKIA5110_Y_SIZE/8)
#define NOKIA5110_DATA_SELECT                             1
#define NIKIA5110_COMMAND_SELECT                          0
#define NIKIA5110_FUNCTION_VERTICAL_BA                    0x22  //Lenh co ban, va dung che do doc
#define NIKIA5110_FUNCTION_VERTICAL_EX                    0x23  //Lenh them, va dung che do doc
#define NIKIA5110_FUNCTION_HORIZONTA_BA                   0x20	//Lenh co ban, va dung che do ngang
#define NIKIA5110_FUNCTION_HORIZONTA_EX                   0x21  //Lenh them, va dung che do ngang
#define NIKIA5110_DISPLAY_BLANK                           0x08  // Nhap nhay con tro 
#define NIKIA5110_DISPLAY_ALL_ON                          0x09  // Bat tat ca cac segment
#define NIKIA5110_DISPLAY_NORMAL                          0x0d  // Che do binh thuong  
#define NIKIA5110_DISPLAY_IN_VIDEO                        0x0D  // Che do chuyen doi Video      
#define NOKIA5110_X_ADDRESS                               0x40        
#define NOKIA5110_Y_ADDRESS                               0x80


#ifdef __cplusplus
extern "C"{
#endif

void Fn_N5110_WriteData(uint8_t Data);
void Fn_N5110_WriteCommand(uint8_t Command);
void Fn_N5110_Init(void);
void Fn_N5110_GotoXY(uint8_t X, uint8_t Y);
void Fn_N5110_Clear(void);
void Fn_N5110_PutChar(uint8_t C);
void Fn_N5110_Puts(uint8_t *s);
#ifdef __cplusplus
}
#endif





#endif

