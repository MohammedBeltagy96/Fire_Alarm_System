
#include "StdTypes.h"
#include "DIO_Interface.h"

/*const global array so it'll be located on FLASH at .ROWDATA section and the programmer can't change it by code*/

/*NOTE: this type of Configuration using array i called "LINKING_CFG "(BECAUSE AFTER CFG THIS FILE YOU'LL BIULD IT ONLY,NOT ALL THE PROJECT )*/


/********************CHOOSE: OUTPUT / INFREE / INPULL ******************************/
	
const DIO_PinStatus_type DIO_PinsStatusArr[TOTAL_PINS]={
	OUTPUT,      /* Port A Pin 0 */                       //ADC_CH0 (INFREE).
	OUTPUT,      /* Port A Pin 1 */  //segment_A (OUTPUT) //LCD-->RS (OUTPUT) //ADC_CH1 (INFREE).
	OUTPUT,      /* Port A Pin 2 */  //segment_B (OUTPUT) //LCD-->EN (OUTPUT) //ADC_CH2 (INFREE).
	OUTPUT,      /* Port A Pin 3 */  //segment_C (OUTPUT) //LCD-->D4 (OUTPUT) //ADC_CH3 (INFREE).
	OUTPUT,      /* Port A Pin 4 */  //segment_D (OUTPUT) //LCD-->D5 (OUTPUT) //ADC_CH4 (INFREE).
	OUTPUT,      /* Port A Pin 5 */  //segment_E (OUTPUT) //LCD-->D6 (OUTPUT) //ADC_CH5 (INFREE).
	OUTPUT,      /* Port A Pin 6 */  //segment_F (OUTPUT) //LCD-->D7 (OUTPUT) //ADC_CH6 (INFREE).
	INFREE,      /* Port A Pin 7 */  //segment_G (OUTPUT) //ADC_CH7 (INFREE).
	
	OUTPUT,      /* Port B Pin 0 */
	OUTPUT,      /* Port B Pin 1 */
	OUTPUT,		 /* Port B Pin 2 */
	OUTPUT,		 /* Port B Pin 3 */
	OUTPUT,		 /* Port B Pin 4 */  //KeyPad_ROW1 (OUTPUT)
	OUTPUT,		 /* Port B Pin 5 */  //KeyPad_ROW2 (OUTPUT)
	OUTPUT,		 /* Port B Pin 6 */  //KeyPad_ROW3 (OUTPUT)
	OUTPUT,		 /* Port B Pin 7 */  //KeyPad_ROW4 (OUTPUT)
	
	OUTPUT,		 /* Port C Pin 0 */  //Red led
	OUTPUT,		 /* Port C Pin 1 */  //Green led
	OUTPUT,		 /* Port C Pin 2 */  //Blue led
	OUTPUT,		 /* Port C Pin 3 */
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */   //Buzzer (OUTPUT)
	OUTPUT,		 /* Port C Pin 6 */   //7Seg 1st digit Common (OUTPUT)
	OUTPUT,		 /* Port C Pin 7 */   //7Seg 2nd digit Common (OUTPUT)
	
	OUTPUT,		 /* Port D Pin 0 */
	OUTPUT,		 /* Port D Pin 1 */
    INPULL,      /* Port D Pin 2 */   //EXI0->INPULL //KeyPad_COL1->INPULL //Keypad Direct Mode->INPULL //Button1_stopwatch
	INPULL,      /* Port D Pin 3 */   //EXI1->INPULL //KeyPad_COL2->INPULL //Keypad Direct Mode->INPULL //Button2_stopwatch
	INPULL,		 /* Port D Pin 4 */                  //KeyPad_COL3->INPULL //Keypad Direct Mode->INPULL //Button3_stopwatch
	INPULL,		 /* Port D Pin 5 */                  //KeyPad_COL4->INPULL //Keypad Direct Mode->INPULL
	INFREE,		 /* Port D Pin 6 */  //ICP->INFREE
	OUTPUT		 /* Port D Pin 7 */
};	

