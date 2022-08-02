/*
 * DIO_prv.h
 *
 *  Created on: Jul 19, 2022
 *      Author: user
 */

#ifndef MCAL_DIO_DIO_PRV_H_
#define MCAL_DIO_DIO_PRV_H_


#define DDRA    *((volatile u08*)(0x3A))
#define PORTA   *((volatile u08*)(0x3B))
#define PINA    *((volatile u08*)(0x39))

#define DDRB    *((volatile u08*)(0x37))
#define PORTB   *((volatile u08*)(0x38))
#define PINB    *((volatile u08*)(0x36))

#define DDRC    *((volatile u08*)(0x34))
#define PORTC   *((volatile u08*)(0x35))
#define PINC    *((volatile u08*)(0x33))

#define DDRD    *((volatile u08*)(0x31))
#define PORTD   *((volatile u08*)(0x32))
#define PIND    *((volatile u08*)(0x30))

#endif /* MCAL_DIO_DIO_PRV_H_ */
