#include "StdTypes.h"
#include "DIO_Interface.h"

#include "MOTOR_Cfg.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Private.h"


void MOTOR_Init(void)
{
	
};

void MOTOR_Stop(MOTOR_type motor)
{
	DIO_WritePin(MotorPins_Arr[motor][IN1],LOW);
	DIO_WritePin(MotorPins_Arr[motor][IN2],LOW);
	
	/* in case of using Struct instead of Array:
	DIO_WritePin(MotorPins_Arr2[motor].IN1,LOW);
	DIO_WritePin(MotorPins_Arr2[motor].IN2,LOW);
	*/
	
}

void MOTOR_CW(MOTOR_type motor)
{
		DIO_WritePin(MotorPins_Arr[motor][IN1],LOW);
		DIO_WritePin(MotorPins_Arr[motor][IN2],HIGH);
}

void MOTOR_CCW(MOTOR_type motor)
{
		DIO_WritePin(MotorPins_Arr[motor][IN1],HIGH);
		DIO_WritePin(MotorPins_Arr[motor][IN2],LOW);
}



void MOTOR_Speed(MOTOR_type m,u8 speed)
{
	if(speed>MOTOR_MAX_SPEED)
	{
		speed=MOTOR_MAX_SPEED;
		
	}
	
	
}


/*
void MOTOR_Stop(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,LOW);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,LOW);
		break;
	}
	
}

void MOTOR_CW(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(M1_IN1,LOW);
		DIO_WritePin(M1_IN2,HIGH);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,LOW);
		DIO_WritePin(M2_IN2,HIGH);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,LOW);
		DIO_WritePin(M3_IN2,HIGH);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,LOW);
		DIO_WritePin(M4_IN2,HIGH);
		break;
	}
}

void MOTOR_CCW(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(M1_IN1,HIGH);
		DIO_WritePin(M1_IN2,LOW);
		break;
		
		case M2:
		DIO_WritePin(M2_IN1,HIGH);
		DIO_WritePin(M2_IN2,LOW);
		break;
		
		case M3:
		DIO_WritePin(M3_IN1,HIGH);
		DIO_WritePin(M3_IN2,LOW);
		break;
		
		case M4:
		DIO_WritePin(M4_IN1,HIGH);
		DIO_WritePin(M4_IN2,LOW);
		break;
	}
}

*/