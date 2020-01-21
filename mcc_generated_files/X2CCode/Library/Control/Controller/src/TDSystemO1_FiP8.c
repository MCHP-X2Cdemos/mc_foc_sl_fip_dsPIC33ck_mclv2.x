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
#include "TDSystemO1_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO1_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 		(*pTTDSystemO1_FiP8->In)	/* Q7 */

/* Outputs */
#define OUT		(pTTDSystemO1_FiP8->Out)	/* Q7 */

/* Matrices */
#define A11		(pTTDSystemO1_FiP8->a11)	/* Qa */
#define B11		(pTTDSystemO1_FiP8->b11)	/* Qb */
#define C11		(pTTDSystemO1_FiP8->c11)	/* Qc */
#define D11 	(pTTDSystemO1_FiP8->d11)	/* Qd */

/* Shift factor of matrices */
#define SFRA11 	(pTTDSystemO1_FiP8->sfra11)	/* a */
#define SFRB11 	(pTTDSystemO1_FiP8->sfrb11)	/* b */
#define SFRC11 	(pTTDSystemO1_FiP8->sfrc11)	/* c */
#define SFRD11 	(pTTDSystemO1_FiP8->sfrd11)	/* d */

/* State */
#define X1	 	(pTTDSystemO1_FiP8->x1)		/* Q7 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO1_FiP8_Update(TDSYSTEMO1_FIP8 *pTTDSystemO1_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 temp;
	
	/* Calculation of output (with old state) */
	temp  =  ((int16)C11 * (int16)X1) >> SFRC11; 	/* y = c11*x1 */
	temp += (((int16)D11 * (int16)IN) >> SFRD11);	/* y = c11*x1 + d11*u */
	LIMIT(temp, INT8_MAX);							/* limit output to 8Bit range */
	OUT = (int8)temp;								/* assign output */ 
  
	/* Calculation of new state */
	temp  =  ((int16)A11 * (int16)X1) >> SFRA11;	/* x1 = a11*x1 */
	temp += (((int16)B11 * (int16)IN) >> SFRB11);	/* x1 = a11*x1 + b11*u */
	LIMIT(temp, INT8_MAX);							/* limit state to 8Bit range */
	X1 = (int8)temp;								/* assign state */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO1_FiP8_Init(TDSYSTEMO1_FIP8 *pTTDSystemO1_FiP8)
{
    pTTDSystemO1_FiP8->ID = TDSYSTEMO1_FIP8_ID;
    pTTDSystemO1_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset state */
     X1 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_FiP8_Load(const TDSYSTEMO1_FIP8 *pTTDSystemO1_FiP8, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTTDSystemO1_FiP8->a11;
        data[1] = (uint8)pTTDSystemO1_FiP8->b11;
        data[2] = (uint8)pTTDSystemO1_FiP8->c11;
        data[3] = (uint8)pTTDSystemO1_FiP8->d11;
        data[4] = (uint8)pTTDSystemO1_FiP8->sfra11;
        data[5] = (uint8)pTTDSystemO1_FiP8->sfrb11;
        data[6] = (uint8)pTTDSystemO1_FiP8->sfrc11;
        data[7] = (uint8)pTTDSystemO1_FiP8->sfrd11;
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO1_FiP8_Save(TDSYSTEMO1_FIP8 *pTTDSystemO1_FiP8, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        pTTDSystemO1_FiP8->a11 = UINT8_TO_INT8((uint8)data[0]);
        pTTDSystemO1_FiP8->b11 = UINT8_TO_INT8((uint8)data[1]);
        pTTDSystemO1_FiP8->c11 = UINT8_TO_INT8((uint8)data[2]);
        pTTDSystemO1_FiP8->d11 = UINT8_TO_INT8((uint8)data[3]);
        pTTDSystemO1_FiP8->sfra11 = ((uint8)data[4]);
        pTTDSystemO1_FiP8->sfrb11 = ((uint8)data[5]);
        pTTDSystemO1_FiP8->sfrc11 = ((uint8)data[6]);
        pTTDSystemO1_FiP8->sfrd11 = ((uint8)data[7]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO1_FIP8_ISLINKED)
void* TDSystemO1_FiP8_GetAddress(const TDSYSTEMO1_FIP8* block, uint16 elementId)
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
