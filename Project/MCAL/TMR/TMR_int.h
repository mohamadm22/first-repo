/*
 * TMR_int.h
 *
 *  Created on: Jul 21, 2022
 *      Author: user
 */

#ifndef MCAL_TMR_TMR_INT_H_
#define MCAL_TMR_TMR_INT_H_

typedef enum
{
	ICU_Falling,
	ICU_Rising
}ICU_Trigger_t;

void MTMR_vChangeMood(u08 A_u8TimerNO,u08 A_u8Mood);
void MTMR_vInit(void);
void MTMR_vSetPreloadValue(u08 A_u8TimerNO,u16 A_u16Preload);
void MTMR_vStartTimer(u08 A_u8TimerNO);
void MTMR_vEndTimer(u08 A_u8TimerNO);
void MTMR_vDelayOVF(u08 A_u8TimerNO,u16 A_u16Time,void(*ptr)(void));
void MTMR_vSetCompareValue(u08 A_u8TimerNO,u16 A_u16CompareValue);
void MTMR_vSetTopValue(u16 A_u16TopValue);
u16 MTMR_u16GetCaptureTime(void);
void MTMR_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger);
void MTMR_vEnableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType);
void MTMR_vDisableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType);
u08 MTMR_u8GetTimeValue(void);
void MTMR_vReadSignals(u16* A_u8TimeOn,u16* A_u8TimeOff);
void MTMR_vCheckTasks(void(*ptr)(void));
void MTMR_vDeleteTask(u08 A_u8TimerNO,void(*ptr)(void));
void MTMR_vSwapTasksPeriority(void(*ptr_1)(void),void(*ptr_2)(void));

#define NORMAL      0
#define COMPARE     1
#define PWM         2
#define FAST_PWM    3
#define ICU         4

#define OVF_INTERRUPT     0
#define CTC_INTERRUPT     1
#define ICU_INTERRUPT     2

#define ENABLE      1
#define DISABLE     0

#define Prescaler_0_1        0b001
#define Prescaler_0_8        0b010
#define Prescaler_0_64       0b011
#define Prescaler_0_256      0b100
#define Prescaler_0_1024     0b101

#define Prescaler_1_1        0b001
#define Prescaler_1_8        0b010
#define Prescaler_1_64       0b011
#define Prescaler_1_256      0b100
#define Prescaler_1_1024     0b101

#define Prescaler_2_1        0b001
#define Prescaler_2_8        0b010
#define Prescaler_2_32       0b011
#define Prescaler_2_64       0b100
#define Prescaler_2_128      0b101
#define Prescaler_2_256      0b110
#define Prescaler_2_1024     0b111

#define Timer0     0
#define Timer1     1
#define Timer2     2


#endif /* MCAL_TMR_TMR_INT_H_ */
