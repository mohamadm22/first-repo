/*
 * TMR_prg.c
 *
 *  Created on: Jul 20, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"

#include"../DIO/DIO_int.h"

#include"TMR_int.h"
#include"TMR_prv.h"
#include"TMR_cfg.h"
/*global variables*/
static u16 GS_u16pt=0;
static u16 GS_u16ont=0;
static u08 GS_u8ReadFlag=0;
/*pointers of function to use in interrupt*/
void (*TMR0_OVF_callback[5])(void);
u08 TMR0_OVF_Pointer[5]={0};
u08 Pointer_0_deg=0;

void (*TMR1_OVF_callback[5])(void);
void (*TMR1_ICU_callback)(void);
u08 TMR1_OVF_Pointer[5]={0};
u08 Pointer_1_deg=0;

void (*TMR2_OVF_callback[5])(void);
u08 TMR2_OVF_Pointer[5]={0};
u08 Pointer_2_deg=0;


/*global variables used in interrupts*/
u16 G_u16CounterOVF0[5];
u08  G_u8FlagOVF0[5];
u08 G_u8I0;

u16 G_u16CounterOVF1[5];
u08 G_u8I1;

u16 G_u16CounterOVF2[5];
u08 G_u8I2;



void MTMR_vChangeMood(u08 A_u8TimerNO,u08 A_u8Mood)
{
	if(A_u8TimerNO==Timer0)
	{
		if(A_u8Mood==NORMAL)
		{
			/*choose the normal mood*/
				CLR_BIT(TCCR0, WGM01) ;
				CLR_BIT(TCCR0, WGM00) ;
			/*dont need it in normal mode*/
				CLR_BIT(TCCR0, COM00) ;
				CLR_BIT(TCCR0, COM01) ;
			/*enable TMR0 OVF interrupt*/
				SET_BIT(TIMSK, TOIE0) ;
		}
		else if(A_u8Mood==PWM)
		{
			CLR_BIT(TCCR0, WGM01) ;
			SET_BIT(TCCR0, WGM00) ;
			CLR_BIT(TCCR0, COM00) ;
			SET_BIT(TCCR0, COM01) ;
			MDIO_vSetPinDir(DIO_PORTB,DIO_PIN3,DIO_Output);
		}
		else if(A_u8Mood==FAST_PWM)
		{
			SET_BIT(TCCR0, WGM01) ;
			SET_BIT(TCCR0, WGM00) ;
			CLR_BIT(TCCR0, COM00) ;
			SET_BIT(TCCR0, COM01) ;
			MDIO_vSetPinDir(DIO_PORTB,DIO_PIN3,DIO_Output);
		}
		else if(A_u8Mood==COMPARE)
		{
			/*choose the CTC mood*/
				SET_BIT(TCCR0, WGM01) ;
				CLR_BIT(TCCR0, WGM00) ;
			/*dont need it in CTC mode*/
				CLR_BIT(TCCR0, COM00) ;
				CLR_BIT(TCCR0, COM01) ;
			/*enable TMR0 CTC interrupt*/
				SET_BIT(TIMSK,OCIE0);
		}
	}
	if(A_u8TimerNO==Timer1)
	{
		if(A_u8Mood==NORMAL)
		{
			/*dont need it in normal mode*/
				CLR_BIT(TCCR1A, COM1A1) ;
				CLR_BIT(TCCR1A, COM1A0) ;
				CLR_BIT(TCCR1A, COM1B1) ;
				CLR_BIT(TCCR1A, COM1B0) ;
			/*choose the normal mood*/
				CLR_BIT(TCCR1A, WGM11) ;
				CLR_BIT(TCCR1A, WGM10) ;
				CLR_BIT(TCCR1B, WGM12) ;
				CLR_BIT(TCCR1B, WGM13) ;
			/*enable TMR1 OVF interrupt*/
				SET_BIT(TIMSK, TOIE1) ;
		}
		else if(A_u8Mood==FAST_PWM)
		{
			/*set direction of PWM signal in normal not reversed*/
				SET_BIT(TCCR1A, COM1A1) ;
				CLR_BIT(TCCR1A, COM1A0) ;
				SET_BIT(TCCR1A, COM1B1) ;
				CLR_BIT(TCCR1A, COM1B0) ;
			/*choose the Fast PWM mood which i can define top value*/

			/*i choose her mood which i put top value in icr and compare value in ocr to activate pwm in 2 pins*/
				SET_BIT(TCCR1A, WGM11) ;
				CLR_BIT(TCCR1A, WGM10) ;
				SET_BIT(TCCR1B, WGM12) ;
				SET_BIT(TCCR1B, WGM13) ;
				TCCR1B = (TCCR1B & 0xF8) | Prescaler_1_8 ;

				MDIO_vSetPinDir(DIO_PORTD,DIO_PIN4,DIO_Output);
				MDIO_vSetPinDir(DIO_PORTD,DIO_PIN5,DIO_Output);
		}
		else if(A_u8Mood==COMPARE)
		{
			/*dont need it in CTC mode*/
				CLR_BIT(TCCR1A, COM1A1) ;
				CLR_BIT(TCCR1A, COM1A0) ;
				CLR_BIT(TCCR1A, COM1B1) ;
				CLR_BIT(TCCR1A, COM1B0) ;
			/*choose the CTC mood*/
				CLR_BIT(TCCR1A, WGM11) ;
				CLR_BIT(TCCR1A, WGM10) ;
				SET_BIT(TCCR1B, WGM12) ;
				SET_BIT(TCCR1B, WGM13) ;
			/*enable TMR1 CTC A and B interrupt*/
				SET_BIT(TIMSK, OCIE1A) ;
				SET_BIT(TIMSK, OCIE1B) ;
		}
		else if(A_u8Mood==ICU)
		{
			TCCR1A = 0;
			TCCR1B = 0b01000001;

			SET_BIT(TIMSK, TICIE1) ;
			SET_BIT(TIFR,5);
			TCCR1B = (TCCR1B & 0xF8) | Prescaler_1_64 ;

		}
	}
	if(A_u8TimerNO==Timer2)
	{
		if(A_u8Mood==NORMAL)
		{
			/*choose the normal mood*/
				CLR_BIT(TCCR2, WGM21) ;
				CLR_BIT(TCCR2, WGM20) ;
			/*enable TMR2 OVF interrupt*/
				SET_BIT(TIMSK, TOIE2) ;
		}
		else if(A_u8Mood==PWM)
		{
			/*choose the PWM phase correct mood*/
				CLR_BIT(TCCR2, WGM21) ;
				SET_BIT(TCCR2, WGM20) ;
				CLR_BIT(TCCR2, COM20) ;
				SET_BIT(TCCR2, COM21) ;
				MDIO_vSetPinDir(DIO_PORTD,DIO_PIN7,DIO_Output);
		}
		else if(A_u8Mood==FAST_PWM)
		{
			/*choose the Fast PWM mood*/
			SET_BIT(TCCR2, WGM21) ;
			SET_BIT(TCCR2, WGM20) ;
			CLR_BIT(TCCR2, COM20) ;
			SET_BIT(TCCR2, COM21) ;
			MDIO_vSetPinDir(DIO_PORTD,DIO_PIN7,DIO_Output);
		}
		else if(A_u8Mood==COMPARE)
		{
			/*choose the CTC mood*/
				SET_BIT(TCCR2, WGM21) ;
				CLR_BIT(TCCR2, WGM20) ;
			/*enable TMR2 CTC interrupt*/
				SET_BIT(TIMSK,OCIE2);
		}

	}


}
void MTMR_vInit(void)
{
#if TIMER0_ENABLE==ENABLE
#if TIMER0_MODE==NORMAL
/*choose the normal mood*/
	CLR_BIT(TCCR0, WGM01) ;
	CLR_BIT(TCCR0, WGM00) ;
/*dont need it in normal mode*/
	CLR_BIT(TCCR0, COM00) ;
	CLR_BIT(TCCR0, COM01) ;
/*enable TMR0 OVF interrupt*/
	SET_BIT(TIMSK, TOIE0) ;

#elif TIMER0_MODE==PWM
/*choose the PWM phase correct mood*/
	CLR_BIT(TCCR0, WGM01) ;
	SET_BIT(TCCR0, WGM00) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#endif
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN3,DIO_Output);
#elif TIMER0_MODE==FAST_PWM
/*choose the Fast PWM mood*/
	SET_BIT(TCCR0, WGM01) ;
	SET_BIT(TCCR0, WGM00) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR0, COM00) ;
	SET_BIT(TCCR0, COM01) ;
#endif
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN3,DIO_Output);
#elif TIMER0_MODE==CTC
/*choose the CTC mood*/
	SET_BIT(TCCR0, WGM01) ;
	CLR_BIT(TCCR0, WGM00) ;
/*dont need it in CTC mode*/
	CLR_BIT(TCCR0, COM00) ;
	CLR_BIT(TCCR0, COM01) ;
/*enable TMR0 CTC interrupt*/
	SET_BIT(TIMSK,OCIE0);

#endif
#endif

/********************************************************************************/

#if TIMER1_ENABLE==ENABLE
#if TIMER1_MODE==NORMAL
/*dont need it in normal mode*/
	CLR_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	CLR_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
/*choose the normal mood*/
	CLR_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	CLR_BIT(TCCR1B, WGM12) ;
	CLR_BIT(TCCR1B, WGM13) ;
/*enable TMR1 OVF interrupt*/
	SET_BIT(TIMSK, TOIE1) ;


#elif TIMER1_MODE==FAST_PWM
/*set direction of PWM signal in normal not reversed*/
	SET_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	SET_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
/*choose the Fast PWM mood which i can define top value*/

/*i choose her mood which i put top value in icr and compare value in ocr to activate pwm in 2 pins*/
	SET_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	SET_BIT(TCCR1B, WGM12) ;
	SET_BIT(TCCR1B, WGM13) ;

	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN4,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN5,DIO_Output);

#elif TIMER1_MODE==CTC
/*dont need it in CTC mode*/
	CLR_BIT(TCCR1A, COM1A1) ;
	CLR_BIT(TCCR1A, COM1A0) ;
	CLR_BIT(TCCR1A, COM1B1) ;
	CLR_BIT(TCCR1A, COM1B0) ;
/*choose the CTC mood*/
	CLR_BIT(TCCR1A, WGM11) ;
	CLR_BIT(TCCR1A, WGM10) ;
	SET_BIT(TCCR1B, WGM12) ;
	SET_BIT(TCCR1B, WGM13) ;
/*enable TMR1 CTC A and B interrupt*/
	SET_BIT(TIMSK, OCIE1A) ;
	SET_BIT(TIMSK, OCIE1B) ;
#elif TIMER1_MODE==ICU
	TCCR1A = 0;
	TCCR1B = 0b01000001;

#endif
#if ICU_ENABLE==ENABLE
	SET_BIT(TIMSK, TICIE1) ;
	SET_BIT(TIFR,5);

#endif
#endif
/********************************************************************************/

#if TIMER2_ENABLE==ENABLE
#if TIMER2_MODE==NORMAL

/*choose the normal mood*/
	CLR_BIT(TCCR2, WGM21) ;
	CLR_BIT(TCCR2, WGM20) ;
/*enable TMR2 OVF interrupt*/
	SET_BIT(TIMSK, TOIE2) ;

#elif TIMER2_MODE==PWM
/*choose the PWM phase correct mood*/
	CLR_BIT(TCCR2, WGM21) ;
	SET_BIT(TCCR2, WGM20) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR2, COM20) ;
	SET_BIT(TCCR2, COM21) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR2, COM20) ;
	SET_BIT(TCCR2, COM21) ;
#endif
	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN7,DIO_Output);
#elif TIMER2_MODE==FAST_PWM
	/*choose the Fast PWM mood*/
	SET_BIT(TCCR2, WGM21) ;
	SET_BIT(TCCR2, WGM20) ;
#if REVERSED_VALUE==ENABLE
	SET_BIT(TCCR2, COM20) ;
	SET_BIT(TCCR2, COM21) ;
#elif REVERSED_VALUE==DISABLE
	CLR_BIT(TCCR2, COM20) ;
	SET_BIT(TCCR2, COM21) ;
#endif
	MDIO_vSetPinDir(DIO_PORTD,DIO_PIN7,DIO_Output);
#elif TIMER2_MODE==CTC
/*choose the CTC mood*/
	SET_BIT(TCCR2, WGM21) ;
	CLR_BIT(TCCR2, WGM20) ;
/*enable TMR2 CTC interrupt*/
	SET_BIT(TIMSK,OCIE2);

#endif
#endif

}

void MTMR_vSetPreloadValue(u08 A_u8TimerNO,u16 A_u16Preload)
{
//TCNT is regester used in preload
	switch (A_u8TimerNO)
		{
		case Timer0:
			TCNT0 = A_u16Preload ;
			break;

		case Timer1:
			TCNT1 = A_u16Preload ;
			break;

		case Timer2:
			TCNT2 = A_u16Preload ;
			break;
		}
}

void MTMR_vSetCompareValue(u08 A_u8TimerNO,u16 A_u16CompareValue)
{
//OCR is regester used in set compare value in
	switch (A_u8TimerNO)
			{
			case Timer0:
				OCR0=A_u16CompareValue;
				break;

			case Timer1:
				OCR1A=A_u16CompareValue;
				OCR1B=A_u16CompareValue;
				break;

			case Timer2:
				OCR2=A_u16CompareValue;
				break;

			}
}

void MTMR_vSetTopValue(u16 A_u16TopValue)
{
//this function use with timer 1 only
	ICR1 = A_u16TopValue ;
}

void MTMR_vStartTimer(u08 A_u8TimerNO)
{
//set prescaler in regester tccr to activate timer prephral
	switch (A_u8TimerNO)
	{
	case Timer0:
		TCCR0 = (TCCR0 & 0xF8) | Prescaler_0 ;
		break;

	case Timer1:
		TCCR1B = (TCCR1B & 0xF8) | Prescaler_1 ;
		break;

	case Timer2:
		TCCR2 = (TCCR2 & 0xF8) | Prescaler_2 ;
		break;
	}

}

void MTMR_vEndTimer(u08 A_u8TimerNO)
{
//clear prescaler in regester tccr to dictivate timer prephral
	switch (A_u8TimerNO)
		{
		case Timer0:
			TCCR0 = (TCCR0 & 0xF8)  ;
			break;

		case Timer1:
			TCCR1B = (TCCR1B & 0xF8)  ;
			break;
		case Timer2:
			TCCR2 = (TCCR2 & 0xF8)  ;
			break;

		}
}

void MTMR_vDelayOVF(u08 A_u8TimerNO,u16 A_u16Time,void(*ptr)(void))
{
/* i tried to make timer 0&2 count to 250 micro second by calc:
 * preload value= ((2 power(regester size))-(250/1000000)*frecuency/prescaler)
 */
	switch (A_u8TimerNO)
	{
	case Timer0:
/* time measure by ms and timer prephral count to 250 micro so:
1ms=1000 micro
counter = 1000micro/250 micro
*/
		G_u16CounterOVF0[G_u8I0] = A_u16Time*4 ;
		TMR0_OVF_callback[G_u8I0] = ptr ;
		Pointer_0_deg++;
		TMR0_OVF_Pointer[G_u8I0]=Pointer_0_deg;
#if Prescaler_0==Prescaler_1
// prescaler 1 count less than 250 micro so i make i edited counter to make it count to 250 micro
		G_u16CounterOVF0[G_u8I0] = (G_u16CounterOVF0[G_u8I0]*125)/16 ;
#elif Prescaler_0==Prescaler_0_8
		MTMR_vSetPreloadValue(Timer0,6);
#elif Prescaler_0==Prescaler_0_64
		MTMR_vSetPreloadValue(Timer0,225);
#elif Prescaler_0==Prescaler_0_256
		MTMR_vSetPreloadValue(Timer0,248);
#elif Prescaler_0==PPrescaler_0_1024
		MTMR_vSetPreloadValue(Timer0,254);
#endif
		if(G_u8I0==5)
			G_u8I0=0;
		G_u8I0++;
		break;
/* i tried to make timer 1 count to 50 ms by calc:
 * preload value= ((2 power(regester size))-(50/1000)*frecuency/prescaler)
 */
	case Timer1:
		G_u16CounterOVF1[G_u8I1] = A_u16Time/50 ;
		TMR1_OVF_callback[G_u8I1] = ptr ;
#if Prescaler_1==Prescaler_1
// prescaler 1 count less than 50ms so i make i edited counter to make it count to 50ms
		G_u16CounterOVF1[G_u8I1] = (G_u16CounterOVF1[G_u8I1]*3125)/512 ;
#elif Prescaler_1==Prescaler_1_8
		MTMR_vSetPreloadValue(Timer1,15536);
#elif Prescaler_1=Prescaler_1_64
		MTMR_vSetPreloadValue(Timer1,59286);
#elif Prescaler_1==Prescaler_1_256
		MTMR_vSetPreloadValue(Timer1,63973);
#elif Prescaler_1==Prescaler_1_1024
		MTMR_vSetPreloadValue(Timer1,65145);
#endif
		G_u8I1++;
		break;
	case Timer2:
		G_u16CounterOVF2[G_u8I2] = A_u16Time*4 ;
		TMR2_OVF_callback[G_u8I2] = ptr ;
#if Prescaler_2==Prescaler_2_1
		G_u16CounterOVF2[G_u8I2] = (G_u16CounterOVF2[G_u8I2]*125)/16 ;
#elif Prescaler_2==Prescaler_2_8
		MTMR_vSetPreloadValue(Timer2,6);
#elif Prescaler_2==Prescaler_2_32
		MTMR_vSetPreloadValue(Timer2,193);
#elif Prescaler_2==Prescaler_2_64
		MTMR_vSetPreloadValue(Timer2,225);
#elif Prescaler_2==Prescaler_2_128
		MTMR_vSetPreloadValue(Timer2,240);
#elif Prescaler_2==Prescaler_2_256
		MTMR_vSetPreloadValue(Timer2,248);
#elif Prescaler_2==Prescaler_2_1024
		MTMR_vSetPreloadValue(Timer2,254);
#endif
		G_u8I2++;
		break;
	}
	MTMR_vStartTimer(A_u8TimerNO);





}

void MTMR_vSwapTasksPeriority(void(*ptr_1)(void),void(*ptr_2)(void))
{
	u08 TaskPeriority;
	for(u08 L_u8I1=0;L_u8I1<5;L_u8I1++)
	{
			if(TMR0_OVF_callback[L_u8I1] == ptr_1)
			{
				TaskPeriority=TMR0_OVF_Pointer[L_u8I1];
				for(u08 L_u8I2=0;L_u8I2<5;L_u8I2++)
				{
					if(TMR0_OVF_callback[L_u8I2] == ptr_2)
					{
						TMR0_OVF_Pointer[L_u8I1]=TMR0_OVF_Pointer[L_u8I2];
						TMR0_OVF_Pointer[L_u8I2]=TaskPeriority;
					}
				}

			}


	}
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{

	}
}

void MTMR_vDeleteTask(u08 A_u8TimerNO,void(*ptr)(void))
{
	if(A_u8TimerNO==Timer0)
	{
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{

			if(TMR0_OVF_callback[L_u8I] == ptr)
			{
				TMR0_OVF_callback[L_u8I]=NULL;
				TMR0_OVF_Pointer[L_u8I]=0;
				Pointer_0_deg--;

			}


	}
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if(TMR0_OVF_Pointer[L_u8I] != 0)
		{
			TMR0_OVF_Pointer[L_u8I]--;
		}

	}
	}
	else if(A_u8TimerNO==Timer1)
	{
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{

			if(TMR1_OVF_callback[L_u8I] == ptr)
			{
				TMR1_OVF_callback[L_u8I]=NULL;
				TMR1_OVF_Pointer[L_u8I]=0;
				Pointer_1_deg--;

			}


	}
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if(TMR1_OVF_Pointer[L_u8I] != 0)
		{
			TMR1_OVF_Pointer[L_u8I]--;
		}
	}
	}
	else if(A_u8TimerNO==Timer2)
	{
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{

			if(TMR2_OVF_callback[L_u8I] == ptr)
			{
				TMR2_OVF_callback[L_u8I]=NULL;
				TMR2_OVF_Pointer[L_u8I]=0;
				Pointer_2_deg--;

			}


	}
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if(TMR2_OVF_Pointer[L_u8I] != 0)
		{
			TMR2_OVF_Pointer[L_u8I]--;
		}

	}
	}


}

void MTMR_vCheckTasks(void(*ptr)(void))
{
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{

		if((TMR0_OVF_Pointer[L_u8I] == 1)&&(TMR0_OVF_callback[L_u8I] != NULL)&&(G_u8FlagOVF0[L_u8I]==1)&&(ptr!=TMR0_OVF_callback[L_u8I]))
		{
			TMR0_OVF_callback[L_u8I]();
			G_u8FlagOVF0[L_u8I]=0;

		}

	}

}

u16 MTMR_u16GetCaptureTime(void)
{

	return ICR1;

}

u08 MTMR_u8GetTimeValue(void)
{

	return TCNT0;

}

void MTMR_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger)
{
//this func used in icu to change trigger mood from rise to fall and from fall to rise
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
//timsk is regester used to control all timer praphral interrupt
	switch (A_u8TimerNO)
	{
	case Timer0:
		switch (A_u8InterruptType)
		{
		case OVF_INTERRUPT:
			SET_BIT(TIMSK, TOIE0) ;
			break;
		case CTC_INTERRUPT:
			SET_BIT(TIMSK, OCIE0) ;
			break;
		}
		break;

		case Timer1:
			switch (A_u8InterruptType)
			{
			case OVF_INTERRUPT:
				SET_BIT(TIMSK, TOIE1) ;
				break;
			case CTC_INTERRUPT:
				SET_BIT(TIMSK, OCIE1A) ;
				SET_BIT(TIMSK, OCIE1B) ;
				break;
			case ICU_INTERRUPT:
				SET_BIT(TIMSK, TICIE1) ;
				break;
			}
			break;

			case Timer2:
				switch (A_u8InterruptType)
				{
				case OVF_INTERRUPT:
					SET_BIT(TIMSK, TOIE2) ;
					break;
				case CTC_INTERRUPT:
					SET_BIT(TIMSK, OCIE2) ;
					break;
				}

				break;
	}
}

void MTMR_vDisableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType)
{
	switch (A_u8TimerNO)
	{
	case Timer0:
		switch (A_u8InterruptType)
		{
		case OVF_INTERRUPT:
			CLR_BIT(TIMSK, TOIE0) ;
			break;
		case CTC_INTERRUPT:
			CLR_BIT(TIMSK, OCIE0) ;
			break;
		}
		break;

		case Timer1:
			switch (A_u8InterruptType)
			{
			case OVF_INTERRUPT:
				CLR_BIT(TIMSK, TOIE1) ;
				break;
			case CTC_INTERRUPT:
				CLR_BIT(TIMSK, OCIE1A) ;
				CLR_BIT(TIMSK, OCIE1B) ;
				break;
			case ICU_INTERRUPT:
				CLR_BIT(TIMSK, TICIE1) ;
				break;
			}
			break;
			case Timer2:
				switch (A_u8InterruptType)
				{
				case OVF_INTERRUPT:
					CLR_BIT(TIMSK, TOIE2) ;
					break;
				case CTC_INTERRUPT:
					CLR_BIT(TIMSK, OCIE2) ;
					break;
				}
				break;
	}
}

void MTMR_vReadSignals(u16* A_u16TimeOn,u16* A_u16TimeAll)
{
	ICR1=0;
	MTMR_vEnableInterrupt(Timer1,ICU_INTERRUPT);
	//wait icu mission complete
	while(GS_u8ReadFlag==0);


	//to wait again when use this function next time
	GS_u8ReadFlag=0;
	//return time on and off values
	*A_u16TimeOn=GS_u16ont;
	*A_u16TimeAll=GS_u16pt;
}
//interrupts:
void __vector_11(void)  __attribute__((signal));//TMR_0_ovf
void __vector_11(void)
{
	static u32 LS_u32Counter = 0;


#if Prescaler_0==Prescaler_0_8
		MTMR_vSetPreloadValue(Timer0,6);
#elif Prescaler_0==Prescaler_0_64
		MTMR_vSetPreloadValue(Timer0,225);
#elif Prescaler_0==Prescaler_0_256
		MTMR_vSetPreloadValue(Timer0,248);
#elif Prescaler_0==Prescaler_0_1024
		MTMR_vSetPreloadValue(Timer0,254);
#endif
//searching in functions which saved in array of pointer to function if any of them should run
	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if((LS_u32Counter % G_u16CounterOVF0[L_u8I])==0)
		{
			if((TMR0_OVF_callback[L_u8I] != NULL)&&(G_u8FlagOVF0[L_u8I]==0))
			{
				G_u8FlagOVF0[L_u8I]=1;
				TMR0_OVF_callback[L_u8I]();
				G_u8FlagOVF0[L_u8I]=0;

			}

		}
	}


//make limit to timer 0 to 2w
		if(LS_u32Counter==4294964000)
		{
			LS_u32Counter=0;
		}
		LS_u32Counter++ ;

}
void __vector_9(void)  __attribute__((signal));//TMR_1_ovf
void __vector_9(void)
{
	static u16 LS_u16Counter = 0;
#if Prescaler_1==Prescaler_1_8
		MTMR_vSetPreloadValue(Timer1,15536);
#elif Prescaler_1==Prescaler_1_64
		MTMR_vSetPreloadValue(Timer1,59286);
#elif Prescaler_1==Prescaler_1_256
		MTMR_vSetPreloadValue(Timer1,63973);
#elif Prescaler_1==Prescaler_1_1024
		MTMR_vSetPreloadValue(Timer1,65145);
#endif
//searching in functions which saved in array of pointer to function if any of them should run

	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if((LS_u16Counter % G_u16CounterOVF1[L_u8I])==0)
		{
			if(TMR1_OVF_callback[L_u8I] != NULL)
			{
				TMR1_OVF_callback[L_u8I]();
			}

		}
	}


		MTMR_vSetPreloadValue(Timer0,6);

//make limit to timer 1 to 10ms
		if(LS_u16Counter==500)
		{
			LS_u16Counter=0;
		}
		LS_u16Counter++ ;

}
void __vector_5(void)  __attribute__((signal));//TMR_2_ovf
void __vector_5(void)
{
	static u32 LS_u32Counter = 0;
#if Prescaler_2==Prescaler_2_8
		MTMR_vSetPreloadValue(Timer2,6);
#elif Prescaler_2==Prescaler_2_32
		MTMR_vSetPreloadValue(Timer2,193);
#elif Prescaler_2==Prescaler_2_64
		MTMR_vSetPreloadValue(Timer2,225);
#elif Prescaler_2==Prescaler_2_128
		MTMR_vSetPreloadValue(Timer2,240);
#elif Prescaler_2==Prescaler_2_256
		MTMR_vSetPreloadValue(Timer2,248);
#elif Prescaler_2==Prescaler_2_1024
		MTMR_vSetPreloadValue(Timer2,254);
#endif
//searching in functions which saved in array of pointer to function if any of them should run

	for(u08 L_u8I=0;L_u8I<5;L_u8I++)
	{
		if((LS_u32Counter % G_u16CounterOVF2[L_u8I])==0)
		{
			if(TMR2_OVF_callback[L_u8I] != NULL)
			{
				TMR2_OVF_callback[L_u8I]();
			}

		}
	}

//make limit to timer 2 to 2w
		if(LS_u32Counter==4294964000)
		{
			LS_u32Counter=0;
		}
		LS_u32Counter++ ;

}

void __vector_6(void)  __attribute__((signal));//TMR_1_ICU
void __vector_6(void)
{

	static u08 LS_u8counter=0;
	static u16 timetriggered[3];
	LS_u8counter++;
	switch (LS_u8counter)
	{
	case 1:
		timetriggered[LS_u8counter-1]=MTMR_u16GetCaptureTime();
		MTMR_vSetIcuTrigger(ICU_Rising);
		break;
	case 2:
		timetriggered[LS_u8counter-1]=MTMR_u16GetCaptureTime();
		MTMR_vSetIcuTrigger(ICU_Falling);
		GS_u16pt=timetriggered[1]-timetriggered[0];
		break;
	case 3:
		timetriggered[LS_u8counter-1]=MTMR_u16GetCaptureTime();
		MTMR_vSetIcuTrigger(ICU_Rising);
		MTMR_vDisableInterrupt(Timer1,ICU_INTERRUPT);
		GS_u16ont=timetriggered[2]-timetriggered[1];
		LS_u8counter=0;
		GS_u8ReadFlag=1;

		break;
	}



}
