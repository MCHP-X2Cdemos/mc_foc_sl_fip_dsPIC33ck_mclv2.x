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
/**     Description:	PI Controller with                                  **/
/**							- Enable Input									 **/
/**							- Anti Wind-up									 **/
/**							- Initial Condition Input	 					 **/
/**						Calculation ZOH:									 **/
/**	       						                1          			 		 **/
/** 						y = ( Kp + Ki*Ts* -----  ) * u					 **/
/**          					              z - 1	   						 **/
/**																			 **/
/**						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)				 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "PI_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PI_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPI_Float64->In)
#define ENABLE 			(*pTPI_Float64->Enable)
#define INIT 			(*pTPI_Float64->Init)

/* Outputs */
#define OUT	 			(pTPI_Float64->Out)

/* Parameter */
#define	B0				(pTPI_Float64->b0)
#define	B1				(pTPI_Float64->b1)

/* Variables */
#define I_OLD			(pTPI_Float64->i_old)
#define ENABLE_OLD		(pTPI_Float64->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PI_Float64_Update(PI_FLOAT64 *pTPI_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 y;

    if (ENABLE) /* Block enabled */
    {
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
		{
		 	/* preset old value */
		 	I_OLD = INIT;
		}

		/* Proportional term */
		y = B1 * IN;

		/* Sum of proportional and integral term */
		y = y + I_OLD;

		/* Integral term */
		I_OLD += (B0 * IN);

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
void PI_Float64_Init(PI_FLOAT64 *pTPI_Float64)
{
    pTPI_Float64->ID = PI_FLOAT64_ID;
    pTPI_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* preset old values */
   	I_OLD = INIT;
  	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PI_Float64_Load(const PI_FLOAT64 *pTPI_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)16 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint64*)&(pTPI_Float64->b0)) & 0x00000000000000FF);
        data[1] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 8) & 0x00000000000000FF);
        data[2] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 16) & 0x00000000000000FF);
        data[3] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 24) & 0x00000000000000FF);
        data[4] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 32) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 40) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 48) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(pTPI_Float64->b0) >> 56) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(pTPI_Float64->b1)) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 8) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 16) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 24) & 0x00000000000000FF);
        data[12] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 32) & 0x00000000000000FF);
        data[13] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 40) & 0x00000000000000FF);
        data[14] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 48) & 0x00000000000000FF);
        data[15] = (uint8)((*(uint64*)&(pTPI_Float64->b1) >> 56) & 0x00000000000000FF);
        *dataLength = (uint16)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PI_Float64_Save(PI_FLOAT64 *pTPI_Float64, const uint8 data[], uint16 dataLength)
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
        pTPI_Float64->b0 = (float64)(*(float64*)&tmp64);
        tmp64 = (uint64)data[8] + \
            ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
            ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
            ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
            ((uint64)data[15] << 56);
        pTPI_Float64->b1 = (float64)(*(float64*)&tmp64);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PI_FLOAT64_ISLINKED)
void* PI_Float64_GetAddress(const PI_FLOAT64* block, uint16 elementId)
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
