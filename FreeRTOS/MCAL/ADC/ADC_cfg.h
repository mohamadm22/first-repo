/*
 * ADC_cfg.h
 *
 *  Created on: Aug 3, 2022
 *      Author: user
 */

#ifndef MCAL_ADC_ADC_CFG_H_
#define MCAL_ADC_ADC_CFG_H_

/*options:AVCC/INTERNAL_REF/AREF */
#define ADC_REF_VOLT  AVCC

/*options:Prescaler_2/Prescaler_4/Prescaler_8/Prescaler_16/Prescaler_32/Prescaler_64/Prescaler_64 */
#define Prescaler Prescaler_8

/*options:
 * Free_Running_mode
 * Analog_Comparator
 * External_Interrupt_Request_0
 * Timer_Counter0_Compare
 * Timer_Counter0_Overflow
 * Timer_Counter1_Compare Match_B
 * Timer_Counter1_Overflow
 * Timer_Counter1_Capture
 */
#define Auto_Trigger_Mode    Free_Running_mode

#define Auto_Trigger         DISABLE

#endif /* MCAL_ADC_ADC_CFG_H_ */
