/*
 * WDT_prg.c
 *
 *  Created on: Jul 28, 2022
 *      Author: mazen
 */


#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"



#include "WDT_int.h"
#include "WDT_prv.h"
#include "WDT_cfg.h"



void MWDT_vTurnOn(u08 A_u8Timeout)
{
	/* set timeout */
	WDTCR = (WDTCR& 0xF8) | A_u8Timeout ;
	/* set WDE */
	SET_BIT(WDTCR, WDE);
}

void MWDT_vTurnOff(void)
{
	u08 WDTCR_SETTING=0;
	SET_BIT(WDTCR_SETTING, WDE);
	SET_BIT(WDTCR_SETTING, WDTOE);
	WDTCR=WDTCR_SETTING;
	CLR_BIT(WDTCR, WDE);
}


