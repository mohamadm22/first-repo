/*
 * UART_cfg.h
 *
 *  Created on: Jul 28, 2022
 *      Author: mazen
 */

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

/*
 * BR_X where x=
2400
4800
9600
14400
19200
28800
38400
57600
76800
115200
250000
500000
 */
#define UART_BAUD_RATE		BR_9600

/*
 * options:
 * 5_bit
 * 6_bit
 * 7_bit
 * 8_bit
 * 9_bit
 */
#define Character_Size      bit_8

/*options:zero/one*/
#define Stop_Bit            zero

/*options:
 * DISABLE
 * Even
 * Odd
 */
#define Parity_Mode         DISABLE

/*options:Asynchronous/synchronous*/
#define USART_Mode          Asynchronous


#endif /* MCAL_UART_UART_CFG_H_ */
