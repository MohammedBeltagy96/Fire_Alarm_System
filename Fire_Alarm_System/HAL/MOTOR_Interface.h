

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#define IN1 0
#define IN2 1

typedef enum{
	M1=0,
	M2,
	M3,
	M4,
}MOTOR_type;


void MOTOR_Init(void); /* Any driver must has it's initialization fun "Fun_Init()" */

void MOTOR_Stop(MOTOR_type motor);

void MOTOR_CW(MOTOR_type motor);

void MOTOR_CCW(MOTOR_type motor);

/* speed 0:100*/
/* speed 0:1400*/
void MOTOR_Speed(MOTOR_type motor,u8 speed);


#endif /* MOTOR_INTERFACE_H_ */