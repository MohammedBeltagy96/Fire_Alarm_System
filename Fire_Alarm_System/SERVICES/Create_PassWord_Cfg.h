
#ifndef CREATE_PASSWORD_CFG_H_
#define CREATE_PASSWORD_CFG_H_

/*NOTE:password frame consists of 10 bytes,starts from Byte-0:Byte-9 in the EEPROM,So [PASSWORD_LENGTH <= 9 ] */

#define PASSWORD_LENGTH       5     //NOTE: default password's elements is Zeros
#define EEPROM_PASSWORD_FLAG '#'






#endif /* CREATE_PASSWORD_CFG_H_ */

