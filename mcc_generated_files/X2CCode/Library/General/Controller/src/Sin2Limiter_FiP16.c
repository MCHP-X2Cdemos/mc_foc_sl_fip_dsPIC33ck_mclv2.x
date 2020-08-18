/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 1894 $
 * $LastChangedDate:: 2020-04-28 23:26:04 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Continuously differentiable output change rate limitation with	sin^2 shape                  **/
/**						Calculation:                               													 **/
/**							du/dt = 0:																				 **/
/**								y = u																				 **/
/**							du/dt <> 0:																				 **/
/**								y = u * sin^2(t)		(simplified)												 **/
/**																													 **/
/**		Caution:	A step in the input signal during a	running limitation process will not abort the running        **/
/**					limitation process!																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "Sin2Limiter_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Sin2Limiter_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin2_Data.h"

/* Inputs */
#define IN 					(*pTSin2Limiter_FiP16->In)
#define INIT                (*pTSin2Limiter_FiP16->Init)
#define ENABLE              (*pTSin2Limiter_FiP16->Enable)

/* Outputs */
#define OUT 				(pTSin2Limiter_FiP16->Out)

/* Parameters */
#define RATE_UP				(pTSin2Limiter_FiP16->RateUp)			/* rising slew rate */
#define RATE_DOWN			(pTSin2Limiter_FiP16->RateDown)			/* falling slew rate */

/* Variables */
#define SCALED_RATE_UP		(pTSin2Limiter_FiP16->Scaled_RateUp)	/* to step height adjusted rising slew rate */
#define SCALED_RATE_DOWN	(pTSin2Limiter_FiP16->Scaled_RateDown)	/* to step height adjusted falling slew rate */
#define OUT_END				(pTSin2Limiter_FiP16->Out_end)			/* desired target value */
#define LEVEL	  			(pTSin2Limiter_FiP16->Level)			/* current input level (argument) for sin^2 calculation */
#define STEP_HEIGHT			(pTSin2Limiter_FiP16->Step_Height)		/* current step height */
#define STATE				(pTSin2Limiter_FiP16->State)			/* 1 -> limiting at rising flank, -1 -> limiting at falling flank, 0 -> no limiting */
#define ENABLE_OLD          (pTSin2Limiter_FiP16->Enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP16_Update(SIN2LIMITER_FIP16 *pTSin2Limiter_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16	sin2;
 	int32	derivative, temp;
	
    if (!ENABLE)    /* Rate limiting disabled */
    {
        OUT = 0;
    }
    else            /* Rate limiting enabled */
    {
        if (!ENABLE_OLD)
        {
            /* rising edge of enable signal occurred */
            OUT = INIT; /* assign output to init value */
            STATE = 0;  /* reset state */
        }

        if (STATE == 0)
        {
            /* derivative */
            derivative = (int32)IN - (int32)OUT;

            /* check for change in input signal */
            if (derivative > 1)			/* positive step (greater 1 is required to prevent division by zero) */
            {
                STATE = 1;							/* save direction information */
                LEVEL = UINT32_MAX;					/* preset level */
                STEP_HEIGHT = derivative << 15;		/* save step height [Q30] */
                OUT_END = IN;

                /* justification of rate factor in respect to step height */
                if ((RATE_UP>>1) >= STEP_HEIGHT)	/* result is not in 0..1 range */
                {
                    SCALED_RATE_UP = INT32_MAX;		/* positive saturation */
                }
                else								/* result is in 0..1 range */
                {
                    SCALED_RATE_UP = (((int64)RATE_UP)<<31) / STEP_HEIGHT;
                }
            }
            else
            {
                if (derivative < -1)		/* negative step (smaller -1 is required to prevent division by zero) */
                {
                    STATE = -1;							/* save direction information */
                    LEVEL = UINT32_MAX;					/* preset level */
                    STEP_HEIGHT = (-derivative) << 15;	/* save step height [Q30] */
                    OUT_END = IN;

                    /* justification of rate factor in respect to step height */
                    if ((RATE_DOWN>>1) >= STEP_HEIGHT)	/* result is not in -1..0 range */
                    {
                        SCALED_RATE_DOWN = INT32_MAX;	/* negative saturation */
                    }
                    else								/* result is in -1..0 range */
                    {
                        SCALED_RATE_DOWN = (((int64)RATE_DOWN)<<31) / STEP_HEIGHT;
                    }
                }
            }
        }

        switch(STATE)
        {
            case 0:		/* no rate limiting in progress */
                OUT = IN;
                break;

            case 1:		/* positive rate limiting */
                if (LEVEL <= SCALED_RATE_UP)   /* check if level has reached final value */
                {
                    /* rate limitation has finished */
                    LEVEL = 0;
                    STATE = 0;
                }
                else
                {
                    LEVEL -= SCALED_RATE_UP;	/* calculate new level value */
                }
                LOOKUP16(Sin2_Table16, (LEVEL>>16), sin2);		/* calculate sin^2(level) */
                temp = ((int32)sin2 * (STEP_HEIGHT>>15)) >> 15;	/* scale sin^2 to step height */
                OUT = OUT_END - (int16)temp;					/* subtract sin^2 from desired end value */

                break;

            case -1:	/* negative rate limiting */
                if (LEVEL <= SCALED_RATE_DOWN)	   /* check if level has reached final value */
                {
                    /* rate limitation has finished */
                    LEVEL = 0;
                    STATE = 0;
                }
                else
                {
                    LEVEL -= SCALED_RATE_DOWN;	/* calculate new level value */
                }
                LOOKUP16(Sin2_Table16, (LEVEL>>16), sin2);		/* calculate sin^2(level) */
                sin2 = -sin2;									/* adapt sin^2 to falling flank */
                temp = ((int32)sin2 * (STEP_HEIGHT>>15)) >> 15;	/* scale sin^2 to step height */
                OUT  = OUT_END - (int16)temp;					/* subtract sin^2 from desired end value */
                break;
            default:	/* should not occur */
                OUT = IN;
                STATE = 0;
                break;
        }
    }
    ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP16_Init(SIN2LIMITER_FIP16 *pTSin2Limiter_FiP16)
{
    pTSin2Limiter_FiP16->ID = SIN2LIMITER_FIP16_ID;
    pTSin2Limiter_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    SCALED_RATE_UP   = 0;
    SCALED_RATE_DOWN = 0;
	OUT_END = 0;
	LEVEL = 0;
	STEP_HEIGHT = 0;
	STATE = 0;
	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_FiP16_Load(const SIN2LIMITER_FIP16 *pTSin2Limiter_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSin2Limiter_FiP16->RateUp & 0x000000FF);
        data[1] = (uint8)((pTSin2Limiter_FiP16->RateUp >> 8) & 0x000000FF);
        data[2] = (uint8)((pTSin2Limiter_FiP16->RateUp >> 16) & 0x000000FF);
        data[3] = (uint8)((pTSin2Limiter_FiP16->RateUp >> 24) & 0x000000FF);
        data[4] = (uint8)(pTSin2Limiter_FiP16->RateDown & 0x000000FF);
        data[5] = (uint8)((pTSin2Limiter_FiP16->RateDown >> 8) & 0x000000FF);
        data[6] = (uint8)((pTSin2Limiter_FiP16->RateDown >> 16) & 0x000000FF);
        data[7] = (uint8)((pTSin2Limiter_FiP16->RateDown >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_FiP16_Save(SIN2LIMITER_FIP16 *pTSin2Limiter_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        pTSin2Limiter_FiP16->RateUp = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTSin2Limiter_FiP16->RateDown = UINT32_TO_INT32((uint32)data[4] + \
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
#if !defined(SIN2LIMITER_FIP16_ISLINKED)
void* Sin2Limiter_FiP16_GetAddress(const SIN2LIMITER_FIP16* block, uint16 elementId)
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
