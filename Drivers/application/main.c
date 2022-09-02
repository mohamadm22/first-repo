/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#include "../LIB/STD_TYPE.h"
#include"SNAKE/SNAKE_int.h"
#include"../HAL/KPD/KPD_int.h"

u08 arr1[]={
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00001010,
		0b00011111,
		0b00001110,
		0b00000100,
};
u08 arr2[]={
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000100,
		0b00001110,
		0b00011111,
		0b00001010,
};

int main(void)
{
	HLCD_vInit();
	/*SNAKE_vInit();
	HKPD_init();*/
	while(1)
	{
		HLCD_vSetCursorPosition(0,0);
		HLCD_vClearDisplay();
		HLCD_vSaveCustomChar(1,arr1);
		HLCD_vSendChar(1);
		HLCD_vSaveCustomChar(1,arr2);
		HLCD_vSetCursorPosition(0,1);
		HLCD_vSendChar(1);


		/*if(HKPD_u8GetPressedKey()==2)
			SNAKE_vMoveUp();
		else if(HKPD_u8GetPressedKey()==5)
			SNAKE_vMoveUp();
		else if(HKPD_u8GetPressedKey()==7)
			SNAKE_vMoveUp();
		else if(HKPD_u8GetPressedKey()==10)
			SNAKE_vMoveUp();
		SNAKE_vGetLong();
		SNAKE_vGameOver();*/


	}
}
