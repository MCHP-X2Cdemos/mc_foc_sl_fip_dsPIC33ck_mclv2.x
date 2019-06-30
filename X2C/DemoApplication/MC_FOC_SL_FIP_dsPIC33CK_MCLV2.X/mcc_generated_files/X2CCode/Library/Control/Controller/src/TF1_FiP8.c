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
/**     Description:	First order transfer function                        **/
/**						Calculation:										 **/
/**	       						 b1.z + b0							   		 **/
/** 						y = ----------- u						   		 **/
/**          					   z + a0									 **/
/**							-> y(k) = u(k).b1 + u(k-1).b0 - y(k-1).a0		 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "TF1_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF1_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF1_FiP8->In)		/* Q7 */

/* Outputs */
#define OUT			(pTTF1_FiP8->Out)		/* Q7 */

/* Parameter */
#define	A0			(pTTF1_FiP8->a0)		/* Qa */
#define	B0			(pTTF1_FiP8->b0)		/* Qb */
#define	B1			(pTTF1_FiP8->b1)		/* Qb */
#define SFRA		(pTTF1_FiP8->sfra)		/* a */
#define SFRB		(pTTF1_FiP8->sfrb)		/* b */

/* Variables */
#define IN_OLD		(pTTF1_FiP8->in_old)	/* Q7 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF1_FiP8_Update(TF1_FIP8 *pTTF1_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 temp;

	temp  = ((int16)B0 * (int16)IN_OLD);		/* y = b0.u(k-1) */
	temp += ((int16)B1 * (int16)IN);			/* y = b0.u(k-1) + b1.u(k) */
	temp  = temp >> SFRB;		/* Q7 */
	temp -= (((int16)A0 * (int16)OUT) >> SFRA);	/* y = b0.u(k-1) + b1.u(k) - a0.y(k-1) */

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
	IN_OLD = IN;
	OUT    = (int8)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF1_FiP8_Init(TF1_FIP8 *pTTF1_FiP8)
{
    pTTF1_FiP8->ID = TF1_FIP8_ID;
    pTTF1_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old input value */
     IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_FiP8_Load(const TF1_FIP8 *pTTF1_FiP8, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)5 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTTF1_FiP8->b0;
        data[1] = (uint8)pTTF1_FiP8->b1;
        data[2] = (uint8)pTTF1_FiP8->a0;
        data[3] = (uint8)pTTF1_FiP8->sfrb;
        data[4] = (uint8)pTTF1_FiP8->sfra;
        *dataLength = (uint16)5;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_FiP8_Save(TF1_FIP8 *pTTF1_FiP8, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)5)
    {
        error = (uint8)1;
    }
    else
    {
        pTTF1_FiP8->b0 = UINT8_TO_INT8((uint8)data[0]);
        pTTF1_FiP8->b1 = UINT8_TO_INT8((uint8)data[1]);
        pTTF1_FiP8->a0 = UINT8_TO_INT8((uint8)data[2]);
        pTTF1_FiP8->sfrb = UINT8_TO_INT8((uint8)data[3]);
        pTTF1_FiP8->sfra = UINT8_TO_INT8((uint8)data[4]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF1_FIP8_ISLINKED)
void* TF1_FiP8_GetAddress(const TF1_FIP8* block, uint16 elementId)
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
