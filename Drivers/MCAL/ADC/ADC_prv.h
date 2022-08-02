/*
 * ADC_pvr.h
 *
 *  Created on: Jul 8, 2022
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_

#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define ADATE   5
#define ADEN    7
#define ADIE    3
#define ADIF    4
#define ADSC    6

#define AVCC          1
#define INTERNAL_REF  2
#define AREF          3

#define ADMUX     *((volatile u08*)(0x27))
#define ADCSRA    *((volatile u08*)(0x26))
#define ADCL      *((volatile u08*)(0x24))
#define ADCH      *((volatile u08*)(0x25))
#define SFIOR     *((volatile u08*)(0x50))
#define ADC       *((volatile u16*)(0x24))

#endif /* MCAL_ADC_ADC_PRV_H_ */
