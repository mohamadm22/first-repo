/*
 * TWI_int.h
 *
 *  Created on: Aug 10, 2022
 *      Author: user
 */

#ifndef MCAL_TWI_TWI_INT_H_
#define MCAL_TWI_TWI_INT_H_

#define TWI_ACK  1
#define TWI_NACK 0



void TWI_vInit(void);
u08 TWI_u08SendStartCondition(void);
u08 TWI_u08SendRepeatedStartCondition(void);
u08 TWI_u08SendSlaveAddressRW(u08 A_u08SLA , u08 A_u08RW);
u08 TWI_u08SendByte(u08 A_u08Byte);
u08 TWI_u08SendStopCondition(void);
u08 TWI_u08ReceiveByte(u08* A_pu08Byte ,u08 A_u08ACK);
//u08 MTWI_u8GetStatus(void);


#define TWI_WRITE		0
#define TWI_READ		1

#endif /* MCAL_TWI_TWI_INT_H_ */
