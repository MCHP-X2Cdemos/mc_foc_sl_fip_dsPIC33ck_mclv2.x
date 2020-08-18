/*
 * Copyright (c) 2018, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 1894 $
 * $LastChangedDate:: 2020-04-28 23:26:04 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Continuously differentiable output change rate limitation with	sin^2 shape                  **/
/**						Calculation:                               													 **/
/**							du/dt = 0:																				 **/
/**								y = u																				 **/
/**							du/dt <> 0:																				 **/
/**								y = u * sin^2(t)		(simplified)												 **/
/**																													 **/
/**		Caution:	A step in the input signal during a	running limitation process will not abort the running        **/
/**					limitation process!																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#ifndef SIN2LIMITER_FIP32_H
#define SIN2LIMITER_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FIP32_ISLINKED)
#define SIN2LIMITER_FIP32_ID ((uint16)114)

typedef struct {
    uint16          ID;
    int32           *In;
    int32           *Init;
    bool            *Enable;
    int32           Out;
    int32           RateUp;
    int32           RateDown;
    int32           Scaled_RateUp;
    int32           Scaled_RateDown;
    int32           Out_end;
    uint32          Level;
    int32           Step_Height;
    int8            State;
    bool            Enable_old;
} SIN2LIMITER_FIP32;

#define SIN2LIMITER_FIP32_FUNCTIONS { \
    SIN2LIMITER_FIP32_ID, \
    (void (*)(void*))Sin2Limiter_FiP32_Update, \
    (void (*)(void*))Sin2Limiter_FiP32_Init, \
    (tLoadImplementationParameter)Sin2Limiter_FiP32_Load, \
    (tSaveImplementationParameter)Sin2Limiter_FiP32_Save, \
    (void* (*)(const void*, uint16))Sin2Limiter_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP32_Update(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32);
void Sin2Limiter_FiP32_Init(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32);
uint8 Sin2Limiter_FiP32_Load(const SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Sin2Limiter_FiP32_Save(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32, const uint8 data[], uint16 dataLength);
void* Sin2Limiter_FiP32_GetAddress(const SIN2LIMITER_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
