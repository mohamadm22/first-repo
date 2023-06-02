/*
 * SPI_prg.c
 *
 *  Created on: Aug 3, 2022
 *      Author: user
 */

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"



#include "SPI_int.h"
#include "SPI_prv.h"
#include "SPI_cfg.h"

void MSPI_vInit(void)
{
#if SPI_INTERRUPT==ENABLE
	SET_BIT(SPCR,SPIE);
#elif SPI_INTERRUPT==DISABLE
	CLR_BIT(SPCR,SPIE);
#endif

#if SPI_MODE==SPI_MASTER
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN4,DIO_Output); //SS
	MDIO_vSetPinVal(DIO_PORTB,DIO_PIN4,DIO_LOW);
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN5,DIO_Output); //mosi
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN6,DIO_Input);  //miso
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN7,DIO_Output); //sck

	SET_BIT(SPCR,MSTR);


#elif SPI_MODE==SPI_Slave
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN4,DIO_Input);   //SS
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN5,DIO_Input);   //mosi
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN6,DIO_Output ); //miso
	MDIO_vSetPinDir(DIO_PORTB,DIO_PIN7,DIO_Input);   //sck
	CLR_BIT(SPCR,MSTR);

#endif

#if DATA_TRANSMATE_FIRST==LSB_start
	SET_BIT(SPCR,DORD);
#elif DATA_TRANSMATE_FIRST==MSB_start
	CLR_BIT(SPCR,DORD);
#endif

	/* Leading Edge:Falling,Setup
	 * Trailing Edge:Rising,Sample*/
	CLR_BIT(SPCR,CPOL);
	SET_BIT(SPCR,CPHA);

#if Prescaler==Prescaler_4
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	CLR_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_16
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	CLR_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_64
	CLR_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1);
	CLR_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_128
	SET_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1);
	CLR_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_2
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_8
	SET_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPSR,SPI2X);

#elif Prescaler==Prescaler_32
	CLR_BIT(SPCR,SPR0);
	SET_BIT(SPCR,SPR1);
	SET_BIT(SPSR,SPI2X);

#endif

	SET_BIT(SPCR,SPE);

}

u08 MSPI_u8Tranciever(u08 A_u8Data)
{
	/* Start transmission */
	SPDR = A_u8Data;
	/* Wait for transmission complete */
	while(!(GET_BIT(SPSR,SPIF)));

	/* Return data register */
	return SPDR;
}
