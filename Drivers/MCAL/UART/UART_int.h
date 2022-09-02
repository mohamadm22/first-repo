/*
 * UART_int.h
 *
 *  Created on: Jul 28, 2022
 *      Author: mazen
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

void MUART_vInit(void);
void MUART_vTransmit(u16 A_u16Byte);
u16   MUART_u8Recieve(void);

void MUART_vSendString(u08* A_u8String);
void MUART_vSendNumber(s32 A_s32Number);
void MUART_vReceiveString(u08* A_u8String,u08 A_u32size);


void MUART_vSetBaudRate(void);

#define BR_2400          207
#define BR_4800          103
#define BR_9600          51
#define BR_14400         34
#define BR_19200         25
#define BR_28800         16
#define BR_38400         12
#define BR_57600         8
#define BR_76800         6
#define BR_115200        3
#define BR_250000        1
#define BR_500000        0

#define bit_5            5
#define bit_6            6
#define bit_7            7
#define bit_8            8
#define bit_9            9

#define DISABLE          0
#define Odd              1
#define Even             2

#define Asynchronous     0
#define synchronous      1

#define zero             0
#define one              1

#endif /* MCAL_UART_UART_INT_H_ */
