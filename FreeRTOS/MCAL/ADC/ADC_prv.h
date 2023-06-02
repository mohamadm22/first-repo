/*
  * ADC_pvr.h
 *
 *  Created on: Jul 8, 2022
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_

//ADMUX:
#define REFS1   7
#define REFS0   6
#define ADLAR   5

//ADCSRA:
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

#define ADMUX     *((volatile u08*)(0x27))
#define ADCSRA    *((volatile u08*)(0x26))
#define SFIOR     *((volatile u08*)(0x50))
#define ADC       *((volatile u16*)(0x24))

#endif /* MCAL_ADC_ADC_PRV_H_ */
