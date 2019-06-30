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
#include "TDSystemO2_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(TDSystemO2_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs*/
#define IN1 	(*pTTDSystemO2_FiP16->In1)
#define IN2 	(*pTTDSystemO2_FiP16->In2)

/* Outputs*/
#define OUT1	(pTTDSystemO2_FiP16->Out1)
#define OUT2	(pTTDSystemO2_FiP16->Out2)

/* Matrices */
#define A11		(pTTDSystemO2_FiP16->a11)
#define A12		(pTTDSystemO2_FiP16->a12)
#define A21		(pTTDSystemO2_FiP16->a21)
#define A22		(pTTDSystemO2_FiP16->a22)
#define B11		(pTTDSystemO2_FiP16->b11)
#define B12		(pTTDSystemO2_FiP16->b12)
#define B21		(pTTDSystemO2_FiP16->b21)
#define B22		(pTTDSystemO2_FiP16->b22)

/* Shift factor of matrices */
#define SFRA11 	(pTTDSystemO2_FiP16->sfra11)
#define SFRA12 	(pTTDSystemO2_FiP16->sfra12)
#define SFRA21 	(pTTDSystemO2_FiP16->sfra21)
#define SFRA22 	(pTTDSystemO2_FiP16->sfra22)
#define SFRB11 	(pTTDSystemO2_FiP16->sfrb11)
#define SFRB12 	(pTTDSystemO2_FiP16->sfrb12)
#define SFRB21 	(pTTDSystemO2_FiP16->sfrb21)
#define SFRB22 	(pTTDSystemO2_FiP16->sfrb22)

/* States */
#define X1		(pTTDSystemO2_FiP16->x1)
#define X2		(pTTDSystemO2_FiP16->x2)


/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void TDSystemO2_FiP16_Update(TDSYSTEMO2_FIP16 *pTTDSystemO2_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 temp;
	int16 state1;


	/* Calculation of output (= old state) */
	OUT1 = X1;
	OUT2 = X2;

	/* Calculation of new state1 (= output1) */
	temp  =  ((int32)A11 * (int32)X1)  >> SFRA11;	/* x1 = a11*x1 */
	temp += (((int32)A12 * (int32)X2)  >> SFRA12);	/* x1 = a11*x1 + a12*x2 */
	temp += (((int32)B11 * (int32)IN1) >> SFRB11);	/* x1 = a11*x1 + a12*x2 + b11*u1 */
	temp += (((int32)B12 * (int32)IN2) >> SFRB12);	/* x1 = a11*x1 + a12*x2 + b11*u1 + b12*u2 */
	LIMIT(temp, INT16_MAX);							/* limit state to 16Bit range */
	state1 = (int16)temp;

	/* Calculation of new state2 (= output2) */
	temp  =  ((int32)A21 * (int32)X1)  >> SFRA21;	/* x2 = a21*x1 */
	temp += (((int32)A22 * (int32)X2)  >> SFRA22);	/* x2 = a21*x1 + a22*x2 */
	temp += (((int32)B21 * (int32)IN1) >> SFRB21);	/* x2 = a21*x1 + a22*x2 + b21*u1 */
	temp += (((int32)B22 * (int32)IN2) >> SFRB22);	/* x2 = a21*x1 + a22*x2 + b21*u1 + b22*u2 */
	LIMIT(temp, INT16_MAX);							/* limit state to 16Bit range */

	/* assign states */
	X1 = (int16)state1;
	X2 = (int16)temp;


/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void TDSystemO2_FiP16_Init(TDSYSTEMO2_FIP16 *pTTDSystemO2_FiP16)
{
    pTTDSystemO2_FiP16->ID = TDSYSTEMO2_FIP16_ID;
    pTTDSystemO2_FiP16->Out1 = 0;
    pTTDSystemO2_FiP16->Out2 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     /* reset states */
     X1 = 0;
     X2 = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_FiP16_Load(const TDSYSTEMO2_FIP16 *pTTDSystemO2_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)24 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTTDSystemO2_FiP16->a11 & 0x00FF);
        data[1] = (uint8)((pTTDSystemO2_FiP16->a11 >> 8) & 0x00FF);
        data[2] = (uint8)(pTTDSystemO2_FiP16->a12 & 0x00FF);
        data[3] = (uint8)((pTTDSystemO2_FiP16->a12 >> 8) & 0x00FF);
        data[4] = (uint8)(pTTDSystemO2_FiP16->a21 & 0x00FF);
        data[5] = (uint8)((pTTDSystemO2_FiP16->a21 >> 8) & 0x00FF);
        data[6] = (uint8)(pTTDSystemO2_FiP16->a22 & 0x00FF);
        data[7] = (uint8)((pTTDSystemO2_FiP16->a22 >> 8) & 0x00FF);
        data[8] = (uint8)(pTTDSystemO2_FiP16->b11 & 0x00FF);
        data[9] = (uint8)((pTTDSystemO2_FiP16->b11 >> 8) & 0x00FF);
        data[10] = (uint8)(pTTDSystemO2_FiP16->b12 & 0x00FF);
        data[11] = (uint8)((pTTDSystemO2_FiP16->b12 >> 8) & 0x00FF);
        data[12] = (uint8)(pTTDSystemO2_FiP16->b21 & 0x00FF);
        data[13] = (uint8)((pTTDSystemO2_FiP16->b21 >> 8) & 0x00FF);
        data[14] = (uint8)(pTTDSystemO2_FiP16->b22 & 0x00FF);
        data[15] = (uint8)((pTTDSystemO2_FiP16->b22 >> 8) & 0x00FF);
        data[16] = (uint8)pTTDSystemO2_FiP16->sfra11;
        data[17] = (uint8)pTTDSystemO2_FiP16->sfra12;
        data[18] = (uint8)pTTDSystemO2_FiP16->sfra21;
        data[19] = (uint8)pTTDSystemO2_FiP16->sfra22;
        data[20] = (uint8)pTTDSystemO2_FiP16->sfrb11;
        data[21] = (uint8)pTTDSystemO2_FiP16->sfrb12;
        data[22] = (uint8)pTTDSystemO2_FiP16->sfrb21;
        data[23] = (uint8)pTTDSystemO2_FiP16->sfrb22;
        *dataLength = (uint16)24;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 TDSystemO2_FiP16_Save(TDSYSTEMO2_FIP16 *pTTDSystemO2_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)24)
    {
        error = (uint8)1;
    }
    else
    {
        pTTDSystemO2_FiP16->a11 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTTDSystemO2_FiP16->a12 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTTDSystemO2_FiP16->a21 = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTTDSystemO2_FiP16->a22 = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTTDSystemO2_FiP16->b11 = UINT16_TO_INT16((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTTDSystemO2_FiP16->b12 = UINT16_TO_INT16((uint16)data[10] + \
            ((uint16)data[11] << 8));
        pTTDSystemO2_FiP16->b21 = UINT16_TO_INT16((uint16)data[12] + \
            ((uint16)data[13] << 8));
        pTTDSystemO2_FiP16->b22 = UINT16_TO_INT16((uint16)data[14] + \
            ((uint16)data[15] << 8));
        pTTDSystemO2_FiP16->sfra11 = ((uint8)data[16]);
        pTTDSystemO2_FiP16->sfra12 = ((uint8)data[17]);
        pTTDSystemO2_FiP16->sfra21 = ((uint8)data[18]);
        pTTDSystemO2_FiP16->sfra22 = ((uint8)data[19]);
        pTTDSystemO2_FiP16->sfrb11 = ((uint8)data[20]);
        pTTDSystemO2_FiP16->sfrb12 = ((uint8)data[21]);
        pTTDSystemO2_FiP16->sfrb21 = ((uint8)data[22]);
        pTTDSystemO2_FiP16->sfrb22 = ((uint8)data[23]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(TDSYSTEMO2_FIP16_ISLINKED)
void* TDSystemO2_FiP16_GetAddress(const TDSYSTEMO2_FIP16* block, uint16 elementId)
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
