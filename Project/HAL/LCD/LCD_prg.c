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
#include"LCD_cfg.h"
#include"../../MCAL/TWI/TWI_int.h"
#include "../CLR/CLR_int.h"
#include<util/delay.h>

extern u08 Color;
extern u16 Weight;
extern u16 count;

u08 Bodies[5]={0};
u08 Indexes[5]={0};

u08 IR2Flag=0;
u08 IR3Flag=0;
u08 IR4Flag=0;


u08 WeightFlag=0;
u08 CSFlag=0;
u08 SelenderFlag=0;

u08 arrA[]={4, 4, 10, 10, 10, 17, 17, 0, 0, 0};
u08 arrR[]={15, 16, 16, 15, 5, 9, 17, 0, 0, 0};
u08 arrM[]={17, 27, 21, 21, 17, 1, 1, 0, 0, 0};
u08 arr_[]={14, 27, 0, 15, 0, 7, 12, 0, 0, 0};

void HLCD_vShowAnimation(void)
{
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(2,0);
	HLCD_vSendChar(0b10100101);

	HLCD_vSetCursorPosition(0,10);
	HLCD_vPrintString("Count:");
	HLCD_vPrintNumber(count);

	HLCD_vSetCursorPosition(1,10);
	HLCD_vPrintString("Weight:");
	HLCD_vPrintNumber(Weight);

	HLCD_vSetCursorPosition(2,10);
	HLCD_vPrintString("Color:");
	if(Color==RED)
		HLCD_vSendChar('R');
	else if(Color==GREEN)
		HLCD_vSendChar('G');
	else if(Color==BLUE)
		HLCD_vSendChar('B');


	HLCD_vSetCursorPosition(3,8);
	HLCD_vSendChar(1);

	HLCD_vSetCursorPosition(3,9);
	HLCD_vSendChar(2);

	HLCD_vSetCursorPosition(3,10);
	HLCD_vSendChar(3);

	HLCD_vSetCursorPosition(3,11);
	HLCD_vSendChar(4);

	for(u08 i=0;i<5;i++)
	{
		if(Bodies[i]==1)
		{
			HLCD_vSetCursorPosition(0,Indexes[i]);
			HLCD_vSendChar(0xff);
			HLCD_vSetCursorPosition(1,Indexes[i]);
			HLCD_vSendChar(0xff);
		}
	}
	if(WeightFlag==1)
	{
		HLCD_vSetCursorPosition(2,WeightIndex);
		HLCD_vSendChar('Z');
		WeightFlag=2;
	}
	else if(WeightFlag==2)
	{
		HLCD_vSetCursorPosition(2,WeightIndex);
		HLCD_vSendChar('z');
		WeightFlag=0;
	}
	if(IR2Flag==1)
	{
		HLCD_vSetCursorPosition(2,IR2Index);
		HLCD_vSendChar(0b10100101);
		IR2Flag=0;
	}

	if(CSFlag==1)
	{
		HLCD_vSetCursorPosition(2,CSIndex);
		HLCD_vSendChar('x');
		CSFlag=0;
	}

	if(IR3Flag==1)
	{
		HLCD_vSetCursorPosition(2,IR3Index);
		HLCD_vSendChar(0b10100101);
		IR3Flag=0;
	}

	if(SelenderFlag==1)
	{
		HLCD_vSetCursorPosition(2,SelenderIndex);
		HLCD_vSendChar(0b01011111);
		SelenderFlag=2;
	}
	else if(SelenderFlag==2)
	{
		HLCD_vSetCursorPosition(2,SelenderIndex);
		HLCD_vSendChar('T');
		SelenderFlag=0;
	}
	if(IR4Flag==1)
	{
		HLCD_vSetCursorPosition(2,IR4Index);
		HLCD_vSendChar(0b10100101);
		IR4Flag=0;
	}

}

void HLCD_vOpenSensorGraph(u08 Sensor)
{
	if(IR2Index==Sensor)
		IR2Flag=1;
	else if(IR3Index==Sensor)
		IR3Flag=1;
	else if(IR4Index==Sensor)
		IR4Flag=1;
	else if(WeightIndex==Sensor)
		WeightFlag=1;
	else if(CSIndex==Sensor)
		CSFlag=1;
	else if(SelenderIndex==Sensor)
		SelenderFlag=1;

}

void HLCD_vCloseSensorGraph(u08 Sensor)
{
	if(IR2Index==Sensor)
		IR2Flag=0;
	else if(IR3Index==Sensor)
		IR3Flag=0;
	else if(IR4Index==Sensor)
		IR4Flag=0;
	else if(WeightIndex==Sensor)
		WeightFlag=0;
	else if(CSIndex==Sensor)
		CSFlag=0;
	else if(SelenderIndex==Sensor)
		SelenderFlag=0;

}

void HLCD_vDeleteBody(u08 Index)
{
	for(u08 i=0;i<5;i++)
	{
		if(Indexes[i]==Index)
		{
			Bodies[i]=0;
		}
	}

}

void HLCD_vContinue(u08 index)
{
	for(u08 i=0;i<5;i++)
	{
	if(Indexes[i]==index)
		Indexes[i]++;
	if(Indexes[i]==10)
		Bodies[i]=0;
	}

}

void HLCD_vAddBody(void)
{
	for(u08 i=0;i<5;i++)
	{
		if(Bodies[i]==0)
		{
			Indexes[i]=0;
		}
	}

}

void HLCD_vPauseBody(u08 Index)
{
	for(u08 i=0;i<5;i++)
	{
		if(Indexes[i]==Index)
		{
			Indexes[i]--;
		}
	}
}

void HLCD_vClearDisplay(void)
{
	HLCD_vSendCommandIIC(1);
	_delay_ms(2);
}

void HLCD_vSendCommand(u08 A_u8Command)
{
	TWI_u08SendStartCondition();
	TWI_u08SendSlaveAddressRW(0x27,TWI_WRITE);
	TWI_u08SendByte(A_u8Command|0b00001100);
	_delay_ms(1);
	TWI_u08SendByte(A_u8Command|0b00001000);
	_delay_ms(1);
	TWI_u08SendStopCondition();

}
void HLCD_vSendCommandIIC(u08 A_u8Command)
{
	u08 Hcommand=A_u8Command&0b11110000;

	TWI_u08SendStartCondition();
	TWI_u08SendSlaveAddressRW(0x27,TWI_WRITE);
	TWI_u08SendByte(Hcommand|0b00001100);
	_delay_ms(1);
	TWI_u08SendByte(Hcommand|0b00001000);
	_delay_ms(1);
	Hcommand=A_u8Command&0b11110000;
	TWI_u08SendByte(Hcommand|0b00001100);
	_delay_ms(1);
	TWI_u08SendByte(Hcommand|0b00001000);
	_delay_ms(1);
	TWI_u08SendStopCondition();

}
void HLCD_vSendChar(u08 A_u8Char)
{
	u08 highnib=A_u8Char&0xf0;
	u08 lownib=(A_u8Char<<4)&0xf0;
    write4bits((highnib)|1);
	write4bits((lownib)|1);


}
void HLCD_vInit(void)
{
	TWI_vInit();
	u08 displayfunction = LCD_2LINE;
	 MDIO_vSetPinDir(DIO_PORTC,LCD_SCL,DIO_Output);
	 MDIO_vSetPinDir(DIO_PORTC,LCD_SDA,DIO_Output);

	_delay_ms(50);

	expanderWrite(0x08);

	_delay_ms(1000);

	write4bits(0x03 << 4);

	_delay_us(4500);

	write4bits(0x03 << 4);

	_delay_us(4500);

	write4bits(0x03 << 4);

	_delay_us(150);

	write4bits(0x02 << 4);

	command(LCD_FUNCTIONSET | displayfunction);

	u08 displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	command(LCD_DISPLAYCONTROL | displaycontrol);
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	_delay_ms(2);

	u08 displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	command(LCD_ENTRYMODESET | displaymode);

	command(LCD_RETURNHOME);  // set cursor position to zero
	_delay_ms(2);


	/*	HLCD_vSendCommand(0b00111000);
	_delay_ms(5);
	HLCD_vSendCommand(0b00111000);
	_delay_ms(1);
	HLCD_vSendCommand(0b00111000);
	HLCD_vSendCommand(0b00101000);
	HLCD_vSendCommand(0b00101000);
	HLCD_vSendCommand(0b10001000);
	HLCD_vSendCommand(0b00001000);
	HLCD_vSendCommand(0b10001000);
	HLCD_vSendCommand(0b00001000);
	HLCD_vSendCommand(0b00011000);
	HLCD_vSendCommand(0b00001000);
	HLCD_vSendCommand(0b11001000);*/

	HLCD_vSaveCustomChar(1,arrA);
	HLCD_vSaveCustomChar(2,arrR);
	HLCD_vSaveCustomChar(3,arrM);
	HLCD_vSaveCustomChar(4,arr_);
}
void HLCD_vPrintString(u08 A_u8String[]){
	for(u08 L_u8i=0;A_u8String[L_u8i]!='\0';L_u8i++){
		HLCD_vSendChar(A_u8String[L_u8i]);
	}
}
void HLCD_vPrintNumber(s32 A_s32Number){
	u08 L_u8counter=0;
	u32 L_u8power=1;
	s32 A_s32CopyNumber=A_s32Number;
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
	switch(A_u8linePos)
	{
	case 0:
		HLCD_vSendCommand((A_u8lineNum+0)|0x80);
		break;
	case 1:
		HLCD_vSendCommand((A_u8lineNum+0x40)|0x80);
		break;
	case 2:
		HLCD_vSendCommand((A_u8lineNum+0x14)|0x80);
		break;
	case 3:
		HLCD_vSendCommand((A_u8lineNum+0x54)|0x80);
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
void expanderWrite(u08 data)
{
	TWI_u08SendStartCondition();
	TWI_u08SendSlaveAddressRW(0x27,TWI_WRITE);
	TWI_u08SendByte((int)(data) | 0x08);
	TWI_u08SendStopCondition();
}
void write4bits(u08 value)
{
	expanderWrite(value);
	pulseEnable(value);
}
void send(u08 value, u08 mode)
{
	u08 highnib=value&0xf0;
	u08 lownib=(value<<4)&0xf0;
    write4bits((highnib)|mode);
	write4bits((lownib)|mode);
}

void command(u08 value)
{
	send(value, 0);
}

void pulseEnable(u08 data)
{
	expanderWrite(data | 0x04);	// En high
	_delay_us(1);		// enable pulse must be >450ns

	expanderWrite(data & ~(0x04));	// En low
	_delay_us(50);		// commands need > 37us to settle
}
