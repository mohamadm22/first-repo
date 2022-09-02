/*
 * SNAKE_prg.c
 *
 *  Created on: Aug 14, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"

#include"SNAKE_int.h"

#include"../../MCAL/DIO/DIO_int.h"
#include"../../MCAL/TMR/TMR_int.h"
#include"../LNKDLST/LNKDLST_int.h"

#include"../../HAL/LCD/LCD_int.h"

#include<util/delay.h>

extern node es;
u08 arr[14][14]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
u08 RightFlag=0;
u08 LeftFlag=0;
u08 UpFlag=0;
u08 DownFlag=0;

node* head;
node* tail;
node* food;
void SNAKE_vInit(void)
{
	head=CreatFirstNode();
	food=CreatFirstNode();
	tail=head;
	CreatNode(tail);
	head->HorzintalIndex=35;
	head->VerticalIndex=7;
	tail->HorzintalIndex=34;
	tail->VerticalIndex=7;
	SNAKE_vGenrateFood();
	HLCD_vInit();
	MTMR_vDelayOVF(Timer0,15,SNAKE_vGetUpdated);
	MTMR_vDelayOVF(Timer0,1000,SNAKE_vMoveUpdate);


}
void SNAKE_vMoveRight(void)
{
	if(RightFlag!=1)
	{
		node* link=tail;
		while (link!=head)
		{
			link->HorzintalIndex=link->next->HorzintalIndex;
			link->VerticalIndex=link->next->VerticalIndex;
			link=link->next;
		}
		if(head->HorzintalIndex==70)
			head->HorzintalIndex=0;
		else
			head->HorzintalIndex++;

	}
	RightFlag=1;
	LeftFlag=0;
	UpFlag=0;
	DownFlag=0;
}
void SNAKE_vMoveLeft(void)
{
	if(LeftFlag!=1)
	{
		node* link=tail;
		while (link!=head)
		{
			link->HorzintalIndex=link->next->HorzintalIndex;
			link->VerticalIndex=link->next->VerticalIndex;
			link=link->next;
		}
		if(head->HorzintalIndex==0)
			head->HorzintalIndex=70;
		else
			head->HorzintalIndex--;

	}
	RightFlag=0;
	LeftFlag=1;
	UpFlag=0;
	DownFlag=0;

}
void SNAKE_vMoveUp(void)
{
	if(UpFlag!=1)
	{
		node* link=tail;
		while (link!=head)
		{
			link->HorzintalIndex=link->next->HorzintalIndex;
			link->VerticalIndex=link->next->VerticalIndex;
			link=link->next;
		}
		if(head->VerticalIndex==0)
			head->VerticalIndex=14;
		else
			head->VerticalIndex--;

	}
	RightFlag=0;
	LeftFlag=0;
	UpFlag=1;
	DownFlag=0;

}
void SNAKE_vMoveDown(void)
{
	if(DownFlag!=1)
	{
		node* link=tail;
		while (link!=head)
		{
			link->HorzintalIndex=link->next->HorzintalIndex;
			link->VerticalIndex=link->next->VerticalIndex;
			link=link->next;
		}
		if(head->VerticalIndex==14)
			head->VerticalIndex=0;
		else
			head->VerticalIndex++;

	}
	RightFlag=0;
	LeftFlag=0;
	UpFlag=0;
	DownFlag=1;

}
void SNAKE_vGetUpdated(void)
{

	for(u08 i=0;i<14;i++){
		for(u08 j=0;j<14;j++){
			arr[i][j]=0;
		}
	}
	node* link=tail;
	while(link!=NULL)
	{
		arr[link->VerticalIndex][link->HorzintalIndex/5]=(1<<link->HorzintalIndex%5);
		link=link->next;
	}
	u08 arr2[8];
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][0];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][1];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][2];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][3];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][4];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][5];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][6];
	HLCD_vSaveCustomChar(0,arr2);
	HLCD_vSendChar(0);
	HLCD_vSendChar(1);
	HLCD_vSendChar(2);
	HLCD_vSendChar(3);
	HLCD_vSendChar(4);
	HLCD_vSendChar(5);
	HLCD_vSendChar(6);
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,7);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][0];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][1];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][2];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][3];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][4];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][5];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=0;i<7;i++)
		arr2[i]=arr[i][6];
	HLCD_vSaveCustomChar(0,arr2);
	HLCD_vSendChar(0);
	HLCD_vSendChar(1);
	HLCD_vSendChar(2);
	HLCD_vSendChar(3);
	HLCD_vSendChar(4);
	HLCD_vSendChar(5);
	HLCD_vSendChar(6);
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(1,0);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][7];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][8];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][9];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][10];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][11];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][12];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][13];
	HLCD_vSaveCustomChar(0,arr2);
	HLCD_vSendChar(0);
	HLCD_vSendChar(1);
	HLCD_vSendChar(2);
	HLCD_vSendChar(3);
	HLCD_vSendChar(4);
	HLCD_vSendChar(5);
	HLCD_vSendChar(6);
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(1,7);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][7];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][8];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][9];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][10];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][11];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][12];
	HLCD_vSaveCustomChar(0,arr2);
	for(u08 i=7;i<14;i++)
		arr2[i]=arr[i][13];
	HLCD_vSaveCustomChar(0,arr2);
	HLCD_vSendChar(0);
	HLCD_vSendChar(1);
	HLCD_vSendChar(2);
	HLCD_vSendChar(3);
	HLCD_vSendChar(4);
	HLCD_vSendChar(5);
	HLCD_vSendChar(6);
	HLCD_vClearDisplay();
	HLCD_vSetCursorPosition(0,0);
}
void SNAKE_vMoveUpdate(void)
{
	if(RightFlag==1)
	{
		RightFlag=0;
		SNAKE_vMoveRight();
		RightFlag=1;
	}
	if(LeftFlag==1)
	{
		LeftFlag=0;
		SNAKE_vMoveLeft();
		LeftFlag=1;
	}
	if(UpFlag==1)
	{
		UpFlag=0;
		SNAKE_vMoveUp();
		UpFlag=1;
	}
	if(RightFlag==1)
	{
		DownFlag=0;
		SNAKE_vMoveDown();
		DownFlag=1;
	}
}
void SNAKE_vGenrateFood(void)
{
	node* search=tail;
	u08 flag=1;
	u16 FoodAddress;
	while(flag)
	{
		FoodAddress=MTMR_u8GetTimeValue()*4;
		if(FoodAddress>980)
			FoodAddress-=40;
		while(flag==1)
		{
			if(search->next==NULL)
				flag=3;
			if((search->HorzintalIndex==(FoodAddress%5))&&(search->VerticalIndex==(FoodAddress/5)))
				flag=2;
			search=search->next;
		}
		if(flag!=2)
			flag=0;
	}
	food->HorzintalIndex=(FoodAddress%5);
	food->VerticalIndex=(FoodAddress/5);
	free(search);
}
void SNAKE_vGetLong(void)
{
	if((head->HorzintalIndex==food->HorzintalIndex)&&(head->VerticalIndex==food->VerticalIndex))
	{
		SNAKE_vGenrateFood();
		CreatNode(tail);
		if(tail->next->HorzintalIndex==tail->next->next->HorzintalIndex)
		{
			tail->HorzintalIndex=tail->next->HorzintalIndex;
			if(tail->next->VerticalIndex>tail->next->next->VerticalIndex)
			{
				if(tail->next->VerticalIndex==13&&tail->next->next->VerticalIndex==12)
					tail->VerticalIndex=0;
				else if(tail->next->VerticalIndex==13&&tail->next->next->VerticalIndex==0)
					tail->VerticalIndex=tail->next->VerticalIndex-1;
				else
					tail->VerticalIndex=tail->next->VerticalIndex+1;
			}
			else
			{
				if(tail->next->VerticalIndex==0&&tail->next->next->VerticalIndex==1)
					tail->VerticalIndex=13;

				else if(tail->next->VerticalIndex==0&&tail->next->next->VerticalIndex==13)
					tail->VerticalIndex=tail->next->VerticalIndex+1;
				else
					tail->VerticalIndex=tail->next->VerticalIndex-1;
			}
		}
		else if(tail->next->VerticalIndex==tail->next->next->VerticalIndex)
		{
			tail->VerticalIndex=tail->next->VerticalIndex;
			if(tail->next->HorzintalIndex>tail->next->next->HorzintalIndex)
			{
				if(tail->next->HorzintalIndex==69&&tail->next->next->HorzintalIndex==68)
					tail->HorzintalIndex=0;
				else if(tail->next->HorzintalIndex==69&&tail->next->next->HorzintalIndex==0)
					tail->HorzintalIndex=tail->next->HorzintalIndex-1;
				else
					tail->HorzintalIndex=tail->next->HorzintalIndex+1;
			}
			else
			{
				if(tail->next->HorzintalIndex==0&&tail->next->next->HorzintalIndex==1)
					tail->HorzintalIndex=69;

				else if(tail->next->HorzintalIndex==0&&tail->next->next->HorzintalIndex==69)
					tail->HorzintalIndex=tail->next->HorzintalIndex+1;
				else
					tail->HorzintalIndex=tail->next->HorzintalIndex-1;
			}
		}
	}

}
void SNAKE_vGameOver(void)
{
	u08 flag=1;
	node* search=tail;

	while(flag==1)
	{
		if(search->next==head)
			flag=3;
		if(search->HorzintalIndex==head->HorzintalIndex&&search->VerticalIndex==head->VerticalIndex)
			flag=2;
		search=search->next;
	}
	if(flag==2)
	{
		while(tail!=NULL)
		{
			node* DeletNode=tail;
			tail=tail->next;
			free(DeletNode);
		}
		HLCD_vClearDisplay();
		HLCD_vSetCursorPosition(0,6);
		HLCD_vPrintString("game");
		HLCD_vSetCursorPosition(1,6);
		HLCD_vPrintString("over");
		_delay_ms(1000);
		SNAKE_vInit();
		free(search);
	}


}

