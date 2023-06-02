/*
 * IR_prg.c
 *
 *  Created on: May 19, 2023
 *      Author: user
 */

#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"IR_int.h"


u08 HIR_u8ReadIR(IR_t* Sensor)
{
	u08 Read=MDIO_u8GetPinVal(Sensor->Port,Sensor->Pin);
	switch (Read)
	{
	case IR_Exist:
		Read=1;
		break;
	case IR_NotExist:
		Read=0;
		break;

	}
	return Read;
}

