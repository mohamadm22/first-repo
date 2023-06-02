/*
 * TMR_prv.h
 *
 *  Created on: Jul 20, 2022
 *      Author: user
 */

#ifndef MCAL_TMR_TMR_PRV_H_
#define MCAL_TMR_TMR_PRV_H_

#define TCCR0		*((volatile u08*)(0x53))
#define TCNT0		*((volatile u08*)(0x52))
#define OCR0		*((volatile u08*)(0x5C))
#define TIMSK		*((volatile u08*)(0x59))
#define TIFR		*((volatile u08*)(0x58))

#define TCCR2		*((volatile u08*)(0x45))
#define TCNT2		*((volatile u08*)(0x44))
#define OCR2		*((volatile u08*)(0x43))

#define TCCR1A      *((volatile u08*)(0x4F))
#define TCCR1B      *((volatile u08*)(0x4E))
#define TCNT1       *((volatile u16*)(0x4C))
#define OCR1A       *((volatile u16*)(0x4A))
#define OCR1B       *((volatile u16*)(0x48))
#define ICR1        *((volatile u16*)(0x46))

#define WGM00       6
#define WGM01       3
#define COM00       4
#define COM01       5

#define WGM20       6
#define WGM21       3
#define COM20       4
#define COM21       5

#define COM1A1      7
#define COM1A0      6
#define COM1B1      5
#define COM1B0      4
#define WGM11       1
#define WGM10       0
#define WGM12       3
#define WGM13       4

#define TOIE0       0
#define OCIE0       1
#define TICIE1      5
#define OCIE1A      4
#define OCIE1B      3
#define TOIE1       2
#define TOIE2       6
#define OCIE2       7

#define ICES1       6
#endif /* MCAL_TMR_TMR_PRV_H_ */
