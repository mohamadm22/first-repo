/*
 * LCD_prg.c
 *
 *  Created on: May 20, 2022
 *      Author: user
 */

#include"../../LIB/STD_TYPE.h"
#include"../../LIB/BIT_MATH.h"

#include"../../MCAL/DIO/DIO_int.h"

#include"LCD_int.h"


#include"util/delay.h"




void HLCD_vSendCommand(u08 A_u8Command)
{
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_RS_PIN,DIO_LOW);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_RW_PIN,DIO_LOW);
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Command);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_EN_PIN,DIO_LOW);
	_delay_ms(1);


}
void HLCD_vSendChar(u08 A_u8Char)
{
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_RS_PIN,DIO_HIGH);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_RW_PIN,DIO_LOW);
	MDIO_vSetPortVal(LCD_DATA_PORT,A_u8Char);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT,LCD_EN_PIN,DIO_LOW);
	_delay_ms(1);
}
void HLCD_vInit(void)
{
	MDIO_vSetPortDir(LCD_DATA_PORT,0xff);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_RS_PIN,DIO_Output);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_RW_PIN,DIO_Output);
	MDIO_vSetPinDir(LCD_CTRL_PORT,LCD_EN_PIN,DIO_Output);

	_delay_ms(50);

	HLCD_vSendCommand(0b00111000);
	_delay_ms(1);
	HLCD_vSendCommand(0b00001100);
	_delay_ms(1);
	HLCD_vSendCommand(0b00000001);
	_delay_ms(3);
	HLCD_vSendCommand(0b00000110);
	_delay_ms(1);
}
void HLCD_vPrintString(u08 A_u8String[]){
	for(u08 L_u8i=0;A_u8String[L_u8i]!='\0';L_u8i++){
		HLCD_vSendChar(A_u8String[L_u8i]);
	}
}
void HLCD_vPrintNumber(s08 A_s32Number){
	u08 L_u8counter=0;
	u08 L_u8power=1;
	s08 A_s32CopyNumber=A_s32Number;
	while((A_s32CopyNumber/10)!=0)
		{
			L_u8counter++;
			A_s32CopyNumber/=10;
		}
	for(;L_u8counter>0;L_u8counter--)
	{
		L_u8power*=10;
	}
	if((A_s32Number/10)>=0&&(A_s32Number%10)>=0)
	{
		while(L_u8power>1)
		{
			if((A_s32Number>=(L_u8power)))
			{
			HLCD_vSendChar(48+(A_s32Number/(L_u8power)));}
			else
				HLCD_vSendChar(48+0);
			A_s32Number-=(A_s32Number/(L_u8power))*(L_u8power);
			L_u8power/=10;

		}
		HLCD_vSendChar(48+(A_s32Number%10));

	}

	else
	{
		HLCD_vSendChar('-');
		A_s32Number*=-1;
		while(L_u8power!=0)
		{
			if((A_s32Number>=(L_u8power)))
						{
						HLCD_vSendChar(48+(A_s32Number/(L_u8power)));}
						else
							HLCD_vSendChar(48+0);
			A_s32Number-=(A_s32Number/(L_u8power))*(L_u8power);
			L_u8power/=10;

		}
		HLCD_vSendChar(48+(A_s32Number%10));


	}
}
void HLCD_vSetCursorPosition(u08 A_u8linePos,u08 A_u8lineNum)
{
	switch(A_u8lineNum)
	{
	case 0:
		HLCD_vSendCommand(0x80+A_u8linePos+(A_u8lineNum+0));
		break;
	case 1:
		HLCD_vSendCommand(0x80+A_u8linePos+(A_u8lineNum+64));
		break;



	}
}
void HLCD_vSaveCustomChar(u08 A_u8Cgram_index,u08 A_u8CharData[])
{
	HLCD_vSendCommand(0b01000000+(A_u8Cgram_index*8));
	for(u08 L_u8Idx=0;L_u8Idx<8;L_u8Idx++)
	{
		HLCD_vSendChar(A_u8CharData[L_u8Idx]);
	}
	HLCD_vSendCommand(0x80);
}
