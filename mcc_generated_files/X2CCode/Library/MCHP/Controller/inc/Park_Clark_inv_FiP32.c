/*
 * Copyright (c) {YEAR}, {ORGANIZATION_NAME}, {ORGANIZATION_WEB}
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#include "Park_Clark_inv_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Park_Clark_inv_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"
#define     HALFPIINT32 0x40000000

#define D 			*pTPark_Clark_inv_FiP32->d
#define Q 			*pTPark_Clark_inv_FiP32->q
#define THETA		*pTPark_Clark_inv_FiP32->theta

#define FORCED_MODE_EN		*pTPark_Clark_inv_FiP32->forcedMode
#define FORCED_VALUE		*pTPark_Clark_inv_FiP32->forcedValue

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define 	A_OUT	(pTPark_Clark_inv_FiP32->A)
#define 	B_OUT 	(pTPark_Clark_inv_FiP32->B)
#define		C_OUT	(pTPark_Clark_inv_FiP32->C)

#define 	V_ALPHA (pTPark_Clark_inv_FiP32->Valpha)
#define		V_BETA	(pTPark_Clark_inv_FiP32->Vbeta)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Park_Clark_inv_FiP32_Update(PARK_CLARK_INV_FIP32 *pTPark_Clark_inv_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 sin_theta, cos_theta;
	int32 alpha, beta, a, b, c;
	int32 temp;
		
	if(FORCED_MODE_EN != 0){ /* If forced mode enabled */
		/* alpha = FORCED_VALUE, beta = 0 , so simplified clark and SVM can be used*/
		/*calculate 0,75*alpha = alpha-alpha/4*/
		temp = FORCED_VALUE - (FORCED_VALUE>>2);
		
		/* mul by -0.55 -0x46666666(Q31) then just shift with 30 not 31*/ 
		A_OUT = (((int64)(  temp ))*-0x46666666)>>30;
		B_OUT = (((int64)( -temp ))*-0x46666666)>>30;
		C_OUT = (((int64)( -temp ))*-0x46666666)>>30;	
	
		return;
	}
/*Park_inverse*/
	/* Calculate alpha = d.cos(theta) - q.sin(theta)
	beta = d.sin(theta) + q.cos(theta*/

	LOOKUP32(Sin_Table32, HALFPIINT32 - THETA, cos_theta);
	LOOKUP32(Sin_Table32, THETA, sin_theta);
	
	alpha = (int32) (( ( (int64) D * cos_theta ) - ( (int64) Q * sin_theta ) )>>31);
	beta  = (int32) (( ( (int64) D * sin_theta ) + ( (int64) Q * cos_theta ) )>>31);
	
	V_ALPHA = alpha ;
	V_BETA 	= beta;
  
	/*Clark_inverse*/
	a = alpha;
  
	temp = ((int64)beta*0x6ED9EBA1)>>31; /* BETA*sqrt(3)/2, sqrt(3)/2 = 0.8660254037(DEC) = 0x6ED9EBA1 (Q31) */
  
	b =     temp - (alpha>>1);	/* (BETA*sqrt(3)/2) - ALPHA/2 */
	c = 0 - temp - (alpha>>1);	/* - (BETA*sqrt(3)/2) - ALPHA/2 */ 
  
	/*Space Vector Modulation*/
  
  	/* Calculate (MAX(A,B,C)+MIN(A,B,C))/2 */
	temp =          ( MAX ( MAX ( a , b ) , c ) ) >> 1;
	temp = temp + ( ( MIN ( MIN ( a , b ) , c ) ) >> 1 );
	
	/* Calculate out = (IN-temp)*(-1.1)  */
	A_OUT = (((int64)( a - temp  ))*-0x46666666)>>30; /* mul by -0.55 -0x46666666(Q31) then just shift with 30 not 31*/ 
	B_OUT = (((int64)( b - temp  ))*-0x46666666)>>30; /* mul by -0.55 -0x46666666(Q31) then just shift with 30 not 31*/ 
	C_OUT = (((int64)( c - temp  ))*-0x46666666)>>30; /* mul by -0.55 -0x46666666(Q31) then just shift with 30 not 31*/ 

	

	
	

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Park_Clark_inv_FiP32_Init(PARK_CLARK_INV_FIP32 *pTPark_Clark_inv_FiP32)
{
    pTPark_Clark_inv_FiP32->ID = PARK_CLARK_INV_FIP32_ID;
    pTPark_Clark_inv_FiP32->A = 0;
    pTPark_Clark_inv_FiP32->B = 0;
    pTPark_Clark_inv_FiP32->C = 0;
    pTPark_Clark_inv_FiP32->Valpha = 0;
    pTPark_Clark_inv_FiP32->Vbeta = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** No Load function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** No Save function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PARK_CLARK_INV_FIP32_ISLINKED)
void* Park_Clark_inv_FiP32_GetAddress(const PARK_CLARK_INV_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->d;
            break;
        case 2:
            addr = (void*)block->q;
            break;
        case 3:
            addr = (void*)block->theta;
            break;
        case 4:
            addr = (void*)block->forcedMode;
            break;
        case 5:
            addr = (void*)block->forcedValue;
            break;
        case 6:
            addr = (void*)&block->A;
            break;
        case 7:
            addr = (void*)&block->B;
            break;
        case 8:
            addr = (void*)&block->C;
            break;
        case 9:
            addr = (void*)&block->Valpha;
            break;
        case 10:
            addr = (void*)&block->Vbeta;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
