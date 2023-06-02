/*
 * TMR__cfg.h
 *
 *  Created on: Jul 20, 2022
 *      Author: user
 */

#ifndef MCAL_TMR_TMR_CFG_H_
#define MCAL_TMR_TMR_CFG_H_

/* options: DISABLE/ENABLE */

#define TIMER0_ENABLE   ENABLE
#define TIMER1_ENABLE   ENABLE
#define TIMER2_ENABLE   ENABLE

#define ICU_ENABLE      ENABLE
#define REVERSED_VALUE  DISABLE

/* options: NORMAL/COMPARE/PWM/FAST_PWM/ICU */
#define TIMER0_MODE NORMAL
#define TIMER1_MODE PWM
#define TIMER2_MODE NORMAL

/* options: Prescaler_1/Prescaler_8/Prescaler_64/Prescaler_256/Prescaler_1024 */
#define Prescaler_0 Prescaler_0_8

#define Prescaler_1 Prescaler_1_64


/* options: Prescaler_1/Prescaler_8/Prescaler_32/Prescaler_64/Prescaler_128/Prescaler_256/Prescaler_1024 */
#define Prescaler_2 Prescaler_2_8


#endif /* MCAL_TMR_TMR_CFG_H_ */
