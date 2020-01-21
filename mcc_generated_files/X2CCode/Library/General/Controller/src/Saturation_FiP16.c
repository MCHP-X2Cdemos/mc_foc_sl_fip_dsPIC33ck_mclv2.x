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
/**     Description:	Saturation of output to adjustable upper and lower	 **/
/**						limit.												 **/	
/**                     Calculation:                                         **/
/**							Out = In										 **/
/**								--> with Out = [min..max]			 		 **/
/**						Range:												 **/
/**							In:		-1..1								 	 **/
/**							Out:	min..max							 	 **/
/**							min:	-1..max									 **/
/**							max:	min..1	 								 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "Saturation_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Saturation_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 		(*pTSaturation_FiP16->In)		/* Q15 */

/* Outputs */
#define OUT	 	(pTSaturation_FiP16->Out)		/* Q15 */

/* Parameter */
#define MAX		(pTSaturation_FiP16->max)		/* upper limit, Q15 */
#define MIN		(pTSaturation_FiP16->min)		/* lower limit, Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Saturation_FiP16_Update(SATURATION_FIP16 *pTSaturation_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	OUT = IN;
	if (OUT > MAX)
	{
		/* input signal is higher than maximum allowed value */
		OUT = MAX;
	}
	else if (OUT < MIN)
	{
		/* input signal is lower than minimum allowed value */
		OUT = MIN;
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Saturation_FiP16_Init(SATURATION_FIP16 *pTSaturation_FiP16)
{
    pTSaturation_FiP16->ID = SATURATION_FIP16_ID;
    pTSaturation_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Saturation_FiP16_Load(const SATURATION_FIP16 *pTSaturation_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)4 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSaturation_FiP16->max & 0x00FF);
        data[1] = (uint8)((pTSaturation_FiP16->max >> 8) & 0x00FF);
        data[2] = (uint8)(pTSaturation_FiP16->min & 0x00FF);
        data[3] = (uint8)((pTSaturation_FiP16->min >> 8) & 0x00FF);
        *dataLength = (uint16)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Saturation_FiP16_Save(SATURATION_FIP16 *pTSaturation_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)4)
    {
        error = (uint8)1;
    }
    else
    {
        pTSaturation_FiP16->max = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTSaturation_FiP16->min = UINT16_TO_INT16((uint16)data[2] + \
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
#if !defined(SATURATION_FIP16_ISLINKED)
void* Saturation_FiP16_GetAddress(const SATURATION_FIP16* block, uint16 elementId)
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
