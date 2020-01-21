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
/**     Description: 1st Order Time Discrete System                         										 **/
/**					 Calculation:																					 **/
/**						x(k+1) = a11*x(k) + b11*u(k)																 **/
/**						y(k)   = c11*x(k) + d11*u(k)																 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TDSystemO1_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO1_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 		(*pTTDSystemO1_Float64->In)

/* Outputs */
#define OUT		(pTTDSystemO1_Float64->Out)

/* Matrices */
#define A11		(pTTDSystemO1_Float64->a11)
#define B11		(pTTDSystemO1_Float64->b11)
#define C11		(pTTDSystemO1_Float64->c11)
#define D11 	(pTTDSystemO1_Float64->d11)


/* State */
#define X1 		(pTTDSystemO1_Float64->x1)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO1_Float64_Update(TDSYSTEMO1_FLOAT64 *pTTDSystemO1_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp;

	/* Calculation of output (with old state) */
	temp  =  C11 * X1; 		/* y = c11*x1 */
	temp += (D11 * IN);		/* y = c11*x1 + d11*u */
	OUT   = temp;			/* assign output  */

	/* Calculation of new state */
	temp  =  A11 * X1;		/* x1 = a11*x1 */
	temp += (B11 * IN);		/* x1 = a11*x1 + b11*u */
	X1    = temp;			/* assign state */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO1_Float64_Init(TDSYSTEMO1_FLOAT64 *pTTDSystemO1_Float64)
{
    pTTDSystemO1_Float64->ID = TDSYSTEMO1_FLOAT64_ID;
    pTTDSystemO1_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset state */
     X1 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_Float64_Load(const TDSYSTEMO1_FLOAT64 *pTTDSystemO1_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)32 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->a11) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->b11) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->c11) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTTDSystemO1_Float64->d11) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)32;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_Float64_Save(TDSYSTEMO1_FLOAT64 *pTTDSystemO1_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)32)
    {
        error = (uint8)1;
    }
    else
    {
        tmp64 = (uint64)data[0] + \
            ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
            ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
            ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
            ((uint64)data[7] << 56);
        pTTDSystemO1_Float64->a11 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTTDSystemO1_Float64->b11 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTTDSystemO1_Float64->c11 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTTDSystemO1_Float64->d11 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO1_FLOAT64_ISLINKED)
void* TDSystemO1_Float64_GetAddress(const TDSYSTEMO1_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
