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
#include "SinGen_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(SinGen_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Input */
#define AMPLITUDE	(*pTSinGen_FiP16->A)
#define FREQUENCY	(*pTSinGen_FiP16->f)

/* Output */
#define OUT		 	(pTSinGen_FiP16->u)

/* Parameter */
#define OFFSET		(pTSinGen_FiP16->offset)
#define PHASE		(pTSinGen_FiP16->phase)
#define DELTA_PHI	(pTSinGen_FiP16->delta_phi)

/* Variables */
#define PHI			(pTSinGen_FiP16->phi)

/* Constants */
#define ROUNDING	0x4000				/* value used for rounding */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void SinGen_FiP16_Update(SINGEN_FIP16 *pTSinGen_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 	sine, angle;
	int32	temp;

	temp  = (int32)DELTA_PHI * (int32)FREQUENCY;	/* calculate angle increment */
	temp += ROUNDING;
	PHI  += ((int16)(temp >> 15));					/* scale to 16 Bit (Q30 -> Q15) and increment angle */

	/* sine interpolation */
	angle = PHI + PHASE;						/* phi+phase */
	LOOKUP16(Sin_Table16, angle, sine);			/* sin(phi+phase) */
	/* amplification */
	temp  = (int32)AMPLITUDE * (int32)sine;		/* A*sin(phi+phase) */
	temp  = (temp + ROUNDING) >> 15;			/* round and convert from Q30 to Q15 */
	/* offset */
	temp += (int32)OFFSET;						/* A*sin(phi+phase) + Offset */
	/* output limitation */
	LIMIT(temp, INT16_MAX);

	OUT = (int16)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void SinGen_FiP16_Init(SINGEN_FIP16 *pTSinGen_FiP16)
{
    pTSinGen_FiP16->ID = SINGEN_FIP16_ID;
    pTSinGen_FiP16->u = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_FiP16_Load(const SINGEN_FIP16 *pTSinGen_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)6 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSinGen_FiP16->delta_phi & 0x00FF);
        data[1] = (uint8)((pTSinGen_FiP16->delta_phi >> 8) & 0x00FF);
        data[2] = (uint8)(pTSinGen_FiP16->phase & 0x00FF);
        data[3] = (uint8)((pTSinGen_FiP16->phase >> 8) & 0x00FF);
        data[4] = (uint8)(pTSinGen_FiP16->offset & 0x00FF);
        data[5] = (uint8)((pTSinGen_FiP16->offset >> 8) & 0x00FF);
        *dataLength = (uint16)6;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_FiP16_Save(SINGEN_FIP16 *pTSinGen_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)6)
    {
        error = (uint8)1;
    }
    else
    {
        pTSinGen_FiP16->delta_phi = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTSinGen_FiP16->phase = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTSinGen_FiP16->offset = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SINGEN_FIP16_ISLINKED)
void* SinGen_FiP16_GetAddress(const SINGEN_FIP16* block, uint16 elementId)
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
