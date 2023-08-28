#include "temperature.h"

static double B = 13750.0;	// K
static double T0 = 298.15;
static double R = 9840.0;
static double Temp = 0, Temp_c = 0   ;
static double Rntc = 0 ;
static double ln = 0,  Read = 0 ;


double Convert_Thermistor(float v_out)
{
	Read = v_out * (3.3 / 4095.0);
	Usart_SendNumber(Read);
	Usart_Send_Char('\n');
	Rntc = (Read * R) / (3.3 - Read);               //Resistance of RT
	ln = log(Rntc / R );
	Temp = (T0 * B) / ((T0 * ln) + B);					//Temperature from sensor
	Temp_c = (float)Temp - 273.15;                 //Conversion to Celsius
	return Temp_c;
}

