

#ifndef TEMP_FILTER_H_
#define TEMP_FILTER_H_

void FILTER_Init(void);
void FILTER_Runnable(void);
u16 FILTER_GetFilterdTemp(void);
u16 FILTER_GetUnFilterdTemp(void);
void SET_DATA(u8 x);








#endif /* TEMP_FILTER_H_ */