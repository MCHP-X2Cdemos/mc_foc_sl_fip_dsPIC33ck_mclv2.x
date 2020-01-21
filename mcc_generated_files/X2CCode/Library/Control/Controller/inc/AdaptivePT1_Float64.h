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
/**     Description:    First order proportional element with adjustable cut-off frequency							 **/
/**						Calculation:																				 **/
/**	       						  b0							   													 **/
/** 						y = ------ u						   		 											 **/
/**          					z + a0									 											 **/
/**							-> y(k) = u(k-1).b0 - y(k-1).a0        													 **/
/**								with a0 = -exp(-2*pi*Ts*fc)															 **/
/**								and  b0 = V*(1 - exp(-2*pi*Ts*fc))													 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#ifndef ADAPTIVEPT1_FLOAT64_H
#define ADAPTIVEPT1_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(ADAPTIVEPT1_FLOAT64_ISLINKED)
#define ADAPTIVEPT1_FLOAT64_ID ((uint16)3412)

typedef struct {
    uint16          ID;
    float64         *In;
    float64         *fc;
    float64         Out;
    float64         w_scale;
    float64         gain;
    float64         in_old;
} ADAPTIVEPT1_FLOAT64;

#define ADAPTIVEPT1_FLOAT64_FUNCTIONS { \
    ADAPTIVEPT1_FLOAT64_ID, \
    (void (*)(void*))AdaptivePT1_Float64_Update, \
    (void (*)(void*))AdaptivePT1_Float64_Init, \
    (tLoadImplementationParameter)AdaptivePT1_Float64_Load, \
    (tSaveImplementationParameter)AdaptivePT1_Float64_Save, \
    (void* (*)(const void*, uint16))AdaptivePT1_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void AdaptivePT1_Float64_Update(ADAPTIVEPT1_FLOAT64 *pTAdaptivePT1_Float64);
void AdaptivePT1_Float64_Init(ADAPTIVEPT1_FLOAT64 *pTAdaptivePT1_Float64);
uint8 AdaptivePT1_Float64_Load(const ADAPTIVEPT1_FLOAT64 *pTAdaptivePT1_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 AdaptivePT1_Float64_Save(ADAPTIVEPT1_FLOAT64 *pTAdaptivePT1_Float64, const uint8 data[], uint16 dataLength);
void* AdaptivePT1_Float64_GetAddress(const ADAPTIVEPT1_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
