/*
 * TMR_prg.c
 *
 *  Created on: Jul 20, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"



#include"TMR_int.h"
#include"TMR_prv.h"
#include"TMR_cfg.h"


void (*TMR_OVF_callback[5])(void);
void (*TMR_CTC_callback)(void);
void (*TMR_ICU_callback)(void);

u16 G_u16CounterOVF[5];
u16 G_u16CounterCTC;
u08 G_u8I;

void MTMR_vInit(void)
{
#if TIMER0_ENABLE==ENABLE
#if TIMER0_MODE==NORMAL

	CLR_BIT(TCCR0, WGM01) ;
	CLR_BIT(TCCR0, WGM00) ;
	SET_BIT(TIMSK, TOIE0) ;

#elif TIMER0_MODE==PWM

	CLR_BIT(TCCR0, WGM01) ;
	SET_BIT(TCCR0, WGM00) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#endif
#elif TIMER0_MODE==FAST_PWM

	SET_BIT(TCCR0, WGM01) ;
	SET_BIT(TCCR0, WGM00) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#endif
#elif TIMER0_MODE==CTC

	SET_BIT(TCCR0, WGM01) ;
	CLR_BIT(TCCR0, WGM00) ;
	SET_BIT(TIMSK,OCIE0);

#endif
#endif

/********************************************************************************/

#if TIMER1_ENABLE==ENABLE
#if TIMER1_MODE==NORMAL

	CLR_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	CLR_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
	CLR_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	CLR_BIT(TCCR1B, WGM12) ;
	CLR_BIT(TCCR1B, WGM13) ;

	SET_BIT(TIMSK, TOIE1) ;


#elif TIMER1_MODE==FAST_PWM

	SET_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	SET_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
	SET_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	SET_BIT(TCCR1B, WGM12) ;
	SET_BIT(TCCR1B, WGM13) ;


#elif TIMER1_MODE==CTC

	CLR_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	CLR_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
	CLR_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	SET_BIT(TCCR1B, WGM12) ;
	SET_BIT(TCCR1B, WGM13) ;

	SET_BIT(TIMSK, OCIE1A) ;
	SET_BIT(TIMSK, OCIE1B) ;

#endif
#if ICU_ENABLE==ENABLE
	SET_BIT(TIMSK, TICIE1) ;
#endif
#endif

}

void MTMR_vSetPreloadValue(u08 A_u8TimerNO,u16 A_u16Preload)
{
	switch (A_u8TimerNO)
		{
		case Timer0:
			TCNT0 = A_u16Preload ;
			break;

		case Timer1:
			TCNT1 = A_u16Preload ;
			break;
		}
}
void MTMR_vSetCompareValue(u08 A_u8TimerNO,u16 A_u16CompareValue)
{
	switch (A_u8TimerNO)
			{
			case Timer0:
				OCR0=A_u16CompareValue;
				break;

			case Timer1:
				OCR1A=A_u16CompareValue;
				OCR1B=A_u16CompareValue;
				break;
			}
}
void MTMR_vSetTopValue(u16 A_u16TopValue)
{
	ICR1 = A_u16TopValue ;
}
void MTMR_vStartTimer(u08 A_u8TimerNO)
{
	switch (A_u8TimerNO)
	{
	case Timer0:
		TCCR0 = (TCCR0 & 0xF8) | Prescaler ;
		break;

	case Timer1:
		TCCR1B = (TCCR1B & 0xF8) | Prescaler ;
		break;
	}

}
void MTMR_vEndTimer(u08 A_u8TimerNO)
{
	switch (A_u8TimerNO)
		{
		case Timer0:
			TCCR0 = (TCCR0 & 0xF8)  ;
			break;

		case Timer1:
			TCCR1B = (TCCR1B & 0xF8)  ;
			break;
		}
}
void MTMR_vDelayOVF(u16 A_u8Time,void(*ptr)(void))
{

	G_u16CounterOVF[G_u8I] = A_u8Time*4 ;
	TMR_OVF_callback[G_u8I] = ptr ;


	G_u8I++;
		/*  start timer */
		MTMR_vStartTimer(Timer0);

}

void MTMR_vDelayCTC(u08 A_u8Time,u08 L_u8CompareVaule,void(*ptr)(void))
{
	G_u16CounterCTC=(A_u8Time*1000)/L_u8CompareVaule;
	MTMR_vSetCompareValue(Timer0,L_u8CompareVaule);
	TMR_CTC_callback=ptr;
	MTMR_vStartTimer(Timer0);

}
u16 MTMR_u16GetCaptureTime(u08 A_u8TimerNO)
{

	return ICR1;

}
void MTMR_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger)
{
	switch (A_xIcuTrigger)
	{
	case ICU_Falling:
		CLR_BIT(TCCR1B, ICES1) ;
		break;
	case ICU_Rising:
		SET_BIT(TCCR1B, ICES1) ;
		break;
	}
}
void MTMR_vEnableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType)
{
	SET_BIT(TIMSK, TICIE1) ;
}
void MTMR_vDisableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType)
{
	CLR_BIT(TIMSK, TICIE1) ;
}
void MTMR_vSetCallback(void (*ptr)(void))
{
	TMR_CTC_callback=ptr;

}
void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	static u16 LS_u16Counter = 0;


	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if((LS_u16Counter % G_u16CounterOVF[L_u8I])==0)
		{
			if(TMR_OVF_callback[L_u8I] != NULL)
			{
				TMR_OVF_callback[L_u8I]();
			}

		}
	}

		if(LS_u16Counter%4==0)
		{
			MTMR_vSetPreloadValue(Timer0,6);
		}
		if(LS_u16Counter==40000)
		{
			LS_u16Counter=0;
		}
		LS_u16Counter++ ;

}
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{

	while(G_u16CounterCTC!=0)
		{
		G_u16CounterCTC--;

		}
		if(G_u16CounterCTC==0)
			TMR_CTC_callback();



}
void __vector_6(void)  __attribute__((signal));
void __vector_6(void)
{



}
