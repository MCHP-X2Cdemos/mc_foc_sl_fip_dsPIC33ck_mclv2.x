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
/**     Description:    First order proportional element with adjustable cut-off frequency							 **/
/**						Calculation:																				 **/
/**	       						  b0							   													 **/
/** 						y = ------ u						   		 											 **/
/**          					z + a0									 											 **/
/**							-> y(k) = u(k-1).b0 - y(k-1).a0        													 **/
/**								with a0 = -exp(-2*pi*Ts*fc)															 **/
/**								and  b0 = V*(1 - exp(-2*pi*Ts*fc))													 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "AdaptivePT1_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AdaptivePT1_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

#define IN			(*pTAdaptivePT1_Float32->In)
#define F_C			(*pTAdaptivePT1_Float32->fc)

/* Outputs */
#define OUT			(pTAdaptivePT1_Float32->Out)

/* Parameter */
#define	W_SCALE		(pTAdaptivePT1_Float32->w_scale)	/* Calculation base for wc: -2*pi*Ts*fmax */
#define	GAIN		(pTAdaptivePT1_Float32->gain)		/* Gain */

/* Variables */
#define IN_OLD		(pTAdaptivePT1_Float32->in_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AdaptivePT1_Float32_Update(ADAPTIVEPT1_FLOAT32 *pTAdaptivePT1_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 temp, temp_exp;


	temp = F_C * W_SCALE;		/* -2*pi*Ts*fc */
	temp_exp = exp(temp);		/* exp(-2*pi*Ts*fc) */

	temp  = 1 - temp_exp;		/* 1 - exp(-wc*Ts) */
	temp  = (temp * GAIN);		/* V*(1-exp(-wc*Ts) */
	temp  = (temp * IN_OLD);	/* u(k-1)*V*(1-exp(-wc*Ts) */

	temp += (temp_exp * OUT);	/* y(k-1)*exp(-wc*Ts) + u(k-1)*V*(1-exp(-wc*Ts)*/

	OUT    = temp;				/* assign output */
	IN_OLD = IN;				/* save input for next cycle */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void AdaptivePT1_Float32_Init(ADAPTIVEPT1_FLOAT32 *pTAdaptivePT1_Float32)
{
    pTAdaptivePT1_Float32->ID = ADAPTIVEPT1_FLOAT32_ID;
    pTAdaptivePT1_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old input value */
     IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptivePT1_Float32_Load(const ADAPTIVEPT1_FLOAT32 *pTAdaptivePT1_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->w_scale)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->w_scale) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->w_scale) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->w_scale) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->gain)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->gain) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->gain) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTAdaptivePT1_Float32->gain) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AdaptivePT1_Float32_Save(ADAPTIVEPT1_FLOAT32 *pTAdaptivePT1_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTAdaptivePT1_Float32->w_scale = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTAdaptivePT1_Float32->gain = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(ADAPTIVEPT1_FLOAT32_ISLINKED)
void* AdaptivePT1_Float32_GetAddress(const ADAPTIVEPT1_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->fc;
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
