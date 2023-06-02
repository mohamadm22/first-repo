#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"

#include "TWI_int.h"
#include "TWI_prv.h"
#include "TWI_cfg.h"








void TWI_vInit(void)
{
	/*
	 * 1- interrupt enable/disable
	 */
	CLR_BIT(TWCR,TWIE);


	 /*
	 * 2- bit rate
	 */
	TWBR = 10 ;


}

u08 TWI_u08SendStartCondition(void)
{

	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN) ;//TWINT cleared to send data

	while (!(TWCR & (1<<TWINT)));

	/*check status code */

	return (TWSR & 0xF8) ;
}


u08 TWI_u08SendRepeatedStartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN) ;//TWINT cleared to send data

	while (!(TWCR & (1<<TWINT)));

	/*check status code */

	return (TWSR & 0xF8) ;


}



u08 TWI_u08SendSlaveAddressRW(u08 A_u08SLA , u08 A_u08RW)
{
	TWDR = (A_u08SLA << 1) | (A_u08RW) ; //7bits of slave & RW
	TWCR = (1<<TWINT) | (1<<TWEN);

	CLR_BIT(TWCR ,TWSTA) ; //once you sent start condition pulse you have to start


	while (!(TWCR & (1<<TWINT))) ;

	/*check status code */

	return (TWSR & 0xF8) ;
}


u08 TWI_u08SendByte(u08 A_u08Byte)
{
	TWDR = A_u08Byte ; //7bits of slave & RW
	TWCR = (1<<TWINT) | (1<<TWEN);

	CLR_BIT(TWCR ,TWSTA) ; //once you sent start condition pulse you have to start


	while (!(TWCR & (1<<TWINT))) ;

	/*check status code */

	return (TWSR & 0xF8) ;


}

u08 TWI_u08ReceiveByte(u08* A_pu08Byte ,u08 A_u08ACK)
{
	switch(A_u08ACK)
	{
	case TWI_ACK :
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		break;
	case TWI_NACK:
		TWCR = (1<<TWINT) | (1<<TWEN) ;
		CLR_BIT(TWCR ,TWEA);
		break;
	}

	while (!(TWCR & (1<<TWINT))) ;


	*A_pu08Byte = TWDR ;

	/*check status code */

	return (TWSR & 0xF8) ;


}


u08 TWI_u08SendStopCondition(void)
{

	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);

	return (TWSR & 0xF8) ;
}
