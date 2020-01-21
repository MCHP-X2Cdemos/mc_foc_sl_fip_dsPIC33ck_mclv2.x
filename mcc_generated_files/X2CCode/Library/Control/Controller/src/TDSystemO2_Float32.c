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
#include "TDSystemO2_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO2_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs*/
#define IN1 	(*pTTDSystemO2_Float32->In1)
#define IN2 	(*pTTDSystemO2_Float32->In2)

/* Outputs*/
#define OUT1	(pTTDSystemO2_Float32->Out1)
#define OUT2	(pTTDSystemO2_Float32->Out2)

/* Matrices */
#define A11		(pTTDSystemO2_Float32->a11)
#define A12		(pTTDSystemO2_Float32->a12)
#define A21		(pTTDSystemO2_Float32->a21)
#define A22		(pTTDSystemO2_Float32->a22)
#define B11		(pTTDSystemO2_Float32->b11)
#define B12		(pTTDSystemO2_Float32->b12)
#define B21		(pTTDSystemO2_Float32->b21)
#define B22		(pTTDSystemO2_Float32->b22)

/* States */
#define X1		(pTTDSystemO2_Float32->x1)
#define X2		(pTTDSystemO2_Float32->x2)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO2_Float32_Update(TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 temp, state1;


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
void TDSystemO2_Float32_Init(TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32)
{
    pTTDSystemO2_Float32->ID = TDSYSTEMO2_FLOAT32_ID;
    pTTDSystemO2_Float32->Out1 = 0;
    pTTDSystemO2_Float32->Out2 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset states */
     X1 = 0;
     X2 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_Float32_Load(const TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)32 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a11)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a11) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a11) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a11) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a12)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a12) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a12) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a12) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a21)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a21) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a21) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a21) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a22)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a22) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a22) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->a22) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b11)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b11) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b11) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b11) >> 24) & 0x000000FF);
        data[20] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b12)) & 0x000000FF);
        data[21] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b12) >> 8) & 0x000000FF);
        data[22] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b12) >> 16) & 0x000000FF);
        data[23] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b12) >> 24) & 0x000000FF);
        data[24] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b21)) & 0x000000FF);
        data[25] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b21) >> 8) & 0x000000FF);
        data[26] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b21) >> 16) & 0x000000FF);
        data[27] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b21) >> 24) & 0x000000FF);
        data[28] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b22)) & 0x000000FF);
        data[29] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b22) >> 8) & 0x000000FF);
        data[30] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b22) >> 16) & 0x000000FF);
        data[31] = (uint8)((*(uint32*)&(pTTDSystemO2_Float32->b22) >> 24) & 0x000000FF);
        *dataLength = (uint16)32;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_Float32_Save(TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)32)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTTDSystemO2_Float32->a11 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTTDSystemO2_Float32->a12 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTTDSystemO2_Float32->a21 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTTDSystemO2_Float32->a22 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTTDSystemO2_Float32->b11 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[20] + \
            ((uint32)data[21] << 8) + ((uint32)data[22] << 16) + \
            ((uint32)data[23] << 24);
        pTTDSystemO2_Float32->b12 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[24] + \
            ((uint32)data[25] << 8) + ((uint32)data[26] << 16) + \
            ((uint32)data[27] << 24);
        pTTDSystemO2_Float32->b21 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[28] + \
            ((uint32)data[29] << 8) + ((uint32)data[30] << 16) + \
            ((uint32)data[31] << 24);
        pTTDSystemO2_Float32->b22 = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO2_FLOAT32_ISLINKED)
void* TDSystemO2_Float32_GetAddress(const TDSYSTEMO2_FLOAT32* block, uint16 elementId)
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
