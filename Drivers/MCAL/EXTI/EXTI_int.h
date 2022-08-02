/*
 * EXTI_int.h
 *
 *  Created on: Jul 5, 2022
 *      Author: user
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define INT0_ENABLE   ENABLE
#define INT1_ENABLE   DISABLE
#define INT2_ENABLE   DISABLE


#define INT0_SENSE_CONTROL FALLING_EDGE
#define INT1_SENSE_CONTROL FALLING_EDGE
#define INT2_SENSE_CONTROL FALLING_EDGE

void MEXTI_vinit(void);

#endif /* MCAL_EXTI_EXTI_INT_H_ */
