/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/TMR/TMR_int.h"
#include "../MCAL/GIE/GIE_int.h"

void toggle(void)
{
	MDIO_vTogglePin(DIO_PORTA, DIO_PIN0);
}
void toggle2(void)
{
	MDIO_vTogglePin(DIO_PORTA, DIO_PIN1);
}
int main(void)
{
	MDIO_vSetPinDir(DIO_PORTD, DIO_PIN5, DIO_Output);

	MTMR_vInit();
	MTMR_vSetTopValue(2500);
	MTMR_vSetCompareValue(Timer1,195);
	MTMR_vStartTimer(Timer1);

	while(1)
	{



	}
}
