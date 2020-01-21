/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description: Division of input Num by input Den																 **/
/**                     Calculation:                                     										     **/
/**							out = Num / Den								 											 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "Div_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Div_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1		(*pTDiv_FiP16->Num)		/* Numerator */
#define IN2		(*pTDiv_FiP16->Den)		/* Denominator */
			
/* Outputs */
#define OUT 	(pTDiv_FiP16->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Div_FiP16_Update(DIV_FIP16 *pTDiv_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 num = (int16)IN1;
	int16 den = (int16)IN2;
	int16 abs_num, abs_den;

	abs_num = ABS_I16(num);
	abs_den = ABS_I16(den);
		
	if(abs_num >= abs_den)	/* |y| >= |x|: result is not in -1..1 range */
	{ 
		if ((num==(int16)0) && (den==(int16)0))	/* division zero by zero */
		{
			OUT = (int16)0;
		}
		else
		{
			if (( (num>(int16)0) && (den>=(int16)0) ) || ( (num<(int16)0) && (den<(int16)0) ))	
			{
				OUT = INT16_MAX;	/* positive saturation */
			}
			else
			{
				OUT = -INT16_MAX;	/* negative saturation */
			}
		}
	}
	else								/* result is in -1..1 range */
	{
#if defined(__XC16__)
		OUT = __builtin_divsd((((int32)num) << 15), den);
#else
        OUT = (int16)((((int32)num) << 15) / den);
#endif
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Div_FiP16_Init(DIV_FIP16 *pTDiv_FiP16)
{
    pTDiv_FiP16->ID = DIV_FIP16_ID;
    pTDiv_FiP16->Out = 0;
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
#if !defined(DIV_FIP16_ISLINKED)
void* Div_FiP16_GetAddress(const DIV_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->Num;
            break;
        case 2:
            addr = (void*)block->Den;
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
