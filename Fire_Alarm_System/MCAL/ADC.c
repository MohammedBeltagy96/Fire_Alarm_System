#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"


static u8 ADC_BusyFlag=0;  //used in ADC_GetReadPeriodic();

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/* vref*/

	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	/* pre-scaler*/
	
	scaler= scaler & 0X07; //Mask: guarantees that we'll take only the value of the first 3 bits in case of the enum has more than 7 elements.
	ADCSRA= ADCSRA & 0XF8; //Mask: 0xF8 --> 1111 1000
	ADCSRA= ADCSRA | scaler;
	
	/* enable ADC*/ //NOTE:you must turn on ADC after finishing the configuration(selecting the Vref),Other wise it will work with the old Vref.
	
	SET_BIT(ADCSRA,ADEN);
	
	/*The pre-scaler starts counting from the moment the ADC is switched on by setting the ADEN bit
	in ADCSRA. The pre-scaler keeps running for as long as the ADEN bit is set, and is continuously
	reset when ADEN is low.
	A normal conversion takes 13 ADC clock cycles. The first conversion after the ADC is switched
	on (ADEN in ADCSRA is set) takes 25 ADC clock cycles in order to initialize the analog circuitry.
	*/
	/*By the designe where we enable the ADC at the {ADC_Init(); }-->it will
	be ON all the time that'll increase power consumption
	but on the other hand it'll save the stating time of the ADC and it'll take
	only the time of the 13-ADC_clock_cycles for conversion */
}


u16 ADC_Read(ADC_Channel_type CH)
{
	/* set channel MUX4:0*/
	
	ADMUX = ADMUX & 0XE0;//MASK:0xE0 ---> 111 00000
	ADMUX = ADMUX | CH;
	
	/*start conversion*/
	
	SET_BIT(ADCSRA,ADSC);         //NOTE: Once conversion is done ADSC-bit written low Automatically by hardware.
	while(READ_BIT(ADCSRA,ADSC)); //w8 ADC finish--->Busy Wait(Blocking)
	
	/* get read */
	/*
	// IF ADLR==0 --> by defult
	u16 adc=ADCL;   //referred to DataSheet: we must read the ADCL first then the ADCH
	adc= adc|(ADCH<<8);
	*/
	
	/*
	// IF ADLR==1
	u16 adc=ADCL>>6;
	adc=adc|ADCH<<2;
	
	//if the result is left adjusted and no more than 8-bit precision is required, it is sufficient to read ADCH
	u16 adc=ADCH;
	*/
	return ADC; //NOTE:as ADCL & ADCH located beside each other we used pointer to short to access the address [0x24] as 2 bytes to read both on one time .
}


/*************************** Divide "ADC_READ()" into two Separated functions***************************/


/********************** 1st function ************************/

void ADC_StartConversion(ADC_Channel_type CH)
{
	if (ADC_BusyFlag==0)
	{
		/* set channel mux*/
		ADMUX = ADMUX & 0XE0; //MASK: 111 00000
		ADMUX = ADMUX | CH;
		
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		
		ADC_BusyFlag=1;
	}
}

/********************** 2st function: Blocking /Periodic/ NoBlocking [using Interrupt]  ************************/

u16 ADC_GetReadBlocking(void) //GetRead using Blocking
{
	while(READ_BIT(ADCSRA,ADSC)); //w8 ADC finish current conversion "busy wait( blocking )".

	ADC_BusyFlag=0; //mlho4 lzma hna b3d el busy wait bs ana 7tato 34an m3ml4 fun startConvr lel blocking 3'ar bta3 el periodic.
	
	return ADC;
}

ADC_ConvState_type ADC_GetReadPeriodic( u16* P_data) //NOTE: it return '0' or '1' and takes pointer to return the adc read inside.
{
	/* periodic check  (polling)*/
	
	if (READ_BIT(ADCSRA,ADSC)==0)
	{
		*P_data=ADC;
		
		ADC_BusyFlag=0;
		
		return CONV_COMPLET; //CASE: the conversion completed and new data read.
	}
	return CONV_INPROGRESS;      //CASE: the conversion it still in progress and no new data read.
}

u16 ADC_GetReadNoblock(void) //GetRead using Interrupt(it'll be called inside the "ISR" of ADC )
{
	return ADC;
}

/**********************************************************************************************************/

u16 ADC_VoltRead(ADC_Channel_type CH) //NOT Generic function ,it depends on specific Vref value.
{
	u16 volt;
	u16 adc;
	adc=ADC_Read(CH);
	
	volt=(adc*(u32)5000)/1024; //IN Case of Vref=5000mV & steps=1024 and we've to cast the {5000} to {(u32)5000} because adc=0:1024 Multiplied with 5000 = 0: 5 115 000 so we can't use u16.
	
	return volt;
	
}