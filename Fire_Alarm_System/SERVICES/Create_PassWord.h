

#ifndef CREATE_PASSWORD_H_
#define CREATE_PASSWORD_H_

void PassWord_Init(void);
u8 Set_PassWord (u8* str);  //make it return Done,InvalidePW_Length.Or just return 0/1.
void Get_PassWord (u8* str);

#endif /* CREATE_PASSWORD_H_ */