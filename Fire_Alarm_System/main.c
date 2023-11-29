//#include <avr/io.h>

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "MOTOR_Interface.h"
#include "ADC_Interface.h"
#include "Sensors_Interface.h"
#include "TEMP_Filter.h"
#include "Create_PassWord.h"
#include "FireAlarm.h"



int main(void)
{
	DIO_Init();  /*NOTE:DIO_Init(),must be called first before the initialization of any H.W componant uses PINS ex:MOTOR,sensors,LCD */
	LCD_Init();
	KEYPAD_Init();
	MOTOR_Init();
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	
	FILTER_Init(); //CASE: we want filtered temperature
	PassWord_Init();
	FIRE_ALARM_Init();
	
	while(1)
	{

		FILTER_Runnable(); //CASE: we want filtered temperature
		FIRE_ALARM_Runnable();
		
	}
	
}
