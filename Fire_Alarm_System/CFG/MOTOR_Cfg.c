#include "StdTypes.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "MOTOR_Cfg.h"

const DIO_Pin_type MotorPins_Arr[TOTAL_MOTORS][2]={
	{M1_IN1 ,M1_IN2}, /*MOTOR 1 IN1,IN2 */
	{M2_IN1 ,M2_IN2}, /*MOTOR 2 IN1,IN2 */
	{M3_IN1 ,M3_IN2}, /*MOTOR 3 IN1,IN2 */
	{M4_IN1 ,M4_IN2}  /*MOTOR 4 IN1,IN2 */
};


/********USING STRUCT***********/

/*

typedef struct{
	DIO_Pin_type IN1;
	DIO_Pin_type IN2;
	
}MotorPins_type;


const MotorPins_type MotorPins_Arr2[TOTAL_MOTORS]={
	{M1_IN1 ,M1_IN2}, //MOTOR 1 IN1,IN2.
	{M2_IN1 ,M2_IN2}, //MOTOR 2 IN1,IN2 
	{M3_IN1 ,M3_IN2}, //MOTOR 3 IN1,IN2 
	{M4_IN1 ,M4_IN2}  //MOTOR 4 IN1,IN2 
};
*/
