#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/*NOTE:the advantage of using "typedef enum" instead of "#define" is that you can pass it to function as an argument(new type) and Debugging */
typedef enum{
	VREF_AREF, //external voltage reference <= 5v.
	VREF_AVCC, //the MCU voltage source=5v.
	VREF_256V  //internal voltage reference=2.56V.
}ADC_VoltRef_type;

typedef enum{
	ADC_SCALER_2=1,   //NOTE:ENUM default start with 0 ,so we must write the number we want to start with and it will be increased by 1.
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;

typedef enum{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;

typedef enum{
	CONV_INPROGRESS,
	CONV_COMPLET
	}ADC_ConvState_type;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler);


u16 ADC_Read(ADC_Channel_type CH); /*u16 --> Max return value=1023 */

//breaking "ADC_Read()" into two functions "ADC_StartConversion()" & "ADC_GetReadNoblock() Or ADC_GetReadPeriodic() Or ADC_GetReadBlocking "
void ADC_StartConversion(ADC_Channel_type CH);

ADC_ConvState_type ADC_GetReadPeriodic(u16*pdata);
u16 ADC_GetReadBlocking(void);

u16 ADC_GetReadNoblock(void);//GetRead using Interrupt


/* return mV*/
u16 ADC_VoltRead(ADC_Channel_type CH); //using "ADC_Read()"

#endif /* ADC_INTERFACE_H_ */