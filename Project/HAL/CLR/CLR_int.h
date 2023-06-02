/*
 * CLR_int.h
 *
 *  Created on: May 20, 2023
 *      Author: user
 */

#ifndef HAL_CLR_CLR_INT_H_
#define HAL_CLR_CLR_INT_H_

typedef enum
{
	RED,
	GREEN,
	BLUE
}Color_t;


void HCLR_vInit(void);
u08 HCLR_u8ScanColor(void);


#endif /* HAL_CLR_CLR_INT_H_ */
