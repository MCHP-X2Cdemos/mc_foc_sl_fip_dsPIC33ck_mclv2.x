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
/**     Description: 2nd Order Time Discrete System with 2 in- and outputs. 										 **/
/**					 Calculation:																					 **/
/**						x(k+1) = A*x(k) + B*u(k)																	 **/
/**						y(k)   =   x(k)																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TDSystemO2_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO2_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs*/
#define IN1 	(*pTTDSystemO2_Float64->In1)
#define IN2 	(*pTTDSystemO2_Float64->In2)

/* Outputs*/
#define OUT1	(pTTDSystemO2_Float64->Out1)
#define OUT2	(pTTDSystemO2_Float64->Out2)

/* Matrices */
#define A11		(pTTDSystemO2_Float64->a11)
#define A12		(pTTDSystemO2_Float64->a12)
#define A21		(pTTDSystemO2_Float64->a21)
#define A22		(pTTDSystemO2_Float64->a22)
#define B11		(pTTDSystemO2_Float64->b11)
#define B12		(pTTDSystemO2_Float64->b12)
#define B21		(pTTDSystemO2_Float64->b21)
#define B22		(pTTDSystemO2_Float64->b22)

/* States */
#define X1		(pTTDSystemO2_Float64->x1)
#define X2		(pTTDSystemO2_Float64->x2)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO2_Float64_Update(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp, state1;


	/* Calculation of output (= old state) */
	OUT1 = X1;
	OUT2 = X2;

	/* Calculation of new state1 */
	temp  =  A11 * X1;		/* x1 = a11*x1 */
	temp += (A12 * X2);		/* x1 = a11*x1 + a12*x2 */
	temp += (B11 * IN1);	/* x1 = a11*x1 + a12*x2 + b11*u1 */
	temp += (B12 * IN2);	/* x1 = a11*x1 + a12*x2 + b11*u1 + b12*u2 */
	state1 = temp;

	/* Calculation of new state2 */
	temp  =  A21 * X1;		/* x2 = a21*x1 */
	temp += (A22 * X2);		/* x2 = a21*x1 + a22*x2 */
	temp += (B21 * IN1);	/* x2 = a21*x1 + a22*x2 + b21*u1 */
	temp += (B22 * IN2);	/* x2 = a21*x1 + a22*x2 + b21*u1 + b22*u2 */

	/* assign states */
	X1 = state1;
	X2 = temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO2_Float64_Init(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64)
{
    pTTDSystemO2_Float64->ID = TDSYSTEMO2_FLOAT64_ID;
    pTTDSystemO2_Float64->Out1 = 0;
    pTTDSystemO2_Float64->Out2 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset states */
     X1 = 0;
     X2 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_Float64_Load(const TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)64 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a11) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a12) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a21) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->a22) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b11) >> 56) & 0x00000000000000FF);
        data[40] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12)) & 0x00000000000000FF);
        data[41] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 8) & 0x00000000000000FF);
        data[42] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 16) & 0x00000000000000FF);
        data[43] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 24) & 0x00000000000000FF);
        data[44] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 32) & 0x00000000000000FF);
        data[45] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 40) & 0x00000000000000FF);
        data[46] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 48) & 0x00000000000000FF);
        data[47] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b12) >> 56) & 0x00000000000000FF);
        data[48] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21)) & 0x00000000000000FF);
        data[49] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 8) & 0x00000000000000FF);
        data[50] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 16) & 0x00000000000000FF);
        data[51] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 24) & 0x00000000000000FF);
        data[52] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 32) & 0x00000000000000FF);
        data[53] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 40) & 0x00000000000000FF);
        data[54] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 48) & 0x00000000000000FF);
        data[55] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b21) >> 56) & 0x00000000000000FF);
        data[56] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22)) & 0x00000000000000FF);
        data[57] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 8) & 0x00000000000000FF);
        data[58] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 16) & 0x00000000000000FF);
        data[59] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 24) & 0x00000000000000FF);
        data[60] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 32) & 0x00000000000000FF);
        data[61] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 40) & 0x00000000000000FF);
        data[62] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 48) & 0x00000000000000FF);
        data[63] = (uint8)((*(uint64*)&(pTTDSystemO2_Float64->b22) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)64;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_Float64_Save(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)64)
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
        pTTDSystemO2_Float64->a11 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTTDSystemO2_Float64->a12 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTTDSystemO2_Float64->a21 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTTDSystemO2_Float64->a22 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        pTTDSystemO2_Float64->b11 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[40] + \
            ((uint64)data[41] << 8) + ((uint64)data[42] << 16) + \
            ((uint64)data[43] << 24) + ((uint64)data[44] << 32) + \
            ((uint64)data[45] << 40) + ((uint64)data[46] << 48) + \
            ((uint64)data[47] << 56);
        pTTDSystemO2_Float64->b12 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[48] + \
            ((uint64)data[49] << 8) + ((uint64)data[50] << 16) + \
            ((uint64)data[51] << 24) + ((uint64)data[52] << 32) + \
            ((uint64)data[53] << 40) + ((uint64)data[54] << 48) + \
            ((uint64)data[55] << 56);
        pTTDSystemO2_Float64->b21 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[56] + \
            ((uint64)data[57] << 8) + ((uint64)data[58] << 16) + \
            ((uint64)data[59] << 24) + ((uint64)data[60] << 32) + \
            ((uint64)data[61] << 40) + ((uint64)data[62] << 48) + \
            ((uint64)data[63] << 56);
        pTTDSystemO2_Float64->b22 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO2_FLOAT64_ISLINKED)
void* TDSystemO2_Float64_GetAddress(const TDSYSTEMO2_FLOAT64* block, uint16 elementId)
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
            addr = (void*)&block->Out1;
            break;
        case 4:
            addr = (void*)&block->Out2;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
