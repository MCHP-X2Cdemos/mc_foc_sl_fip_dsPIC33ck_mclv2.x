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
/**     Description: 2nd Order Time Discrete System with 2 in- and outputs. 										 **/
/**					 Calculation:																					 **/
/**						x(k+1) = A*x(k) + B*u(k)																	 **/
/**						y(k)   =   x(k)																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "TDSystemO2_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO2_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs*/
#define IN1 	(*pTTDSystemO2_FiP8->In1)
#define IN2 	(*pTTDSystemO2_FiP8->In2)

/* Outputs*/
#define OUT1	(pTTDSystemO2_FiP8->Out1)
#define OUT2	(pTTDSystemO2_FiP8->Out2)

/* Matrices */
#define A11		(pTTDSystemO2_FiP8->a11)
#define A12		(pTTDSystemO2_FiP8->a12)
#define A21		(pTTDSystemO2_FiP8->a21)
#define A22		(pTTDSystemO2_FiP8->a22)
#define B11		(pTTDSystemO2_FiP8->b11)
#define B12		(pTTDSystemO2_FiP8->b12)
#define B21		(pTTDSystemO2_FiP8->b21)
#define B22		(pTTDSystemO2_FiP8->b22)

/* Shift factor of matrices */
#define SFRA11 	(pTTDSystemO2_FiP8->sfra11)
#define SFRA12 	(pTTDSystemO2_FiP8->sfra12)
#define SFRA21 	(pTTDSystemO2_FiP8->sfra21)
#define SFRA22 	(pTTDSystemO2_FiP8->sfra22)
#define SFRB11 	(pTTDSystemO2_FiP8->sfrb11)
#define SFRB12 	(pTTDSystemO2_FiP8->sfrb12)
#define SFRB21 	(pTTDSystemO2_FiP8->sfrb21)
#define SFRB22 	(pTTDSystemO2_FiP8->sfrb22)

/* States */
#define X1		(pTTDSystemO2_FiP8->x1)
#define X2		(pTTDSystemO2_FiP8->x2)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO2_FiP8_Update(TDSYSTEMO2_FIP8 *pTTDSystemO2_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 temp;
	int8 state1;

	/* Calculation of output (= old state) */
	OUT1 = X1;
	OUT2 = X2;

	/* Calculation of new state1 */
	temp  =  ((int16)A11 * (int16)X1)  >> SFRA11;	/* x1 = a11*x1 */
	temp += (((int16)A12 * (int16)X2)  >> SFRA12);	/* x1 = a11*x1 + a12*x2 */
	temp += (((int16)B11 * (int16)IN1) >> SFRB11);	/* x1 = a11*x1 + a12*x2 + b11*u1 */
	temp += (((int16)B12 * (int16)IN2) >> SFRB12);	/* x1 = a11*x1 + a12*x2 + b11*u1 + b12*u2 */
	LIMIT(temp, INT8_MAX);							/* limit state to 8Bit range */
	state1 = (int8)temp;

	/* Calculation of new state2 */
	temp  =  ((int16)A21 * (int16)X1)  >> SFRA21;	/* x2 = a21*x1 */
	temp += (((int16)A22 * (int16)X2)  >> SFRA22);	/* x2 = a21*x1 + a22*x2 */
	temp += (((int16)B21 * (int16)IN1) >> SFRB21);	/* x2 = a21*x1 + a22*x2 + b21*u1 */
	temp += (((int16)B22 * (int16)IN2) >> SFRB22);	/* x2 = a21*x1 + a22*x2 + b21*u1 + b22*u2 */
	LIMIT(temp, INT8_MAX);							/* limit state to 8Bit range */

	/* assign states */
	X1 = (int8)state1;
	X2 = (int8)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO2_FiP8_Init(TDSYSTEMO2_FIP8 *pTTDSystemO2_FiP8)
{
    pTTDSystemO2_FiP8->ID = TDSYSTEMO2_FIP8_ID;
    pTTDSystemO2_FiP8->Out1 = 0;
    pTTDSystemO2_FiP8->Out2 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset states */
     X1 = 0;
     X2 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_FiP8_Load(const TDSYSTEMO2_FIP8 *pTTDSystemO2_FiP8, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)16 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTTDSystemO2_FiP8->a11;
        data[1] = (uint8)pTTDSystemO2_FiP8->a12;
        data[2] = (uint8)pTTDSystemO2_FiP8->a21;
        data[3] = (uint8)pTTDSystemO2_FiP8->a22;
        data[4] = (uint8)pTTDSystemO2_FiP8->b11;
        data[5] = (uint8)pTTDSystemO2_FiP8->b12;
        data[6] = (uint8)pTTDSystemO2_FiP8->b21;
        data[7] = (uint8)pTTDSystemO2_FiP8->b22;
        data[8] = (uint8)pTTDSystemO2_FiP8->sfra11;
        data[9] = (uint8)pTTDSystemO2_FiP8->sfra12;
        data[10] = (uint8)pTTDSystemO2_FiP8->sfra21;
        data[11] = (uint8)pTTDSystemO2_FiP8->sfra22;
        data[12] = (uint8)pTTDSystemO2_FiP8->sfrb11;
        data[13] = (uint8)pTTDSystemO2_FiP8->sfrb12;
        data[14] = (uint8)pTTDSystemO2_FiP8->sfrb21;
        data[15] = (uint8)pTTDSystemO2_FiP8->sfrb22;
        *dataLength = (uint16)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_FiP8_Save(TDSYSTEMO2_FIP8 *pTTDSystemO2_FiP8, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)16)
    {
        error = (uint8)1;
    }
    else
    {
        pTTDSystemO2_FiP8->a11 = UINT8_TO_INT8((uint8)data[0]);
        pTTDSystemO2_FiP8->a12 = UINT8_TO_INT8((uint8)data[1]);
        pTTDSystemO2_FiP8->a21 = UINT8_TO_INT8((uint8)data[2]);
        pTTDSystemO2_FiP8->a22 = UINT8_TO_INT8((uint8)data[3]);
        pTTDSystemO2_FiP8->b11 = UINT8_TO_INT8((uint8)data[4]);
        pTTDSystemO2_FiP8->b12 = UINT8_TO_INT8((uint8)data[5]);
        pTTDSystemO2_FiP8->b21 = UINT8_TO_INT8((uint8)data[6]);
        pTTDSystemO2_FiP8->b22 = UINT8_TO_INT8((uint8)data[7]);
        pTTDSystemO2_FiP8->sfra11 = ((uint8)data[8]);
        pTTDSystemO2_FiP8->sfra12 = ((uint8)data[9]);
        pTTDSystemO2_FiP8->sfra21 = ((uint8)data[10]);
        pTTDSystemO2_FiP8->sfra22 = ((uint8)data[11]);
        pTTDSystemO2_FiP8->sfrb11 = ((uint8)data[12]);
        pTTDSystemO2_FiP8->sfrb12 = ((uint8)data[13]);
        pTTDSystemO2_FiP8->sfrb21 = ((uint8)data[14]);
        pTTDSystemO2_FiP8->sfrb22 = ((uint8)data[15]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO2_FIP8_ISLINKED)
void* TDSystemO2_FiP8_GetAddress(const TDSYSTEMO2_FIP8* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->In2;
            break;
        case 3:
            addr = (void*)&block->Out1;
            break;
        case 4:
            addr = (void*)&block->Out2;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
