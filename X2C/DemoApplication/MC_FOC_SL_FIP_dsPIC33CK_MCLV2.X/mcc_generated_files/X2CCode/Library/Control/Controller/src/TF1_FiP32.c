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
#include "TF1_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TF1_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN			(*pTTF1_FiP32->In)		/* Q31 */

/* Outputs */
#define OUT			(pTTF1_FiP32->Out)		/* Q31 */

/* Parameter */
#define	A0			(pTTF1_FiP32->a0)		/* Qa */
#define	B0			(pTTF1_FiP32->b0)		/* Qb */
#define	B1			(pTTF1_FiP32->b1)		/* Qb */
#define SFRA		(pTTF1_FiP32->sfra)		/* a */
#define SFRB		(pTTF1_FiP32->sfrb)		/* b */

/* Variables */
#define IN_OLD		(pTTF1_FiP32->in_old)	/* Q31 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TF1_FiP32_Update(TF1_FIP32 *pTTF1_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 temp;

	temp  = ((int64)B0 * (int64)IN_OLD);		/* y = b0.u(k-1) */
	temp += ((int64)B1 * (int64)IN);			/* y = b0.u(k-1) + b1.u(k) */
	temp  = temp >> SFRB;		/* Q31 */
	temp -= (((int64)A0 * (int64)OUT) >> SFRA);	/* y = b0.u(k-1) + b1.u(k) - a0.y(k-1) */

	/* check for overflow, though it shouldn't be possible to get one */
	if (temp > (int64)INT32_MAX)
	{
		temp = (int64)INT32_MAX;
	}
	else
	{
		if (temp < -(int64)INT32_MAX)
		{
			temp = -(int64)INT32_MAX;
		}
	}

	/* save values for next update call and assign output */
	IN_OLD = IN;
	OUT    = (int32)temp;


/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TF1_FiP32_Init(TF1_FIP32 *pTTF1_FiP32)
{
    pTTF1_FiP32->ID = TF1_FIP32_ID;
    pTTF1_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset old input value */
     IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_FiP32_Load(const TF1_FIP32 *pTTF1_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)14 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTF1_FiP32->b0 & 0x000000FF);
        data[1] = (uint8)((pTTF1_FiP32->b0 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTTF1_FiP32->b0 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTTF1_FiP32->b0 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTTF1_FiP32->b1 & 0x000000FF);
        data[5] = (uint8)((pTTF1_FiP32->b1 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTTF1_FiP32->b1 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTTF1_FiP32->b1 >> 24) & 0x000000FF);
        data[8] = (uint8)(pTTF1_FiP32->a0 & 0x000000FF);
        data[9] = (uint8)((pTTF1_FiP32->a0 >> 8) & 0x000000FF);
        data[10] = (uint8)((pTTF1_FiP32->a0 >> 16) & 0x000000FF);
        data[11] = (uint8)((pTTF1_FiP32->a0 >> 24) & 0x000000FF);
        data[12] = (uint8)pTTF1_FiP32->sfrb;
        data[13] = (uint8)pTTF1_FiP32->sfra;
        *dataLength = (uint16)14;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TF1_FiP32_Save(TF1_FIP32 *pTTF1_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)14)
    {
        error = (uint8)1;
    }
    else
    {
        pTTF1_FiP32->b0 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTTF1_FiP32->b1 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTTF1_FiP32->a0 = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTTF1_FiP32->sfrb = UINT8_TO_INT8((uint8)data[12]);
        pTTF1_FiP32->sfra = UINT8_TO_INT8((uint8)data[13]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TF1_FIP32_ISLINKED)
void* TF1_FiP32_GetAddress(const TF1_FIP32* block, uint16 elementId)
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
