/*
 * TWI_prv.h
 *
 *  Created on: Aug 10, 2022
 *      Author: user
 */

#ifndef MCAL_TWI_TWI_PRV_H_
#define MCAL_TWI_TWI_PRV_H_

#define TWBR      *((volatile u08*)(0x20))
#define TWCR      *((volatile u08*)(0x56))
#define TWSR      *((volatile u08*)(0x21))
#define TWDR      *((volatile u08*)(0x23))
#define TWAR      *((volatile u08*)(0x22))

//TWBR:
#define TWBR7       7
#define TWBR6       6
#define TWBR5       5
#define TWBR4       4
#define TWBR3       3
#define TWBR2       2
#define TWBR1       1
#define TWBR0       0

//TWCR:
#define TWINT       7
#define TWEA        6
#define TWSTA       5
#define TWSTO       4
#define TWWC        3
#define TWEN        2
#define TWIE        0

//TWSR:
#define TWS7        7
#define TWS6        6
#define TWS5        5
#define TWS4        4
#define TWS3        3
#define TWPS1       1
#define TWPS0       0

//TWDR:
#define TWD7        7
#define TWD6        6
#define TWD5        5
#define TWD4        4
#define TWD3        3
#define TWD2        2
#define TWD1        1
#define TWD0        0

//TWAR:
#define TWA6        7
#define TWA5        6
#define TWA4        5
#define TWA3        4
#define TWA2        3
#define TWA1        2
#define TWA0        1
#define TWGCE       0

#endif /* MCAL_TWI_TWI_PRV_H_ */
