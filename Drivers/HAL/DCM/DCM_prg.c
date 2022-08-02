/*
 * DCM_prg.c
 *
 *  Created on: May 31, 2022
 *      Author: mazen
 */


#include "../../LIB/STD_TYPE.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "DCM_int.h"
#include "DCM_cfg.h"


void HDCM_vInit(void)
{
	MDIO_vSetPinDir(DCM_PORT,DCM_PIN1, DIO_Output );
	MDIO_vSetPinDir(DCM_PORT,DCM_PIN2, DIO_Output );
	/* TODO: Setup Speed control Pin */

}

void HDCM_vRotateCW(void)
{
	/* TODO: implement speed as input */

	MDIO_vSetPinVal(DCM_PORT, DCM_PIN1, DIO_HIGH);
	MDIO_vSetPinVal(DCM_PORT, DCM_PIN2, DIO_LOW);
}

void HDCM_vRotateCCW(void)
{
	/* TODO: implement speed as input */
	MDIO_vSetPinVal(DCM_PORT, DCM_PIN1, DIO_LOW);
	MDIO_vSetPinVal(DCM_PORT, DCM_PIN2, DIO_HIGH);

}

void HDCM_vStop(void)
{
	MDIO_vSetPinVal(DCM_PORT, DCM_PIN1, DIO_LOW);
	MDIO_vSetPinVal(DCM_PORT, DCM_PIN2, DIO_LOW);
}



void HDCM_xRotateCW(DCM_t*  xMotor )
{
	/* TODO: implement speed as input */
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin1, DIO_HIGH);
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin2, DIO_LOW);
}

void HDCM_xRotateCCW(DCM_t* xMotor)
{
	/* TODO: implement speed as input */
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin1, DIO_LOW);
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin2, DIO_HIGH);
}

void HDCM_xStop(DCM_t* xMotor)
{
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin1, DIO_LOW);
	MDIO_vSetPinVal(xMotor->Port, xMotor->Pin2, DIO_LOW);
}

DCM_t HDCM_xInit(u08 A_u8Port,
   				u08 A_u8Pin1,
				u08 A_u8Pin2)
{
	DCM_t L_xNewMotor ;

	L_xNewMotor.Port = A_u8Port;
	L_xNewMotor.Pin1 = A_u8Pin1;
	L_xNewMotor.Pin2 = A_u8Pin2;

	return L_xNewMotor;
}


















