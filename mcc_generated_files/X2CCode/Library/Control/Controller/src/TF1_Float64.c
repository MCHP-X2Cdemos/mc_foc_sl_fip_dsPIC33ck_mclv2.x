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
/**     Description:	First order transfer function                        **/
/**						Calculation:										 **/
/**	       						 b1.z + b0							   		 **/
/** 						y = ----------- u						   		 **/
/**          					  z + a0									 **/
/**							-> y(k) = u(k).b1 + u(k-1).b0 - y(k-1).a0		 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "TF1_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF1_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF1_Float64->In)

/* Outputs */
#define OUT			(pTTF1_Float64->Out)

/* Parameter */
#define	A0			(pTTF1_Float64->a0)
#define	B0			(pTTF1_Float64->b0)
#define	B1			(pTTF1_Float64->b1)

/* Variables */
#define IN_OLD		(pTTF1_Float64->in_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF1_Float64_Update(TF1_FLOAT64 *pTTF1_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp;

	temp  = B0 * IN_OLD;	/* y = b0.u(k-1) */
	temp += (B1 * IN);		/* y = b0.u(k-1) + b1.u(k) */
	temp -= (A0 * OUT);		/* y = b0.u(k-1) + b1.u(k) - a0.y(k-1) */

	/* save values for next update call and assign output */
	IN_OLD = IN;
	OUT    = temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF1_Float64_Init(TF1_FLOAT64 *pTTF1_Float64)
{
    pTTF1_Float64->ID = TF1_FLOAT64_ID;
    pTTF1_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old input value */
     IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_Float64_Load(const TF1_FLOAT64 *pTTF1_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)24 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTTF1_Float64->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTTF1_Float64->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTTF1_Float64->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTTF1_Float64->b1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTTF1_Float64->a0)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTTF1_Float64->a0) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)24;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_Float64_Save(TF1_FLOAT64 *pTTF1_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)24)
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
        pTTF1_Float64->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTTF1_Float64->b1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTTF1_Float64->a0 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF1_FLOAT64_ISLINKED)
void* TF1_Float64_GetAddress(const TF1_FLOAT64* block, uint16 elementId)
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
