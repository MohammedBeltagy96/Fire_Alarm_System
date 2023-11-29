


#define  KEYPAD_PRG  1  /* define it by value to be true ,TO include KeysArr[] only here when including the "KeyPad_Cfg.h"*/

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Interface.h"



void KEYPAD_Init(void)
{
	for (u8 r=0; r<ROWS; r++)
	{
		//	DIO_WritePin(RowsArr[r],HIGH);
		DIO_InitPin(RowsArr[r],INPULL);
	}
}


u8 KEYPAD_Getkey(void)  //NOTE:when we call it ,it'll works as Polling/periodic-check fun.
{
	u8 r,c;
	u8 key=NO_KEY;
	
	for (r=0;r<ROWS;r++)
	{
		
		//DIO_WritePin(RowsArr[r],LOW);
		DIO_InitPin(RowsArr[r],OUTPUT);
		DIO_WritePin(RowsArr[r],LOW);
		
		for (c=0;c<COLS;c++)
		{
			if (DIO_ReadPin(ColsArr[c])==LOW)
			{
				key=KeysArr[r][c];
				
				_delay_ms(10);                         //small delay to solve denouncing issue.
				while(DIO_ReadPin(ColsArr[c])==LOW);   //busy wait to solve the issue of long press.
				_delay_ms(10);                         //small delay to solve denouncing issue.
			}
		}
		
		//DIO_WritePin(RowsArr[r],HIGH);
		DIO_InitPin(RowsArr[r],INPULL);
	}
	
	return key;
	
}

/*

void KEYPAD_Init(void)
{
for (u8 r=0;r<ROWS;r++)
{
DIO_WritePin(FIRST_OUTPUT+r,HIGH);
}
}


u8 KEYPAD_GetKey(void)
{
u8 r,c,key=NO_KEY;

for (r=0;r<ROWS;r++)
{
DIO_WritePin(FIRST_OUTPUT+r,LOW);
for (c=0;c<COLS;c++)
{
if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
{
key=KeysArr[r][c];
_delay_ms(10);
while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
_delay_ms(10);
}
}
DIO_WritePin(FIRST_OUTPUT+r,HIGH);
}

return key;

}

*/