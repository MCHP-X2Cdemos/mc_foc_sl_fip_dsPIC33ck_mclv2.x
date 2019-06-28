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
#include "Div_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Div_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1		(*pTDiv_FiP8->Num)		/* Numerator */
#define IN2		(*pTDiv_FiP8->Den)		/* Denominator */
			
/* Outputs */
#define OUT 	(pTDiv_FiP8->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Div_FiP8_Update(DIV_FIP8 *pTDiv_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8 num = (int8)IN1;
	int8 den = (int8)IN2;
	int8 abs_num, abs_den;

	abs_num = ABS_I8(num);
	abs_den = ABS_I8(den);
		
	if(abs_num >= abs_den)	/* |y| >= |x|: result is not in -1..1 range */
	{ 
		if ((num==(int8)0) && (den==(int8)0))	/* division zero by zero */
		{
			OUT = (int8)0;
		}
		else
		{
			if (( (num>(int8)0) && (den>=(int8)0) ) || ( (num<(int8)0) && (den<(int8)0) ))	
			{
				OUT = INT8_MAX;	/* positive saturation */
			}
			else
			{
				OUT = -INT8_MAX;	/* negative saturation */
			}
		}
	}
	else					/* result is in -1..1 range */
	{
		OUT = (int8)((((int16)num) << 7) / den);
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Div_FiP8_Init(DIV_FIP8 *pTDiv_FiP8)
{
    pTDiv_FiP8->ID = DIV_FIP8_ID;
    pTDiv_FiP8->Out = 0;
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
#if !defined(DIV_FIP8_ISLINKED)
void* Div_FiP8_GetAddress(const DIV_FIP8* block, uint16 elementId)
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
