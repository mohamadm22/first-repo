/*
 * SRV_prg.c
 *
 *  Created on: Aug 11, 2022
 *      Author: user
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPE.h"

#include"../../MCAL/DIO/DIO_int.h"
#include"../../MCAL/TMR/TMR_int.h"
#include"../../MCAL/TMR/TMR_cfg.h"

#include"SRV_int.h"

void HSRV_vInit(void)
{
	MTMR_vInit();
#if Prescaler==Prescaler_8
	MTMR_vSetTopValue(20000);
#elif Prescaler==Prescaler_64
	MTMR_vSetTopValue(2500);
#endif
}

void HSRV_vSetAngle(u08 A_u8Angle)
{
	for(u08 L_u8I=0;L_u8I<15;L_u8I++)
	{
#if Prescaler==Prescaler_8
	MTMR_vSetCompareValue(Timer1,((A_u8Angle*10)+520));
#elif Prescaler==Prescaler_64
	MTMR_vSetCompareValue(Timer1,((A_u8Angle*225/180)+65));
#endif
	MTMR_vStartTimer(Timer1);
	}
}
