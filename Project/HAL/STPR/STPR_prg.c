/*
 * STPR_prg.c
 *
 *  Created on: May 15, 2023
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include<util/delay.h>
#include"../../MCAL/DIO/DIO_int.h"
#include"STPR_int.h"
#include"STPR_cfg.h"
#include"../SHFT/SHFT_int.h"

void HSTPR_Init(void)
{
	MDIO_vSetPinDir(STPR_PORT,STPR_SleepPin,DIO_Output);
	MDIO_vSetPinDir(STPR_PORT,STPR_StepPin,DIO_Output);

	MDIO_vSetPinVal(STPR_PORT,STPR_SleepPin,DIO_LOW);
	MDIO_vSetPinVal(STPR_PORT,STPR_StepPin,DIO_LOW);

}

void HSTPR_Rotate(void)
{
	MDIO_vTogglePin(STPR_PORT,STPR_StepPin);

	ShiftRegester();
}
void HSTPR_Stop(void)
{
	MDIO_vSetPinVal(STPR_PORT,STPR_SleepPin,DIO_LOW);
}
void HSTPR_Walk(void)
{
	MDIO_vSetPinVal(STPR_PORT,STPR_SleepPin,DIO_HIGH);
}




