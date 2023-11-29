#include "StdTypes.h"
#include "Sensors_Interface.h"
#include "TEMP_Filter.h"

#define TotalSamples 10

static u16 FILTER_TempArr[10]={0};
static u16 FILTER_FilteredTemp=0;
static u16 FILTER_UnFilteredTemp=0;
//static u16 Temp_temp=0;


void FILTER_Init(void)
{
	FILTER_UnFilteredTemp=TEMP_Read();
	
	for (u8 i=0; i<TotalSamples; i++)
	{
		FILTER_TempArr[i]=FILTER_UnFilteredTemp;
	}
}
/*
void FILTER_Init(void) //we will take 1st temperature sample and fill the array with it and it will be the unfiltered value in case the program needed the reading before call filter_Runable().
{
u16 Temp_Init;

Temp_Init=TEMP_Read();

FILTER_UnFilteredTemp=Temp_Init;

for (u8 i=0; i<10; i++)
{
FILTER_TempArr[i]=Temp_Init;
}

Temp_temp=Temp_Init;
}*/

/* not more than 250 us*/ //----->one normal Convertion time 13 adc-clk-cycle = 104 us ,so 10 reads will need 130 cycle =1040 us.
void FILTER_Runnable(void)
{
	static u8 i=0;
	u16 Temp_sum=0;
	
	FILTER_TempArr[i]=TEMP_Read();
	
	FILTER_UnFilteredTemp=FILTER_TempArr[i];
	
	i++;
	if (i==10)
	{
		i=0;
	}
	
	for (u8 j=0; j<10; j++)
	{
		Temp_sum += FILTER_TempArr[j];
	}
	
	FILTER_FilteredTemp=Temp_sum/10;
	
}

u16 FILTER_GetFilterdTemp(void)
{
	return FILTER_FilteredTemp;
}

u16 FILTER_GetUnFilterdTemp(void)
{
	return FILTER_UnFilteredTemp;
}

/*
void SET_DATA(u8 x) //to
{
	FILTER_FilteredTemp=x;
}
*/



/*
t_Un_filtered=FILTER_GetUnFilterdTemp();
t_filtered=FILTER_GetFilterdTemp();
LCD_GoTo(0,0);
LCD_WriteString("un_filtered: ");
LCD_WriteNumber_4D(t_Un_filtered);
LCD_GoTo(1,0);
LCD_WriteString("filtered   : ");
LCD_WriteNumber_4D(t_filtered);
*/
