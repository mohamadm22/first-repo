/*
 * LCD_int.h
 *
 *  Created on: May 20, 2022
 *      Author: user
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

void HLCD_vAddBody(void);
void HLCD_vShowAnimation(void);
void HLCD_vDeleteBody(u08 Index);
void HLCD_vPauseBody(u08 Index);
void HLCD_vPause(void);
void HLCD_vContinue(u08 index);
void HLCD_vSendCommandIIC(u08 A_u8Command);
void HLCD_vSendCommand(u08 A_u8Command);
void HLCD_vSendChar(u08 A_u8Char);
void HLCD_vInit(void);
void HLCD_vPrintString(u08 A_u8String[]);
void HLCD_vPrintNumber(s32 A_s32Number);
void HLCD_vSetCursorPosition(u08 A_u8linePos,u08 A_u8lineNum);
void HLCD_vSaveCustomChar(u08 A_u8Cgram_index,u08 A_u8CharData[]);
void HLCD_vClearDisplay(void);
void HLCD_vOpenSensorGraph(u08 Sensor);
void HLCD_vCloseSensorGraph(u08 Sensor);

void expanderWrite(u08 data);
void write4bits(u08 value);
void send(u08 value, u08 mode);
void command(u08 value);
void pulseEnable(u08 data);

#define IR2Index                 3
#define WeightIndex              1
#define IR3Index                 6
#define CSIndex                  4
#define IR4Index                 9
#define SelenderIndex            7

#endif /* HAL_LCD_LCD_INT_H_ */
