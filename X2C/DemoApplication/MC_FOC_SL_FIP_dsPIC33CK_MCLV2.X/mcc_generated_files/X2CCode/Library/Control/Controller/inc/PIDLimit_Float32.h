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
#ifndef PIDLIMIT_FLOAT32_H
#define PIDLIMIT_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(PIDLIMIT_FLOAT32_ISLINKED)
#define PIDLIMIT_FLOAT32_ID ((uint16)3267)

typedef struct {
    uint16          ID;
    float32         *In;
    float32         *Init;
    float32         *max;
    float32         *min;
    bool            *Enable;
    float32         Out;
    float32         b0;
    float32         b1;
    float32         b0d;
    float32         b1d;
    float32         a0d;
    float32         in_old;
    float32         i_old;
    float32         d_old;
    bool            enable_old;
} PIDLIMIT_FLOAT32;

#define PIDLIMIT_FLOAT32_FUNCTIONS { \
    PIDLIMIT_FLOAT32_ID, \
    (void (*)(void*))PIDLimit_Float32_Update, \
    (void (*)(void*))PIDLimit_Float32_Init, \
    (tLoadImplementationParameter)PIDLimit_Float32_Load, \
    (tSaveImplementationParameter)PIDLimit_Float32_Save, \
    (void* (*)(const void*, uint16))PIDLimit_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void PIDLimit_Float32_Update(PIDLIMIT_FLOAT32 *pTPIDLimit_Float32);
void PIDLimit_Float32_Init(PIDLIMIT_FLOAT32 *pTPIDLimit_Float32);
uint8 PIDLimit_Float32_Load(const PIDLIMIT_FLOAT32 *pTPIDLimit_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 PIDLimit_Float32_Save(PIDLIMIT_FLOAT32 *pTPIDLimit_Float32, const uint8 data[], uint16 dataLength);
void* PIDLimit_Float32_GetAddress(const PIDLIMIT_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
