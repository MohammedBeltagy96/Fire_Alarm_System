
#ifndef MEMMAP_H_
#define MEMMAP_H_

/*
char---> register size is 1byte(8 bits).
Volatile--> h.w register.
unsigned--->to use bitwise operation without problems of exciting 1 in the last bit of signed num.
const---> in case the register is read olny.
*/

/****************************************** DIO_REGISTERS *************************************/

#define PORTA  (*(volatile unsigned char* )(0x3B)) /* R/W */
#define DDRA   (*(volatile unsigned char* )(0x3A)) /* R/W */
#define PINA   (*(const volatile unsigned char* )(0x39)) //we used "CoNST" because it read only register 

#define PORTB  (*(volatile unsigned char* )(0x38))
#define DDRB   (*(volatile unsigned char* )(0x37))
#define PINB   (*(const volatile unsigned char* )(0x36))

#define PORTC  (*(volatile unsigned char* )(0x35))
#define DDRC   (*(volatile unsigned char* )(0x34))
#define PINC   (*(volatile unsigned char* )(0x33))

#define PORTD  (*(volatile unsigned char* )(0x32))
#define DDRD   (*(volatile unsigned char* )(0x31))
#define PIND   (*(const volatile unsigned char* )(0x30))


/******************************************  ADC_REGISTERS  *************************************/

#define ADMUX (*(volatile unsigned char*)0x27)  //ADC Multiplexer Selection Register.

/*MUX4:0: Analog Channel and Gain Selection Bits*/
#define MUX0  0
#define MUX1  1
#define MUX2  2
#define MUX3  3
#define MUX4  4

#define ADLAR 5 //ADC Left Adjust Result.

/*REFS1:REFS0 : Voltage Reference Selection Bits*/
#define REFS0 6
#define REFS1 7


#define ADCSRA (*(volatile unsigned char*)0x26) //ADC Control and Status Register A.

/* ADPS2:0: ADC Pre-scaler Select Bits*/
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2

#define ADIE  3 //ADC Interrupt Enable
#define ADIF  4 //ADC Interrupt Flag
#define ADATE 5 //ADC Auto Trigger Enable
#define ADSC  6 //ADC Start Conversion
#define ADEN  7 //ADC Enable:


#define ADCL (*(volatile unsigned char*)0x24) //ADC Data Register Low Byte
#define ADCH (*(volatile unsigned char*)0x25) //ADC Data Register High Byte

#define ADC  (*(volatile unsigned short*)0x24)//NOTE:as ADCL & ADCH located beside each other we used pointer to short to access the address [0x24] as 2 bytes to read both on one time .



/*************************************************************** __INTERRUPT__ ****************************************************/

/************************************** Interrupt functions ************************/

//NOTE:you can Enable/ Disable the GI using C-Language by writing on the SREG I-bit ,But using Attributes is faster.
# define sei()  __asm__ __volatile__ ("sei" ::) //Set Interrupt   -->Enable Global Interrupt. //NOTE: the paranthieses'()' for readiablty to make it like function.
# define cli()  __asm__ __volatile__ ("cli" ::) //Clear Interrupt -->Disable Global Interrupt.

# define reti()  __asm__ __volatile__ ("reti" ::) //(For ISR call)       -->Update the PC with the saved value from stack and Enable the Global interrupt by setting the 7th bit of the SREG by 1.
# define ret()  __asm__ __volatile__ ("ret" ::)   //(For normal fun call)-->Update the PC with the saved value from stack,Only.

//Interrupt Service Routine as Veridical Micro Like Function .NOTE: to make Context save and restore we use this attribute (__attribute__ ((signal))__VA_ARGS__)
#  define ISR(vector,...) \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#  define ISR_NOBLOCK    __attribute__((interrupt)) //if you want to open GI before the Context Save not after finishing ISR_code as normally happens.
#  define ISR_NAKED      __attribute__((naked)) //you tell the compiler not to make Save/restore and do only the writen code in ISR.

/************************************ Interrupt vectors ****************************/

/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3

//------------------------------------------------------>>>
/* Timer/Counter2--> Compare Match */
#define TIMER2_OC_vect	__vector_4               //#define TIMER2_COMP_vect	__vector_4
/* Timer/Counter2--> Overflow Interrupt */
#define TIMER2_OVF_vect		__vector_5

/* Timer/Counter1--> Input Capture Unit "Event" Interrupt */
#define TIMER1_ICU_vect		__vector_6
/* Timer/Counter1--> Output Compare Match Interrupt A */
#define TIMER1_OCA_vect		__vector_7
/* Timer/Counter1--> Output Compare Match Interrupt B */
#define TIMER1_OCB_vect		__vector_8
/* Timer/Counter1--> Overflow */
#define TIMER1_OVF_vect		__vector_9

/* Timer/Counter0--> Output Compare Match Interrupt */
#define TIMER0_OC_vect		__vector_10
/* Timer/Counter0--> Overflow Interrupt*/
#define TIMER0_OVF_vect		__vector_11
//------------------------------------------------------>>>

/* Serial Transfer Complete */
#define SPI_STC_vect		__vector_12

/* USART, Rx Complete */
#define UART_RX_vect		__vector_13
/* USART Data Register Empty */
#define UART_UDRE_vect		__vector_14
/* USART, Tx Complete */
#define UART_TX_vect		__vector_15

/* ADC Conversion Complete */
#define ADC_vect		    __vector_16

/* EEPROM Ready */
#define EE_RDY_vect		    __vector_17

/* Analog Comparator */
#define ANA_COMP_vect		__vector_18

/* 2-wire Serial Interface */
#define TWI_vect		    __vector_19

/* Store Program Memory Ready */
#define SPM_RDY_vect		__vector_20

#define BAD_vect            __vector_default  //Default_Vectore(go to 0x0 --> rest vectore) in case you make an interrupt without without specific ISR.
 
 /*NOTE: to change this default vector you write an ISR for it
 void ISR(BAD_vect)
 {
	 DIO_TogglePin(PINC2);//Blue Led
	 _delay_ms(200);
 }										        
*/											


/*********************************************** INTERRUPT_REGISTERS *************************/

/*External Interrupt */

#define MCUCR   (*(volatile unsigned char*)0x55) //The MCU Control Register contains control bits for power management.
#define ISC00 0 // ISC00, ISC01: Interrupt Sense Control 0 (INT0)-->{Low-level / Logic change / Raising-edge /Falling-edge}.
#define ISC01 1
#define ISC10 2 // ISC10, ISC11: Interrupt Sense Control 1 (INT1)-->{Low-level / Logic change / Raising-edge /Falling-edge}.
#define ISC11 3

#define MCUCSR   (*(volatile unsigned char*)0x54) //The MCU Control and Status Register provides information on which reset source caused an MCU Reset.
#define ISC2 6          // ISC2: Interrupt Sense Control 2 (INT2) -->{ '0' Falling-edge/ '1' Raising-edge}.

#define GICR     (*(volatile unsigned char*)0x5B) //General Interrupt Control Register.
#define INT2 5  //Bit 5 – INT0:External Interrupt Request 2 Enable.
#define INT0 6  //Bit 6 – INT0:External Interrupt Request 0 Enable.
#define INT1 7  //Bit 7 – INT1:External Interrupt Request 1 Enable.

#define GIFR    (*(volatile unsigned char*)0x5A) //General Interrupt Flag Register.
#define INTF2 5 //Bit 5 – INTF2: External Interrupt Flag 2.
#define INTF0 6 //Bit 6 – INTF0: External Interrupt Flag 0.
#define INTF1 7 //Bit 7 – INTF1: External Interrupt Flag 1.

/*********************************************** TIMERS_REGISTERS *************************/

#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)
#define TIFR    (*(volatile unsigned char*)0x58)

#define TIMSK   (*(volatile unsigned char*)0x59)  //Timer Interrupt Mask Register.
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52)

#define TCCR0   (*(volatile unsigned char*)0x53) // Timer/Counter Control Register.
#define FOC0    7    //Force Output Compare match.(will not set the OCF0 Flag or reload/clear the timer, but the OC0 pin will be updated as if a real compare match had occurred)
#define WGM00   6
#define COM01   5   //The Compare Output mode (COM01:0) bits.
#define COM00   4
#define WGM01   3
#define CS02    2   //Clock Select (CS01:2) bits
#define CS01    1
#define CS00    0

#define OCR0    (*(volatile unsigned char*)0x5C) // Output Compare Register of TIMER0.

/******************************************************************/
/*TIMER 1*/

/*ICR1-->Input Capture unite Register*/
#define ICR1         (*(volatile unsigned short*)0x46) //accesses the smaller address with pointer to short to read both bytes at once.
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)

/*OCR-->OutPut Compare Register*/
#define OCR1B     (*(volatile unsigned short*)0x48) //accesses the smaller address with pointer to short to read both bytes at once
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)

/*ICR1-->Output Compare Register of TIMER1*/
#define OCR1A     (*(volatile unsigned short*)0x4A) //accesses the smaller address with pointer to short to read both bytes at once
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)

/*TCNT-->Timer Counter Register*/
#define TCNT1       (*(volatile unsigned short*)0x4C)//accesses the smaller address with pointer to short to read both bytes at once
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)

#define TCCR1B       (*(volatile unsigned char*)0x4E)  // Timer/Counter Control Register.
#define ICNC1   7
#define ICES1   6
// bit 5 reserved 
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

#define TCCR1A        (*(volatile unsigned char*)0x4F) // Timer/Counter Control Register.
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)
/******************************************************************/
/* Timer 2 */

#define OCR2     (*(volatile unsigned char*)0x43) //OCR-->Output Compare Register.
#define TCNT2    (*(volatile unsigned char*)0x44) //TCNT-->Timer Counter Register.

#define TCCR2    (*(volatile unsigned char*)0x45) // Timer/Counter Control Register.
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

#define ASSR    (*(volatile unsigned char*)0x42) //ASSR-->Asynchronous Status Register.
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0





/********************************************************** Watch Dog Timer Register ********************************************/
/* WDTCR */
#define WDTCR    (*(volatile unsigned char*)0x41)
/* bits 7-5 reserved */
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0



/************************************************************ UART_Registers ****************************************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0
/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define    URSEL        7
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0



/************************************************************ SPI_Registers ********************************************/
/* SPI */
/* SPI Control Register */
#define SPCR       (*(volatile unsigned char*)0x2D)
/* SPI Status Register */
#define SPSR       (*(volatile unsigned char*)0x2E)
/* SPI I/O Data Register */
#define SPDR       (*(volatile unsigned char*)0x2F)

/* SPI Status Register - SPSR */
#define    SPIF         7
#define    WCOL         6
#define    SPI2X        0

/* SPI Control Register - SPCR */
#define    SPIE         7
#define    SPE          6
#define    DORD         5
#define    MSTR         4
#define    CPOL         3
#define    CPHA         2
#define    SPR1         1
#define    SPR0         0

/***************************************************** EEPROM_Control_Register ************************************************/

#define EECR	(*(volatile unsigned char*)0x3C)  // EEPROM Control Register.

//NOTE: Bits 7..4 – Reserved Bits.-->These bits are reserved bits in the ATmega32 and will always read as zero.
#define    EERIE        3   //EEPROM Ready Interrupt Enable.
#define    EEMWE        2   //EEPROM Master Write Enable.
#define    EEWE         1   //EEPROM Write Enable.
#define    EERE         0   //EEPROM Read Enable.

#define EEDR	(*(volatile unsigned char*)0x3D) // EEPROM Data Register.

/* EEPROM Address Register */
#define EEAR	(*(volatile unsigned short*)0x3E) //Casting the Low register address to "short"
#define EEARL	(*(volatile unsigned char*)0x3E)
#define EEARH	(*(volatile unsigned char*)0x3F)


/************************************************************ I2C_Registers ********************************************/


/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define TWBR    (*(volatile unsigned char*)0x20)
#define TWSR    (*(volatile unsigned char*)0x21)
#define TWAR    (*(volatile unsigned char*)0x22)
#define TWDR    (*(volatile unsigned char*)0x23)

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

/* SPMCR */
#define SPMIE   7
#define RWWSB   6
/* bit 5 reserved */
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

/********************************************************** Interrupt-Vectors & Functions ****************************************/









#endif /* MEMMAP_H_ */