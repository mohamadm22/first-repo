/*
 * CLR_prg.c
 *
 *  Created on: May 20, 2023
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TMR/TMR_int.h"
#include "../../MCAL/GIE/GIE_int.h"
#include <util/delay.h>
#include "CLR_cfg.h"
#include "CLR_int.h"
#include"../SHFT/SHFT_int.h"


void HCLR_vInit(void)
{

	MTMR_vInit();

	MDIO_vSetPinDir(OUT_Port,OUT_Pin,DIO_Input);
	MDIO_vSetPinDir(CLR_Port,S0_Pin,DIO_Output);
	MDIO_vSetPinDir(CLR_Port,S1_Pin,DIO_Output);
	MDIO_vSetPinDir(CLR_Port,S2_Pin,DIO_Output);
	MDIO_vSetPinDir(CLR_Port,S3_Pin,DIO_Output);

	MDIO_vSetPinVal(CLR_Port,S0_Pin,DIO_HIGH);
	MDIO_vSetPinVal(CLR_Port,S1_Pin,DIO_LOW);

	MGIE_vEnableGlobalInterrubt();

}

u08 HCLR_u8ScanColor(void)
{
	static u16 redFrequency;
	static u16 greenFrequency;
	static u16 blueFrequency;
	static u08 x;
	static u08 Read;

	_delay_ms(100);

	// Setting RED (R) filtered photodiodes to be read
	MDIO_vSetPinVal(CLR_Port,S2_Pin,DIO_LOW);
	MDIO_vSetPinVal(CLR_Port,S3_Pin,DIO_LOW);

	// Reading the output frequency
	MTMR_vReadSignals(&redFrequency,&x);

	_delay_ms(100);

	// Setting GREEN (G) filtered photodiodes to be read
	MDIO_vSetPinVal(CLR_Port,S2_Pin,DIO_HIGH);
	MDIO_vSetPinVal(CLR_Port,S3_Pin,DIO_HIGH);

	// Reading the output frequency
	MTMR_vReadSignals(&greenFrequency,&x);

	_delay_ms(100);

	// Setting BLUE (B) filtered photodiodes to be read
	MDIO_vSetPinVal(CLR_Port,S2_Pin,DIO_LOW);
	MDIO_vSetPinVal(CLR_Port,S3_Pin,DIO_HIGH);

	// Reading the output frequency
	MTMR_vReadSignals(&blueFrequency,&x);


	if((redFrequency<greenFrequency)&&(redFrequency<blueFrequency))
	{
		Read = RED;
	}
	else if((greenFrequency<redFrequency)&&(greenFrequency<blueFrequency))
	{
		Read = GREEN;

	}
	else if((blueFrequency<redFrequency)&&(blueFrequency<greenFrequency))
	{
		Read = BLUE;
	}
	else
		HCLR_u8ScanColor();
	return Read;


}
