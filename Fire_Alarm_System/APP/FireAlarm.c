#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "Sensors_Interface.h"
#include "TEMP_Filter.h"
#include "Create_PassWord.h"
#include "FireAlarm_Cfg.h"
#include "FireAlarm.h"


static Sys_Mode_t mode=RUNNING ;  //NOTE:initial Mode Running.

static Sys_State_t state=FINE ;   //NOTE:initial state fine.
static u8 flag_reversable=1;
static u8 flag_Change_PW=0;

static u8 Real_PassWordStr[MAX_PW_LENGTH+1]={0};
static u8 Entered_PassWordStr[MAX_PW_LENGTH+1]={0};
	
static PassWord_t PassWord=WRONG_PW;
static u8 PASSWORD_LENGTH;

static u8 key=NO_KEY;

/**********************************************************************************************************************/

static u8 Str_Length (u8*str)
{
	u8 i=0;
	for(i=0; str[i]; i++)
	{
		//NoThingToDo
	}
	return (i);
}


void FIRE_ALARM_Init(void)
{
	Get_PassWord(Real_PassWordStr); //Get password from EEPROM (the default one / the last updated one ).
	PASSWORD_LENGTH=Str_Length(Real_PassWordStr);
	
	LCD_GoTo(0,0);
	LCD_WriteString("Press '1' or '2' ");
	_delay_ms(500);
	LCD_GoTo(0,0);
	LCD_WriteString("1-Change  2-Run  ");
	LCD_GoTo(1,0);
	LCD_WriteString("PassWrd.  ( sec)");
	
	s16 i=0;
	u8 flag=0;
	
	for (i=(100*(start_time_Sec)+99); ((i>=99)&&(flag==0)); i--)
	{
		key=KEYPAD_Getkey();
		
		if (key != NO_KEY)
		{
			if (key=='1')
			{
				mode=CHANGING_PW;
				flag=1;
			}
			else if (key=='2')
			{
				mode=RUNNING;
				flag=1;
			}
		}
		else
		{
			LCD_GoTo(1,11);
			LCD_WriteNumber(i/100);
			_delay_ms(5);   //you can use any timer for this counting by set callback
		}
	}

}

void FIRE_ALARM_Runnable(void)
{
	
	static u8 LCD_Running_flag=0;
	static u8 LCD_ChangingPW_flag=0;
	static u8 LCD_EnteringPW_flag=0;
	
	static u8 Total_Entered_PW=0;
	u16 Temp,Smoke;
	
	key=KEYPAD_Getkey();  //key periodic check.
	
	switch (mode)
	{
		
		case RUNNING:
		
		if (LCD_Running_flag==0)
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteString("Temp");
			LCD_GoTo(0,11);
			LCD_WriteString("smoke");
			LCD_GoTo(1,11);
			LCD_WriteString("----"); //clear smoke reading.
			
			LCD_Running_flag=1;
		}
		
		Temp=FILTER_GetFilterdTemp();
		//Temp=TEMP_Read();  //without filtering temperture read.
		
		if(state != FIRE_ALARM)
		{
			LCD_GoTo(1,0);
			LCD_WriteNumber_4D(Temp);
		}
		
		if(Temp<=CRITICAL_TEMP && flag_reversable==1)
		{
			state=FINE;
		}
		else if (Temp>=(CRITICAL_TEMP+HYSTERESIS_VALUE) && flag_reversable==1 )
		{
			Smoke=PRESSURE_Read();
			LCD_GoTo(1,11);
			LCD_WriteNumber_4D(Smoke);
			
			if(Smoke<=CRITICAL_SMOKE && flag_reversable==1)
			{
				state=HEAT;
			}
			else
			{
				state=FIRE_ALARM;
				flag_reversable=0; //NOTE:system can't return from "FIRE_ALARM" state to "PRE_ALARM" neither "STABLE".
				LCD_GoTo(0,0);
				LCD_WriteString("     FIRE!!!!!     ");
				LCD_GoTo(1,0);
				LCD_WriteString("To Rest Press 1     ");
				LCD_GoTo(1,0);
				
			}
		}
		else if( key != NO_KEY && flag_reversable==0 )
		{
			if(key=='1')
			{
				mode=ENTERING_PW;  //Exit running mode to enter the password and reset the sys manually.
				LCD_EnteringPW_flag=0;
			}
			
		}
		
		switch (state)
		{
			case FINE:
			LCD_GoTo(1,6);
			LCD_WriteString("FINE");
			LCD_GoTo(1,11);
			LCD_WriteString("----"); //clear smoke reading.

			DIO_WritePin(Buzzer,LOW);
			DIO_WritePin(GreanLed,HIGH);
			DIO_WritePin(RedLed,LOW);
			DIO_WritePin(OrangeLed,LOW);
			MOTOR_Stop(M1);
			break;
			
			case HEAT:
			LCD_GoTo(1,6);
			LCD_WriteString("HEAT");
			
			DIO_WritePin(Buzzer,LOW);
			DIO_WritePin(GreanLed,LOW);
			DIO_WritePin(RedLed,LOW);
			DIO_WritePin(OrangeLed,HIGH);
			MOTOR_Stop(M1);
			break;
			
			case FIRE_ALARM:
			DIO_WritePin(Buzzer,HIGH);
			DIO_WritePin(GreanLed,LOW);
			DIO_WritePin(RedLed,HIGH);
			DIO_WritePin(OrangeLed,LOW);
			MOTOR_CW(M1);
			break;
		}
		break;
		/***********************************************************__case ENTERING_PW__***********************************************/
		case ENTERING_PW:
		
		if (LCD_EnteringPW_flag==0)
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteString("Enter PassWord:");
			LCD_GoTo(1,0);
			LCD_WriteString("*****           ");
			LCD_GoTo(1,0);

			LCD_EnteringPW_flag=1;
		}
		
		if (key != NO_KEY )
		{
			if (Total_Entered_PW<PASSWORD_LENGTH && key!='C' && (key >='0' && key <='9'))
			{
				Entered_PassWordStr[Total_Entered_PW]=key;
				LCD_WriteChar(key);
				Total_Entered_PW++;
			}
			else if(key=='C')
			{
				Total_Entered_PW=0;
				LCD_GoTo(1,0);
				LCD_WriteString("*****           ");
				LCD_GoTo(1,0);
			}
			else if(key=='=' && Total_Entered_PW==PASSWORD_LENGTH )
			{
				Entered_PassWordStr[Total_Entered_PW]=0; 
				PassWord=Check_PassWord(Real_PassWordStr,Entered_PassWordStr);
				if(PassWord==RIGHT_PW)
				{
					Total_Entered_PW=0;
					state=FINE;
					flag_reversable=1;
					mode=RUNNING;
					LCD_Running_flag=0;
				}
				else
				{
					LCD_GoTo(1,0);
					LCD_WriteString("Wrong PassWord!!!       ");
				}
			}
			else
			{
				//NoThing
			}
			
		}
		break;
		/***********************************************************__case CHANGING_PW__***********************************************/

		case CHANGING_PW:
		
		if (LCD_ChangingPW_flag==0)
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteString("Enter Old PW :    ");
			LCD_GoTo(1,0);
			LCD_WriteString("*****           ");
			LCD_GoTo(1,0);
			
			LCD_ChangingPW_flag=1;
		}
		
		if (key != NO_KEY )
		{
			if (flag_Change_PW==0)
			{
				if (Total_Entered_PW<PASSWORD_LENGTH && key!='C' && (key >='0' && key <='9'))
				{
					Entered_PassWordStr[Total_Entered_PW]=key;
					LCD_WriteChar(key);
					Total_Entered_PW++;
				}
				else if(key=='C')
				{
					Total_Entered_PW=0;
					LCD_GoTo(1,0);
					LCD_WriteString("*****           ");
					LCD_GoTo(1,0);
				}
				else if(key=='=' && Total_Entered_PW==PASSWORD_LENGTH )
				{
					Entered_PassWordStr[Total_Entered_PW]=0;
					PassWord=Check_PassWord(Real_PassWordStr,Entered_PassWordStr);
					if(PassWord==RIGHT_PW)
					{
						LCD_Clear();
						LCD_GoTo(0,0);
						LCD_WriteString("Enter New PW:");
						LCD_GoTo(1,0);
						LCD_WriteString("*****           ");
						LCD_GoTo(1,0);
						
						Total_Entered_PW=0;
						flag_Change_PW=1;
						
					}
					else
					{
						LCD_GoTo(1,0);
						LCD_WriteString("Wrong PassWord!!!");
						
					}
				}
				else
				{
					//Nothing
				}
			}
			
			else
			{
				if (Total_Entered_PW<PASSWORD_LENGTH && key!='C' && (key >='0' && key <='9'))
				{
					Entered_PassWordStr[Total_Entered_PW]=key;
					LCD_WriteChar(key);
					Total_Entered_PW++;
				}
				else if(key=='C')
				{
					Total_Entered_PW=0;
					LCD_GoTo(1,0);
					LCD_WriteString("*****           ");
					LCD_GoTo(1,0);
				}
				else if(key=='=')
				{
					if (Set_PassWord(Entered_PassWordStr))
					{
						LCD_Clear();
						LCD_GoTo(0,0);
						LCD_WriteString("Password Changed");
						LCD_GoTo(1,0);
						LCD_WriteString("Done !!!!");
						_delay_ms(1000);
						//you need to Update the static global string "Real_PassWordStr".
						for (u8 i=0; i<PASSWORD_LENGTH; i++)
						{
							Real_PassWordStr[i]=Entered_PassWordStr[i];
						}
						
						mode=RUNNING;
						LCD_Running_flag=0;
					}
					else
					{
						flag_Change_PW=0;
						mode=CHANGING_PW;
						LCD_ChangingPW_flag=0;
						
						LCD_Clear();
						LCD_GoTo(0,0);
						LCD_WriteString("PW Changing");
						LCD_GoTo(0,1);
						LCD_WriteString("Failed !!!!");
						_delay_ms(1000);
						
					}
					
				}
				else
				{
					//NoThing
				}
			}
			

		}
		break;
	}

}


PassWord_t Check_PassWord (u8* str1 ,u8* str2)
{
	u8 i=0;
	PassWord_t result=RIGHT_PW;
	for(i=0; str1[i]; i++)
	{
		if(str1[i] != str2[i])
		{
			result=WRONG_PW;
			break;
		}
	}
	
	return result;
}


