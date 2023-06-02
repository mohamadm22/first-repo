/*
 * LDCL_prg.c
 *
 *  Created on: May 22, 2023
 *      Author: user
 */

#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include<util/delay.h>

#include"LDCL_int.h"
#include"LDCL_cfg.h"

void HLDCL_vInit(void)
{
	MDIO_vSetPinDir(SCL_Port,SCL_Pin,DIO_Output);
	MDIO_vSetPinDir(DOUT_Port,DOUT_Pin,DIO_Input);
	MDIO_vSetPinVal(SCL_Port,SCL_Pin,DIO_LOW);


}

u32 HLDCL_u32Read(void)
{

	while(MDIO_u8GetPinVal(DOUT_Port,DOUT_Pin)==DIO_HIGH);
	u32 Weight;
    for(u08 i = 0; i < 24; i++)
    {
    	MDIO_vSetPinVal(SCL_Port,SCL_Pin, DIO_HIGH);
    	_delay_ms(1);
    	Weight |= ((MDIO_u8GetPinVal(DOUT_Port,DOUT_Pin) << (23-i)));
        MDIO_vSetPinVal(SCL_Port,SCL_Pin, DIO_LOW);
        _delay_ms(1);
    }
	MDIO_vSetPinVal(SCL_Port,SCL_Pin, DIO_HIGH);
	_delay_ms(1);
    MDIO_vSetPinVal(SCL_Port,SCL_Pin, DIO_LOW);
    _delay_ms(1);
    if(Weight&0x800000)
    {
    	Weight|=0xff000000;
    }

    return Weight;
}

u32 HLDCL_u32Weight(void)
{
	u32 sum = 0;
	if(MDIO_u8GetPinVal(DOUT_Port,DOUT_Pin)==DIO_LOW)
	{
		for (u08 i = 0; i < 10; i++)
		{
			sum += HLDCL_u32Read();
			// Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on ESP.
			// https://github.com/bogde/HX711/issues/73
			_delay_ms(0);
		}
	}
	return (sum/10);

}
/*
sbit ADDO = P1^5;
sbit ADSK = P0^0;
unsigned long ReadCount(void){
 unsigned long Count;
 unsigned char i;
 ADDO=1;
 ADSK=0;
 Count=0;
 while(ADDO);
 for (i=0;i<24;i++){
 ADSK=1;
 Count=Count<<1;
 ADSK=0;
 if(ADDO) Count++;
 }
 ADSK=1;
 Count=Count^0x800000;
 ADSK=0;
 return(Count);
} 
*/
