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
/**     Description: 1st Order Time Discrete System                         										 **/
/**					 Calculation:																					 **/
/**						x(k+1) = a11*x(k) + b11*u(k)																 **/
/**						y(k)   = c11*x(k) + d11*u(k)																 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TDSystemO1_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO1_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 		(*pTTDSystemO1_FiP32->In)		/* Q31 */

/* Outputs */
#define OUT		(pTTDSystemO1_FiP32->Out)		/* Q31 */

/* Matrices */
#define A11		(pTTDSystemO1_FiP32->a11)		/* Qa */
#define B11		(pTTDSystemO1_FiP32->b11)		/* Qb */
#define C11		(pTTDSystemO1_FiP32->c11)		/* Qc */
#define D11 	(pTTDSystemO1_FiP32->d11)		/* Qd */

/* Shift factor of matrices */
#define SFRA11 	(pTTDSystemO1_FiP32->sfra11)	/* a */
#define SFRB11 	(pTTDSystemO1_FiP32->sfrb11)	/* b */
#define SFRC11 	(pTTDSystemO1_FiP32->sfrc11)	/* c */
#define SFRD11 	(pTTDSystemO1_FiP32->sfrd11)	/* d */

/* State */
#define X1 		(pTTDSystemO1_FiP32->x1)		/* Q31 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO1_FiP32_Update(TDSYSTEMO1_FIP32 *pTTDSystemO1_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 temp;
	
	/* Calculation of output (with old state) */
	temp  =  ((int64)C11 * (int64)X1) >> SFRC11; 	/* y = c11*x1 */
	temp += (((int64)D11 * (int64)IN) >> SFRD11);	/* y = c11*x1 + d11*u */
	LIMIT(temp, INT32_MAX);							/* limit output to 32Bit range */
	OUT = (int32)temp;								/* assign output  */
  
	/* Calculation of new state */
	temp  =  ((int64)A11 * (int64)X1) >> SFRA11;	/* x1 = a11*x1 */
	temp += (((int64)B11 * (int64)IN) >> SFRB11);	/* x1 = a11*x1 + b11*u */
	LIMIT(temp, INT32_MAX);							/* limit state to 32Bit range */
	X1 = (int32)temp;								/* assign state */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO1_FiP32_Init(TDSYSTEMO1_FIP32 *pTTDSystemO1_FiP32)
{
    pTTDSystemO1_FiP32->ID = TDSYSTEMO1_FIP32_ID;
    pTTDSystemO1_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset state */
     X1 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_FiP32_Load(const TDSYSTEMO1_FIP32 *pTTDSystemO1_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)20 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTDSystemO1_FiP32->a11 & 0x000000FF);
        data[1] = (uint8)((pTTDSystemO1_FiP32->a11 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTTDSystemO1_FiP32->a11 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTTDSystemO1_FiP32->a11 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTTDSystemO1_FiP32->b11 & 0x000000FF);
        data[5] = (uint8)((pTTDSystemO1_FiP32->b11 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTTDSystemO1_FiP32->b11 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTTDSystemO1_FiP32->b11 >> 24) & 0x000000FF);
        data[8] = (uint8)(pTTDSystemO1_FiP32->c11 & 0x000000FF);
        data[9] = (uint8)((pTTDSystemO1_FiP32->c11 >> 8) & 0x000000FF);
        data[10] = (uint8)((pTTDSystemO1_FiP32->c11 >> 16) & 0x000000FF);
        data[11] = (uint8)((pTTDSystemO1_FiP32->c11 >> 24) & 0x000000FF);
        data[12] = (uint8)(pTTDSystemO1_FiP32->d11 & 0x000000FF);
        data[13] = (uint8)((pTTDSystemO1_FiP32->d11 >> 8) & 0x000000FF);
        data[14] = (uint8)((pTTDSystemO1_FiP32->d11 >> 16) & 0x000000FF);
        data[15] = (uint8)((pTTDSystemO1_FiP32->d11 >> 24) & 0x000000FF);
        data[16] = (uint8)pTTDSystemO1_FiP32->sfra11;
        data[17] = (uint8)pTTDSystemO1_FiP32->sfrb11;
        data[18] = (uint8)pTTDSystemO1_FiP32->sfrc11;
        data[19] = (uint8)pTTDSystemO1_FiP32->sfrd11;
        *dataLength = (uint16)20;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_FiP32_Save(TDSYSTEMO1_FIP32 *pTTDSystemO1_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)20)
    {
        error = (uint8)1;
    }
    else
    {
        pTTDSystemO1_FiP32->a11 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTTDSystemO1_FiP32->b11 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTTDSystemO1_FiP32->c11 = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTTDSystemO1_FiP32->d11 = UINT32_TO_INT32((uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24));
        pTTDSystemO1_FiP32->sfra11 = ((uint8)data[16]);
        pTTDSystemO1_FiP32->sfrb11 = ((uint8)data[17]);
        pTTDSystemO1_FiP32->sfrc11 = ((uint8)data[18]);
        pTTDSystemO1_FiP32->sfrd11 = ((uint8)data[19]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO1_FIP32_ISLINKED)
void* TDSystemO1_FiP32_GetAddress(const TDSYSTEMO1_FIP32* block, uint16 elementId)
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
