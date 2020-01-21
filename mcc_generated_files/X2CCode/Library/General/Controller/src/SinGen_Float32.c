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
/*      Description:    Sine Wave Generation
 *                     Calculation:
 *							u =  A*sin(phi(t)+Phase) + Offset
 *							phi(t) = phi(t-1) + 2*pi*Ts*f
 */
/* USERCODE-END:Description                                                                                           */
#include "SinGen_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(SinGen_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Input */
#define AMPLITUDE	(*pTSinGen_Float32->A)
#define FREQUENCY	(*pTSinGen_Float32->f)

/* Output */
#define OUT		 	(pTSinGen_Float32->u)

/* Parameter */
#define OFFSET		(pTSinGen_Float32->offset)
#define PHASE		(pTSinGen_Float32->phase)
#define DELTA_PHI	(pTSinGen_Float32->delta_phi)

/* Variables */
#define PHI 	 	(pTSinGen_Float32->phi)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void SinGen_Float32_Update(SINGEN_FLOAT32 *pTSinGen_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32	sine, angle;
	float32	temp;

	temp = DELTA_PHI * FREQUENCY;			/* calculate angle increment */
	PHI += temp;							/* increment angle */

	/* angle limitation to -pi..+pi range */
	if (PHI >= PI_R32)
	{
		PHI = PHI - (2 * PI_R32);
	}
	else if (PHI < -PI_R32)
	{
		PHI = PHI + (2 * PI_R32);
	}

	/* sine calculation */
	angle = PHI + PHASE;					/* phi+phase (though angle might exceeds -pi..pi range, sine will be computed correctly) */
	sine  = (float32)sinf((float64)angle);	/* sin(phi+phase) */

	/* amplification */
	temp = AMPLITUDE * sine;				/* A*sin(phi+phase) */

	/* offset */
	temp += OFFSET;							/* A*sin(phi+phase) + Offset */

	OUT = temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void SinGen_Float32_Init(SINGEN_FLOAT32 *pTSinGen_Float32)
{
    pTSinGen_Float32->ID = SINGEN_FLOAT32_ID;
    pTSinGen_Float32->u = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
  	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_Float32_Load(const SINGEN_FLOAT32 *pTSinGen_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTSinGen_Float32->delta_phi)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTSinGen_Float32->delta_phi) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTSinGen_Float32->delta_phi) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTSinGen_Float32->delta_phi) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTSinGen_Float32->phase)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTSinGen_Float32->phase) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTSinGen_Float32->phase) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTSinGen_Float32->phase) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTSinGen_Float32->offset)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTSinGen_Float32->offset) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTSinGen_Float32->offset) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTSinGen_Float32->offset) >> 24) & 0x000000FF);
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_Float32_Save(SINGEN_FLOAT32 *pTSinGen_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTSinGen_Float32->delta_phi = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTSinGen_Float32->phase = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTSinGen_Float32->offset = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SINGEN_FLOAT32_ISLINKED)
void* SinGen_Float32_GetAddress(const SINGEN_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->A;
            break;
        case 2:
            addr = (void*)block->f;
            break;
        case 3:
            addr = (void*)&block->u;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
