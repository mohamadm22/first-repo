/*
 * EEPROM_prg.c
 *
 *  Created on:
 *      Author: Benz
 */
#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"


#include"../../MCAL/TWI/TWI_int.h"

void HEEPROM_vWriteByte(u08 A_SlaveAddress,u08 A_u8Byte,u16 A_u16Adress)
{
	if(A_u16Adress>255)
		A_SlaveAddress|=(A_u16Adress>>8);
	MTWI_u8SetStartCondition();
	MTWI_u8SendAddress(A_SlaveAddress,TWI_WRITE);
	MTWI_u8SendData((u08)A_u16Adress);
	MTWI_u8SendData(A_u8Byte);
	MTWI_u8SetStopCondition();
}
u08 HEEPROM_u8ReadByte(u08 A_SlaveAddress,u16 A_u16Adress)
{
	if(A_u16Adress>255)
		A_SlaveAddress|=(A_u16Adress>>8);
	u08 L_u8Byte=0;
	MTWI_u8SetStartCondition();
	MTWI_u8SendAddress(A_SlaveAddress,TWI_WRITE);
	MTWI_u8SendData((u08)A_u16Adress);
	MTWI_u8SetStartCondition();
	MTWI_u8SendAddress(A_SlaveAddress,TWI_READ);
	MTWI_u8RecieveByte(&L_u8Byte);
	MTWI_u8SetStopCondition();
	return L_u8Byte;
}
