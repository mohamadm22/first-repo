/*
 * ROBOT_prg.c
 *
 *  Created on: Jul 21, 2022
 *      Author: user
 */
#include"../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_int.h"
#include"../../HAL/DCM/DCM_int.h"
#include"ROBOT_int.h"
#include"ROBOT_cfg.h"

DCM_t MOTOR_1;
DCM_t MOTOR_2;

void AROBOT_vInit(void)
{
	MOTOR_1=HDCM_xInit(ROBOT_MOTOR_1,ROBOT_MOTOR_1_PIN1,ROBOT_MOTOR_1_PIN2);
	MOTOR_2=HDCM_xInit(ROBOT_MOTOR_2,ROBOT_MOTOR_2_PIN1,ROBOT_MOTOR_2_PIN2);
}
void AROBOT_vMoveForward(void)
{
	HDCM_xRotateCW(&MOTOR_1 );
	HDCM_xRotateCW(&MOTOR_2 );
}
void AROBOT_vMoveRight(void)
{
	HDCM_xRotateCW(&MOTOR_1 );
	HDCM_xRotateCCW(&MOTOR_2 );
}
void AROBOT_vMoveLeft(void)
{
	HDCM_xRotateCCW(&MOTOR_1 );
	HDCM_xRotateCW(&MOTOR_2 );
}
void AROBOT_vMoveBack(void)
{
	HDCM_xRotateCCW(&MOTOR_1 );
	HDCM_xRotateCCW(&MOTOR_2 );
}
void AROBOT_vStop(void)
{
	HDCM_xStop(&MOTOR_1 );
	HDCM_xStop(&MOTOR_2 );
}
