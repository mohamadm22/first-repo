/*
 * KPD_prg.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"

#include"../../MCAL/DIO/DIO_int.h"

#include"KPD_int.h"


#include"util/delay.h"


void HKPD_init(void){
	MDIO_vSetPortDir(KPD_PORT,0x0f);
	MDIO_vSetPortVal(KPD_PORT,0xff);
}

u08 HKPD_u8GetPressedKey(void)
{
	u08 L_u8Pressed_key = 0 ;
	u08 L_u8Pressed_key_1 = 0 ;
		for (u08 cols = 0 ; cols < 4 ; cols ++)
		{
			MDIO_vSetPinVal(KPD_PORT,cols,DIO_LOW);

			for (u08 rows = 0 ; rows<4;rows++)
			{
				if (MDIO_u8GetPinVal(KPD_PORT,rows+4)==0)
				{
					L_u8Pressed_key = rows + (cols * 4) + 1 ;
				}
				while (MDIO_u8GetPinVal(KPD_PORT,rows+4)==0)
				{
					MDIO_vSetPinVal(KPD_PORT,cols,DIO_HIGH);
					for (u08 col = 0 ; col < 4 ; col ++)
					{

						MDIO_vSetPinVal(KPD_PORT,col,DIO_LOW);

						for (u08 row = 0 ; row<4;row++)
						{


							if (MDIO_u8GetPinVal(KPD_PORT,row+4)==0&&(col!=cols)&&(rows!=row))
							{
								L_u8Pressed_key_1 = 1 ;
							}
							while (MDIO_u8GetPinVal(KPD_PORT,row+4)==0&&(col!=cols)&&(rows!=row));
							_delay_ms(10);
						}
						MDIO_vSetPinVal(KPD_PORT,col,DIO_HIGH);
					}
					MDIO_vSetPinVal(KPD_PORT,cols,DIO_LOW);
				}

				_delay_ms(10);
			}
			MDIO_vSetPinVal(KPD_PORT,cols,DIO_HIGH);
		}
		if(L_u8Pressed_key_1!=0)
		{
			L_u8Pressed_key=22;
		}

	return L_u8Pressed_key ;
}
