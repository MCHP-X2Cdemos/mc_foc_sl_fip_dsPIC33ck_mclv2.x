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
/**     Description:	PI Controller with                                   **/
/**							- Enable Input									 **/
/**							- Anti Wind-up									 **/
/**							- Initial Condition Input	 					 **/
/**							- Output Limitation								 **/
/**						Calculation ZOH:									 **/
/**	       						                1          			 		 **/
/** 						y = ( Kp + Ki*Ts* -----  ) * u					 **/
/**          					              z - 1	   						 **/
/**																			 **/
/**						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)				 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "PILimit_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PILimit_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPILimit_Float32->In)
#define ENABLE 			(*pTPILimit_Float32->Enable)
#define INIT 			(*pTPILimit_Float32->Init)
#define LIMIT_UP 		(*pTPILimit_Float32->max)
#define LIMIT_DOWN 		(*pTPILimit_Float32->min)

/* Outputs */
#define OUT	 			(pTPILimit_Float32->Out)

/* Parameter */
#define	B0				(pTPILimit_Float32->b0)
#define	B1				(pTPILimit_Float32->b1)

/* Variables */
#define I_OLD			(pTPILimit_Float32->i_old)
#define ENABLE_OLD		(pTPILimit_Float32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PILimit_Float32_Update(PILIMIT_FLOAT32 *pTPILimit_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 y, yp;

	if (ENABLE)	/* Block enabled */
	{
		if (!ENABLE_OLD)	/* rising edge of enable signal occurred */
		{
		 	/* preset old value */
		 	I_OLD = INIT;
		}

		/* Proportional term */
		yp = B1 * IN;

		/* Sum of proportional and integral term */
		y = yp + I_OLD;

		/* Output limitation and anti wind-up */
		if (y > LIMIT_UP)			/* output is beyond upper limit */
		{
			/* output limitation to upper boundary */
			y = LIMIT_UP;

			/* limitation of integral part */
			if (yp > LIMIT_UP)
			{
				yp = LIMIT_UP;
			}
			I_OLD = LIMIT_UP - yp;

		}
		else if (y < LIMIT_DOWN)	/* output is beyond lower limit */
		{
			/* output limitation to lower boundary */
			y = LIMIT_DOWN;

			/* limitation of integral part */
			if (yp < LIMIT_DOWN)
			{
				yp = LIMIT_DOWN;
			}
			I_OLD = LIMIT_DOWN - yp;
		}
		else
		{
			/* No output limitation -> no limitation of integral term */
			I_OLD += (B0 * IN);
		}

		/* Assign output */
		OUT = y;

	}
	else				/* Block disabled */
	{
		OUT = 0;	/* reset output */
	}
	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void PILimit_Float32_Init(PILIMIT_FLOAT32 *pTPILimit_Float32)
{
    pTPILimit_Float32->ID = PILIMIT_FLOAT32_ID;
    pTPILimit_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* preset old values */
   	I_OLD = INIT;
  	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PILimit_Float32_Load(const PILIMIT_FLOAT32 *pTPILimit_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTPILimit_Float32->b0)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTPILimit_Float32->b0) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTPILimit_Float32->b0) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTPILimit_Float32->b0) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTPILimit_Float32->b1)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTPILimit_Float32->b1) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTPILimit_Float32->b1) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTPILimit_Float32->b1) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PILimit_Float32_Save(PILIMIT_FLOAT32 *pTPILimit_Float32, const uint8 data[], uint16 dataLength)
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
        pTPILimit_Float32->b0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTPILimit_Float32->b1 = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PILIMIT_FLOAT32_ISLINKED)
void* PILimit_Float32_GetAddress(const PILIMIT_FLOAT32* block, uint16 elementId)
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
            addr = (void*)block->max;
            break;
        case 4:
            addr = (void*)block->min;
            break;
        case 5:
            addr = (void*)block->Enable;
            break;
        case 6:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
