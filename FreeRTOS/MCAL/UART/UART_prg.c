/*
 * UART_prg.c
 *
 *  Created on: Jul 28, 2022
 *      Author: mazen
 */


#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"



#include "UART_int.h"
#include "UART_prv.h"
#include "UART_cfg.h"

void MUART_vSetBoudRate(void)
{
	if(UART_BAUD_RATE>255)
	{
		UBRRL=UART_BAUD_RATE&0xff;
		UBRRH=UART_BAUD_RATE>>8;
	}
	else
		UBRRL=UART_BAUD_RATE;
}

void MUART_vInit(void)
{
#if UART_INTERRUPT==ENABLE
	SET_BIT(UCSRB,RXCIE);
	SET_BIT(UCSRB,TXCIE);
	SET_BIT(UCSRB,UDRIE);
#endif

	u08 UCSRC_SETTING=0;
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
#if USART_Mode==Asynchronous
	CLR_BIT(UCSRC_SETTING,UMSEL);
#elif USART_Mode==synchronous
	SET_BIT(UCSRC_SETTING,UMSEL);
#endif
#if Parity_Mode==DISABLE
	CLR_BIT(UCSRC_SETTING,UPM0);
	CLR_BIT(UCSRC_SETTING,UPM1);

#elif Parity_Mode==Even
	CLR_BIT(UCSRC_SETTING,UPM0);
	SET_BIT(UCSRC_SETTING,UPM1);

#elif Parity_Mode==Odd
	SET_BIT(UCSRC_SETTING,UPM0);
	SET_BIT(UCSRC_SETTING,UPM1);
#endif

#if Stop_Bit==zero
	CLR_BIT(UCSRC_SETTING,USBS);

#elif Stop_Bit==one
	SET_BIT(UCSRC_SETTING,USBS);
#endif
#if   Character_Size==bit_5
	CLR_BIT(UCSRC_SETTING,UCSZ1);
	CLR_BIT(UCSRC_SETTING,UCSZ0);
#elif Character_Size==bit_6
	CLR_BIT(UCSRC_SETTING,UCSZ1);
	SET_BIT(UCSRC_SETTING,UCSZ0);
#elif Character_Size==bit_7
	SET_BIT(UCSRC_SETTING,UCSZ1);
	CLR_BIT(UCSRC_SETTING,UCSZ0);
#elif Character_Size==bit_8
	SET_BIT(UCSRC_SETTING,UCSZ1);
	SET_BIT(UCSRC_SETTING,UCSZ0);
#elif Character_Size==bit_9
	SET_BIT(UCSRC_SETTING,UCSZ1);
	SET_BIT(UCSRC_SETTING,UCSZ0);
	SET_BIT(UCSRB,UCSZ2);
#endif
	SET_BIT(UCSRC_SETTING,URSEL);
	SET_BIT(UCSRC_SETTING,UCSZ1);
	SET_BIT(UCSRC_SETTING,UCSZ0);

	UCSRC = UCSRC_SETTING;

	MUART_vSetBoudRate(); // 9600
}

void MUART_vTransmit(u16 A_u16Byte)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );

#if Character_Size==bit_9
	if(GET_BIT(A_u16Byte,8))
		SET_BIT(UCSRB,TXB8);
	else
		CLR_BIT(UCSRB,TXB8);
#endif
	/* Put data into buffer, sends the data */
	UDR = A_u16Byte&0xff;
}

u16   MUART_u8Recieve(void)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
#if  Character_Size==bit_9
	return (UDR|(GET_BIT(UCSRB,RXB8)<<8));
#endif
	return (UDR);
}
void MUART_vSendString(u08* A_u8String)
{
	while(*A_u8String!='\0'){
		MUART_vTransmit(*A_u8String);
		A_u8String++;
	}

}
void MUART_vSendNumber(s32 A_s32Number)
{
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
				MUART_vTransmit(48+(A_s32Number/(L_u8power)));}
			else
				MUART_vTransmit(48+0);
			A_s32Number-=(A_s32Number/(L_u8power))*(L_u8power);
			L_u8power/=10;

		}
		MUART_vTransmit(48+(A_s32Number%10));

	}

	else
	{
		MUART_vTransmit('-');
		A_s32Number*=-1;
		while(L_u8power!=0)
		{
			if((A_s32Number>=(L_u8power)))
			{
				MUART_vTransmit(48+(A_s32Number/(L_u8power)));}
			else
				MUART_vTransmit(48+0);
			A_s32Number-=(A_s32Number/(L_u8power))*(L_u8power);
			L_u8power/=10;

		}
		MUART_vTransmit(48+(A_s32Number%10));


	}
}
void MUART_vReceiveString(u08* A_u8String,u08 A_u32size)
{
	for(u32 L_u32I=0;L_u32I<A_u32size;L_u32I++)
	{
		A_u8String[L_u32I]=MUART_u8Recieve();
		if(A_u8String[L_u32I]!='\n'||A_u8String[L_u32I]!='\0'||A_u8String[L_u32I]!='\r')
		{
			A_u8String[L_u32I]='\0';
			break;
		}
		A_u8String[A_u32size-1]='\0';
	}
}

