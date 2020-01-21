/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*      Description:	Addition of Input 1 and Input 2 with output wrapping. */
/*						Calculation:										  */
/* 							Out = In1 + In2									  */
/* 																			  */
/* USERCODE-END:Description                                                                                           */
#include "uAdd_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(uAdd_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN1		(*pTuAdd_Float64->In1)
#define IN2		(*pTuAdd_Float64->In2)

/* Outputs */
#define OUT 	(pTuAdd_Float64->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void uAdd_Float64_Update(UADD_FLOAT64 *pTuAdd_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 result; 
	
	result = IN1 + IN2;

	/* output wrapping */
	if (result >= PI_R64)
	{
		result = fmod(result, (2*PI_R64));
		if (result >= PI_R64)
		{
			result = result - (2*PI_R64);
		}
	}
	else if (result < -PI_R64)
	{
		result = fmod(result, (2*PI_R64));
		if (result < -PI_R64)
		{
			result = result + (2*PI_R64);
		}
	}
	
	OUT = result;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uAdd_Float64_Init(UADD_FLOAT64 *pTuAdd_Float64)
{
    pTuAdd_Float64->ID = UADD_FLOAT64_ID;
    pTuAdd_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** No Load function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** No Save function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(UADD_FLOAT64_ISLINKED)
void* uAdd_Float64_GetAddress(const UADD_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->In2;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
