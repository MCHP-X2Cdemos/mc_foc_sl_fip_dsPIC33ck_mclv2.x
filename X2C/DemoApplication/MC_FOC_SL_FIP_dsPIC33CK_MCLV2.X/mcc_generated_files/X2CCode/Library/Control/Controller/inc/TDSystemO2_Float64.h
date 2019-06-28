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
#ifndef TDSYSTEMO2_FLOAT64_H
#define TDSYSTEMO2_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TDSYSTEMO2_FLOAT64_ISLINKED)
#define TDSYSTEMO2_FLOAT64_ID ((uint16)3364)

typedef struct {
    uint16          ID;
    float64         *In1;
    float64         *In2;
    float64         Out1;
    float64         Out2;
    float64         a11;
    float64         a12;
    float64         a21;
    float64         a22;
    float64         b11;
    float64         b12;
    float64         b21;
    float64         b22;
    float64         x1;
    float64         x2;
} TDSYSTEMO2_FLOAT64;

#define TDSYSTEMO2_FLOAT64_FUNCTIONS { \
    TDSYSTEMO2_FLOAT64_ID, \
    (void (*)(void*))TDSystemO2_Float64_Update, \
    (void (*)(void*))TDSystemO2_Float64_Init, \
    (tLoadImplementationParameter)TDSystemO2_Float64_Load, \
    (tSaveImplementationParameter)TDSystemO2_Float64_Save, \
    (void* (*)(const void*, uint16))TDSystemO2_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TDSystemO2_Float64_Update(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64);
void TDSystemO2_Float64_Init(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64);
uint8 TDSystemO2_Float64_Load(const TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TDSystemO2_Float64_Save(TDSYSTEMO2_FLOAT64 *pTTDSystemO2_Float64, const uint8 data[], uint16 dataLength);
void* TDSystemO2_Float64_GetAddress(const TDSYSTEMO2_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
