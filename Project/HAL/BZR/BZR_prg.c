/*
 * BZR_prg.c
 *
 *  Created on: May 22, 2023
 *      Author: user
 */

#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include<util/delay.h>

#include"BZR_int.h"
#include"BZR_cfg.h"

void HBZR_vInit(void)
{
	MDIO_vSetPinDir(BZR_Port,BZR_Pin,DIO_Output);
	MDIO_vSetPinVal(BZR_Port,BZR_Pin,DIO_LOW);

}
void HBZR_vFinish(void)
{
	MDIO_vSetPinVal(BZR_Port,BZR_Pin,DIO_HIGH);
	_delay_ms(1000);
	MDIO_vSetPinVal(BZR_Port,BZR_Pin,DIO_LOW);

}
void HBZR_vError(void)
{
	MDIO_vTogglePin(BZR_Port,BZR_Pin);

}
