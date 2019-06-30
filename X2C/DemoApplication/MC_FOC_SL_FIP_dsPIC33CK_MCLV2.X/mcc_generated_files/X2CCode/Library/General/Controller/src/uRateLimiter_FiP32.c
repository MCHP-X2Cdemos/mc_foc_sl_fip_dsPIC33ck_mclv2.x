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
/*      Description:	Output change rate limitation of angle signals        */
/* 						Calculation:										  */
/* 							u > y:											  */
/* 								y(k)     = y(k-1) + RateUp					  */
/* 								RateUp   = 1/Tr * Ts						  */
/* 							u < y:											  */
/* 								y(k)     = y(k-1) - RateDown				  */
/* 								RateDown = 1/Tf * Ts						  */
/*                                                                            */
/* USERCODE-END:Description                                                                                           */
#include "uRateLimiter_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(uRateLimiter_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTuRateLimiter_FiP32->In)			/* Q31 */
#define INIT		(*pTuRateLimiter_FiP32->Init)		/* Q31 */
#define ENABLE		(*pTuRateLimiter_FiP32->Enable)		/* Q0  */

/* Outputs */
#define OUT 		(pTuRateLimiter_FiP32->Out)			/* Q31 */

/* Parameters */
#define RATE_UP		(pTuRateLimiter_FiP32->RateUp)		/* Q31 */
#define RATE_DOWN	(pTuRateLimiter_FiP32->RateDown)	/* Q31 */

/* Variables */
#define ENABLE_OLD	(pTuRateLimiter_FiP32->enable_old)	/* Q0  */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void uRateLimiter_FiP32_Update(URATELIMITER_FIP32 *pTuRateLimiter_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
 	int32	Diff;

 	if (!ENABLE)	/* Rate limiting disabled */
 	{
 		OUT = IN;
 	}
 	else				/* Rate limiting enabled */
 	{
 		if (!ENABLE_OLD)
 		{
 			/* rising edge of enable signal occurred */
 			OUT = INIT;						/* assign output to init value */
 		}
 		else
 		{
			/* step height */
			Diff = IN - OUT;	/* overflow is allowed */

			/* check for type of step */
			if (Diff > 0)		/* positive step */
			{
				if (Diff > RATE_UP)			/* step is higher than RateUp */
				{
					OUT = OUT + RATE_UP;	/* increase output */
				}
				else
				{
					OUT = IN;				/* assign output */
				}
			}
			else if (Diff < 0)	/* negative step */
			{
				if (-Diff > RATE_DOWN)	/* step is lower than RateDown */
				{
					OUT = OUT - RATE_DOWN;	/* decrease output */
				}
				else
				{
					OUT = IN;				/* assign output */
				}
			}
 		}
 	}
 	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uRateLimiter_FiP32_Init(URATELIMITER_FIP32 *pTuRateLimiter_FiP32)
{
    pTuRateLimiter_FiP32->ID = URATELIMITER_FIP32_ID;
    pTuRateLimiter_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uRateLimiter_FiP32_Load(const URATELIMITER_FIP32 *pTuRateLimiter_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTuRateLimiter_FiP32->RateUp & 0x000000FF);
        data[1] = (uint8)((pTuRateLimiter_FiP32->RateUp >> 8) & 0x000000FF);
        data[2] = (uint8)((pTuRateLimiter_FiP32->RateUp >> 16) & 0x000000FF);
        data[3] = (uint8)((pTuRateLimiter_FiP32->RateUp >> 24) & 0x000000FF);
        data[4] = (uint8)(pTuRateLimiter_FiP32->RateDown & 0x000000FF);
        data[5] = (uint8)((pTuRateLimiter_FiP32->RateDown >> 8) & 0x000000FF);
        data[6] = (uint8)((pTuRateLimiter_FiP32->RateDown >> 16) & 0x000000FF);
        data[7] = (uint8)((pTuRateLimiter_FiP32->RateDown >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uRateLimiter_FiP32_Save(URATELIMITER_FIP32 *pTuRateLimiter_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        pTuRateLimiter_FiP32->RateUp = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTuRateLimiter_FiP32->RateDown = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(URATELIMITER_FIP32_ISLINKED)
void* uRateLimiter_FiP32_GetAddress(const URATELIMITER_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->Init;
            break;
        case 3:
            addr = (void*)block->Enable;
            break;
        case 4:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
