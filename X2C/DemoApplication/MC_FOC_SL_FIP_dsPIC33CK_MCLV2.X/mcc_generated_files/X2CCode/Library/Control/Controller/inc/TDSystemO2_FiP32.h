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
#ifndef TDSYSTEMO2_FIP32_H
#define TDSYSTEMO2_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TDSYSTEMO2_FIP32_ISLINKED)
#define TDSYSTEMO2_FIP32_ID ((uint16)3362)

typedef struct {
    uint16          ID;
    int32           *In1;
    int32           *In2;
    int32           Out1;
    int32           Out2;
    int32           a11;
    int32           a12;
    int32           a21;
    int32           a22;
    int32           b11;
    int32           b12;
    int32           b21;
    int32           b22;
    uint8           sfra11;
    uint8           sfra12;
    uint8           sfra21;
    uint8           sfra22;
    uint8           sfrb11;
    uint8           sfrb12;
    uint8           sfrb21;
    uint8           sfrb22;
    int32           x1;
    int32           x2;
} TDSYSTEMO2_FIP32;

#define TDSYSTEMO2_FIP32_FUNCTIONS { \
    TDSYSTEMO2_FIP32_ID, \
    (void (*)(void*))TDSystemO2_FiP32_Update, \
    (void (*)(void*))TDSystemO2_FiP32_Init, \
    (tLoadImplementationParameter)TDSystemO2_FiP32_Load, \
    (tSaveImplementationParameter)TDSystemO2_FiP32_Save, \
    (void* (*)(const void*, uint16))TDSystemO2_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TDSystemO2_FiP32_Update(TDSYSTEMO2_FIP32 *pTTDSystemO2_FiP32);
void TDSystemO2_FiP32_Init(TDSYSTEMO2_FIP32 *pTTDSystemO2_FiP32);
uint8 TDSystemO2_FiP32_Load(const TDSYSTEMO2_FIP32 *pTTDSystemO2_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TDSystemO2_FiP32_Save(TDSYSTEMO2_FIP32 *pTTDSystemO2_FiP32, const uint8 data[], uint16 dataLength);
void* TDSystemO2_FiP32_GetAddress(const TDSYSTEMO2_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
