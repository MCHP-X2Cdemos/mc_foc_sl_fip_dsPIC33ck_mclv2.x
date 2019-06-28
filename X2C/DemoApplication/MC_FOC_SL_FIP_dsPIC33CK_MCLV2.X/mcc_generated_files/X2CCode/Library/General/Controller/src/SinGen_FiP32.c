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
#include "SinGen_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(SinGen_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Input */
#define AMPLITUDE	(*pTSinGen_FiP32->A)
#define FREQUENCY	(*pTSinGen_FiP32->f)

/* Output */
#define OUT		 	(pTSinGen_FiP32->u)

/* Parameter */
#define OFFSET		(pTSinGen_FiP32->offset)
#define PHASE		(pTSinGen_FiP32->phase)
#define DELTA_PHI	(pTSinGen_FiP32->delta_phi)

/* Variables */
#define PHI 	 	(pTSinGen_FiP32->phi)

/* Constants */
#define ROUNDING	0x40000000			/* value used for rounding */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void SinGen_FiP32_Update(SINGEN_FIP32 *pTSinGen_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32	sine, angle;
	int64	temp;

	temp = (int64)DELTA_PHI * (int64)FREQUENCY;	/* calculate angle increment */
	temp += ROUNDING;
	PHI += ((int32)(temp >> 31));				/* scale to 32 Bit (Q62 -> Q31) and increment angle */

	/* sine interpolation */
	angle = PHI + PHASE;						/* phi+phase */
	LOOKUP32(Sin_Table32, angle, sine);			/* sin(phi+phase) */
	/* amplification */
	temp = (int64)AMPLITUDE * (int64)sine;		/* A*sin(phi+phase) */
	temp = (temp + ROUNDING) >> 31;				/* round and convert from Q62 to Q31 */
	/* offset */
	temp += (int64)OFFSET;						/* A*sin(phi+phase) + Offset */
	/* output limitation */
	LIMIT(temp, INT32_MAX);

	OUT = (int32)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void SinGen_FiP32_Init(SINGEN_FIP32 *pTSinGen_FiP32)
{
    pTSinGen_FiP32->ID = SINGEN_FIP32_ID;
    pTSinGen_FiP32->u = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_FiP32_Load(const SINGEN_FIP32 *pTSinGen_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSinGen_FiP32->delta_phi & 0x000000FF);
        data[1] = (uint8)((pTSinGen_FiP32->delta_phi >> 8) & 0x000000FF);
        data[2] = (uint8)((pTSinGen_FiP32->delta_phi >> 16) & 0x000000FF);
        data[3] = (uint8)((pTSinGen_FiP32->delta_phi >> 24) & 0x000000FF);
        data[4] = (uint8)(pTSinGen_FiP32->phase & 0x000000FF);
        data[5] = (uint8)((pTSinGen_FiP32->phase >> 8) & 0x000000FF);
        data[6] = (uint8)((pTSinGen_FiP32->phase >> 16) & 0x000000FF);
        data[7] = (uint8)((pTSinGen_FiP32->phase >> 24) & 0x000000FF);
        data[8] = (uint8)(pTSinGen_FiP32->offset & 0x000000FF);
        data[9] = (uint8)((pTSinGen_FiP32->offset >> 8) & 0x000000FF);
        data[10] = (uint8)((pTSinGen_FiP32->offset >> 16) & 0x000000FF);
        data[11] = (uint8)((pTSinGen_FiP32->offset >> 24) & 0x000000FF);
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 SinGen_FiP32_Save(SINGEN_FIP32 *pTSinGen_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        pTSinGen_FiP32->delta_phi = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTSinGen_FiP32->phase = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTSinGen_FiP32->offset = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SINGEN_FIP32_ISLINKED)
void* SinGen_FiP32_GetAddress(const SINGEN_FIP32* block, uint16 elementId)
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
