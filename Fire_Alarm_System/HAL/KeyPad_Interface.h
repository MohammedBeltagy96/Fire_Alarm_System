
#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_




#include "KeyPad_Cfg.h" /*NOTE: WE had to include[KeyPad_Cfg.h] here ,to be included with [KeyPad_Interface] as we will need to 
                               #define ROWS 4 ,#define COLS 4,#define NO_KEY 'T' */

void KEYPAD_Init(void);

u8 KEYPAD_Getkey(void);



#endif /* KEYPAD_INTERFACE_H_ */