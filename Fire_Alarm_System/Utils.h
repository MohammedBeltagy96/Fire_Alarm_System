#ifndef UTILS_H_
#define UTILS_H_


//#define  READ_BIT2(reg,bit) ( reg & (1<<bit) ) /*NOTE: result=0 Or value*/.

#define  READ_BIT(reg,bit) (((reg)>>(bit))&1) /*NOTE: result=0 Or 1  ---> So We prefer this. */
#define  SET_BIT(reg,bit)  (reg = (reg) | (1<<(bit)))
#define  CLR_BIT(reg,bit)  (reg = (reg) & (~(1<<(bit))))
#define  TOG_BIT(reg,bit)  (reg = (reg) ^ (1<<(bit)))


#define F_CPU 8000000  /* 8MHz Cyrstal--> we must put {#define F_CPU 8000000} before including { #include <util/delay.h> }*/
#include <util/delay.h> /* To can use " _delay(); " */


#endif /* UTILS_H_ */