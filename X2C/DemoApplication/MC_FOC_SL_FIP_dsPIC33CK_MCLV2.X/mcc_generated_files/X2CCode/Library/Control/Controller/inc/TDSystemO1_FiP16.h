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
#ifndef TDSYSTEMO1_FIP16_H
#define TDSYSTEMO1_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TDSYSTEMO1_FIP16_ISLINKED)
#define TDSYSTEMO1_FIP16_ID ((uint16)3345)

typedef struct {
    uint16          ID;
    int16           *In;
    int16           Out;
    int16           a11;
    int16           b11;
    int16           c11;
    int16           d11;
    uint8           sfra11;
    uint8           sfrb11;
    uint8           sfrc11;
    uint8           sfrd11;
    int16           x1;
} TDSYSTEMO1_FIP16;

#define TDSYSTEMO1_FIP16_FUNCTIONS { \
    TDSYSTEMO1_FIP16_ID, \
    (void (*)(void*))TDSystemO1_FiP16_Update, \
    (void (*)(void*))TDSystemO1_FiP16_Init, \
    (tLoadImplementationParameter)TDSystemO1_FiP16_Load, \
    (tSaveImplementationParameter)TDSystemO1_FiP16_Save, \
    (void* (*)(const void*, uint16))TDSystemO1_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TDSystemO1_FiP16_Update(TDSYSTEMO1_FIP16 *pTTDSystemO1_FiP16);
void TDSystemO1_FiP16_Init(TDSYSTEMO1_FIP16 *pTTDSystemO1_FiP16);
uint8 TDSystemO1_FiP16_Load(const TDSYSTEMO1_FIP16 *pTTDSystemO1_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TDSystemO1_FiP16_Save(TDSYSTEMO1_FIP16 *pTTDSystemO1_FiP16, const uint8 data[], uint16 dataLength);
void* TDSystemO1_FiP16_GetAddress(const TDSYSTEMO1_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
