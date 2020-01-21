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
/* Description: 															  */
/*		Passing through of input signal selected by the select inport:		  */
/*		  Select = 0 (DSP): Out = In0										  */
/*		  Select = 1 (DSP): Out = In1										  */
/*  	  ...																  */
/*  	  Select = 7 (DSP): Out = In7										  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#include "Selector_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Selector_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN0 			(*pTSelector_Float32->In0)
#define IN1 			(*pTSelector_Float32->In1)
#define IN2 			(*pTSelector_Float32->In2)
#define IN3 			(*pTSelector_Float32->In3)
#define IN4 			(*pTSelector_Float32->In4)
#define IN5 			(*pTSelector_Float32->In5)
#define IN6 			(*pTSelector_Float32->In6)
#define IN7 			(*pTSelector_Float32->In7)
#define SELECT 			(*pTSelector_Float32->Select)

/* Outputs */
#define OUT 			(pTSelector_Float32->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Selector_Float32_Update(SELECTOR_FLOAT32 *pTSelector_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	OUT = **(&pTSelector_Float32->In0 + SELECT);

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Selector_Float32_Init(SELECTOR_FLOAT32 *pTSelector_Float32)
{
    pTSelector_Float32->ID = SELECTOR_FLOAT32_ID;
    pTSelector_Float32->Out = 0;
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
#if !defined(SELECTOR_FLOAT32_ISLINKED)
void* Selector_Float32_GetAddress(const SELECTOR_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In0;
            break;
        case 2:
            addr = (void*)block->In1;
            break;
        case 3:
            addr = (void*)block->In2;
            break;
        case 4:
            addr = (void*)block->In3;
            break;
        case 5:
            addr = (void*)block->In4;
            break;
        case 6:
            addr = (void*)block->In5;
            break;
        case 7:
            addr = (void*)block->In6;
            break;
        case 8:
            addr = (void*)block->In7;
            break;
        case 9:
            addr = (void*)block->Select;
            break;
        case 10:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
