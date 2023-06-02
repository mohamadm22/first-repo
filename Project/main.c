/*
 * main.c
 *
 *  Created on: May 10, 2023
 *      Author: user
 */

#include"LIB/STD_TYPE.h"
#include"LIB/BIT_MATH.h"
#include<util/delay.h>
#include "MCAL/DIO/DIO_int.h"
#include "MCAL/TMR/TMR_int.h"
#include "MCAL/TWI/TWI_int.h"
#include "MCAL/GIE/GIE_int.h"

#include "HAL/BZR/BZR_int.h"
#include "HAL/CLR/CLR_int.h"
#include "HAL/IR/IR_int.h"
#include "HAL/KPD/KPD_int.h"
#include "HAL/LDCL/LDCL_int.h"
#include "HAL/SHFT/SHFT_int.h"
#include "HAL/SRV/SRV_int.h"
#include "HAL/SSD/SSD_int.h"
#include "HAL/STPR/STPR_int.h"
#include "HAL/SYS/SYS_int.h"
#include"HAL/LCD/LCD_int.h"

#define C2S    1000
#define C2B    1000
#define W2C    1000
#define W2S    2000

#define MotorRefreshTime    1
#define SSDRefreshTime      20
#define IR2S                100
#define SelenderBack        100
#define IR2C                100

#define ERRORtime           2000
u08 ErrorFlag=0;
u08 container;
u16 count=0;
u16 IMGcount=0;
u08 Color=0;
u16 Weight=0;
u16 counter=0;

u08 ScanColor_Flag=0;
u08 OpenSelender_Flag=0;
u08 FillBox_Flag=0;

IR_t IR1_t={DIO_PORTD,DIO_PIN1};
IR_t IR2_t={DIO_PORTD,DIO_PIN2};
IR_t IR3_t={DIO_PORTD,DIO_PIN3};
IR_t IR4_t={DIO_PORTD,DIO_PIN4};

static u32 i2_Selender=0;
static u32 i2_CS=0;


void interface(void);
void OpenSelender(void);
void SSD_DESPLAY(void);
void ScanColor(void);
void FillBox(void);
void WeightBody(void);

void main(void){


	HCLR_vInit();
	HBZR_vInit();
	HKPD_init();
	HLCD_vInit();
	HLDCL_vInit();
	HSRV_vInit();
	HSYS_vInit();
	HSTPR_Init();
	HSHFT_vInit();

	interface();

	MTMR_vInit();

	MGIE_vEnableGlobalInterrubt();

	MTMR_vDelayOVF(Timer2,SSDRefreshTime,SSD_DESPLAY);
	MTMR_vDelayOVF(Timer2,MotorRefreshTime,HSTPR_Rotate);
	MTMR_vStartTimer(Timer2);
	MTMR_vStartTimer(Timer0);
	while(1)
	{
		MTMR_vCheckTasks(WeightBody);
		if(HIR_u8ReadIR(&IR1_t)&&(IMGcount<count))
		{
			WeightBody();
		}
	}
}

void WeightBody(void)
{
	u08 Weight_B;
	IMGcount++;
	HLCD_vAddBody();
	HSYS_vTurnON(LC);
	HLCD_vOpenSensorGraph(WeightIndex);
	HLCD_vShowAnimation();
	Weight_B=HLDCL_u32Weight();
	HLCD_vContinue(WeightIndex-1);
	HLCD_vShowAnimation();
	if((Weight_B>=(Weight-100))||(Weight_B<=(Weight+100)))
	{
		MTMR_vDelayOVF(Timer0,W2C,ScanColor);
	}
	else
	{
		MTMR_vDelayOVF(Timer0,W2S,ScanColor);

	}
	HSYS_vTurnOFF(LC);
	MTMR_vEndTimer(Timer0);
	HSTPR_Stop();
	MTMR_vChangeMood(Timer1,PWM);
	HSYS_vTurnON(Servo);
	HSRV_vSetAngle(90);
	HSTPR_Walk();
	_delay_ms(50);
	HSRV_vSetAngle(90);
	_delay_ms(50);
	HSYS_vTurnOFF(Servo);
	HSTPR_Walk();
	MTMR_vStartTimer(Timer0);
	HLCD_vContinue(WeightIndex);
	HLCD_vCloseSensorGraph(WeightIndex);
	HLCD_vShowAnimation();

}

void interface(void)
{
	_delay_ms(500);
	HLCD_vSetCursorPosition(1,8);
	HLCD_vPrintString("Hello");
	_delay_ms(1000);
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,1);
	HLCD_vPrintString("Color: ");
	HLCD_vSetCursorPosition(1,1);
	HLCD_vPrintString("1-RED ");
	HLCD_vSetCursorPosition(2,1);
	HLCD_vPrintString("2-GREEN ");
	HLCD_vSetCursorPosition(3,1);
	HLCD_vPrintString("3-BLUE ");
	Color=HKPD_u8GetPressedKey();
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,1);
	HLCD_vPrintString("Weight(in grams): ");
	u08 counter_1=0;
	while((container=HKPD_u8GetPressedKey())!='#')
	{
		Weight+=container-'0';
		Weight*=10;
		counter_1++;
		HLCD_vSetCursorPosition(0,20-counter_1);
		HLCD_vPrintNumber(Weight);

	}
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,1);
	HLCD_vPrintString("Count: ");
	u08 counter_2=0;
	while((container=HKPD_u8GetPressedKey())!='#')
	{
		count+=container-'0';
		count*=10;
		counter_2++;
		HLCD_vSetCursorPosition(0,20-counter_2);
		HLCD_vPrintNumber(count);

	}


}


void OpenSelender(void)
{
	ScanColor_Flag=0;
	OpenSelender_Flag=1;
	FillBox_Flag=0;
	u08 IR2Flag=0;
	static u32 i=0;
	if(OpenSelender_Flag)
	{
	HSYS_vTurnON(IR_3);
	HLCD_vOpenSensorGraph(IR3Index);
	HLCD_vShowAnimation();
	}
	MTMR_vCheckTasks(OpenSelender);
	for(;(i<ERRORtime)&&(~(HIR_u8ReadIR(&IR3_t)))&&OpenSelender_Flag;i++)
	{
		if(HIR_u8ReadIR(&IR2_t))
		{
			MTMR_vSwapTasksPeriority(OpenSelender,ScanColor);
			MTMR_vCheckTasks(OpenSelender);
		}
		if(HIR_u8ReadIR(&IR4_t))
		{
			MTMR_vSwapTasksPeriority(OpenSelender,FillBox);
			MTMR_vCheckTasks(OpenSelender);
		}
	}
	if(OpenSelender_Flag)
	{
	HLCD_vContinue(IR3Index-1);
	HLCD_vShowAnimation();
	}
	if(i==ERRORtime)
	{
		MTMR_vEndTimer(Timer0);
		HSTPR_Stop();
		ErrorFlag=1;
		MTMR_vDelayOVF(Timer2,ERROR_TIME,HBZR_vError);
		HLCD_vClearDisplay();
		HLCD_vSetCursorPosition(0,1);
		HLCD_vPrintString("Product is missing");
		HLCD_vSetCursorPosition(1,0);
		HLCD_vPrintString("In Selender Process");
		HLCD_vSetCursorPosition(3,0);
		HLCD_vPrintString("Press # to continue");
		while(HKPD_u8GetPressedKey()!='#');
		IMGcount--;
		MTMR_vDeleteTask(Timer2,HBZR_vError);
		HSTPR_Walk();
		MTMR_vStartTimer(Timer0);
	}
	i=0;
	if(ErrorFlag==0)
	{
		if(OpenSelender_Flag)
		{
		HLCD_vOpenSensorGraph(SelenderIndex);
		HLCD_vContinue(IR3Index);
		HLCD_vShowAnimation();
		}
		for(;(i2_Selender<IR2S)&&OpenSelender_Flag;i2_Selender++)
		{
			if(HIR_u8ReadIR(&IR2_t)||IR2Flag)
			{
				i2_CS++;
				IR2Flag=1;

			}
			if(HIR_u8ReadIR(&IR1_t))
			{
				counter++;
				MTMR_vDeleteTask(Timer0,FillBox);
				HSYS_vTurnOFF(IR_4);
			}
		}
		if((ErrorFlag==0)&&OpenSelender_Flag)
		{
		MTMR_vEndTimer(Timer0);
		HLCD_vContinue(IR3Index);
		IR2Flag=0;
		i2_Selender=0;
		MTMR_vDeleteTask(Timer0,OpenSelender);
		HSTPR_Stop();
		HSYS_vTurnOFF(IR_3);
		HLCD_vCloseSensorGraph(IR3Index);
		HSYS_vTurnON(Selender);
		HLCD_vShowAnimation();
		_delay_ms(SelenderBack);
		HSYS_vTurnOFF(Selender);
		HLCD_vCloseSensorGraph(IR3Index);
		HLCD_vDeleteBody(SelenderIndex);
		HLCD_vCloseSensorGraph(SelenderIndex);
		HLCD_vContinue(SelenderIndex);
		HLCD_vShowAnimation();
		HSTPR_Walk();
		OpenSelender_Flag=0;
		MTMR_vStartTimer(Timer0);
		}
	}
}


void SSD_DESPLAY(void)
{
	HSSD_vDisplayNum(counter);
}

void ScanColor(void)
{
	u08 Color_B;
	ScanColor_Flag=1;
	OpenSelender_Flag=0;
	FillBox_Flag=0;
	u08 IR3Flag=0;
	static u32 i=0;
	if(ScanColor_Flag)
	{
	HSYS_vTurnON(IR_2);
	HLCD_vOpenSensorGraph(IR2Index);
	HLCD_vShowAnimation();
	}
	MTMR_vCheckTasks(ScanColor);
	for(i=0;(i<ERRORtime)&&(~(HIR_u8ReadIR(&IR2_t)))&&ScanColor_Flag;i++)
	{
		if(HIR_u8ReadIR(&IR3_t))
		{
			MTMR_vSwapTasksPeriority(OpenSelender,ScanColor);
			MTMR_vCheckTasks(OpenSelender);
		}
		if(HIR_u8ReadIR(&IR4_t))
		{
			MTMR_vSwapTasksPeriority(ScanColor,FillBox);
			MTMR_vCheckTasks(ScanColor);
		}
	}
	if(ScanColor_Flag)
	{
	HLCD_vContinue(IR2Index-1);
	HLCD_vShowAnimation();
	}
	if(i==ERRORtime)
	{
		MTMR_vEndTimer(Timer0);
		HSTPR_Stop();
		ErrorFlag=1;
		MTMR_vDelayOVF(Timer2,ERROR_TIME,HBZR_vError);
		HLCD_vClearDisplay();
		HLCD_vSetCursorPosition(0,1);
		HLCD_vPrintString("Product is missing");
		HLCD_vSetCursorPosition(1,2);
		HLCD_vPrintString("In Color Process");
		HLCD_vSetCursorPosition(3,0);
		HLCD_vPrintString("Press # to continue");
		while(HKPD_u8GetPressedKey()!='#');
		IMGcount--;
		MTMR_vDeleteTask(Timer2,HBZR_vError);
		HSTPR_Walk();
		MTMR_vStartTimer(Timer0);
	}
	i=0;
	if(ErrorFlag==0)
	{
		if(OpenSelender_Flag)
		{
			HLCD_vOpenSensorGraph(CSIndex);
			HLCD_vContinue(IR2Index);
			HLCD_vShowAnimation();
		}
		HSYS_vTurnON(ColorSensor);
		for(u16 i=0;(i<IR2C)&&ScanColor_Flag;i++)
		{
			if(HIR_u8ReadIR(&IR3_t)||IR3Flag)
			{
				i2_Selender++;
				IR3Flag=1;

			}
			if(HIR_u8ReadIR(&IR4_t))
			{
				counter++;
				MTMR_vDeleteTask(Timer0,FillBox);
				HSYS_vTurnOFF(IR_4);
			}
		}
		if((ErrorFlag==0)&&ScanColor_Flag)
		{
		MTMR_vEndTimer(Timer0);
		HLCD_vContinue(IR2Index);
		IR3Flag=0;
		i2_Selender=0;
		MTMR_vDeleteTask(Timer0,ScanColor);
		HSTPR_Stop();
		HSYS_vTurnOFF(IR_2);
		HLCD_vCloseSensorGraph(IR2Index);
		HLCD_vShowAnimation();
		MTMR_vChangeMood(Timer1,ICU);
		Color_B=HCLR_u8ScanColor();
		MTMR_vChangeMood(Timer1,PWM);
		if(Color_B==(Color-1))
			MTMR_vDelayOVF(Timer0,C2B,FillBox);
		else
			MTMR_vDelayOVF(Timer0,C2S,OpenSelender);
		HSYS_vTurnOFF(ColorSensor);
		HLCD_vCloseSensorGraph(IR2Index);
		HLCD_vCloseSensorGraph(CSIndex);
		HLCD_vContinue(CSIndex);
		HLCD_vShowAnimation();
		HSTPR_Walk();
		ScanColor_Flag=0;
		MTMR_vStartTimer(Timer0);
		}

	}
}

void FillBox(void)
{
	ScanColor_Flag=0;
	OpenSelender_Flag=0;
	FillBox_Flag=1;
	static u32 i=0;
	if(FillBox_Flag)
	{
	HSYS_vTurnON(IR_4);
	HLCD_vOpenSensorGraph(IR4Index);
	HLCD_vShowAnimation();
	}
	MTMR_vCheckTasks(FillBox);
	for(i=0;(i<ERRORtime)&&(~(HIR_u8ReadIR(&IR4_t)))&&FillBox_Flag;i++)
	{
		if(HIR_u8ReadIR(&IR2_t))
		{
			MTMR_vSwapTasksPeriority(FillBox,ScanColor);
			MTMR_vCheckTasks(OpenSelender);
		}
		if(HIR_u8ReadIR(&IR3_t))
		{
			MTMR_vSwapTasksPeriority(OpenSelender,FillBox);
			MTMR_vCheckTasks(OpenSelender);
		}
	}

	if(i==ERRORtime)
		if(i==ERRORtime)
		{
			MTMR_vEndTimer(Timer0);
			HSTPR_Stop();
			ErrorFlag=1;
			MTMR_vDelayOVF(Timer2,ERROR_TIME,HBZR_vError);
			HLCD_vClearDisplay();
			HLCD_vSetCursorPosition(0,1);
			HLCD_vPrintString("Product is missing");
			HLCD_vSetCursorPosition(1,1);
			HLCD_vPrintString("In Filling Process");
			HLCD_vSetCursorPosition(3,0);
			HLCD_vPrintString("Press # to continue");
			while(HKPD_u8GetPressedKey()!='#');
			IMGcount--;
			MTMR_vDeleteTask(Timer2,HBZR_vError);
			HSTPR_Walk();
			MTMR_vStartTimer(Timer0);
		}
	i=0;
	if((ErrorFlag==0)&&FillBox_Flag)
	{
		MTMR_vEndTimer(Timer0);
		MTMR_vDeleteTask(Timer0,FillBox);
		counter++;
		HSYS_vTurnOFF(IR_4);
		FillBox_Flag=0;
		MTMR_vStartTimer(Timer0);
	}
}
