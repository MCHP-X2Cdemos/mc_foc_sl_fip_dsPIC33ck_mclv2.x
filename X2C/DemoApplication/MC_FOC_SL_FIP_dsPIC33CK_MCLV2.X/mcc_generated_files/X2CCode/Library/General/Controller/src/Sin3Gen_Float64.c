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
/*     Description:    Sine Wave Generation for 3 Phase System
 *                     Calculation:
 *							u =  A*sin(phi(t)) + Offset
 *							v =  A*sin(phi(t) - 2*pi/3) + Offset
 *							w =  A*sin(phi(t) + 2*pi/3) + Offset
 *							phi(t) = phi(t-1) + 2*pi*Ts*f
 */
/* USERCODE-END:Description                                                                                           */
#include "Sin3Gen_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Sin3Gen_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define AMPLITUDE 		(*pTSin3Gen_Float64->A)
#define FREQUENCY 		(*pTSin3Gen_Float64->f)

/* Outputs */
#define OUT_U			(pTSin3Gen_Float64->u)
#define OUT_V			(pTSin3Gen_Float64->v)
#define OUT_W			(pTSin3Gen_Float64->w)

/* Parameter */
#define OFFSET 			(pTSin3Gen_Float64->offset)
#define DELTA_PHI 		(pTSin3Gen_Float64->delta_phi)

/* Variables */
#define PHI 	 		(pTSin3Gen_Float64->phi)

/* Constants */
#define TWOPITHIRD		(PI_R64 * (float64)2.0/(float64)3.0)				/* 2*Pi/3 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin3Gen_Float64_Update(SIN3GEN_FLOAT64 *pTSin3Gen_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64	sine, out1, out2, angle;
	float64	temp;

	temp = DELTA_PHI * FREQUENCY;			/* calculate angle increment */
	PHI += temp;							/* increment angle */

	/* angle limitation to -pi..+pi range */
	if (PHI >= PI_R64)
	{
		PHI = PHI - (2 * PI_R64);
	}
	else if (PHI < -PI_R64)
	{
		PHI = PHI + (2 * PI_R64);
	}

	/*------------------------------------------------------------------------*/
	/* Calculation of phase U 												  */
	/*------------------------------------------------------------------------*/
	/* sine calculation */
	sine = sin(PHI);						/* sin(phi) */

	/* amplification */
	temp = AMPLITUDE * sine;				/* A*sin(phi) */

	/* offset */
	temp += OFFSET;							/* A*sin(phi) + Offset */

	out1 = temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase V 												  */
	/*------------------------------------------------------------------------*/
	/* sine interpolation */
	angle = PHI - TWOPITHIRD;				/* phi - 2*pi/3 (though angle might exceeds -pi..pi range, sine will be computed correctly) */
	sine = sin(angle);						/* sin(phi - 2*pi/3) */

	/* amplification */
	temp = AMPLITUDE * sine;				/* A*sin(phi - 2*pi/3) */

	/* offset */
	temp += OFFSET;							/* A*sin(phi - 2*pi/3) + Offset*/

	out2 = temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase W 												  */
	/*------------------------------------------------------------------------*/
	/* sine interpolation */
	angle = PHI + TWOPITHIRD;				/* phi + 2*pi/3 (though angle might exceeds -pi..pi range, sine will be computed correctly) */
	sine = sin(angle);						/* sin(phi + 2*pi/3) */

	/* amplification */
	temp = AMPLITUDE * sine;				/* A*sin(phi + 2*pi/3) */

	/* offset */
	temp += OFFSET;							/* A*sin(phi + 2*pi/3) + Offset*/

	/*------------------------------------------------------------------------*/
	/* Assigning of outputs													  */
	/*------------------------------------------------------------------------*/
	OUT_U = out1;
	OUT_V = out2;
	OUT_W = temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sin3Gen_Float64_Init(SIN3GEN_FLOAT64 *pTSin3Gen_Float64)
{
    pTSin3Gen_Float64->ID = SIN3GEN_FLOAT64_ID;
    pTSin3Gen_Float64->u = 0;
    pTSin3Gen_Float64->v = 0;
    pTSin3Gen_Float64->w = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
  	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_Float64_Load(const SIN3GEN_FLOAT64 *pTSin3Gen_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)16 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->delta_phi) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTSin3Gen_Float64->offset) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_Float64_Save(SIN3GEN_FLOAT64 *pTSin3Gen_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint64 tmp64;

    if (dataLength != (uint16)16)
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
        pTSin3Gen_Float64->delta_phi = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTSin3Gen_Float64->offset = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SIN3GEN_FLOAT64_ISLINKED)
void* Sin3Gen_Float64_GetAddress(const SIN3GEN_FLOAT64* block, uint16 elementId)
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
        case 4:
            addr = (void*)&block->v;
            break;
        case 5:
            addr = (void*)&block->w;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
