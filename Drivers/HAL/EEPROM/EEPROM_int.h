/*
 * EEPROM_int.h
 *
 *  Created on: ١٢‏/٠٨‏/٢٠٢٢
 *      Author: Benz
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

void HEEPROM_vWriteByte(u08 A_SlaveAddress,u08 A_u8Byte,u16 A_u16Adress);
u08 HEEPROM_u8ReadByte(u08 A_SlaveAddress,u16 A_u16Adress);


#endif /* HAL_EEPROM_EEPROM_INT_H_ */
