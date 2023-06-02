/*
 * SYS_prg.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: moham
 */
#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"SYS_int.h"

void HSYS_vInit(void)
{
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN3,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN4,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN5,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN6,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN7,DIO_Output);

	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN3,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN5,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN6,DIO_Output);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN7,DIO_Output);



	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN3,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN4,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN5,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN6,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTA,DIO_PIN7,DIO_LOW);

	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN3,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN5,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN6,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTC,DIO_PIN7,DIO_LOW);
}
void HSYS_vTurnON(SYS_Combonant_t Combonant)
{
	if(Combonant==Selender)
	MDIO_vSetPinVal(DIO_PORTA,DIO_PIN3,DIO_HIGH);
	else if(Combonant==IR_2)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN4,DIO_HIGH);
	else if(Combonant==IR_3)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN5,DIO_HIGH);
	else if(Combonant==IR_4)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN6,DIO_HIGH);
	else if(Combonant==ColorSensor)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN7,DIO_HIGH);
	else if(Combonant==Servo)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	else if(Combonant==LC)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN4,DIO_HIGH);
	else if(Combonant==ELSE1)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN5,DIO_HIGH);
	else if(Combonant==ELSE2)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN6,DIO_HIGH);
	else if(Combonant==ELSE3)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN7,DIO_HIGH);

}
void HSYS_vTurnOFF(SYS_Combonant_t Combonant)
{
	if(Combonant==IR_2)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN3,DIO_LOW);
	else if(Combonant==IR_3)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN4,DIO_LOW);
	else if(Combonant==IR_4)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN5,DIO_LOW);
	else if(Combonant==ColorSensor)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN6,DIO_LOW);
	else if(Combonant==Servo)
		MDIO_vSetPinVal(DIO_PORTA,DIO_PIN7,DIO_LOW);
	else if(Combonant==LC)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN3,DIO_LOW);
	else if(Combonant==Selender)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN4,DIO_LOW);
	else if(Combonant==ELSE1)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN5,DIO_LOW);
	else if(Combonant==ELSE2)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN6,DIO_LOW);
	else if(Combonant==ELSE3)
		MDIO_vSetPinVal(DIO_PORTC,DIO_PIN7,DIO_LOW);

}
