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
/**     Description:	Second order transfer function                      										 **/
/**						Calculation:																				 **/
/**	       						 b2.z^2 + b1.z + b0					   												 **/
/** 						y = ------------------ u				   												 **/
/**          					  z^2 + a1.z + a0																	 **/
/**							-> y(k) = u(k).b2 + u(k-1).b1 + u(k-2).b0												 **/
/**									- y(k-1).a1 - y(k-2).a0															 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TF2_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF2_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF2_FiP8->In)			/* Q7 */

/* Outputs */
#define OUT			(pTTF2_FiP8->Out)			/* Q7 */

/* Parameter */
#define	A0			(pTTF2_FiP8->a0)			/* Qa */
#define	A1			(pTTF2_FiP8->a1)			/* Qa */
#define	B0			(pTTF2_FiP8->b0)			/* Qb */
#define	B1			(pTTF2_FiP8->b1)			/* Qb */
#define	B2			(pTTF2_FiP8->b2)			/* Qb */
#define SFRA		(pTTF2_FiP8->sfra)			/* a */
#define SFRB		(pTTF2_FiP8->sfrb)			/* b */

/* Variables */
#define IN_OLD		(pTTF2_FiP8->in_old)		/* Q7 */
#define IN_VERYOLD	(pTTF2_FiP8->in_veryold)	/* Q7 */
#define OUT_OLD		(pTTF2_FiP8->out_old)		/* Q7 */
#define OUT_VERYOLD	(pTTF2_FiP8->out_veryold)	/* Q7 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF2_FiP8_Update(TF2_FIP8 *pTTF2_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 temp, temp1;

	temp  =  ((int16)B0 * (int16)IN_VERYOLD) >> 1;	/* y(k) = b0.u(k-2) */
	temp += (((int16)B1 * (int16)IN_OLD)     >> 1);	/* y(k) = b0.u(k-2) + b1.u(k-1) */
	temp += (((int16)B2 * (int16)IN)         >> 1);	/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) */
	if (1 > SFRB)	/* check which direction to shift */
	{
		temp = temp << (1-SFRB);					/* Q7 */
	}
	else
	{
		temp = temp >> (SFRB-1);					/* Q7 */
	}

	temp1  =  (int16)A0 * (int16)OUT_VERYOLD;		/* y1(k) = a0.y(k-2) */
	temp1 += ((int16)A1 * (int16)OUT_OLD);			/* y1(k) = a0.y(k-2) + a1.y(k-1) */
	temp1  = temp1 >> SFRA;							/* Q7 */

	temp   = temp - temp1;							/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) - a0.y(k-2) - a1.y(k-1)*/

	/* check for overflow */
	if (temp > (int16)INT8_MAX)
	{
		temp = (int16)INT8_MAX;
	}
	else
	{
		if (temp < -(int16)INT8_MAX)
		{
			temp = -(int16)INT8_MAX;
		}
	}

	/* save values for next update call and assign output */
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = (int8)temp;
	OUT         = OUT_OLD;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF2_FiP8_Init(TF2_FIP8 *pTTF2_FiP8)
{
    pTTF2_FiP8->ID = TF2_FIP8_ID;
    pTTF2_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old values */
     IN_OLD      = 0;
     IN_VERYOLD  = 0;
     OUT_OLD     = 0;
     OUT_VERYOLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_FiP8_Load(const TF2_FIP8 *pTTF2_FiP8, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)7 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTTF2_FiP8->b0;
        data[1] = (uint8)pTTF2_FiP8->b1;
        data[2] = (uint8)pTTF2_FiP8->b2;
        data[3] = (uint8)pTTF2_FiP8->a0;
        data[4] = (uint8)pTTF2_FiP8->a1;
        data[5] = (uint8)pTTF2_FiP8->sfrb;
        data[6] = (uint8)pTTF2_FiP8->sfra;
        *dataLength = (uint16)7;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_FiP8_Save(TF2_FIP8 *pTTF2_FiP8, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)7)
    {
        error = (uint8)1;
    }
    else
    {
        pTTF2_FiP8->b0 = UINT8_TO_INT8((uint8)data[0]);
        pTTF2_FiP8->b1 = UINT8_TO_INT8((uint8)data[1]);
        pTTF2_FiP8->b2 = UINT8_TO_INT8((uint8)data[2]);
        pTTF2_FiP8->a0 = UINT8_TO_INT8((uint8)data[3]);
        pTTF2_FiP8->a1 = UINT8_TO_INT8((uint8)data[4]);
        pTTF2_FiP8->sfrb = UINT8_TO_INT8((uint8)data[5]);
        pTTF2_FiP8->sfra = UINT8_TO_INT8((uint8)data[6]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF2_FIP8_ISLINKED)
void* TF2_FiP8_GetAddress(const TF2_FIP8* block, uint16 elementId)
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
