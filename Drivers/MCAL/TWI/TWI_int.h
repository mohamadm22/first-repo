/*
 * TWI_int.h
 *
 *  Created on: Aug 10, 2022
 *      Author: user
 */

#ifndef MCAL_TWI_TWI_INT_H_
#define MCAL_TWI_TWI_INT_H_

u08 MTWI_u8SetStartCondition(void);
u08 MTWI_u8SetRepeatStartCondition(void);
u08 MTWI_u8SendAddress(u08 A_u8SlaveAddress,u08 A_u8OperationRW);
u08 MTWI_u8SendData(u08 A_u8Data);
u08 MTWI_u8SetStopCondition(void);
u08 MTWI_u8RecieveByte(u08* A_u8ByteSaver );
u08 MTWI_u8GetStatus(void);


#define TWI_WRITE		0
#define TWI_READ		1

#endif /* MCAL_TWI_TWI_INT_H_ */
