

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_


#define NO_KEY 'T'

#define ROWS 4
#define COLS 4

/*
#define FIRST_OUTPUT PINB4
#define FIRST_INPUT  PIND2
*/



/************************ TRICK: to can put array at the header file instead of creating KeyPad_Cfg.c file************/

#if KEYPAD_PRG   

 const u8 KeysArr[ROWS][COLS]={
	  {'7','8','9','/'}
	 ,{'4','5','6','*'}
	 ,{'1','2','3','-'}
	 ,{'C','0','=','+'}
 };

const DIO_Pin_type RowsArr[ROWS]={PINB4,PINB5,PINB6,PINB7};
const DIO_Pin_type ColsArr[COLS]={PIND2,PIND3,PIND4,PIND5};

#endif






#endif /* KEYPAD_CFG_H_ */