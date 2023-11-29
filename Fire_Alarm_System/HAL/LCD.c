
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"




#if LCD_MODE == _8_BIT


static void WriteIns(u8 ins)   /* NOTE:this function is Static because we only use it here */
{
	DIO_WritePin(RS,LOW); /* RS-->LOW : what means you're sending an Instruction. */
	DIO_WritePort(LCD_PORT,ins);
	
	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);
	
}

static void WriteData(u8 data)  /* NOTE:this function is  Static because we only use it here " */
{
	DIO_WritePin(RS,HIGH); /* RS-->HIGH : what means you're sending Data. */
	DIO_WritePort(LCD_PORT,data);

	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	_delay_ms(50); /* FROM DATA_SHEET: wait for more than 30ms after VDD raises to 4.5v */
	//0x38
	WriteIns(0x38);
	WriteIns(0x0c);//0x0c->No cursor , 0x0e--> cursor without blink, 0x0f--> cursor with blink.
	WriteIns(0x01);//clear screen
	_delay_ms(1);  /* NOTE: there's already _delay_ms(1) on the "WriteIns()" ,so we need just 1ms delay here to get total 2ms delay.*/
	WriteIns(0x06); /* Entry Mode set: increase DDRAM address by 1 and shifting is off*/

}


#else


static void WriteIns(u8 ins)   /* NOTE:this function is Static because we only use it here */
{
	DIO_WritePin(RS,LOW); /* RS-->LOW  what means you're sending an Instruction. */
	
	/*We send High Nibble part first*/
	
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));

	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);
	
	/*Then We send the Low Nibble part first*/
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));

	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);
	
}

static void WriteData(u8 data)  /* NOTE:this function is  Static because we only use it here " */
{
	DIO_WritePin(RS,HIGH); /* RS-->HIGH   what means you're sending Data. */

	/*We send the High Nibble part first*/

	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));

	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);

	/*Then We send the Low Nibble part first*/
	
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));

	DIO_WritePin(EN,HIGH); //Trigger raising edge.
	_delay_ms(1);
	DIO_WritePin(EN,LOW); //Trigger falling edge.
	_delay_ms(1);
	
}


void LCD_Init(void)
{
	_delay_ms(50);
	
	/*NOTE: we want to send 3 halves of instruction 1st=2 ,2nd=2 ,3rd=8 */
	/*DON'T FORGET: the function "WriteIns()" on 4_BIT mode it takes the Most signefent part(High Nibble) first*/
	WriteIns(0x02); //it will send 0 (no effect),then 2
                	//But if you sent0x20--> it will send 2 then 0 what'll mean 2nd ins-half =0 not 2 as required
	WriteIns(0x28);//it will send 2 then 8
	
	WriteIns(0x0c);//0x0c->No cursor , 0x0e--> cursor without blink, 0x0f--> cursor with blink.
	WriteIns(0x01);//clear screen
	_delay_ms(1);  /* NOTE: there's already _delay_ms(1) on the "WriteIns()" ,so we need just 1ms delay here to get total 2ms delay.*/
	WriteIns(0x06); /* Entry Mode set: increase DDRAM address by 1 and shifting is off*/

}


#endif





void LCD_GoTo(u8 line,u8 cell)
{
	if (line==0)
	{
		WriteIns( START_OF_LINE0 + cell);  /* (0X80)-->Instruction to SET DDRAM address:(0X80)+address */
	}
	else if (line==1)
	{
		WriteIns( START_OF_LINE1 + cell);  /* (0X80)-->Instruction to SET DDRAM address:(0X80)+(0x40 + address) */
	}
	
}


void LCD_Clear(void)
{
	WriteIns(0x01);//clear screen
	_delay_ms(1);
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}


void LCD_WriteString(c8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}



void LCD_WriteString_Goto(u8 line ,u8 cell,c8* str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}



void LCD_WriteNumber(s32 num) //ex:125  
{
	/*NOTE:if you want to print a descending value call this { LCD_WriteChar('  '); } right after it */
	
	c8 str[20]={0};
	u8 i=0;
	s8 j=0;  //NOTE: j must be sighed to reach -1 when we decrement it
	
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if(num<0) //to print negative numbers.
	{
		LCD_WriteChar('-');
		num=num*-1;
	}
	
	while(num)
	{
		str[i]=(num%10)+'0';
		i++;
		num=num/10;
	}
	
	for(j=i-1; j>=0; j--)
	{
		LCD_WriteChar(str[j]);
	}

}



void LCD_WriteNumber_4D(u16 num) //ex:12087
{
	LCD_WriteChar((num%10000)/1000 +'0'); // 2087/1000=2
	LCD_WriteChar((num%1000)/100 +'0');  // 87/100=0
	LCD_WriteChar((num%100)/10 +'0');   // 87/10=8
	LCD_WriteChar((num%10)/1 +'0');    // 7/1=7
	
}


void LCD_WriteBinary(u8 num)
{
	s8 i=0;
	for(i=7; i>=0; i--)
	{
		//LCD_WriteChar( READ_BIT(num,i)?'1':'0' );
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteHex(u8 num)
{
	//u8 rem=num%16;
	//u8 div=num/16;
	
	u8 HN=num>>4;
	u8 LN=num & 0x0f;
	
	if(HN<10)
	{
		LCD_WriteChar( HN + '0');
	}
	else
	{
		LCD_WriteChar( (HN-10) + 'A');
	}
	
	if(LN<10)
	{
		LCD_WriteChar( LN + '0');
	}
	else
	{
		LCD_WriteChar( (LN-10) + 'A');
	}
	
	
}


/*address= 0:7 ,when you want to type the saved pattern (char ) use function [ LCD_WriteChar(address); ] */
void LCD_CustomChar(u8 address,u8* pattern)
{
	WriteIns(0x40 + address * 8); /*SET CGRAM address: 0x0100_ _ _ _  + address */ 
	                         /*address=block's number={0,1,2,3,4,5,6,7},So we multibly it by 8 to get the byte address*/
	for(u8 i=0; i<8; i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80+0);  /*SET DDRAM address: 0x80 + address */
}

/*
u8 p1[] = {
	0x04,
	0x0A,
	0x04,
	0x0E,
	0x15,
	0x04,
	0x0A,
	0x00
};
u8 p2[] = {
	0x02,
	0x05,
	0x02,
	0x14,
	0x0F,
	0x04,
	0x0A,
	0x11
};
*/

void LCD_Clear_Part(u8 line,u8 cell,u8 No_Cells)
{
	LCD_GoTo(line,cell);
	for(s8 i=0; i<No_Cells; i++)
	{
		LCD_WriteChar(' ');
	}
}