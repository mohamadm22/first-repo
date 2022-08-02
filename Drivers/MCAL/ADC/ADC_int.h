/*
 * ADC_int.h
 *
 *  Created on: Jul 6, 2022
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#define ADC_REF_VOLT AVCC


void MADC_vinit(void);
u16 MADC_u16AnalogRead(u08 A_u8ChannelNo);
void MADC_vSetCallback(void (*ptr)(void),u08 A_u8ChannelNo);
u16 MADC_u16GetData(void);



#endif /* MCAL_ADC_ADC_INT_H_ */
