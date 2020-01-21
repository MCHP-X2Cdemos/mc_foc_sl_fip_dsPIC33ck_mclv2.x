/*
 * $LastChangedRevision: 1552 $
 * $LastChangedDate:: 2018-09-28 16:54:50 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "CheckValidApplication.h"

extern volatile tTableStruct TheTableStruct;

#if defined(__TMS320F2806X__) || defined(__TMS320F2803X__) || \
	defined(__TMS320F2833X__) || defined(__TMS320F280X__) || \
	defined(__TMS320F281X__) || defined(__TMS320F2802X__)
extern void c_int00(void);
int16 watchdogResetState[4];
#elif defined(__SERIES_TM4C__)
#pragma DATA_SECTION(watchdogResetState, ".resetCounter")
int16 watchdogResetState[4];
#elif defined(__STM32F10XXX__) || defined(__COMPILER_ST__)
int16 __attribute__ ((zero_init)) watchdogResetState[4];
#elif defined(__COMPILER_MICROCHIP__)
int16 __attribute__ ((persistent)) watchdogResetState[4];
#elif defined(__SERIES_XMC4800__) || defined(__SERIES_XMC4700__) || defined(__SERIES_XMC4400__) || defined(__SERIES_XMC4500__)
int16 watchdogResetState[4] __attribute__ ((section (".uninitialized")));
#elif defined(__COMPILER_CODEWARRIOR_ECLIPSE__)
#pragma push
#pragma section data_type sdata_type ".resetWatchdogInit" ".resetWatchdogUninit"
static int16 watchdogResetState[4];
#pragma pop
#else
#error PROCESSOR TYPE NOT DEFINED
#endif

/* check reset count & start monitor */
void boot(void)
{
	if ((TheTableStruct.DSPState != MONITOR_STATE) && \
			(watchdogResetState[1] == (int16)'W') && \
			(watchdogResetState[2] == (int16)'D') && \
			(watchdogResetState[3] == (int16)'R') )
	{
		if ((watchdogResetState[0] < (int16)0) || \
				(watchdogResetState[0] > MAX_WATCHDOG_RESTS))
		{
			/* reset counter */
			watchdogResetState[0] = (int16)1;
		}
		else if (++watchdogResetState[0] == MAX_WATCHDOG_RESTS)
		{
			watchdogResetState[0] = MAX_WATCHDOG_RESTS;
		}
	}
	else
	{
		/* reset counter */
		watchdogResetState[0] = (int16)0;
	}
	/* keys to prevent detection of wrong watchdog resets */
	watchdogResetState[1] = (int16)'W';
	watchdogResetState[2] = (int16)'D';
	watchdogResetState[3] = (int16)'R';

#if defined(__TMS320F2806X__) || defined(__TMS320F2803X__) || \
	defined(__TMS320F2833X__) || defined(__TMS320F280X__) || \
	defined(__TMS320F281X__) || defined(__TMS320F2802X__)
	c_int00();
#elif defined(__SERIES_TM4C__)
	/* do nothing */
#elif defined(__STM32F10XXX__) || defined(__VENDOR_ST__)
	/* function was called from main -> simply return */
#elif defined(__VENDOR_MICROCHIP__)
    /* function was called from main -> simply return */
#elif defined(__VENDOR_INFINEON__)
	/* function was called from main -> simply return */
#elif defined(__COMPILER_CODEWARRIOR_ECLIPSE__)
	/* TODO simply return ? */
#else
#error PROCESSOR TYPE NOT DEFINED
#endif
}

/* check if reset counter exceeds maximum value */
uint8 checkValidApplication(void)
{
	return !((watchdogResetState[0] >= (int16)MAX_WATCHDOG_RESTS) && \
			(watchdogResetState[1] == (int16)'W') && \
			(watchdogResetState[2] == (int16)'D') && \
			(watchdogResetState[3] == (int16)'R') );
}
