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
#include "TF2_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF2_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF2_FiP16->In)			/* Q15 */

/* Outputs */
#define OUT			(pTTF2_FiP16->Out)			/* Q15 */

/* Parameter */
#define	A0			(pTTF2_FiP16->a0)			/* Qa */
#define	A1			(pTTF2_FiP16->a1)			/* Qa */
#define	B0			(pTTF2_FiP16->b0)			/* Qb */
#define	B1			(pTTF2_FiP16->b1)			/* Qb */
#define	B2			(pTTF2_FiP16->b2)			/* Qb */
#define SFRA		(pTTF2_FiP16->sfra)			/* a */
#define SFRB		(pTTF2_FiP16->sfrb)			/* b */

/* Variables */
#define IN_OLD		(pTTF2_FiP16->in_old)		/* Q15 */
#define IN_VERYOLD	(pTTF2_FiP16->in_veryold)	/* Q15 */
#define OUT_OLD		(pTTF2_FiP16->out_old)		/* Q15 */
#define OUT_VERYOLD	(pTTF2_FiP16->out_veryold)	/* Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF2_FiP16_Update(TF2_FIP16 *pTTF2_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp, temp1;

	temp  =  ((int32)B0 * (int32)IN_VERYOLD) >> 1;	/* y(k) = b0.u(k-2) */
	temp += (((int32)B1 * (int32)IN_OLD)     >> 1);	/* y(k) = b0.u(k-2) + b1.u(k-1) */
	temp += (((int32)B2 * (int32)IN)         >> 1);	/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) */
	if (1 > SFRB)	/* check which direction to shift */
	{
		temp = temp << (1-SFRB);					/* Q15 */
	}
	else
	{
		temp = temp >> (SFRB-1);					/* Q15 */
	}

	temp1  =  (int32)A0 * (int32)OUT_VERYOLD;		/* y1(k) = a0.y(k-2) */
	temp1 += ((int32)A1 * (int32)OUT_OLD);			/* y1(k) = a0.y(k-2) + a1.y(k-1) */
	temp1  = temp1 >> SFRA;							/* Q15 */

	temp   = temp - temp1;							/* y(k) = b0.u(k-2) + b1.u(k-1) + b2.u(k) - a0.y(k-2) - a1.y(k-1) */

	/* check for overflow */
	if (temp > (int32)INT16_MAX)
	{
		temp = (int32)INT16_MAX;
	}
	else
	{
		if (temp < -(int32)INT16_MAX)
		{
			temp = -(int32)INT16_MAX;
		}
	}

	/* set values for next update call and assign output */
	IN_VERYOLD  = IN_OLD;
	IN_OLD      = IN;
	OUT_VERYOLD = OUT_OLD;
	OUT_OLD     = (int16)temp;
	OUT         = OUT_OLD;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF2_FiP16_Init(TF2_FIP16 *pTTF2_FiP16)
{
    pTTF2_FiP16->ID = TF2_FIP16_ID;
    pTTF2_FiP16->Out = 0;
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
uint8 TF2_FiP16_Load(const TF2_FIP16 *pTTF2_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTF2_FiP16->b0 & 0x00FF);
        data[1] = (uint8)((pTTF2_FiP16->b0 >> 8) & 0x00FF);
        data[2] = (uint8)(pTTF2_FiP16->b1 & 0x00FF);
        data[3] = (uint8)((pTTF2_FiP16->b1 >> 8) & 0x00FF);
        data[4] = (uint8)(pTTF2_FiP16->b2 & 0x00FF);
        data[5] = (uint8)((pTTF2_FiP16->b2 >> 8) & 0x00FF);
        data[6] = (uint8)(pTTF2_FiP16->a0 & 0x00FF);
        data[7] = (uint8)((pTTF2_FiP16->a0 >> 8) & 0x00FF);
        data[8] = (uint8)(pTTF2_FiP16->a1 & 0x00FF);
        data[9] = (uint8)((pTTF2_FiP16->a1 >> 8) & 0x00FF);
        data[10] = (uint8)pTTF2_FiP16->sfrb;
        data[11] = (uint8)pTTF2_FiP16->sfra;
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF2_FiP16_Save(TF2_FIP16 *pTTF2_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        pTTF2_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTTF2_FiP16->b1 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTTF2_FiP16->b2 = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTTF2_FiP16->a0 = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTTF2_FiP16->a1 = UINT16_TO_INT16((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTTF2_FiP16->sfrb = UINT8_TO_INT8((uint8)data[10]);
        pTTF2_FiP16->sfra = UINT8_TO_INT8((uint8)data[11]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF2_FIP16_ISLINKED)
void* TF2_FiP16_GetAddress(const TF2_FIP16* block, uint16 elementId)
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
