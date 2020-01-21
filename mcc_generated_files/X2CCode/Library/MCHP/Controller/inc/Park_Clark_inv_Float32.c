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
#include "Park_Clark_inv_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Park_Clark_inv_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

#define D 			*pTPark_Clark_inv_Float32->d
#define Q 			*pTPark_Clark_inv_Float32->q
#define THETA		*pTPark_Clark_inv_Float32->theta

#define FORCED_MODE_EN		*pTPark_Clark_inv_Float32->forcedMode
#define FORCED_VALUE		*pTPark_Clark_inv_Float32->forcedValue

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define 	A_OUT	(pTPark_Clark_inv_Float32->A)
#define 	B_OUT 	(pTPark_Clark_inv_Float32->B)
#define		C_OUT	(pTPark_Clark_inv_Float32->C)

#define 	V_ALPHA (pTPark_Clark_inv_Float32->Valpha)
#define		V_BETA	(pTPark_Clark_inv_Float32->Vbeta)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Park_Clark_inv_Float32_Update(PARK_CLARK_INV_FLOAT32 *pTPark_Clark_inv_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 sin_theta, cos_theta;
	float32 alpha, beta;
	float32 a,b,c;
 	float32 temp; 
	
	if(FORCED_MODE_EN != 0){ /* If forced mode enabled */
	/* alpha = FORCED_VALUE, beta = 0 , so simplified clark and SVM can be used*/
			
		/*calculate 0,75*alpha = alpha-alpha/4*/
		temp = FORCED_VALUE*0.75;
		
		A_OUT = (  temp )*-1.1;
		B_OUT = ( -temp )*-1.1;
		C_OUT = ( -temp )*-1.1;	
	
		return;
	}
	
/*Park_inverse*/
	cos_theta = cos ( THETA );
	sin_theta = sin ( THETA );
	
	alpha = ( D * cos_theta ) - ( Q * sin_theta );
	beta  = ( D * sin_theta ) + ( Q * cos_theta );
  
  	V_ALPHA = alpha ;
	V_BETA 	= beta;

/*Clark_inverse*/
	a =  alpha;		/*sqrt(3)/2 = 0.8660254*/
	b = (alpha * -0.5 ) + ( beta * 0.8660254); /* (BETA*sqrt(3)/2) - ALPHA/2 */
	c = (alpha * -0.5 ) + ( beta * -0.8660254); /* - (BETA*sqrt(3)/2) - ALPHA/2 */

/*Space vector modulation*/

	/* Calculate (MAX(A,B,C)+MIN(A,B,C))/2 */
	temp =          ( MAX ( MAX ( a , b ) , c) );
	temp = temp + ( ( MIN ( MIN ( a , b ) , c) ));
	temp = temp * 0.5;
	
	/* Calculate out = (IN-temp)*(-1.1) */
	A_OUT = ( a - temp  )*-1.1; 
	B_OUT = ( b - temp  )*-1.1; 
	C_OUT = ( c - temp  )*-1.1; 


/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Park_Clark_inv_Float32_Init(PARK_CLARK_INV_FLOAT32 *pTPark_Clark_inv_Float32)
{
    pTPark_Clark_inv_Float32->ID = PARK_CLARK_INV_FLOAT32_ID;
    pTPark_Clark_inv_Float32->A = 0;
    pTPark_Clark_inv_Float32->B = 0;
    pTPark_Clark_inv_Float32->C = 0;
    pTPark_Clark_inv_Float32->Valpha = 0;
    pTPark_Clark_inv_Float32->Vbeta = 0;
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
#if !defined(PARK_CLARK_INV_FLOAT32_ISLINKED)
void* Park_Clark_inv_Float32_GetAddress(const PARK_CLARK_INV_FLOAT32* block, uint16 elementId)
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
