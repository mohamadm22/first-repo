/*
 * DIO_int.h
 *
 *  Created on: May 18, 2022
 *      Author: user
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

#define DIO_Input  0
#define DIO_Output 1

#define DIO_LOW  0
#define DIO_HIGH 1


void MDIO_vSetPinDir(u08 A_u8PortNo,u08 A_u8PinNo,u08 A_u8Dir);
void MDIO_vTogglePin(u08 A_u8PortNo,u08 A_u8PinNo);
void MDIO_vSetPinVal(u08 A_u8PortNo,u08 A_u8PinNo,u08 A_u8Val);
u08 MDIO_u8GetPinVal(u08 A_u8PortNo,u08 A_u8PinNo);
void MDIO_vSetPortDir(u08 A_u8PortNo,u08 A_u8Dir);
void MDIO_vSetPortVal(u08 A_u8PortNo,u08 A_u8Val);
u08 MDIO_u8GetPortVal(u08 A_u8PortNo);

#endif /* MCAL_DIO_DIO_INT_H_ */
