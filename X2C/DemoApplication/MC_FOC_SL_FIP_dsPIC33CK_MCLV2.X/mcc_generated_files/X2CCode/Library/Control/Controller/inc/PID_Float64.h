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
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef PID_FLOAT64_H
#define PID_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(PID_FLOAT64_ISLINKED)
#define PID_FLOAT64_ID ((uint16)3252)

typedef struct {
    uint16          ID;
    float64         *In;
    float64         *Init;
    bool            *Enable;
    float64         Out;
    float64         b0;
    float64         b1;
    float64         b0d;
    float64         b1d;
    float64         a0d;
    float64         in_old;
    float64         i_old;
    float64         d_old;
    bool            enable_old;
} PID_FLOAT64;

#define PID_FLOAT64_FUNCTIONS { \
    PID_FLOAT64_ID, \
    (void (*)(void*))PID_Float64_Update, \
    (void (*)(void*))PID_Float64_Init, \
    (tLoadImplementationParameter)PID_Float64_Load, \
    (tSaveImplementationParameter)PID_Float64_Save, \
    (void* (*)(const void*, uint16))PID_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void PID_Float64_Update(PID_FLOAT64 *pTPID_Float64);
void PID_Float64_Init(PID_FLOAT64 *pTPID_Float64);
uint8 PID_Float64_Load(const PID_FLOAT64 *pTPID_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 PID_Float64_Save(PID_FLOAT64 *pTPID_Float64, const uint8 data[], uint16 dataLength);
void* PID_Float64_GetAddress(const PID_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
