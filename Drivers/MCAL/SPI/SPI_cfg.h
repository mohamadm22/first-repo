/*
 * SPI_cfg.h
 *
 *  Created on: Aug 3, 2022
 *      Author: user
 */

#ifndef MCAL_SPI_SPI_CFG_H_
#define MCAL_SPI_SPI_CFG_H_

/*options:
 * SPI_MASTER
 * SPI_Slave
 */
#define SPI_MODE                 SPI_MASTER

//options:ENABLE/DISABLE
#define SPI_INTERRUPT            DISABLE

//options:LSB_start/MSB_start
#define DATA_TRANSMATE_FIRST     LSB_start

/*Prescaler_X   where X=
 * 2
 * 4
 * 8
 * 16
 * 32
 * 64
 * 128
 */
#define Prescaler                Prescaler_64


#endif /* MCAL_SPI_SPI_CFG_H_ */
