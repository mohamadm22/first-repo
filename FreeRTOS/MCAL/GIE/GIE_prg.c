/*
 * GIE_prg.c
 *
 *  Created on: Jul 6, 2022
 *      Author: user
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPE.h"

#include"GIE_prv.h"
#include"GIE_int.h"


void MGIE_vEnableGlobalInterrubt(void)
{
	SET_BIT(SREG,7);
}
void MGIE_vDisableGlobalInterrubt(void)
{
	CLR_BIT(SREG,7);
}

