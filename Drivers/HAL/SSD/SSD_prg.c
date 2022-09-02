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
#include"SSD_cfg.h"




static const u08 CGS_u8SSD_Num[]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,0b10110110,0b10111110,0b11100000,0b11111110,0b11110110};

void HSSD_init(void)
{
	MDIO_vSetPortDir(SSD_PORT_1,0xff);
	MDIO_vSetPortDir(SSD_PORT_2,0xff);
}

void HSSD_vDisplayNum(u08 A_u8Num)
{
	if(A_u8Num<10)
	{
#if SSD_TYPE==COM_CATHODE
		MDIO_vSetPortVal(SSD_PORT_1,CGS_u8SSD_Num[A_u8Num]);
#elif SSD_TYPE==COM_ANODE
		MDIO_vSetPortVal(SSD_PORT_2,~CGS_u8SSD_Num[A_u8Num]);
#endif
	}
	else if(A_u8Num>=10&&A_u8Num<17)
	{
#if SSD_TYPE==COM_CATHODE
		MDIO_vSetPortVal(SSD_PORT_1,CGS_u8SSD_Num[A_u8Num-10]);
		MDIO_vSetPortVal(SSD_PORT_2,CGS_u8SSD_Num[1]);
#elif SSD_TYPE==COM_ANODE
		MDIO_vSetPortVal(SSD_PORT_1,~CGS_u8SSD_Num[A_u8Num-10]);
		MDIO_vSetPortVal(SSD_PORT_2,~CGS_u8SSD_Num[1]);
#endif
	}
}

void HSSD_vTurnOff(void)
{
#if SSD_TYPE==COM_CATHODE
	MDIO_vSetPortVal(SSD_PORT_1,0);
#elif SSD_TYPE==COM_ANODE
	MDIO_vSetPortVal(SSD_PORT_1,0xff);
#endif
}
