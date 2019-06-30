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
#include "uAdd_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(uAdd_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN1		(*pTuAdd_Float32->In1)
#define IN2		(*pTuAdd_Float32->In2)

/* Outputs */
#define OUT 	(pTuAdd_Float32->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void uAdd_Float32_Update(UADD_FLOAT32 *pTuAdd_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 result;

	result = IN1 + IN2;

	/* output wrapping */
	if (result >= PI_R32)
	{
#if defined(__COMPILER_SCILAB__)
		result = fmod(result, (2*PI_R32));
#else
		result = fmodf(result, (2*PI_R32));
#endif
		if (result >= PI_R32)
		{
			result = result - (2*PI_R32);
		}
	}
	else if (result < -PI_R32)
	{
#if defined(__COMPILER_SCILAB__)
		result = fmod(result, (2*PI_R32));
#else
		result = fmodf(result, (2*PI_R32));
#endif
		if (result < -PI_R32)
		{
			result = result + (2*PI_R32);
		}
	}
	
	OUT = result;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uAdd_Float32_Init(UADD_FLOAT32 *pTuAdd_Float32)
{
    pTuAdd_Float32->ID = UADD_FLOAT32_ID;
    pTuAdd_Float32->Out = 0;
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
#if !defined(UADD_FLOAT32_ISLINKED)
void* uAdd_Float32_GetAddress(const UADD_FLOAT32* block, uint16 elementId)
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
