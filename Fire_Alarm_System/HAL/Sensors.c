#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"




u16 TEMP_Read(void)
{
	u16 temp;
	u16 volt=ADC_VoltRead(LM35_CH);
	
	temp=(volt/5)*5; //NOTE: we divide the read by 5 to guarantee that result's step=0.5
	
	return temp;
}

/*
x=TEMP_Read();
LCD_GoTo(1,0);
LCD_WriteNumber(x/10);
LCD_WriteString(".");
LCD_WriteNumber(x%10);
LCD_WriteString("c   ");
*/

u16 Interpolation(u16 x_adc ,u16 x1 ,u16 x2 ,u16 y1 ,u16 y2)
{
	u16 y=0;
	y= ( 10*( (u32)(y2-y1)*(x_adc)-((u32)(y2-y1)*x1) )/(x2-x1) ) + (10*y1);//we multiplied slop & y1 by 10 to increase the resolution to 0.1.
	
	return y;
}

u16 PRESSURE_Read(void)
{
	u16 pressure=0;
	u16 x=ADC_Read(MPX4115_CH);
	//pressure=( ( (u32)1000*(x-55)+(0.5*921) )/921 )+150 ; //interpolation equation at 15 adc_read=55 ,at 115 adc_read=976.
	//NOTE:we sum the half of the number we divide by it (0.5*921) to make ceiling/flooring.
	pressure=Interpolation(x,55,976,15,115);
	return pressure ;
}


/*
x=PRESSURE_Read();
LCD_GoTo(1,0);
LCD_WriteNumber(x/10);
LCD_WriteString(".");
LCD_WriteNumber(x%10);
LCD_WriteString("pas   ");
*/


/***************************************************  NTC_Temp_fn ************************/

/*
#define  ADC_X   0
#define  TEMP_Y  1
#define  POINTS  10


u16 arr[POINTS][2]={
	{0,10},
	{100,20},
	{200,33},
	{300,60},
	{400,100},
	{550,130},
	{600,150}};
	

	u16 NTC_Temp(void)//370 --->250c
	{
		u8 i;
		u16 temp=0;
		u16 x_adc=0;
		
		x_adc=ADC_Read(NTC_CH);		//		x_adc=370;

		for (i=0;i<POINTS;i++)
		{
			if (x_adc<arr[i][ADC_X])
			{
				temp=Interpolation(x_adc,arr[i-1][ADC_X],arr[i][ADC_X],arr[i-1][TEMP_Y],arr[i][TEMP_Y]);
			}
		}
		return temp;
	}
	
	*/