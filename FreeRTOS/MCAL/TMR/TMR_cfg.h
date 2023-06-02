/*
 * TMR__cfg.h
 *
 *  Created on: Jul 20, 2022
 *      Author: user
 */

#ifndef MCAL_TMR_TMR_CFG_H_
#define MCAL_TMR_TMR_CFG_H_

/* options: DISABLE/ENABLE */

#define TIMER0_ENABLE   DISABLE
#define TIMER1_ENABLE   ENABLE
#define TIMER2_ENABLE   DISABLE

#define ICU_ENABLE      DISABLE
#define REVERSED_VALUE  DISABLE

/* options: NORMAL/COMPARE/PWM/FAST_PWM */
#define TIMER0_MODE NORMAL
#define TIMER1_MODE FAST_PWM
#define TIMER2_MODE NORMAL

/* options: Prescaler_1/Prescaler_8/Prescaler_64/Prescaler_256/Prescaler_1024 */
#define Prescaler Prescaler_8


/* options: Prescaler_1/Prescaler_8/Prescaler_32/Prescaler_64/Prescaler_128/Prescaler_256/Prescaler_1024 */
#define Prescaler_2 Prescaler_2_64


#endif /* MCAL_TMR_TMR_CFG_H_ */
