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
#include "Div_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Div_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1		(*pTDiv_FiP32->Num)		/* Numerator */
#define IN2		(*pTDiv_FiP32->Den)		/* Denominator */
			
/* Outputs */
#define OUT 	(pTDiv_FiP32->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Div_FiP32_Update(DIV_FIP32 *pTDiv_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 num = (int32)IN1;
	int32 den = (int32)IN2;
	int32 abs_num, abs_den;

	abs_num = ABS_I32(num);
	abs_den = ABS_I32(den);
		
	if(abs_num >= abs_den)	/* |y| >= |x|: result is not in -1..1 range */
	{ 
		if ((num==(int32)0) && (den==(int32)0))	/* division zero by zero */
		{
			OUT = (int32)0;
		}
		else
		{
			if (( (num>(int32)0) && (den>=(int32)0) ) || ( (num<(int32)0) && (den<(int32)0) ))	
			{
				OUT = INT32_MAX;	/* positive saturation */
			}
			else
			{
				OUT = -INT32_MAX;	/* negative saturation */
			}
		}
	}
	else					/* result is in -1..1 range */
	{
		OUT = (int32)((((int64)num) << 31) / den);
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Div_FiP32_Init(DIV_FIP32 *pTDiv_FiP32)
{
    pTDiv_FiP32->ID = DIV_FIP32_ID;
    pTDiv_FiP32->Out = 0;
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
#if !defined(DIV_FIP32_ISLINKED)
void* Div_FiP32_GetAddress(const DIV_FIP32* block, uint16 elementId)
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
