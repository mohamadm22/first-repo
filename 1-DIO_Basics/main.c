/*
 * main.c
 *
 *  Created on: May 11, 2022
 *      Author: user
 */


#include<avr/io.h>
#include<util/delay.h>

void main(void)
{
	DDRA= 0b00001111;   //PA0>>OUTPUT
	char i;
	while(1)           //SUPER LOOP
	{
		PORTA=0b00000001;
		for(i=0;i<4;i++){
		_delay_ms(1000);
		PORTA<<=1;
		}

	}
}

