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
#include "Sin2Limiter_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Sin2Limiter_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN 					(*pTSin2Limiter_Float32->In)
#define INIT                (*pTSin2Limiter_Float32->Init)
#define ENABLE              (*pTSin2Limiter_Float32->Enable)

/* Outputs */
#define OUT 				(pTSin2Limiter_Float32->Out)

/* Parameters */
#define RATE_UP				(pTSin2Limiter_Float32->RateUp)				/* rising slew rate */
#define RATE_DOWN			(pTSin2Limiter_Float32->RateDown)			/* falling slew rate */

/* Variables */
#define SCALED_RATE_UP		(pTSin2Limiter_Float32->Scaled_RateUp)		/* to step height adjusted rising slew rate */
#define SCALED_RATE_DOWN	(pTSin2Limiter_Float32->Scaled_RateDown)	/* to step height adjusted falling slew rate */
#define OUT_END				(pTSin2Limiter_Float32->Out_end)			/* desired target value */
#define LEVEL	  			(pTSin2Limiter_Float32->Level)				/* current input level (argument) for sin^2 calculation */
#define STEP_HEIGHT			(pTSin2Limiter_Float32->Step_Height)		/* current step height */
#define STATE				(pTSin2Limiter_Float32->State)				/* 1 -> limiting at rising flank, -1 -> limiting at falling flank, 0 -> no limiting */
#define ENABLE_OLD          (pTSin2Limiter_Float32->Enable_old)

/* Constants */
#define HALFPI				(PI_R32/(float32)2.0)						/* pi/2 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin2Limiter_Float32_Update(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32	sin2;
 	float32	derivative, temp;

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
            derivative = IN - OUT;

            /* check for change in input signal */
            if (derivative > 0)			/* positive step */
            {
                STATE = 1;						/* save direction information */
                LEVEL = HALFPI;					/* preset level */
                STEP_HEIGHT = derivative;		/* save step height*/
                OUT_END = IN;

                /* justification of rate factor in respect to step height */
                SCALED_RATE_UP = RATE_UP / STEP_HEIGHT;
            }
            else
            {
                if (derivative < 0)		/* negative step */
                {
                    STATE = -1;					/* save direction information */
                    LEVEL = HALFPI;				/* preset level */
                    STEP_HEIGHT = -derivative;	/* save step height*/
                    OUT_END = IN;

                    /* justification of rate factor in respect to step height */
                    SCALED_RATE_DOWN = RATE_DOWN / STEP_HEIGHT;
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
                sin2 = sin(LEVEL);				/* calculate sin(level) */
                sin2 = sin2 * sin2;				/* calculate sin^2(level) */
                temp = sin2 * STEP_HEIGHT;		/* scale sin^2 to step height */
                OUT = OUT_END - temp;			/* subtract sin^2 from desired end value */

                break;

            case -1:	/* negative rate limiting */
                if (LEVEL <= SCALED_RATE_DOWN)	/* check if level has reached final value */
                {
                    /* rate limitation has finished */
                    LEVEL = 0;
                    STATE = 0;
                }
                else
                {
                    LEVEL -= SCALED_RATE_DOWN;	/* calculate new level value */
                }
                sin2 = sin(LEVEL);				/* calculate sin(level) */
                sin2 = sin2 * sin2;				/* calculate sin^2(level) */
                sin2 = -sin2;					/* adapt sin^2 to falling flank */
                temp = sin2 * STEP_HEIGHT;		/* scale sin^2 to step height */
                OUT  = OUT_END - temp;			/* subtract sin^2 from desired end value */
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
void Sin2Limiter_Float32_Init(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32)
{
    pTSin2Limiter_Float32->ID = SIN2LIMITER_FLOAT32_ID;
    pTSin2Limiter_Float32->Out = 0;
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
uint8 Sin2Limiter_Float32_Load(const SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateUp)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateUp) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateUp) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateUp) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateDown)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateDown) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateDown) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTSin2Limiter_Float32->RateDown) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_Float32_Save(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32, const uint8 data[], uint16 dataLength)
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
        pTSin2Limiter_Float32->RateUp = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTSin2Limiter_Float32->RateDown = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SIN2LIMITER_FLOAT32_ISLINKED)
void* Sin2Limiter_Float32_GetAddress(const SIN2LIMITER_FLOAT32* block, uint16 elementId)
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
