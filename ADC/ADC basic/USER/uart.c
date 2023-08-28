#include "uart.h"

char data_receice;
uint8_t flag_end_receive = 0;
uint8_t flag_check ;
uint16_t count = 0;
char string_receive[50];

static uint16_t  Usart_Strlen(char *s);

struct __FILE
{
	int dummy;
};
FILE __stdout;

int fputc(int _chr, FILE *f)
{
	Usart_Send_Char( _chr);
	return _chr;
}

void Pin_Config (GPIO_TypeDef * GPIOx, uint16_t TxPINx_, uint16_t RxPINx)
{
	GPIO_InitTypeDef GPIO;
	if(GPIOx == GPIOA )
	{
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE );
	}	
		if(GPIOx == GPIOB )
	{
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE );
	}	
		if(GPIOx == GPIOC )
	{
		RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE );
	}	
	// pin tx
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO.GPIO_Pin = TxPINx_;
	GPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO );
	// pin rx 
	GPIO.GPIO_Pin = RxPINx;
	GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO );
}

void Usart_Config (USART_TypeDef * USARTx, uint32_t BaudRate )
{
	USART_InitTypeDef usart;
	if (USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		Pin_Config (GPIOA, GPIO_Pin_9, GPIO_Pin_10);
		NVIC_EnableIRQ (USART1_IRQn);
	}
	if (USARTx == USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		Pin_Config (GPIOA, GPIO_Pin_2, GPIO_Pin_3);
		NVIC_EnableIRQ (USART2_IRQn);
	}
	if (USARTx == USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		Pin_Config (GPIOB, GPIO_Pin_10, GPIO_Pin_11);
		NVIC_EnableIRQ (USART3_IRQn);
	}
	usart.USART_BaudRate = BaudRate;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_Init (USARTx, &usart);
	
	USART_Cmd (USARTx, ENABLE);
	USART_ITConfig( USARTx, USART_IT_RXNE , ENABLE);
	USART_Cmd (USARTx, ENABLE);
}

void Usart_Send_Char (char _chr)
{
	USART_SendData (USART1, _chr);
	while(USART_GetFlagStatus(USART1 ,USART_FLAG_TXE )== RESET);
}
void Usart_Send_String(char *str)
{
	while(*str != NULL)
	{
		Usart_Send_Char( *str++ );
	}
}

void Usart_SendNumber(float value)
{
	char buf[20];
	uint32_t length, int_value, i, digit;
	float decimal_value;
	if(value < 0)
	{
		Usart_Send_Char ('-');
		value = - value;
	}
	
	int_value = (int)value ;
	length = 0;
	decimal_value = value - int_value;
	while (int_value > 0)
	{
		buf[length++] = '0' + int_value %10;
		int_value /=10;
	}
	for(i =0 ; i< length /2; i++)
	{
		char temp = buf[i];
		buf[i] = buf[length - i -1];
		buf[length - i - 1] = temp;
	}
	if(length == 0)
	{
		buf[length++] = '0';
	}
	
	buf[length++] = '.';
	
	for(i = 0 ; i < 2; i++)
	{
		decimal_value *= 10;
		digit = (uint16_t) decimal_value;
		buf[length++] = '0' + digit ;
		decimal_value -= digit;
	}
	
	for(i = 0; i< length; i++)
	{
		Usart_Send_Char(buf[i]);
	}
}

void USART1_IRQHandler()
 {
	if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET)
	{
		data_receice = USART_ReceiveData(USART1);	
		if(data_receice != '\n')
		{
			string_receive[count] = data_receice;
			count++;
		}
		else
		{
			string_receive[count - 1] = NULL;
			flag_end_receive = 1; 
			count = 0;
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

uint8_t Usart_CheckFlag (void )
{
	if(flag_end_receive == 1)
	{
		flag_end_receive = 0;
		return 1;
	}
	return 0;
}

uint16_t  Usart_Strlen(char *s)
{
	int Dem = 0;
	while(s[++Dem]!=0)
	{
	};
	return Dem;
}

uint16_t Usart_Compare(char *string)
{
	uint16_t i =0;
	uint16_t length1, length2;
	length1 = Usart_Strlen(string_receive);
	length2 = Usart_Strlen(string);
	if(length1 != length2)
	{
		return 0;
	}
	while(string[i] != string_receive[i])
	{
		i = 0;
		return 0;
	}
	return 1;
}

void Usart_Put_Char_Receive (void)
{
	Usart_Send_String(string_receive);
}
