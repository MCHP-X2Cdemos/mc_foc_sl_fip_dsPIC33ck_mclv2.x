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
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "Int2Real_Bool_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Int2Real_Bool_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Input */
#define IN		(*pTInt2Real_Bool_Float64->In)

/* Output */
#define OUT		(pTInt2Real_Bool_Float64->Out)

/* Parameter */
#define SCALE	(pTInt2Real_Bool_Float64->scale)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Int2Real_Bool_Float64_Update(INT2REAL_BOOL_FLOAT64 *pTInt2Real_Bool_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	OUT = (float64)IN * SCALE;

	/* Alternative */
//	if (IN)
//	{
//		OUT = SCALE;
//	}
//	else
//	{
//		OUT = 0.0;
//	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Int2Real_Bool_Float64_Init(INT2REAL_BOOL_FLOAT64 *pTInt2Real_Bool_Float64)
{
    pTInt2Real_Bool_Float64->ID = INT2REAL_BOOL_FLOAT64_ID;
    pTInt2Real_Bool_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Int2Real_Bool_Float64_Load(const INT2REAL_BOOL_FLOAT64 *pTInt2Real_Bool_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTInt2Real_Bool_Float64->scale) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Int2Real_Bool_Float64_Save(INT2REAL_BOOL_FLOAT64 *pTInt2Real_Bool_Float64, const uint8 data[], uint16 dataLength)
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
        pTInt2Real_Bool_Float64->scale = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(INT2REAL_BOOL_FLOAT64_ISLINKED)
void* Int2Real_Bool_Float64_GetAddress(const INT2REAL_BOOL_FLOAT64* block, uint16 elementId)
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
