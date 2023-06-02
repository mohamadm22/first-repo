/*
 * SYS_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: moham
 */

#ifndef HAL_SYS_SYS_INT_H_
#define HAL_SYS_SYS_INT_H_

typedef enum
{
	IR_2,
	IR_3,
	IR_4,
	ColorSensor,
	Servo,
	LC,
	Selender,
	ELSE1,
	ELSE2,
	ELSE3


}SYS_Combonant_t;

void HSYS_vTurnOFF(SYS_Combonant_t Combonant);
void HSYS_vTurnON(SYS_Combonant_t Combonant);
void HSYS_vInit(void);


#endif /* HAL_SYS_SYS_INT_H_ */
