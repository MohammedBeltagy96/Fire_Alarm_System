#ifndef FIREALARM_H_
#define FIREALARM_H_

#define  MAX_PW_LENGTH 9  //As indicated in the Create_PassWord_Cfg file.
#define  start_time_Sec 5 

typedef enum {
	RUNNING,
	ENTERING_PW,
	CHANGING_PW
	
}Sys_Mode_t;

typedef enum {
	FINE,
	HEAT,
	FIRE_ALARM,
}Sys_State_t;

typedef enum {
	RIGHT_PW,
	WRONG_PW
	}PassWord_t;


/*u8 Str_Length (c8*str);*/
PassWord_t Check_PassWord (u8* str1 ,u8* str2);

void FIRE_ALARM_Init(void);
void FIRE_ALARM_Runnable(void);








#endif /* FIREALARM_H_ */