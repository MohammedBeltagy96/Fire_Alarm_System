
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_write(u16 Address, u8 Data);
u8 EEPROM_read(u16 Address);


#endif /* EEPROM_INTERFACE_H_ */