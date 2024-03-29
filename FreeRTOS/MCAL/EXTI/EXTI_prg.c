/*
 * EXTI_int.c
 *
 *  Created on: Jul 5, 2022
 *      Author: user
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPE.h"

#include"EXTI_int.h"
#include"EXTI_prv.h"
#include"EXTI_cfg.h"




void MEXTI_vinit(void)
{
#if INT0_ENABLE==ENABLE
	SET_BIT(GICR,INT0);

#if INT0_SENSE_CONTROL==FALLING_EDGE
	SET_BIT(MCUCR,ISC11);
	CLR_BIT(MCUCR,ISC10);

#elif INT0_SENSE_CONTROL==RISING_EDGE
	SET_BIT(MCUCR,ISC11);
	SET_BIT(MCUCR,ISC10);
#elif INT0_SENSE_CONTROL==LOW_LEVEL
	CLR_BIT(MCUCR,ISC11);
	CLR_BIT(MCUCR,ISC10);
#elif INT0_SENSE_CONTROL==ANY_CHANGE
	CLR_BIT(MCUCR,ISC11);
	SET_BIT(MCUCR,ISC10);
#endif
#endif

#if INT1_ENABLE==ENABLE

#if INT1_SENSE_CONTROL==FALLING_EDGE
	SET_BIT(MCUCR,ISC01);
	CLR_BIT(MCUCR,ISC00);

#elif INT1_SENSE_CONTROL==RISING_EDGE
	SET_BIT(MCUCR,ISC01);
	SET_BIT(MCUCR,ISC00);
#elif INT1_SENSE_CONTROL==LOW_LEVEL
	CLR_BIT(MCUCR,ISC01);
	CLR_BIT(MCUCR,ISC00);
#elif INT1_SENSE_CONTROL==ANY_CHANGE
	CLR_BIT(MCUCR,ISC01);
	SET_BIT(MCUCR,ISC00);
#endif
	SET_BIT(GICR,INT1);
#endif

#if INT2_ENABLE==ENABLE

#if INT1_SENSE_CONTROL==FALLING_EDGE
	SET_BIT(MCUCSR,ISC2);

#elif INT1_SENSE_CONTROL==RISING_EDGE
	CLR_BIT(MCUCSR,ISC2);

#endif


	SET_BIT(GICR,INT2);
#endif

}
