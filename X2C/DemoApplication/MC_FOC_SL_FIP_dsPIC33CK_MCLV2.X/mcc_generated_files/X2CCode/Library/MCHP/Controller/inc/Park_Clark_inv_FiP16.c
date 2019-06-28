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
#include "Park_Clark_inv_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Park_Clark_inv_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#if defined(__dsPIC33F__) || defined(__dsPIC33E__) || defined(__dsPIC33C__)
#include "motor_control.h"
#endif

#include "Sin_Data.h"
#define HALFPIINT16 0x4000	

#define D 			*pTPark_Clark_inv_FiP16->d
#define Q 			*pTPark_Clark_inv_FiP16->q
#define THETA		*pTPark_Clark_inv_FiP16->theta

#define FORCED_MODE_EN		*pTPark_Clark_inv_FiP16->forcedMode
#define FORCED_VALUE		*pTPark_Clark_inv_FiP16->forcedValue



#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define 	A_OUT	(pTPark_Clark_inv_FiP16->A)
#define 	B_OUT 	(pTPark_Clark_inv_FiP16->B)
#define		C_OUT	(pTPark_Clark_inv_FiP16->C)

#define 	V_ALPHA (pTPark_Clark_inv_FiP16->Valpha)
#define		V_BETA	(pTPark_Clark_inv_FiP16->Vbeta)
/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Park_Clark_inv_FiP16_Update(PARK_CLARK_INV_FIP16 *pTPark_Clark_inv_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16 a,b,c;
	int16 temp;
	int16 sin_theta, cos_theta;
	int16 alpha,beta;
	
	if(FORCED_MODE_EN != 0){ /* If forced mode enabled */
		/* alpha = FORCED_VALUE, beta = 0 , so simplified clark and SVM can be used*/
		/*calculate 0,75*alpha = alpha-alpha/4*/
		temp = FORCED_VALUE - (FORCED_VALUE>>2);
		
		/* mul by -0.55 -0x4666(Q15) then just shift with 14 not 15 then we get mul-1.1*/
	A_OUT = (((int32)(  temp  ))*-18022)>>14; 
	B_OUT = (((int32)( -temp  ))*-18022)>>14;  
	C_OUT = (((int32)( -temp  ))*-18022)>>14; 	
	
	return;
	}
	
	
#if defined(__dsPIC33F__) || defined(__dsPIC33E__) || defined(__dsPIC33C__)
    MC_DQ_T mcVDQ;    
    MC_SINCOS_T mcSinCos;    
    MC_ALPHABETA_T mcAlphaBeta;   
    MC_ABC_T mcVabc;	
	
    mcVDQ.d = D;
    mcVDQ.q = Q;
    /* Park_inverse XC16 */
    MC_CalculateSineCosine_Assembly_Ram(THETA, &mcSinCos);
    MC_TransformParkInverse_Assembly(&mcVDQ, &mcSinCos, &mcAlphaBeta);
	
	V_ALPHA = mcAlphaBeta.alpha;
	V_BETA 	= mcAlphaBeta.beta;
	
    /* Built in function uses swapped inputs, so lets change it */
    mcAlphaBeta.alpha = V_BETA;
    mcAlphaBeta.beta = V_ALPHA;
    
	/* Clark_inverse XC16 */
	MC_TransformClarkeInverseSwappedInput_Assembly(&mcAlphaBeta, &mcVabc);
    
	/* Prepare for SVM */
	a = mcVabc.a;
	b = mcVabc.b;
	c = mcVabc.c;
  
#else 

	LOOKUP16(Sin_Table16, HALFPIINT16 - THETA, cos_theta);
	LOOKUP16(Sin_Table16, THETA, sin_theta);
	
	/* Park_inverse */
	alpha = ( ((int32)D * cos_theta) - ((int32)Q * sin_theta) ) >>15;
	beta  = ( ((int32)D * sin_theta) + ((int32)Q * cos_theta) ) >>15;
	V_ALPHA = alpha ;
	V_BETA 	= beta;
	
	/* Clark_inverse */
	a = alpha;
  
	temp = ((int32)beta*0x6EDA)>>15; /* BETA*sqrt(3)/2; sqrt(3)/2 = 0.86603 (DEC) = 0x6EDA (Q15) */
  
	b =     temp - (alpha>>1);	/* (BETA*sqrt(3)/2) - ALPHA/2 */
	c = 0 - temp - (alpha>>1);	/* - (BETA*sqrt(3)/2) - ALPHA/2 */
  
#endif
/*	Space vector modulation	*/
	
	/* Calculate (MAX(A,B,C)+MIN(A,B,C))/2 */
	temp =          ( MAX ( MAX ( a , b ) , c) ) >> 1;
	temp = temp + ( ( MIN ( MIN ( a , b ) , c) ) >> 1 );
	
	/* Calculate out = (IN-temp)*(-1.1)	 */
	A_OUT = (((int32)( a - temp  ))*-0x4666)>>14; /* mul by -0.55 -0x4666(Q15) then just shift with 14 not 15 then we get mul-1.1*/ 
	B_OUT = (((int32)( b - temp  ))*-0x4666)>>14; /* mul by -0.55 -0x4666(Q15) then just shift with 14 not 15 then we get mul-1.1*/
	C_OUT = (((int32)( c - temp  ))*-0x4666)>>14; /* mul by -0.55 -0x4666(Q15) then just shift with 14 not 15 then we get mul-1.1*/ 
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Park_Clark_inv_FiP16_Init(PARK_CLARK_INV_FIP16 *pTPark_Clark_inv_FiP16)
{
    pTPark_Clark_inv_FiP16->ID = PARK_CLARK_INV_FIP16_ID;
    pTPark_Clark_inv_FiP16->A = 0;
    pTPark_Clark_inv_FiP16->B = 0;
    pTPark_Clark_inv_FiP16->C = 0;
    pTPark_Clark_inv_FiP16->Valpha = 0;
    pTPark_Clark_inv_FiP16->Vbeta = 0;
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
#if !defined(PARK_CLARK_INV_FIP16_ISLINKED)
void* Park_Clark_inv_FiP16_GetAddress(const PARK_CLARK_INV_FIP16* block, uint16 elementId)
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
