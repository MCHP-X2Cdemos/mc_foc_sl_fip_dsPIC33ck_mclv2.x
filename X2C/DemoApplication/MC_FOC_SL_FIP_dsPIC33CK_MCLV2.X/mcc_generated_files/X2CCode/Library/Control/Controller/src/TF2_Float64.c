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
/**     Description:	Second order transfer function                      										 **/
/**						Calculation:																				 **/
/**	       						 b2.z^2 + b1.z + b0					   												 **/
/** 						y = ------------------ u				   												 **/
/**          					  z^2 + a1.z + a0																	 **/
/**							-> y(k) = u(k).b2 + u(k-1).b1 + u(k-2).b0												 **/
/**									- y(k-1).a1 - y(k-2).a0															 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TF2_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF2_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF2_Float64->In)

/* Outputs */
#define OUT			(pTTF2_Float64->Out)

/* Parameter */
#define	A0			(pTTF2_Float64->a0)
#define	A1			(pTTF2_Float64->a1)
#define	B0			(pTTF2_Float64->b0)
#define	B1			(pTTF2_Float64->b1)
#define	B2			(pTTF2_Float64->b2)

/* Variables */
#define IN_OLD		(pTTF2_Float64->in_old)
#define IN_VERYOLD	(pTTF2_Float64->in_veryold)
#define OUT_OLD		(pTTF2_Float64->out_old)
#define OUT_VERYOLD	(pTTF2_Float64->out_veryold)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF2_Float64_Update(TF2_FLOAT64 *pTTF2_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 temp, temp1;

	temp  =  B0 * IN_VERYOLD;	/* y(k) = b0.u(k-2) */
	temp += (B1 * IN_OLD);		/* y(k) = b0.u(k-2) + b1.u(k-1) */
	temp += (B2 * IN);			/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) */

	temp1  =  A0 * OUT_VERYOLD;	/* y1(k) = a0.y(k-2) */
	temp1 += (A1 * OUT_OLD);	/* y1(k) = a0.y(k-2) + a1.y(k-1) */

	temp   = temp - temp1;		/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) - a0.y(k-2) - a1.y(k-1) */


	/* save values for next update call and assign output */
	OUT         = temp;
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = OUT;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF2_Float64_Init(TF2_FLOAT64 *pTTF2_Float64)
{
    pTTF2_Float64->ID = TF2_FLOAT64_ID;
    pTTF2_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old values */
     IN_OLD      = 0;
     IN_VERYOLD  = 0;
     OUT_OLD     = 0;
     OUT_VERYOLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_Float64_Load(const TF2_FLOAT64 *pTTF2_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)40 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTTF2_Float64->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTTF2_Float64->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTTF2_Float64->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTTF2_Float64->b1) >> 56) & 0x00000000000000FF);
        data[16] = (uint8)((*(uint64*)&(pTTF2_Float64->b2)) & 0x00000000000000FF);
        data[17] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 8) & 0x00000000000000FF);
        data[18] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 16) & 0x00000000000000FF);
        data[19] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 24) & 0x00000000000000FF);
        data[20] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 32) & 0x00000000000000FF);
        data[21] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 40) & 0x00000000000000FF);
        data[22] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 48) & 0x00000000000000FF);
        data[23] = (uint8)((*(uint64*)&(pTTF2_Float64->b2) >> 56) & 0x00000000000000FF);
        data[24] = (uint8)((*(uint64*)&(pTTF2_Float64->a0)) & 0x00000000000000FF);
        data[25] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 8) & 0x00000000000000FF);
        data[26] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 16) & 0x00000000000000FF);
        data[27] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 24) & 0x00000000000000FF);
        data[28] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 32) & 0x00000000000000FF);
        data[29] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 40) & 0x00000000000000FF);
        data[30] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 48) & 0x00000000000000FF);
        data[31] = (uint8)((*(uint64*)&(pTTF2_Float64->a0) >> 56) & 0x00000000000000FF);
        data[32] = (uint8)((*(uint64*)&(pTTF2_Float64->a1)) & 0x00000000000000FF);
        data[33] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 8) & 0x00000000000000FF);
        data[34] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 16) & 0x00000000000000FF);
        data[35] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 24) & 0x00000000000000FF);
        data[36] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 32) & 0x00000000000000FF);
        data[37] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 40) & 0x00000000000000FF);
        data[38] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 48) & 0x00000000000000FF);
        data[39] = (uint8)((*(uint64*)&(pTTF2_Float64->a1) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)40;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_Float64_Save(TF2_FLOAT64 *pTTF2_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)40)
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
        pTTF2_Float64->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTTF2_Float64->b1 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[16] + \
            ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
            ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
            ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
            ((uint64)data[23] << 56);
        pTTF2_Float64->b2 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[24] + \
            ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
            ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
            ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
            ((uint64)data[31] << 56);
        pTTF2_Float64->a0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[32] + \
            ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
            ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
            ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
            ((uint64)data[39] << 56);
        pTTF2_Float64->a1 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF2_FLOAT64_ISLINKED)
void* TF2_Float64_GetAddress(const TF2_FLOAT64* block, uint16 elementId)
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
