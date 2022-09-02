/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#include "../../LIB/STD_TYPE.h"
#include"../../HAL/LCD/LCD_int.h"
#include"../../HAL/KPD/KPD_int.h"

u08 arr[5];
u08 arr2[5];

void CALC_vInit(void)
{
	HKPD_init();
	HLCD_vInit();
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,0);
}
void CALC_vCalculate(void)
{
	static u08 i=0;
	static u08 z=5;
	static u08 pressedKey;

	pressedKey=HKPD_u8GetPressedKey();
	if(pressedKey<='9'&&pressedKey>='0')
	{
		HLCD_vSendChar(pressedKey);
		arr[i]=(arr[i]*10)+(pressedKey-48);

	}
	if(pressedKey=='/'||pressedKey=='*'||pressedKey=='+'||pressedKey=='-'||pressedKey=='%')
	{
		HLCD_vSendChar(pressedKey);
		arr2[i]=pressedKey;

		i++;

	}
	if(pressedKey=='=')
	{
		HLCD_vSetCursorPosition(1,0);
		HLCD_vSendChar(pressedKey);
		for(i=0;i<z;i++){
			if(arr2[i]=='*')
			{
				arr[i]=arr[i]*arr[i+1];
				for(u08 x=i+1;x<z;x++)
				{
					arr[x]=arr[x+1];
					arr2[x-1]=arr2[x];
				}
				i--;
				z--;

			}
			else if(arr2[i]=='/')
			{
				arr[i]=arr[i]/arr[i+1];
				for(u08 x=i;x<z;x++)
				{
					arr[x]=arr[x+1];

				}
				i--;
				z--;

			}
			else if(arr2[i]=='%')
			{
				arr[i]=arr[i]%arr[i+1];
				for(u08 x=i+1;x<z;x++)
				{
					arr[x]=arr[x+1];

				}
				i--;
				z--;

			}
		}
		for(i=0;i<z;i++){
			if(arr2[i]=='+')
			{
				arr[i]=arr[i]+arr[i+1];
				for(u08 x=i+1;x<z;x++)
				{
					arr[x]=arr[x+1];

				}
				i--;
				z--;
			}
			else if(arr2[i]=='-')
			{
				arr[i]=arr[i]-arr[i+1];
				for(u08 x=i+1;x<z;x++)
				{
					arr[x]=arr[x+1];

				}
				i--;
				z--;
			}
		}
		HLCD_vPrintNumber(arr[0]);
	}



}
