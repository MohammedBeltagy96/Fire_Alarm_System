#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "EEPROM_Interface.h"


void EEPROM_write(u16 Address, u8 Data)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR,EEWE)); //(EECR & (1<<EEWE)) 
	
	/* Set up address and data registers */
	EEAR = Address;
	EEDR = Data;
	
	/* Write logical one to EEMWE */
	SET_BIT(EECR,EEMWE);; //EECR |= (1<<EEMWE);
	
	/* Start eeprom write by setting EEWE */
	SET_BIT(EECR,EEWE); //EECR |= (1<<EEWE);
}


u8 EEPROM_read(u16 Address)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR,EEWE));//(EECR & (1<<EEWE))

	/* Set up address register */
	EEAR = Address;
	
	/* Start eeprom read by writing EERE */
	SET_BIT(EECR,EERE); //EECR |= (1<<EERE);
	
	/* Return data from data register */
	return EEDR;
}