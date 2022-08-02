/*
 * SSD_int.h
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#ifndef HAL_SSD_SSD_INT_H_
#define HAL_SSD_SSD_INT_H_

#define COM_ANODE     0
#define COM_CATHODE   1

#define SSD_TYPE COM_CATHODE
#define SSD_PORT_1 DIO_PORTD
#define SSD_PORT_2 DIO_PORTA

void HSSD_init(void);
void HSSD_vDisplayNum(u08 A_u8Num);
void HSSD_vTurnOff(void);



#endif /* HAL_SSD_SSD_INT_H_ */
