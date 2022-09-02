/*
 * TWI_prg.c
 *
 *  Created on: Aug 10, 2022
 *      Author: user
 */

#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"


#include"TWI_int.h"
#include"TWI_prv.h"
#include"TWI_cfg.h"

u08 MTWI_u8SetStartCondition(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);

	while (!(TWCR & (1<<TWINT)));

	return (TWSR & 0xF8);
}
u08 MTWI_u8SetRepeatStartCondition(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);

	while (!(TWCR & (1<<TWINT)));

	return (TWSR & 0xF8);
}
u08 MTWI_u8SendAddress(u08 A_u8SlaveAddress,u08 A_u8OperationRW)
{
	TWDR =( A_u8SlaveAddress<<1)|A_u8OperationRW;
	SET_BIT(TWCR,TWINT);
	CLR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);

	while (!(TWCR & (1<<TWINT)));
	return (TWSR & 0xF8);
}
u08 MTWI_u8SendData(u08 A_u8Data)
{
	TWDR =A_u8Data;
	SET_BIT(TWCR,TWINT);
	CLR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWEN);
	while (!(TWCR & (1<<TWINT)));
	return (TWSR & 0xF8);
}
u08 MTWI_u8SetStopCondition(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWEN);
	while (!(TWCR & (1<<TWINT)));

	return (TWSR & 0xF8);
}
u08 MTWI_u8RecieveByte(u08* A_u8ByteSaver )
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWEA);
	while (!(TWCR & (1<<TWINT)));
	*A_u8ByteSaver=TWDR;
	return (TWSR & 0xF8);
}
u08 MTWI_u8GetStatus(void)
{
	return (TWSR & 0xF8);
}
