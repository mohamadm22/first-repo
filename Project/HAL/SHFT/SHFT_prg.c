/*
 * (Word<<(ShFT_prg.c
 *
 *  Created on: May 19, 2023
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"SHFT_int.h"
#include"SHFT_cfg.h"
#include"../../MCAL/DIO/DIO_int.h"

void HSHFT_vInit(void)
{
	MDIO_vSetPinDir(LatchPort,LatchPin,DIO_Output);
	MDIO_vSetPinDir(DataPort,DataPin,DIO_Output);
	MDIO_vSetPinDir(ShiftPort,ShiftPin,DIO_Output);


	MDIO_vSetPinVal(LatchPort,LatchPin,DIO_LOW);
	MDIO_vSetPinVal(DataPort,DataPin,DIO_LOW);
	MDIO_vSetPinVal(ShiftPort,ShiftPin,DIO_LOW);

}

void ShiftRegester(void)
{
	u16 word=Word;
	MDIO_vSetPinVal(LatchPort,LatchPin,DIO_LOW);
	for(u08 i=0;i<16;i++)
	{

		MDIO_vSetPinVal(DataPort,DataPin,(word&1));
		word>>=1;
		MDIO_vSetPinVal(ShiftPort,ShiftPin,DIO_HIGH);
		MDIO_vSetPinVal(ShiftPort,ShiftPin,DIO_LOW);

	}

	MDIO_vSetPinVal(LatchPort,LatchPin,DIO_HIGH);


}
