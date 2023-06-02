/*
 * SSD_prg.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"

#include"../../MCAL/DIO/DIO_int.h"

#include"SSD_int.h"

#include"../SHFT/SHFT_int.h"


static const u08 CGS_u8SSD_Num[]={0b01011111,0b01111111,0b00001110,0b01111011,0b01011011,0b01001101,0b01011110,0b01110110,0b00001100,0b00111111};


void HSSD_vDisplayNum(u16 A_u8Num)
{
	Word&=0b1111110000000000;
	MDIO_vSetPinVal(Word,Shift1_Q6,DIO_HIGH);
	Word|=CGS_u8SSD_Num[A_u8Num/100];
	A_u8Num%=100;
	ShiftRegester();

	Word&=0b1111110000000000;
	MDIO_vSetPinVal(Word,Shift1_Q7,DIO_HIGH);
	Word|=CGS_u8SSD_Num[A_u8Num/10];
	A_u8Num%=10;
	ShiftRegester();

	Word&=0b1111110000000000;
	MDIO_vSetPinVal(Word,Shift2_Q0,DIO_HIGH);
	Word|=CGS_u8SSD_Num[A_u8Num];
	ShiftRegester();
}

