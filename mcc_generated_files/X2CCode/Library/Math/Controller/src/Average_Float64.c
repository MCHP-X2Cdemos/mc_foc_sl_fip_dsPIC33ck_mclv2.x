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
/**     Description:	Calculation of moving average value over n numbers.  **/
/**                                                                          **/
/* USERCODE-END:Description                                                                                           */
#include "Average_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Average_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN				(*pTAverage_Float64->In)

/* Outputs */
#define OUT 			(pTAverage_Float64->Out)

/* Parameter */
#define NUMBER			(pTAverage_Float64->n)
#define SFR 			(pTAverage_Float64->sfrn)

/* Variables */
#define SUM				(pTAverage_Float64->sum)
#define AVG				(pTAverage_Float64->avg)
#define CNT				(pTAverage_Float64->count)

/* Constants */
#define MAX_NUMBER		256		/* max size of average window */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Average_Float64_Update(AVERAGE_FLOAT64 *pTAverage_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	/* Adjust array */
	SUM     -= AVG[CNT];		/* remove last entry from sum */
	SUM     += IN;				/* add new value to sum */
	AVG[CNT] = IN;				/* put new value into buffer */

	/* Cyclic index counter */
	CNT++;
	if (CNT >= NUMBER)
	{
		CNT = 0;
	}

	/* Assign output */
	OUT = SUM / NUMBER;			/* calculate average value */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Average_Float64_Init(AVERAGE_FLOAT64 *pTAverage_Float64)
{
    pTAverage_Float64->ID = AVERAGE_FLOAT64_ID;
    pTAverage_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* Reset sum */
     SUM = 0;

     /* Reset array */
     for (CNT=0; CNT<MAX_NUMBER; CNT++)
     {
    	 AVG[CNT] = 0;
     }

     /* Reset counter */
     CNT = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Average_Float64_Load(const AVERAGE_FLOAT64 *pTAverage_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)2 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTAverage_Float64->n & 0x00FF);
        data[1] = (uint8)((pTAverage_Float64->n >> 8) & 0x00FF);
        *dataLength = (uint16)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Average_Float64_Save(AVERAGE_FLOAT64 *pTAverage_Float64, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)2)
    {
        error = (uint8)1;
    }
    else
    {
        pTAverage_Float64->n = ((uint16)data[0] + \
            ((uint16)data[1] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
     /* Reset sum */
     SUM = 0;

     /* Reset array */
     for (CNT=0; CNT<MAX_NUMBER; CNT++)
     {
    	 AVG[CNT] = 0;
     }

     /* Reset counter */
     CNT = 0;
	 
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(AVERAGE_FLOAT64_ISLINKED)
void* Average_Float64_GetAddress(const AVERAGE_FLOAT64* block, uint16 elementId)
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
