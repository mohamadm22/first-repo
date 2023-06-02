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
#include"ADC_cfg.h"
u08 ReadFlag=0;
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

#if Auto_Trigger==ENABLE

	SET_BIT(ADCSRA,ADATE);
	SFIOR&=0x1f;
	SFIOR|=(Auto_Trigger_Mode<<5);

#elif Auto_Trigger==DISABLE

	CLR_BIT(ADCSRA,ADATE);

#endif
	CLR_BIT(ADMUX,ADLAR);
	ADCSRA=(ADCSRA&0xF8)|Prescaler;
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
u16 MADC_u16AnalogReadASYC(u08 A_u8ChannelNo)
{
	ReadFlag=0;
	ADMUX=(ADMUX&0xE0)|(A_u8ChannelNo&0x07);
	SET_BIT(ADCSRA,ADSC);
	SET_BIT(ADCSRA,ADIE);
	while(ReadFlag!=1);
	return ADC;
}

void __vector_16(void)__attribute__((signal));
void __vector_16(void)
{
	ReadFlag=1;

}
