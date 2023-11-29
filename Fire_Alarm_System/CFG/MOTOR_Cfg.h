
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/***************************PIN CONFIGRATION ***************/

#define TOTAL_MOTORS 4

/*M1*/
#define M1_IN1 PIND0
#define M1_IN2 PIND1

/*M2*/
#define M2_IN1 PIND2
#define M2_IN2 PIND3

/*M3*/
#define M3_IN1 PIND4
#define M3_IN2 PIND5

/*M4*/
#define M4_IN1 PIND6
#define M4_IN2 PIND7

/********************************************************************************/

#define  MOTOR_INIT_STATE 0 //start with stopped


#define MOTOR_MAX_SPEED  90



#endif /* MOTOR_CFG_H_ */