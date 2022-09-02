/*
 * main.c
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#include "../../LIB/STD_TYPE.h"
#include "../../MCAL/TMR/TMR_int.h"
#include "../../MCAL/GIE/GIE_int.h"
#include "../../HAL/LCD/LCD_int.h"

#include"DATE_int.h"
#include"DATE_cfg.h"

u08 G_u8Second=Start_Second;
u08 G_u8Minute=Start_Minute;
u08 G_u8Hour=Start_Hour;
u08 G_u8Day=Start_Day;
u08 G_u8Month=Start_Month;
u16 G_u16Year=Start_Year;
void ShowTime(void)
{
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,2);
	if(G_u8Hour<10)
	{
		HLCD_vPrintNumber(0);
		HLCD_vPrintNumber(G_u8Hour);
	}
	else
	{
		HLCD_vPrintNumber(G_u8Hour);
	}


	HLCD_vSendChar(':');
	if(G_u8Minute<10)
	{
		HLCD_vPrintNumber(0);
		HLCD_vPrintNumber(G_u8Minute);
	}
	else
	{
		HLCD_vPrintNumber(G_u8Minute);
	}
	HLCD_vSendChar(':');
	if(G_u8Second<10)
	{
		HLCD_vPrintNumber(0);
		HLCD_vPrintNumber(G_u8Second);
	}
	else
	{
		HLCD_vPrintNumber(G_u8Second);
	}
	HLCD_vSetCursorPosition(1,1);


	HLCD_vPrintNumber(G_u16Year);

	HLCD_vSendChar(':');
	if(G_u8Month<10)
	{
		HLCD_vPrintNumber(0);
		HLCD_vPrintNumber(G_u8Month);
	}
	else
	{
		HLCD_vPrintNumber(G_u8Month);
	}
	HLCD_vSendChar(':');
	if(G_u8Day<10)
	{
		HLCD_vPrintNumber(0);
		HLCD_vPrintNumber(G_u8Day);
	}
	else
	{
		HLCD_vPrintNumber(G_u8Day);
	}


	G_u8Second++;
	if(G_u8Second==60)
	{
		G_u8Second=0;
		G_u8Minute++;
		if(G_u8Minute==60)
		{
			G_u8Minute=0;
			G_u8Hour++;
			if(G_u8Hour==24)
			{
				G_u8Day++;

				if(G_u8Month==2)
				{
					if(G_u16Year%4==0)
					{
						if(G_u8Day==29)
						{
							G_u8Day=0;
							G_u8Month++;
						}

					}
					else
					{
						if(G_u8Day==28)
						{
							G_u8Day=0;
							G_u8Month++;
						}
					}
				}
				else if(G_u8Month==4||G_u8Month==6||G_u8Month==9||G_u8Month==11)
				{
					if(G_u8Day==30)
					{
						G_u8Day=0;
						G_u8Month++;
					}

				}
				else if(G_u8Month==1||G_u8Month==3||G_u8Month==5||G_u8Month==7||G_u8Month==8||G_u8Month==10||G_u8Month==12)
				{
					if(G_u8Day==31)
					{
						G_u8Day=0;
						G_u8Month++;
					}
				}
				if(G_u8Month==13)
				{
					G_u8Month=1;
					G_u16Year++;
				}
			}
		}
	}
}

void DisplayDate(void)
{
	MGIE_vEnableGlobalInterrubt();
	MTMR_vInit();
	MTMR_vDelayOVF(DateTimer,1000,ShowTime);

}

void TurnOffDisplayDate(void)
{

	MTMR_vDisableInterrupt(DateTimer,OVF_INTERRUPT);

}
