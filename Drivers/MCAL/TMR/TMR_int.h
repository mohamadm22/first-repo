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


void MTMR_vInit(void);
void MTMR_vSetPreloadValue(u08 A_u8TimerNO,u16 A_u16Preload);
void MTMR_vStartTimer(u08 A_u8TimerNO);
void MTMR_vEndTimer(u08 A_u8TimerNO);
void MTMR_vDelayOVF(u16 A_u8Time,void(*ptr)(void));
void MTMR_vSetCompareValue(u08 A_u8TimerNO,u16 A_u16CompareValue);
void MTMR_vSetTopValue(u16 A_u16TopValue);
void MTMR_vDelayCTC(u08 A_u8Time,u08 L_u8CompareVaule,void(*ptr)(void));
u16 MTMR_u16GetCaptureTime(u08 A_u8TimerNO);
void MTMR_vSetIcuTrigger(ICU_Trigger_t A_xIcuTrigger);
void MTMR_vEnableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType);
void MTMR_vDisableInterrupt(u08 A_u8TimerNO,u08 A_u8InterruptType);

#define NORMAL      0
#define COMPARE     1
#define PWM         2
#define FAST_PWM    3

#define ENABLE      1
#define DISABLE     0

#define Prescaler_1        0b001
#define Prescaler_8        0b010
#define Prescaler_64       0b011
#define Prescaler_256      0b100
#define Prescaler_1024     0b101

#define Timer0     0
#define Timer1     1
#define Timer2     2


#endif /* MCAL_TMR_TMR_INT_H_ */
