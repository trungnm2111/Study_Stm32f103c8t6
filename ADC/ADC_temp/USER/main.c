#include "adc.h"
#include "temperature.h"

static double v_out = 0 ;
static double i= 0;

int main()
{
	ADC_Config();
	DelayInit();
	Usart_Config(USART1, 9600);
	while(1)
	{
		if(i == 100)
		{
			v_out /= 100;
			Usart_SendNumber(Convert_Thermistor(v_out));
			Usart_Send_String("C\n");
			v_out =  0;
			DelayMs(500);
			i = 0;
		}
		else 
		{
			i++;
			v_out += ADCx_Read();
		}
	}
}
