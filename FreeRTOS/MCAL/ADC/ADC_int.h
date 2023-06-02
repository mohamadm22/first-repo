/*
 * ADC_int.h
 *
 *  Created on: Jul 6, 2022
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_



void MADC_vinit(void);
u16 MADC_u16AnalogRead(u08 A_u8ChannelNo);
u16 MADC_u16AnalogReadASYC(u08 A_u8ChannelNo);
u16 MADC_u16GetData(void);

#define ENABLE          1
#define DISABLE         0

#define Prescaler_2        0b001
#define Prescaler_4        0b010
#define Prescaler_8        0b011
#define Prescaler_16       0b100
#define Prescaler_32       0b101
#define Prescaler_64       0b110
#define Prescaler_128      0b111

#define AVCC          1
#define INTERNAL_REF  2
#define AREF          3

#define Free_Running_mode                    0
#define Analog_Comparator                    1
#define External_Interrupt_Request_0         2
#define Timer_Counter0_Compare               3
#define Timer_Counter0_Overflow              4
#define Timer_Counter1_Compare Match_B       5
#define Timer_Counter1_Overflow              6
#define Timer_Counter1_Capture               7

#endif /* MCAL_ADC_ADC_INT_H_ */
