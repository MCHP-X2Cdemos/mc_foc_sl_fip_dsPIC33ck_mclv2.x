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
/* Description:	  Conversion from floating point to fixed point.		      */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#include "Real2Int_Float64_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Real2Int_Float64_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Input */
#define IN		(*pTReal2Int_Float64_FiP16->In)

/* Output */
#define OUT		(pTReal2Int_Float64_FiP16->Out)

/* Parameter */
#define SCALE	(pTReal2Int_Float64_FiP16->scale)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Real2Int_Float64_FiP16_Update(REAL2INT_FLOAT64_FIP16 *pTReal2Int_Float64_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 tmp;

	tmp = (int32)(IN * SCALE);
	LIMIT(tmp, INT16_MAX);

	OUT = (int16)tmp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Real2Int_Float64_FiP16_Init(REAL2INT_FLOAT64_FIP16 *pTReal2Int_Float64_FiP16)
{
    pTReal2Int_Float64_FiP16->ID = REAL2INT_FLOAT64_FIP16_ID;
    pTReal2Int_Float64_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Real2Int_Float64_FiP16_Load(const REAL2INT_FLOAT64_FIP16 *pTReal2Int_Float64_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTReal2Int_Float64_FiP16->scale) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Real2Int_Float64_FiP16_Save(REAL2INT_FLOAT64_FIP16 *pTReal2Int_Float64_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)8)
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
        pTReal2Int_Float64_FiP16->scale = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(REAL2INT_FLOAT64_FIP16_ISLINKED)
void* Real2Int_Float64_FiP16_GetAddress(const REAL2INT_FLOAT64_FIP16* block, uint16 elementId)
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
