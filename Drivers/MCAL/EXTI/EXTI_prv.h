/*
 * EXTI_prv.h
 *
 *  Created on: Jul 18, 2022
 *      Author: user
 */

#ifndef MCAL_EXTI_EXTI_PRV_H_
#define MCAL_EXTI_EXTI_PRV_H_


#define MCUCR  *((volatile u08*)(0x55))
#define GICR   *((volatile u08*)(0x5B))


#define INT0   6
#define INT1   7
#define INT2   5

#define ENABLE    1
#define DISABLE   0


#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define ISC2    6


#define FALLING_EDGE   0
#define RISING_EDGE    1
#define LOW_LEVEL      2
#define ANY_CHANGE     3



#endif /* MCAL_EXTI_EXTI_PRV_H_ */
