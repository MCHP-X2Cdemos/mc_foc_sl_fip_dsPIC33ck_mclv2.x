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
#include "TF2_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF2_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF2_Float32->In)

/* Outputs */
#define OUT			(pTTF2_Float32->Out)

/* Parameter */
#define	A0			(pTTF2_Float32->a0)
#define	A1			(pTTF2_Float32->a1)
#define	B0			(pTTF2_Float32->b0)
#define	B1			(pTTF2_Float32->b1)
#define	B2			(pTTF2_Float32->b2)

/* Variables */
#define IN_OLD		(pTTF2_Float32->in_old)
#define IN_VERYOLD	(pTTF2_Float32->in_veryold)
#define OUT_OLD		(pTTF2_Float32->out_old)
#define OUT_VERYOLD	(pTTF2_Float32->out_veryold)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF2_Float32_Update(TF2_FLOAT32 *pTTF2_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 temp, temp1;

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
void TF2_Float32_Init(TF2_FLOAT32 *pTTF2_Float32)
{
    pTTF2_Float32->ID = TF2_FLOAT32_ID;
    pTTF2_Float32->Out = 0;
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
uint8 TF2_Float32_Load(const TF2_FLOAT32 *pTTF2_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)20 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTTF2_Float32->b0)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTTF2_Float32->b0) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTTF2_Float32->b0) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTTF2_Float32->b0) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTTF2_Float32->b1)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTTF2_Float32->b1) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTTF2_Float32->b1) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTTF2_Float32->b1) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTTF2_Float32->b2)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTTF2_Float32->b2) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTTF2_Float32->b2) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTTF2_Float32->b2) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTTF2_Float32->a0)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTTF2_Float32->a0) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTTF2_Float32->a0) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTTF2_Float32->a0) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTTF2_Float32->a1)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTTF2_Float32->a1) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTTF2_Float32->a1) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTTF2_Float32->a1) >> 24) & 0x000000FF);
        *dataLength = (uint16)20;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_Float32_Save(TF2_FLOAT32 *pTTF2_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)20)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTTF2_Float32->b0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTTF2_Float32->b1 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTTF2_Float32->b2 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTTF2_Float32->a0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTTF2_Float32->a1 = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF2_FLOAT32_ISLINKED)
void* TF2_Float32_GetAddress(const TF2_FLOAT32* block, uint16 elementId)
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
