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
#include "Sin3Gen_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Sin3Gen_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Inputs */
#define AMPLITUDE 		(*pTSin3Gen_FiP16->A)
#define FREQUENCY 		(*pTSin3Gen_FiP16->f)

/* Outputs */
#define OUT_U 			(pTSin3Gen_FiP16->u)
#define OUT_V 			(pTSin3Gen_FiP16->v)
#define OUT_W 			(pTSin3Gen_FiP16->w)

/* Parameter */
#define OFFSET 			(pTSin3Gen_FiP16->offset)
#define DELTA_PHI 		(pTSin3Gen_FiP16->delta_phi)

/* Variables */
#define PHI 	 		(pTSin3Gen_FiP16->phi)

/* Constants */
#define TWOPITHIRDINT16	0x5555				/* 2*Pi/3 in Q15 format */
#define ROUNDING		0x4000				/* value used for rounding */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin3Gen_FiP16_Update(SIN3GEN_FIP16 *pTSin3Gen_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16	sine, out1, out2, angle;
	int32	temp;

	temp  = (int32)DELTA_PHI * (int32)FREQUENCY;	/* calculate angle increment */
	temp += ROUNDING;
	PHI  += ((int16)(temp >> 15));					/* scale to 16 Bit (Q30 -> Q15) and increment angle */

	/*------------------------------------------------------------------------*/
	/* Calculation of phase U 												  */
	/*------------------------------------------------------------------------*/
	/* sine interpolation */
	LOOKUP16(Sin_Table16, PHI, sine);				/* sin(phi) */
	/* amplification */
	temp = (int32)AMPLITUDE * (int32)sine;			/* A*sin(phi) */
	temp = (temp + ROUNDING) >> 15;
	/* offset */
	temp += (int32)OFFSET;							/* A*sin(phi) + Offset*/
	/* limitation */
	LIMIT(temp, INT16_MAX);
	out1 = (int16)temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase V 												  */
	/*------------------------------------------------------------------------*/
	/* sine interpolation */
	angle = PHI - TWOPITHIRDINT16;					/* phi - 2*pi/3 */
	LOOKUP16(Sin_Table16, angle, sine);				/* sin(phi - 2*pi/3) */
	/* amplification */
	temp = (int32)AMPLITUDE * (int32)sine;			/* A*sin(phi - 2*pi/3) */
	temp = (temp + ROUNDING) >> 15;
	/* offset */
	temp += (int32)OFFSET;							/* A*sin(phi - 2*pi/3) + Offset*/
	/* limitation */
	LIMIT(temp, INT16_MAX);
	out2 = (int16)temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase W 												  */
	/*------------------------------------------------------------------------*/
	/* sine interpolation */
	angle = PHI + TWOPITHIRDINT16;					/* phi + 2*pi/3 */
	LOOKUP16(Sin_Table16, angle, sine);				/* sin(phi + 2*pi/3) */
	/* amplification */
	temp = (int32)AMPLITUDE * (int32)sine;			/* A*sin(phi + 2*pi/3) */
	temp = (temp + ROUNDING) >> 15;
	/* offset */
	temp += (int32)OFFSET;							/* A*sin(phi + 2*pi/3) + Offset*/
	/* limitation */
	LIMIT(temp, INT16_MAX);

	/*------------------------------------------------------------------------*/
	/* Assigning of (remaining) outputs										  */
	/*------------------------------------------------------------------------*/
	OUT_U = out1;
	OUT_V = out2;
	OUT_W = (int16)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sin3Gen_FiP16_Init(SIN3GEN_FIP16 *pTSin3Gen_FiP16)
{
    pTSin3Gen_FiP16->ID = SIN3GEN_FIP16_ID;
    pTSin3Gen_FiP16->u = 0;
    pTSin3Gen_FiP16->v = 0;
    pTSin3Gen_FiP16->w = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_FiP16_Load(const SIN3GEN_FIP16 *pTSin3Gen_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)4 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSin3Gen_FiP16->delta_phi & 0x00FF);
        data[1] = (uint8)((pTSin3Gen_FiP16->delta_phi >> 8) & 0x00FF);
        data[2] = (uint8)(pTSin3Gen_FiP16->offset & 0x00FF);
        data[3] = (uint8)((pTSin3Gen_FiP16->offset >> 8) & 0x00FF);
        *dataLength = (uint16)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_FiP16_Save(SIN3GEN_FIP16 *pTSin3Gen_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)4)
    {
        error = (uint8)1;
    }
    else
    {
        pTSin3Gen_FiP16->delta_phi = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTSin3Gen_FiP16->offset = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SIN3GEN_FIP16_ISLINKED)
void* Sin3Gen_FiP16_GetAddress(const SIN3GEN_FIP16* block, uint16 elementId)
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
