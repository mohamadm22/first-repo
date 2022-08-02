/*
 * LCD_int.h
 *
 *  Created on: May 20, 2022
 *      Author: user
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

#define LCD_CTRL_PORT DIO_PORTA
#define LCD_DATA_PORT DIO_PORTD
#define LCD_RS_PIN DIO_PIN0
#define LCD_RW_PIN DIO_PIN1
#define LCD_EN_PIN DIO_PIN2

void HLCD_vSendCommand(u08 A_u8Command);
void HLCD_vSendChar(u08 A_u8Char);
void HLCD_vInit(void);
void HLCD_vPrintString(u08 A_u8String[]);
void HLCD_vPrintNumber(s08 A_s32Number);
void HLCD_vSetCursorPosition(u08 A_u8linePos,u08 A_u8lineNum);
void HLCD_vSaveCustomChar(u08 A_u8Cgram_index,u08 A_u8CharData[]);

#endif /* HAL_LCD_LCD_INT_H_ */
