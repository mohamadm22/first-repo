/*
 * SPI_int.h
 *
 *  Created on: Aug 3, 2022
 *      Author: user
 */

#ifndef MCAL_SPI_SPI_INT_H_
#define MCAL_SPI_SPI_INT_H_

void MSPI_vInit(void);
u08 MSPI_u8Tranciever(u08 A_u8Data);

#define SPI_MASTER             1
#define SPI_Slave              0

#define Prescaler_2            0
#define Prescaler_4            1
#define Prescaler_8            2
#define Prescaler_16           3
#define Prescaler_32           4
#define Prescaler_64           5
#define Prescaler_128          6

#define ENABLE                 1
#define DISABLE                0

#define LSB_start              0
#define MSB_start              1



#endif /* MCAL_SPI_SPI_INT_H_ */
