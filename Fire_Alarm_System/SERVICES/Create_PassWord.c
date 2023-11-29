
#include "StdTypes.h"
#include "Utils.h"

#include "EEPROM_Interface.h"
#include "Create_PassWord_Cfg.h"
#include "Create_PassWord.h"


static u8 Default_PassWord[PASSWORD_LENGTH+1]={0};
static u8 Real_PassWordStr[PASSWORD_LENGTH+1]={0};


void PassWord_Init(void)
{
	if (EEPROM_read(PASSWORD_LENGTH) != EEPROM_PASSWORD_FLAG) //putting flag inside EEPROM to Distinguish the first time ever we create and save password inside EEPROM.
	{
		u8 i=0;
		for ( i=0; i<PASSWORD_LENGTH; i++)
		{
			EEPROM_write(i,Default_PassWord[i]);
			Real_PassWordStr[i]=Default_PassWord[i];
		}
		Real_PassWordStr[i]='\0';
		EEPROM_write(PASSWORD_LENGTH,EEPROM_PASSWORD_FLAG); //Putting the "EEPROM_PASSWORD_FLAG" in EEPROM.
	}
	else
	{
		Get_PassWord(Real_PassWordStr);
	}

}

static u8 Str_Length (u8*str)
{
	u8 i=0;
	for(i=0; str[i]; i++)
	{
		//NoThingToDo
	}
	return (i);
}



u8 Set_PassWord (u8* str_NewPassWord)
{
	u8 i=0,lenth=0,result=0;
	
	lenth=Str_Length(str_NewPassWord);
	
	if (lenth==PASSWORD_LENGTH)
	{
		for ( i=0; i<PASSWORD_LENGTH; i++)
		{
			Real_PassWordStr[i]=str_NewPassWord[i];
			EEPROM_write(i,Real_PassWordStr[i]);   //you can separate it in another loop in case you used interrupts to not delay the upper line.
		}
		result=1;
	}
	else
	{
		//Nothing
	}
	
	return result;
}

void Get_PassWord (u8* str_RealPassWord)
{
	u8 j=0;
	for ( j=0; j<PASSWORD_LENGTH; j++)
	{
		str_RealPassWord[j]=EEPROM_read(j);
	}
	str_RealPassWord[j]='\0';
}




