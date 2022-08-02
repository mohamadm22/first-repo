/*
 * ADC_prg.c
 *
 *  Created on: Jul 6, 2022
 *      Author: user
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPE.h"


#include"ADC_int.h"
#include"ADC_prv.h"

void (*ADC_callback)(void);


void MADC_vinit(void)
{
#if ADC_REF_VOLT==AVCC
	CLR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
#elif ADC_REF_VOLT==INTERNAL_REF
	SET_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
#elif ADC_REF_VOLT==AREF
	CLR_BIT(ADMUX,REFS1);
	CLR_BIT(ADMUX,REFS0);
#else
#error"select right mode plz!!"
#endif
	CLR_BIT(ADMUX,ADLAR);
	ADCSRA=(ADCSRA&0xF8)|0b110;
	CLR_BIT(ADCSRA,ADATE);
	SET_BIT(ADCSRA,ADEN);
}

u16 MADC_u16AnalogRead(u08 A_u8ChannelNo)
{
	ADMUX=(ADMUX&0xE0)|(A_u8ChannelNo&0x07);
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF)!=1);
	SET_BIT(ADCSRA,ADIF);
	return ADC;

}
void MADC_vSetCallback(void (*ptr)(void),u08 A_u8ChannelNo)
{
	ADMUX=(ADMUX&0xE0)|(A_u8ChannelNo&0x07);
	SET_BIT(ADCSRA,ADSC);
	ADC_callback=ptr;
}
u16 MADC_u16GetData(void)
{
	return ADC;
}

void __vector_16(void)__attribute__((signal));
void __vector_16(void)
{
	ADC_callback();

}
