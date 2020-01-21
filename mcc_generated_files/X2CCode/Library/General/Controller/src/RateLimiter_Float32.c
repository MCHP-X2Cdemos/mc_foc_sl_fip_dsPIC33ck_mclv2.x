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
/**     Description:	Output change rate limitation                        **/
/**						Calculation:										 **/
/**							u > y:											 **/
/**								y(k)     = y(k-1) + RateUp					 **/
/**								RateUp   = 1/Tr * Ts						 **/
/**							u < y:											 **/
/**								y(k)     = y(k-1) - RateDown				 **/
/**								RateDown = 1/Tf * Ts						 **/
/**                                                                          **/
/* USERCODE-END:Description                                                                                           */
#include "RateLimiter_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(RateLimiter_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTRateLimiter_Float32->In)
#define INIT		(*pTRateLimiter_Float32->Init)
#define ENABLE		(*pTRateLimiter_Float32->Enable)

/* Outputs */
#define OUT 		(pTRateLimiter_Float32->Out)

/* Parameters */
#define RATE_UP		(pTRateLimiter_Float32->RateUp)
#define RATE_DOWN	(pTRateLimiter_Float32->RateDown)

/* Variables */
#define ENABLE_OLD	(pTRateLimiter_Float32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void RateLimiter_Float32_Update(RATELIMITER_FLOAT32 *pTRateLimiter_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
 	float32	Diff;

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
			Diff = IN - OUT;

			/* check for type of step */
			if (Diff > 0)		/* positive step */
			{
				if (Diff > RATE_UP)		/* step is higher than RateUp */
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
void RateLimiter_Float32_Init(RATELIMITER_FLOAT32 *pTRateLimiter_Float32)
{
    pTRateLimiter_Float32->ID = RATELIMITER_FLOAT32_ID;
    pTRateLimiter_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 RateLimiter_Float32_Load(const RATELIMITER_FLOAT32 *pTRateLimiter_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateUp)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateUp) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateUp) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateUp) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateDown)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateDown) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateDown) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTRateLimiter_Float32->RateDown) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 RateLimiter_Float32_Save(RATELIMITER_FLOAT32 *pTRateLimiter_Float32, const uint8 data[], uint16 dataLength)
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
        pTRateLimiter_Float32->RateUp = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTRateLimiter_Float32->RateDown = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(RATELIMITER_FLOAT32_ISLINKED)
void* RateLimiter_Float32_GetAddress(const RATELIMITER_FLOAT32* block, uint16 elementId)
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
