/*
 * IR_int.h
 *
 *  Created on: May 19, 2023
 *      Author: user
 */

#ifndef HAL_IR_IR_INT_H_
#define HAL_IR_IR_INT_H_
typedef struct
{
	u08 Port;
	u08 Pin;
}IR_t;

typedef enum
{
	IR_Exist,
	IR_NotExist
}IR_Scan;

u08 HIR_u8ReadIR(IR_t* Sensor);


#endif /* HAL_IR_IR_INT_H_ */
