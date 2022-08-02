/*
 * DCM_int.h
 *
 *  Created on: May 31, 2022
 *      Author: mazen
 */

#ifndef HAL_DCM_DCM_INT_H_
#define HAL_DCM_DCM_INT_H_

typedef struct
{
	u08 Port;
	u08 Pin1;
	u08 Pin2;
}DCM_t;

#define NOSTRUCT	1
#define STRUCT		2
#define METHOD		STRUCT

#if METHOD==NOSTRUCT
void HDCM_vInit(void);
void HDCM_vRotateCW(void); /* TODO: implement speed as input */
void HDCM_vRotateCCW(void); /* TODO: implement speed as input */
void HDCM_vStop(void);
#endif

#if METHOD==STRUCT
DCM_t HDCM_xInit(u08 A_u8Port,
   				u08 A_u8Pin1,
				u08 A_u8Pin2);
void HDCM_xRotateCW(DCM_t*  A_xMotor ); /* TODO: implement speed as input */
void HDCM_xRotateCCW(DCM_t* A_xMotor); /* TODO: implement speed as input */
void HDCM_xStop(DCM_t* A_xMotor);
#endif


#endif /* HAL_DCM_DCM_INT_H_ */
