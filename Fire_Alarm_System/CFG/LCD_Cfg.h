
#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define RS PINA1
#define EN PINA2

/*************** Set LCD_MODE ---> _8_BIT OR 4_BIT ***********************************/
#define LCD_MODE   _4_BIT

/******************* 4_BIT Mode ******************/
#define D4 PINA3
#define D5 PINA4
#define D6 PINA5
#define D7 PINA6

/******************* 8_BIT Mode ******************/
#define LCD_PORT PA    //NOTE:instead of using "PORTA" use "PA" is the enum port_type 


#endif /* LCD_CFG_H_ */


